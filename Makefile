CC = gcc

CFLAGS = -Wall -O2 -Iinclude $(shell pkg-config --cflags dbus-1)

LDFLAGS = -llgpio -lmosquitto -lbluetooth $(shell pkg-config --libs dbus-1)

SRC = src/main.c \
      src/lcd.c \
      src/gpio.c \
      src/dht22.c \
      src/animacion.c \
      src/divoom.c \
      src/ir.c \
      src/mqtt.c

TARGET = temperatura

all:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)