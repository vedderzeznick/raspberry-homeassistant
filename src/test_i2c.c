#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define LCD_ADDR 0x27

int main()
{
    int fd;

    fd = open("/dev/i2c-1", O_RDWR);

    if(fd < 0)
    {
        perror("No puedo abrir I2C");
        return 1;
    }

    if(ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0)
    {
        perror("No puedo acceder al LCD");
        return 1;
    }

    unsigned char b = 0x00;

    if(write(fd, &b, 1) != 1)
    {
        perror("Error escribiendo");
        return 1;
    }

    printf("LCD encontrado correctamente\n");

    close(fd);

    return 0;
}
