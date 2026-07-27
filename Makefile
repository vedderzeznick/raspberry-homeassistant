CC = gcc

CFLAGS = -Wall -O2 -Iinclude

LDFLAGS = -llgpio -lmosquitto -lbluetooth -ldbus-1

SRC=src/main.c \
    src/lcd.c \
    src/gpio.c \
    src/dht22.c \
    src/animacion.c \
    src/divoom.c \
    src/mqtt.c

TARGET = temperatura

all:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
