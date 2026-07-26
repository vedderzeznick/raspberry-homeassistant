#ifndef MQTT_H
#define MQTT_H

int mqtt_init(void);

void mqtt_cleanup(void);

/* Función genérica */
int mqtt_publish_string(const char *topic, const char *payload);

/* Funciones auxiliares */
int mqtt_publish_int(const char *topic, int value);

int mqtt_publish_float(const char *topic, float value, int decimals);

void mqtt_loop(void);

int mqtt_lcd_display_enabled(void);

void mqtt_discovery(void);

#endif
