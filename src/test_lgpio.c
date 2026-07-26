#include <stdio.h>
#include <lgpio.h>

int main(void)
{
    int h;

    h = lgGpiochipOpen(0);

    if (h < 0)
    {
        printf("Error abriendo gpiochip0\n");
        return 1;
    }

    printf("lgpio funcionando correctamente\n");

    lgGpiochipClose(h);

    return 0;
}
