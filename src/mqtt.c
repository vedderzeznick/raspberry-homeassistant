#include <stdio.h>
#include <string.h>
#include <mosquitto.h>

#include "../include/mqtt.h"
#include "../include/lcd.h"

static struct mosquitto *mosq = NULL;
static int lcd_display_enabled = 1;

static void on_message(struct mosquitto *mosq,
                       void *userdata,
                       const struct mosquitto_message *msg)
{
    printf("Topic: %s\n", msg->topic);
    printf("Payload: %.*s\n",
           msg->payloadlen,
           (char *)msg->payload);
   if (strcmp(msg->topic, "home/livingroom/lcd/display/set") == 0)
{
    if (strncmp((char *)msg->payload, "ON", msg->payloadlen) == 0)
    {
        lcd_display_enabled = 1;
        lcd_display_on();

        printf("LCD ON\n");
    }
    else if (strncmp((char *)msg->payload, "OFF", msg->payloadlen) == 0)
    {
        lcd_display_enabled = 0;
        lcd_display_off();

        printf("LCD OFF\n");
    }
}

}

int mqtt_init(void)
{
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    
    if (mosq == NULL)
    {
        return -1;
    }

    mosquitto_message_callback_set(mosq, on_message);

    if (mosquitto_connect(mosq, "localhost", 1883, 60) != MOSQ_ERR_SUCCESS)
    {
        return -1;
    }

    mosquitto_subscribe(
     mosq,
     NULL,
     "home/livingroom/lcd/display/set",
     0
    );

    return 0;
}

int mqtt_publish_string(const char *topic, const char *payload)
{
    if (mosq == NULL)
    {
        return -1;
    }

    return mosquitto_publish(
        mosq,
        NULL,
        topic,
        strlen(payload),
        payload,
        0,
        false
    );
}

int mqtt_publish_int(const char *topic, int value)
{
    char payload[16];

    snprintf(payload, sizeof(payload), "%d", value);

    return mqtt_publish_string(topic, payload);
}

int mqtt_publish_float(const char *topic, float value, int decimals)
{
    char payload[16];
    char format[8];

    snprintf(format, sizeof(format), "%%.%df", decimals);
    snprintf(payload, sizeof(payload), format, value);

    return mqtt_publish_string(topic, payload);
}

void mqtt_loop(void)
{
    if (mosq != NULL)
    {
        mosquitto_loop(mosq, 0, 1);
    }
}

void mqtt_discovery(void)
{
    mqtt_publish_string(
        "homeassistant/sensor/livingroom_temperature/config",
        "{"
        "\"name\":\"Temperatura Salon\","
        "\"unique_id\":\"livingroom_temperature\","
        "\"state_topic\":\"home/livingroom/temperature\","
        "\"unit_of_measurement\":\"°C\","
        "\"device_class\":\"temperature\","
        "\"state_class\":\"measurement\","
        "\"device\":{"
            "\"identifiers\":[\"raspberry_pi_ambiental\"],"
            "\"name\":\"Raspberry Pi Ambiental\","
            "\"manufacturer\":\"Martin\","
            "\"model\":\"Raspberry Pi 5\""
        "}"
        "}"
    );

    mqtt_publish_string(
        "homeassistant/sensor/livingroom_humidity/config",
        "{"
        "\"name\":\"Humedad Salon\","
        "\"unique_id\":\"livingroom_humidity\","
        "\"state_topic\":\"home/livingroom/humidity\","
        "\"unit_of_measurement\":\"%\","
        "\"device_class\":\"humidity\","
        "\"state_class\":\"measurement\","
        "\"device\":{"
            "\"identifiers\":[\"raspberry_pi_ambiental\"],"
            "\"name\":\"Raspberry Pi Ambiental\","
            "\"manufacturer\":\"Martin\","
            "\"model\":\"Raspberry Pi 5\""
        "}"
        "}"
    );
}

void mqtt_cleanup(void)
{
    if (mosq != NULL)
    {
        mosquitto_disconnect(mosq);
        mosquitto_destroy(mosq);
    }

    mosquitto_lib_cleanup();
}

int mqtt_lcd_display_enabled(void)
{
    return lcd_display_enabled;
}
