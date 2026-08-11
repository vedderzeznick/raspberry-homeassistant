#include "../include/ir.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <lgpio.h>

static int gpio_handle = -1;
static int gpio_ir = -1;

int ir_init(int gpio)
{
    gpio_ir = gpio;

    gpio_handle = lgGpiochipOpen(0);

    if (gpio_handle < 0)
    {
        printf("IR: error abriendo GPIO chip\n");
        return -1;
    }

    if (lgGpioClaimInput(gpio_handle, 0, gpio_ir) < 0)
    {
        printf("IR: error reclamando GPIO %d\n", gpio_ir);
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
    {
        return -1;
    }

    memset(code, 0, sizeof(ir_code_t));

    printf("IR: esperando señal...\n");

    return 0;
}

void ir_print(const ir_code_t *code)
{
    if (code == NULL)
    {
        return;
    }

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
}