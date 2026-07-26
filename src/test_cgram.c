#include <unistd.h>
#include <stdint.h>

#include "../include/lcd.h"

static const uint8_t chardino1[8]={
    0b00000,
    0b00000,
    0b00000,
    0b10000,
    0b10000,
    0b10000,
    0b11000,
    0b11100
};

static const uint8_t chardino2[8]={
    0b00000,
    0b00001,
    0b00001,
    0b00001,
    0b00011,
    0b01111,
    0b01111,
    0b11111
};

static const uint8_t chardino3[8]={
    0b11111,
    0b10111,
    0b11111,
    0b11111,
    0b11100,
    0b11111,
    0b11100,
    0b11100
};

static const uint8_t chardino4[8]={
0b10000,
0b11000,
0b11000,
0b11000,
0b00000,
0b10000,
0b00000,
0b00000
};

static const uint8_t chardino5[8]={
0b11111,
0b11111,
0b01111,
0b00111,
0b00011,
0b00011,
0b00010,
0b00011
};

static const uint8_t chardino6[8]={
0b11111,
0b11111,
0b11111,
0b11111,
0b10110,
0b00010,
0b00010,
0b00011
};

static const uint8_t chardino7[8]={
0b11111,
0b11001,
0b10000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000
};

int main()
{
    lcd_init();

    lcd_create_char(0,chardino1);
    lcd_create_char(1,chardino2);
    lcd_create_char(2,chardino3);
    lcd_create_char(3,chardino4);
    lcd_create_char(4,chardino5);
    lcd_create_char(5,chardino6);
    lcd_create_char(6,chardino7);

    lcd_clear();

    lcd_set_cursor(0,0);
    lcd_write_char(0);
    lcd_write_char(1);
    lcd_write_char(2);
    lcd_write_char(3);

    lcd_set_cursor(1,0);
    lcd_write_char(4);
    lcd_write_char(5);
    lcd_write_char(6);

    while(1)
        sleep(1);
}
