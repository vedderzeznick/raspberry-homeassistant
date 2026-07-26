#include <stdio.h>

#include "../include/gpio.h"

#define DHT 6

int main(void)
{
    gpio_init();

    gpio_claim_output(DHT);

    gpio_write(DHT,0);

    delay_ms(18);

    gpio_claim_input(DHT);

    if(gpio_wait_level(DHT,0,200)==0)
        printf("Sensor responde (LOW)\n");
    else
    {
        printf("No hubo respuesta LOW\n");
        return 1;
    }

    if(gpio_wait_level(DHT,1,200)==0)
        printf("Sensor responde (HIGH)\n");
    else
    {
        printf("No hubo respuesta HIGH\n");
        return 1;
    }

    printf("Handshake correcto\n");

    gpio_close();

    return 0;
}
