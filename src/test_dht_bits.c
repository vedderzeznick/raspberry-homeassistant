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

    if(gpio_wait_level(DHT,0,200)!=0)
    {
        printf("No responde\n");
        return 1;
    }

    gpio_wait_level(DHT,1,200);

    gpio_wait_level(DHT,0,200);

    printf("Primeros 8 pulsos HIGH:\n\n");

    for(int i=0;i<8;i++)
    {
        gpio_wait_level(DHT,1,200);

        long t=gpio_pulse_high_us(DHT,120);

        printf("%2d -> %ld us\n",i,t);

        gpio_wait_level(DHT,0,200);
    }

    gpio_close();
}
