#include <unistd.h>
#include <stdint.h>
#include "../include/mqtt.h"
#include "../include/lcd.h"

#define TIEMPO 400000     // microsegundos (400 ms)

// guitar bit map
static const uint8_t guitar0[8] = {
    0b00000,
    0b00000,
    0b00001,
    0b00011,
    0b00111,
    0b01111,
    0b01111,
    0b11110
};

static const uint8_t guitar1[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b10000,
    0b11000,
    0b11111,
    0b00111,
    0b01010
};

static const uint8_t guitar2[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11000,
    0b11100,
    0b10000,
    0b11111
};

static const uint8_t guitar3[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00101,
    0b11111
};

static const uint8_t guitar4[8] = {
    0b11110,
    0b11110,
    0b01110,
    0b01110,
    0b00100,
    0b00110,
    0b00011,
    0b00000
};

static const uint8_t guitar5[8] = {
    0b01010,
    0b01010,
    0b00000,
    0b10000,
    0b00111,
    0b01101,
    0b11000,
    0b00000
};

static const uint8_t guitar6[8] = {
    0b11111,
    0b10000,
    0b10000,
    0b11000,
    0b01000,
    0b11000,
    0b00000,
    0b00000
};

static const uint8_t guitar7[8] = {
    0b11111,
    0b00101,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};


//dino bit map
static const uint8_t chardino1[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b10000,
    0b10000,
    0b10000,
    0b11000,
    0b11100
};

static const uint8_t chardino2[8] = {
    0b00000,
    0b00001,
    0b00001,
    0b00001,
    0b00011,
    0b01111,
    0b01111,
    0b11111
};

static const uint8_t chardino3[8] = {
    0b11111,
    0b10111,
    0b11111,
    0b11111,
    0b11100,
    0b11111,
    0b11100,
    0b11100
};

static const uint8_t chardino4[8] = {
    0b10000,
    0b11000,
    0b11000,
    0b11000,
    0b00000,
    0b10000,
    0b00000,
    0b00000
};

static const uint8_t chardino5[8] = {
    0b11111,
    0b11111,
    0b01111,
    0b00111,
    0b00011,
    0b00011,
    0b00010,
    0b00011
};

static const uint8_t chardino6[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b10110,
    0b00010,
    0b00010,
    0b00011
};

static const uint8_t chardino7[8] = {
    0b11111,
    0b11001,
    0b10000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};
void animacion_dino(void)
{
    if (!mqtt_lcd_display_enabled()) 
	return;

    lcd_create_char(1,chardino1);
    lcd_create_char(2,chardino2);
    lcd_create_char(3,chardino3);
    lcd_create_char(4,chardino4);
    lcd_create_char(5,chardino5);
    lcd_create_char(6,chardino6);
    lcd_create_char(7,chardino7);

    lcd_clear();

    for(int a=0;a<=18;a++)
    {
        if(a>=3)
        {
            lcd_set_cursor(0,a-3);
            lcd_write_char(1);
        }

        if(a>=2)
        {
            lcd_set_cursor(0,a-2);
            lcd_write_char(2);
        }

        if(a>=1)
        {
            lcd_set_cursor(0,a-1);
            lcd_write_char(3);
        }

        if(a<16)
        {
            lcd_set_cursor(0,a);
            lcd_write_char(4);
        }

        if(a>=3)
        {
            lcd_set_cursor(1,a-3);
            lcd_write_char(5);
        }

        if(a>=2)
        {
            lcd_set_cursor(1,a-2);
            lcd_write_char(6);
        }

        if(a>=1)
        {
            lcd_set_cursor(1,a-1);
            lcd_write_char(7);
        }

        usleep(TIEMPO);

        lcd_clear();
    }
}

void pantalla_gato(void)
{
    if (!mqtt_lcd_display_enabled())
        return;

    lcd_create_char(0, guitar0);
    lcd_create_char(1, guitar1);
    lcd_create_char(2, guitar2);
    lcd_create_char(3, guitar3);
    lcd_create_char(4, guitar4);
    lcd_create_char(5, guitar5);
    lcd_create_char(6, guitar6);
    lcd_create_char(7, guitar7);

    lcd_clear();

    lcd_set_cursor(0,0);
    lcd_write_char(0);
    lcd_write_char(1);
    lcd_write_char(2);
    lcd_write_char(3);
    lcd_write_char(4);
    lcd_write_char(5);
    lcd_write_char(6);
    lcd_write_char(7);

    lcd_set_cursor(1,0);

    lcd_set_cursor(0,9);
    lcd_print("LIL'S");

    lcd_set_cursor(1,9);
    lcd_print("HOME");

    sleep(10);
}

