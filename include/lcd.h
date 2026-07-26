#ifndef LCD_H
#define LCD_H

#include <stdint.h>

int lcd_init(void);
void lcd_clear(void);
void lcd_home(void);

void lcd_set_cursor(uint8_t row, uint8_t col);

void lcd_print(const char *text);

void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);

void lcd_backlight(int on);

void lcd_create_char(uint8_t location, const uint8_t bitmap[8]);
void lcd_write_char(uint8_t value);
void lcd_display_on(void);
void lcd_display_off(void);

#endif
