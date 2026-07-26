#include "../include/gpio.h"

#include <lgpio.h>
#include <unistd.h>

static int chip = -1;

int gpio_init(void)
{
    chip = lgGpiochipOpen(0);

    return chip;
}

void gpio_close(void)
{
    if(chip >= 0)
        lgGpiochipClose(chip);
}

int gpio_claim_input(int gpio)
{
    return lgGpioClaimInput(chip, 0, gpio);
}

int gpio_claim_output(int gpio)
{
    return lgGpioClaimOutput(chip, 0, gpio, 0);
}

int gpio_read(int gpio)
{
    return lgGpioRead(chip, gpio);
}

void gpio_write(int gpio, int value)
{
    lgGpioWrite(chip, gpio, value);
}

void delay_us(uint32_t us)
{
    usleep(us);
}

void delay_ms(uint32_t ms)
{
    usleep(ms * 1000);
}

#include <time.h>

int gpio_wait_level(int gpio, int level, int timeout_us)
{
    struct timespec start, now;

    clock_gettime(CLOCK_MONOTONIC, &start);

    while (1)
    {
        if (gpio_read(gpio) == level)
            return 0;

        clock_gettime(CLOCK_MONOTONIC, &now);

        long elapsed =
            (now.tv_sec - start.tv_sec) * 1000000L +
            (now.tv_nsec - start.tv_nsec) / 1000L;

        if (elapsed > timeout_us)
            return -1;
    }
}

long gpio_pulse_high_us(int gpio, int timeout_us)
{
    struct timespec start;
    struct timespec now;

    if(gpio_wait_level(gpio,1,timeout_us)!=0)
        return -1;

    clock_gettime(CLOCK_MONOTONIC_RAW,&start);

    while(gpio_read(gpio)==1)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW,&now);

        long elapsed =
            (now.tv_sec-start.tv_sec)*1000000L+
            (now.tv_nsec-start.tv_nsec)/1000L;

        if(elapsed>timeout_us)
            return timeout_us;
    }

    clock_gettime(CLOCK_MONOTONIC_RAW,&now);

    return
        (now.tv_sec-start.tv_sec)*1000000L+
        (now.tv_nsec-start.tv_nsec)/1000L;
}

