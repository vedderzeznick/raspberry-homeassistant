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
    DBusError err;

    memset(&divoom, 0, sizeof(divoom));

    dbus_error_init(&err);

    divoom.conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);

    if (dbus_error_is_set(&err))
    {
        printf("DBus error: %s\n", err.message);
        dbus_error_free(&err);
        return -1;
    }

    if (divoom.conn == NULL)
    {
        printf("Cannot connect to system bus\n");
        return -1;
    }

    strncpy(divoom.device,
            device_path,
            sizeof(divoom.device)-1);

    strcpy(divoom.write_char,
           "/org/bluez/hci0/dev_B1_21_81_3F_84_7C/service0006/char000c");

    printf("Connected to DBus\n");
    printf("Device : %s\n", divoom.device);
    printf("Write  : %s\n", divoom.write_char);

    return 0;
}

void divoom_close(void)
{
}