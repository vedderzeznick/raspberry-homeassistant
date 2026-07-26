#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "../include/lcd.h"

#define LCD_ADDR 0x27

#define ENABLE 0x04
#define RS 0x01
#define LCD_BACKLIGHT 0x08

static int fd;

static void expanderWrite(uint8_t data)
{
    write(fd, &data, 1);
}

static void pulseEnable(uint8_t data)
{
    expanderWrite(data | ENABLE);
    usleep(1);

    expanderWrite(data & ~ENABLE);
    usleep(50);
}

static void write4bits(uint8_t value)
{
    expanderWrite(value);
    pulseEnable(value);
}

void lcd_command(uint8_t cmd)
{
    write4bits((cmd & 0xF0) | LCD_BACKLIGHT);
    write4bits(((cmd << 4) & 0xF0) | LCD_BACKLIGHT);
}

void lcd_data(uint8_t value)
{
    write4bits((value & 0xF0) | LCD_BACKLIGHT | RS);
    write4bits(((value << 4) & 0xF0) | LCD_BACKLIGHT | RS);
}

int lcd_init()
{
    fd = open("/dev/i2c-1", O_RDWR);

    if(fd < 0)
        return -1;

    if(ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0)
        return -1;

    usleep(50000);

    write4bits(0x30);
    usleep(4500);

    write4bits(0x30);
    usleep(4500);

    write4bits(0x30);
    usleep(150);

    write4bits(0x20);

    lcd_command(0x28);
    lcd_command(0x08);
    lcd_command(0x01);
    usleep(2000);

    lcd_command(0x06);
    lcd_command(0x0C);

    return 0;
}

void lcd_clear()
{
    lcd_command(0x01);
    usleep(2000);
}

void lcd_home()
{
    lcd_command(0x02);
    usleep(2000);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    static uint8_t offsets[] =
    {
        0x00,
        0x40,
        0x14,
        0x54
    };

    lcd_command(0x80 | (col + offsets[row]));
}

void lcd_print(const char *text)
{
    while(*text)
    {
        lcd_data(*text++);
    }
}

void lcd_backlight(int on)
{
    if (on)
        expanderWrite(LCD_BACKLIGHT);
    else
        expanderWrite(0);
}

void lcd_write_char(uint8_t value)
{
    lcd_data(value);
}

void lcd_create_char(uint8_t location, const uint8_t bitmap[8])
{
    location &= 0x07;

    /* Seleccionar CGRAM */
    lcd_command(0x40 | (location << 3));
    usleep(50);

    for(int i = 0; i < 8; i++)
    {
        lcd_data(bitmap[i]);
        usleep(50);
    }

    /* Volver a DDRAM */
    lcd_command(0x80);
    usleep(50);
}

void lcd_display_on(void)
{
    lcd_command(0x0C);
    expanderWrite(LCD_BACKLIGHT);
}

void lcd_display_off(void)
{
    lcd_command(0x08);
    expanderWrite(0x00);
}
