#include "../include/dht22.h"

#include <stdio.h>

#define TEMP_FILE "/sys/bus/iio/devices/iio:device0/in_temp_input"
#define HUM_FILE  "/sys/bus/iio/devices/iio:device0/in_humidityrelative_input"

int dht22_init(int gpio)
{
    (void)gpio;
    return 0;
}

static int read_value(const char *file, float *value)
{
    FILE *fp;
    int raw;

    fp = fopen(file, "r");

    if(fp == NULL)
        return -1;

    if(fscanf(fp, "%d", &raw) != 1)
    {
        fclose(fp);
        return -1;
    }

    fclose(fp);

    *value = raw / 1000.0f;

    return 0;
}

int dht22_read(float *temperature, float *humidity)
{
    if(read_value(TEMP_FILE, temperature) != 0)
        return -1;

    if(read_value(HUM_FILE, humidity) != 0)
        return -1;

    return 0;
}
