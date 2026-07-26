#include <stdio.h>
#include <unistd.h>

#include "../include/gpio.h"

#define DHT_GPIO 6

int main(void)
{
    if (gpio_init() < 0)
    {
        printf("Error inicializando GPIO\n");
        return 1;
    }

    /* Reclamar como salida */
    gpio_claim_output(DHT_GPIO);

    printf("GPIO6 LOW durante 18 ms...\n");

    gpio_write(DHT_GPIO, 0);
    delay_ms(18);

    printf("Pasando a entrada...\n");

    gpio_claim_input(DHT_GPIO);

    printf("Nivel actual: %d\n", gpio_read(DHT_GPIO));

    gpio_close();

    return 0;
}
