#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../include/lcd.h"
#include "../include/gpio.h"
#include "../include/dht22.h"
#include "../include/animacion.h"
#include "../include/mqtt.h"
#include "../include/divoom.h"
#include "../include/ir.h"

int main(void)
{
    float temp;
    float hum;
    char linea[17];

    time_t ahora;
    time_t ultima_animacion;
    struct tm *tm_info;
    static int siguiente_animacion = 0;
    ir_code_t code;

    printf("Inicializando receptor IR...\n");

    if (ir_init(18) != 0)
    {
        printf("Error inicializando receptor IR\n");
        return 1;
    }

    printf("Receptor IR listo en GPIO18\n");

    int result = ir_capture(&code);

    printf("Resultado captura: %d\n", result);

    ir_print(&code);

    ir_close();
    
    if (lcd_init() != 0)
    {
        printf("Error inicializando LCD\n");
        return 1;
    }

    animacion_dino();

    if (gpio_init() < 0)
    {
        printf("Error inicializando GPIO\n");
        return 1;
    }

    dht22_init(6);

    if (mqtt_init() != 0)
    {
        printf("Error conectando con MQTT\n");
        return 1;
    }

    mqtt_discovery();

    //divoom_init("B1:21:81:3F:84:7C");

    //uint8_t test[]={0x00};

    //divoom_write(test,1);

    ultima_animacion = time(NULL);

    animacion_dino();

    while (1)
    {
        mqtt_loop();
        ahora = time(NULL);

        if (mqtt_lcd_display_enabled() &&
        (ahora - ultima_animacion) >= 30)
        {
            if (siguiente_animacion == 0)
            {
                animacion_dino();
                siguiente_animacion = 1;
            }
            else
            {
                pantalla_gato();
                siguiente_animacion = 0;
            }

            ultima_animacion = time(NULL);
        }

        if (dht22_read(&temp, &hum) == 0)
        {
            mqtt_publish_float(
                "home/livingroom/temperature",
                temp,
                1
            );

            mqtt_publish_float(
                "home/livingroom/humidity",
                hum,
                0
            );
            if (mqtt_lcd_display_enabled() && dht22_read(&temp, &hum) == 0) 
            {
                tm_info = localtime(&ahora);

                lcd_clear();

                snprintf(
                    linea,
                    sizeof(linea),
                    "%.1f%cC   %.0f%%RH",
                    temp,
                    0xDF,
                    hum
                );

                lcd_set_cursor(0,0);
                lcd_print(linea);

                strftime(
                    linea,
                    sizeof(linea),
                    "%H:%M",
                    tm_info
                );

                lcd_set_cursor(1,0);
                lcd_print(linea);
            }
        }

        sleep(1);
    }
    mqtt_cleanup();
    gpio_close();

    return 0;
}
