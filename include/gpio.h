#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

int gpio_init(void);
void gpio_close(void);

int gpio_claim_input(int gpio);
int gpio_claim_output(int gpio);

int gpio_read(int gpio);
void gpio_write(int gpio, int value);

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
int gpio_wait_level(int gpio, int level, int timeout_us);
long gpio_pulse_high_us(int gpio, int timeout_us);

#endif
