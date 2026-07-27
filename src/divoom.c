#include "../include/divoom.h"

#include <stdio.h>
#include <string.h>
#include <dbus/dbus.h>

typedef struct
{
    DBusConnection *conn;

    char device[128];

    char write_char[128];

} divoom_t;

static divoom_t divoom;

int divoom_init(const char *device_path)
{
    memset(&divoom, 0, sizeof(divoom));

    strncpy(divoom.device,
            device_path,
            sizeof(divoom.device)-1);

    strcpy(divoom.write_char,
           "/org/bluez/hci0/dev_B1_21_81_3F_84_7C/service0006/char000c");

    printf("Divoom device : %s\n", divoom.device);
    printf("Write char    : %s\n", divoom.write_char);

    return 0;
}

void divoom_close(void)
{
}