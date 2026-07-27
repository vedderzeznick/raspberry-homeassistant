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

int divoom_write(const uint8_t *data, int len)
{
    DBusMessage *msg;
    DBusMessage *reply;
    DBusMessageIter iter;
    DBusMessageIter array;
    DBusMessageIter dict;

    DBusError err;

    dbus_error_init(&err);

    msg = dbus_message_new_method_call(
            "org.bluez",
            divoom.write_char,
            "org.bluez.GattCharacteristic1",
            "WriteValue");

    if (!msg)
    {
        printf("Cannot create DBus message\n");
        return -1;
    }

    dbus_message_iter_init_append(msg, &iter);

    dbus_message_iter_open_container(&iter,
                                     DBUS_TYPE_ARRAY,
                                     "y",
                                     &array);

    for(int i=0;i<len;i++)
    {
        uint8_t b = data[i];

        dbus_message_iter_append_basic(
                &array,
                DBUS_TYPE_BYTE,
                &b);
    }

    dbus_message_iter_close_container(&iter,&array);

    /* opciones = {} */

    dbus_message_iter_open_container(
            &iter,
            DBUS_TYPE_ARRAY,
            "{sv}",
            &dict);

    dbus_message_iter_close_container(
            &iter,
            &dict);

    reply = dbus_connection_send_with_reply_and_block(
            divoom.conn,
            msg,
            3000,
            &err);

    dbus_message_unref(msg);

    if(dbus_error_is_set(&err))
    {
        printf("Write error: %s\n",err.message);
        dbus_error_free(&err);
        return -1;
    }

    if(reply)
        dbus_message_unref(reply);

    printf("Write OK\n");

    return 0;
}

void divoom_close(void)
{
}