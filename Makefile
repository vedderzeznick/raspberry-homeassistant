CC = gcc

CFLAGS = -Wall -O2 -Iinclude

LDFLAGS = -llgpio -lmosquitto

SRC=src/main.c \
    src/lcd.c \
    src/gpio.c \
    src/dht22.c \
    src/animacion.c \
    src/mqtt.c

TARGET = temperatura

all:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
