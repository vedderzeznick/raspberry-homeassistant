#include <stdio.h>
#include <gpiod.h>

int main()
{
    struct gpiod_chip *chip;

    chip = gpiod_chip_open("/dev/gpiochip0");

    if(!chip)
    {
        printf("No puedo abrir gpiochip0\n");
        return 1;
    }

    printf("GPIO abierto correctamente\n");

    gpiod_chip_close(chip);

    return 0;
}

