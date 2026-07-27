#ifndef DIVOOM_H
#define DIVOOM_H

#include <stdint.h>

int divoom_init(const char *device_path);
void divoom_close(void);

int divoom_write(const uint8_t *data, int len);

#endif