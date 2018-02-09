#include <stdio.h>
#include <stdlib.h>
#include "lcd_gdi.h"

int main()
{
    int i = 0, j = 0;
    gdi_setup();

    for(i = 0; i < 26; i++)
    {
        gdi_putch_5x7(j * 5, 0, i + 'a', 0, 1);
        gdi_putch_5x7(j * 5, 10, i + 'A', 0, 1);
        printf("%c-%c-%d\n", i + 'a', i + 'A', j);
        j++;

        if((j >= 15) || ((i >= 15) && (j == 11)))
        {
            j = 0;
            gdi_update();
            printf("\r\n");
        }
    }

    return 0;
}
