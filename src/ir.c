#include "../include/ir.h"

#include <stdio.h>
#include <string.h>
#include <lgpio.h>

static int gpio_handle = -1;
static int gpio_ir = -1;

static ir_code_t *capture_code = NULL;
static uint64_t last_tick = 0;

static void ir_alert(
    int num_alerts,
    lgGpioAlert_p alerts,
    void *userdata)
{
    (void)userdata;

    if (capture_code == NULL)
        return;

    for (int i = 0; i < num_alerts; i++)
    {
        lgGpioAlert_t *alert = &alerts[i];

        if (alert->report.gpio != gpio_ir)
            continue;

        if (last_tick == 0)
        {
            last_tick = alert->report.timestamp;
            continue;
        }

        uint64_t timestamp = alert->report.timestamp;

        uint64_t duration_ns =
            timestamp - last_tick;

        uint32_t duration_us =
            (uint32_t)(duration_ns / 1000);

        last_tick = timestamp;

        if (capture_code->count >= IR_MAX_PULSES)
            continue;

        capture_code->pulses[capture_code->count].duration_us =
            duration_us;

        capture_code->pulses[capture_code->count].level =
            alert->report.level;

        capture_code->count++;
    }
}

int ir_init(int gpio)
{
    gpio_ir = gpio;

    gpio_handle = lgGpiochipOpen(0);

    if (gpio_handle < 0)
    {
        printf("IR: error abriendo GPIO chip\n");
        return -1;
    }

    if (lgGpioClaimAlert(
            gpio_handle,
            0,
            LG_BOTH_EDGES,
            gpio_ir,
            -1) < 0)
    {
        printf("IR: error configurando GPIO %d\n", gpio_ir);

        lgGpiochipClose(gpio_handle);
        gpio_handle = -1;

        return -1;
    }

    if (lgGpioSetAlertsFunc(
            gpio_handle,
            gpio_ir,
            ir_alert,
            NULL) < 0)
    {
        printf("IR: error configurando callback\n");

        lgGpiochipClose(gpio_handle);
        gpio_handle = -1;

        return -1;
    }

    printf("IR: receptor preparado en GPIO %d\n", gpio_ir);

    return 0;
}

int ir_capture(ir_code_t *code)
{
    if (gpio_handle < 0 || code == NULL)
        return -1;

    memset(code, 0, sizeof(ir_code_t));

    capture_code = code;
    last_tick = 0;

    printf("IR: esperando señal durante 10 segundos...\n");

    lguSleep(10.0);

    capture_code = NULL;

    printf("IR: captura terminada\n");

    return code->count;
}

void ir_print(const ir_code_t *code)
{
    if (code == NULL)
        return;

    printf("\n--- IR CODE ---\n");

    for (int i = 0; i < code->count; i++)
    {
        printf("%3d: %s %u us\n",
               i,
               code->pulses[i].level ? "HIGH" : "LOW",
               code->pulses[i].duration_us);
    }

    printf("Pulsos: %d\n", code->count);
    printf("----------------\n");
}

void ir_close(void)
{
    if (gpio_handle >= 0)
    {
        lgGpiochipClose(gpio_handle);
        gpio_handle = -1;
    }

    gpio_ir = -1;
    capture_code = NULL;
}