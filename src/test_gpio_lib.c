#include <stdio.h>

#include "../include/gpio.h"

#define DHT_PIN 6

int main(void)
{
    if(gpio_init() < 0)
    {
        printf("Error inicializando lgpio\n");
        return 1;
    }

    if(gpio_claim_input(DHT_PIN) < 0)
    {
        printf("No puedo reclamar GPIO6\n");
        return 1;
    }

    printf("GPIO6 = %d\n", gpio_read(DHT_PIN));

    gpio_close();

    return 0;
}
