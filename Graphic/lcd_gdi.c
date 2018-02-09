#include <windows.h>
#include <math.h>
#include <conio.h>
#include "font8x8.h"
#include "font5x7.h"
#include "lcd_gdi.h"

#define LCD_GDI_DEBUG_LOG
#ifdef LCD_GDI_DEBUG_LOG
#include "stdio.h"
#define GDI_DBG_LOG_NAME    "gdi_debug.log"
FILE*   GDI_DBG_LOG_FILE    = NULL;
#endif // LCD_GDI_DEBUG_LOG

// Software copy of the framebuffer
static uint8 SCREEN_BUFF[SCREEN_Y][SCREEN_X];//SCREEN_BUFF[y][x]

static int32 maxX = SCREEN_X, maxY = SCREEN_Y;
static int32 lastX = 0, lastY = 0;
static int32 mirrorX = 0, mirrorY = 0;

typedef enum _gdi_col
{
    COL_BLACK = '@',//1和2都是笑脸
    COL_WHITE = ' '
} GDI_COL;


/*
 * gdi_update:
 *  Copy our software version to the real display
 *******************************************************************************
 */
#ifdef LCD_GDI_DEBUG_LOG
int32 gdi_dbg_openlog(void)
{
    GDI_DBG_LOG_FILE = fopen(GDI_DBG_LOG_NAME, "a+");

    if(GDI_DBG_LOG_FILE == NULL)
    {
        return -1;
    }

    return 0;
}

void gdi_dbg_closelog(void)
{
    if(GDI_DBG_LOG_FILE != NULL)
    {
        fclose(GDI_DBG_LOG_FILE);
    }

    GDI_DBG_LOG_FILE = NULL;
}

void gdi_dbg_putc(char c)
{
    fprintf(GDI_DBG_LOG_FILE, "%c", c);
}

void gdi_update(void)
{
    int8 x = 0, y = 0;

    if(gdi_dbg_openlog() < 0)
    {
        return;
    }

    //system("cls");
    gdi_dbg_putc('\n');

    for(x = 0; x < (SCREEN_X); x++)
    {
        gdi_dbg_putc('=');
    }

    gdi_dbg_putc('\n');

    for(y = 0; y < (SCREEN_Y); y++)
    {
        for(x = 0; x < (SCREEN_X); x++)
        {
            //_putch(SCREEN_BUFF[y][x]);
            gdi_dbg_putc(SCREEN_BUFF[y][x]);
        }

        //_putch('+');
        //_putch('\n');
        gdi_dbg_putc('+');
        gdi_dbg_putc('\n');
    }

    for(y = 0; y <= (SCREEN_X); y++)
    {
        //_putch('+');
        gdi_dbg_putc('+');
    }

    //_putch('\n');
    gdi_dbg_putc('\n');

    gdi_dbg_closelog();
}
#else
void gdi_update(void)
{
    int8 x = 0, y = 0;
    system("cls");

    for(y = 0; y < (SCREEN_Y); y++)
    {
        for(x = 0; x < (SCREEN_X); x++)
        {
            _putch(SCREEN_BUFF[y][x]);
        }

        _putch('+');
        _putch('\n');
    }

    for(y = 0; y <= (SCREEN_X); y++)
    {
        _putch('+');
    }

    _putch('\n');
}
#endif // LCD_GDI_DEBUG_LOG

/*
 * gdi_clear:
 *  Clear the display to the given colour.
 *******************************************************************************
 */
void gdi_clear(int32 colour)
{
    int32 x = 0, y = 0;
    int8 col = 0;

    col = (colour) ? (COL_BLACK) : (COL_WHITE);

    for(y = 0; y < (SCREEN_Y); y++)
    {
        for(x = 0; x < (SCREEN_X); x++)
        {
            SCREEN_BUFF[y][x] = col;
        }
    }
}


/*
 * gdi_set_orientation:
 *  Set the display orientation:
 *  0: Normal, the display is portrait mode, 0,0 is top left
 *  1: Mirror x
 *  2: Mirror y
 *  3: Mirror x and y
 *******************************************************************************
 */
void gdi_set_orientation(int32 orientation)
{
    switch(orientation)
    {
    case 0:
        mirrorX = 0;
        mirrorY = 0;
        break;

    case 1:
        mirrorX = 1;
        mirrorY = 0;
        break;

    case 2:
        mirrorX = 0;
        mirrorY = 1;
        break;

    case 3:
        mirrorX = 1;
        mirrorY = 1;
        break;

    default:
        break;
    }
}



/*
 * gdi_get_screen_size:
 *  Return the max X & Y screen sizes. Needs to be called again, if you
 *  change screen orientation.
 *******************************************************************************
 */
void gdi_get_screen_size(int32 *x, int32 *y)
{
    *x = maxX;
    *y = maxY;
}


/*
 *******************************************************************************
 * Standard Graphical Functions
 *******************************************************************************
 */


/*
 * gdi_set_point:
 *  Plot a pixel.
 *******************************************************************************
 */
void gdi_set_point(int32 x, int32 y, int32 colour)
{
    if(mirrorX)
        x = (maxX - x - 1);

    if(mirrorY)
        y = (maxY - y - 1);

    lastX = x;
    lastY = y;

    x = ((x < 0) ? 0 : ((x > (maxX - 1)) ? (maxX - 1) : x));
    y = ((y < 0) ? 0 : ((y > (maxY - 1)) ? (maxY - 1) : y));

    SCREEN_BUFF[y][x] = ((colour) ? COL_BLACK : COL_WHITE);
}

/*
 * gdi_set_point:
 *  Plot a pixel.
 *******************************************************************************
 */
int32 gdi_get_point(int32 x, int32 y)
{
    if(mirrorX)
        x = (maxX - x - 1);

    if(mirrorY)
        y = (maxY - y - 1);

    x = ((x < 0) ? 0 : ((x > (maxX - 1)) ? (maxX - 1) : x));
    y = ((y < 0) ? 0 : ((y > (maxY - 1)) ? (maxY - 1) : y));

    return ((SCREEN_BUFF[y][x] == COL_BLACK) ? TRUE : FALSE);
}


/*
 * gdi_line: gdi_lineto:
 *  Classic Bressenham Line code
 *******************************************************************************
 */
void gdi_line(int32 x0, int32 y0, int32 x1, int32 y1, int32 colour)
{
    int32 dx, dy;
    int32 sx, sy;
    int32 err, e2;

    lastX = x1;
    lastY = y1;

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    sx = (x0 < x1) ? 1 : -1;
    sy = (y0 < y1) ? 1 : -1;

    err = dx - dy;

    for(;;)
    {
        gdi_set_point(x0, y0, colour);

        if((x0 == x1) && (y0 == y1))
            break;

        e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void gdi_lineto(int32 x, int32 y, int32 colour)
{
    gdi_line(lastX, lastY, x, y, colour);
}


/*
 * gdi_rectangle:
 *  A rectangle is a spoilt days fishing
 *******************************************************************************
 */
void gdi_rectangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 colour,
                   int32 filled)
{
    int32 x;

    if(filled)
    {
        if(x1 == x2)
        {
            gdi_line(x1, y1, x2, y2, colour);
        }
        else if(x1 < x2)
        {
            for(x = x1; x <= x2; ++x)
            {
                gdi_line(x, y1, x, y2, colour);
            }
        }
        else
        {
            for(x = x2; x <= x1; ++x)
            {
                gdi_line(x, y1, x, y2, colour);
            }
        }
    }
    else
    {
        gdi_line(x1, y1, x2, y1, colour);
        gdi_lineto(x2, y2, colour);
        gdi_lineto(x1, y2, colour);
        gdi_lineto(x1, y1, colour);
    }
}


/*
 * gdi_circle:
 *      This is the midpoint32 circle algorithm.
 *******************************************************************************
 */
void gdi_circle(int32 x, int32 y, int32 r, int32 colour, int32 filled)
{
    int32 ddF_x = 1;
    int32 ddF_y = -2 * r;

    int32 f = 1 - r;
    int32 x1 = 0;
    int32 y1 = r;

    if(filled)
    {
        gdi_line(x, y + r, x, y - r, colour);
        gdi_line(x + r, y, x - r, y, colour);
    }
    else
    {
        gdi_set_point(x, y + r, colour);
        gdi_set_point(x, y - r, colour);
        gdi_set_point(x + r, y, colour);
        gdi_set_point(x - r, y, colour);
    }

    while(x1 < y1)
    {
        if(f >= 0)
        {
            y1--;
            ddF_y += 2;
            f += ddF_y;
        }

        x1++;
        ddF_x += 2;
        f += ddF_x;

        if(filled)
        {
            gdi_line(x + x1, y + y1, x - x1, y + y1, colour);
            gdi_line(x + x1, y - y1, x - x1, y - y1, colour);
            gdi_line(x + y1, y + x1, x - y1, y + x1, colour);
            gdi_line(x + y1, y - x1, x - y1, y - x1, colour);
        }
        else
        {
            gdi_set_point(x + x1, y + y1, colour);
            gdi_set_point(x - x1, y + y1, colour);
            gdi_set_point(x + x1, y - y1, colour);
            gdi_set_point(x - x1, y - y1, colour);
            gdi_set_point(x + y1, y + x1, colour);
            gdi_set_point(x - y1, y + x1, colour);
            gdi_set_point(x + y1, y - x1, colour);
            gdi_set_point(x - y1, y - x1, colour);
        }
    }
}


/*
 * gdi_ellipse:
 *  Fast ellipse drawing algorithm by
 *      John Kennedy
 *  Mathematics Department
 *  Santa Monica College
 *  1900 Pico Blvd.
 *  Santa Monica, CA 90405
 *  jrkennedy6@gmail.com
 *  -Confirned in email this algorithm is in the public domain -GH-
 *******************************************************************************
 */
static void plot4ellipsePoints(int32 cx, int32 cy, int32 x, int32 y,
                               int32 colour, int32 filled)
{
    if(filled)
    {
        gdi_line(cx + x, cy + y, cx - x, cy + y, colour);
        gdi_line(cx - x, cy - y, cx + x, cy - y, colour);
    }
    else
    {
        gdi_set_point(cx + x, cy + y, colour);
        gdi_set_point(cx - x, cy + y, colour);
        gdi_set_point(cx - x, cy - y, colour);
        gdi_set_point(cx + x, cy - y, colour);
    }
}

void gdi_ellipse(int32 cx, int32 cy, int32 xRadius, int32 yRadius,
                 int32 colour, int32 filled)
{
    int32 x, y;
    int32 xChange, yChange, ellipseError;
    int32 twoAsquare, twoBsquare;
    int32 stoppingX, stoppingY;

    twoAsquare = 2 * xRadius * xRadius;
    twoBsquare = 2 * yRadius * yRadius;

    x = xRadius;
    y = 0;

    xChange = yRadius * yRadius * (1 - 2 * xRadius);
    yChange = xRadius * xRadius;

    ellipseError = 0;
    stoppingX = twoBsquare * xRadius;
    stoppingY = 0;

    while(stoppingX >= stoppingY)   // 1st set of point32s
    {
        plot4ellipsePoints(cx, cy, x, y, colour, filled);
        ++y;
        stoppingY += twoAsquare;
        ellipseError += yChange;
        yChange += twoAsquare;

        if((2 * ellipseError + xChange) > 0)
        {
            --x;
            stoppingX -= twoBsquare;
            ellipseError += xChange;
            xChange += twoBsquare;
        }
    }

    x = 0;
    y = yRadius;

    xChange = yRadius * yRadius;
    yChange = xRadius * xRadius * (1 - 2 * yRadius);

    ellipseError = 0;
    stoppingX = 0;
    stoppingY = twoAsquare * yRadius;

    while(stoppingX <= stoppingY)   //2nd set of point32s
    {
        plot4ellipsePoints(cx, cy, x, y, colour, filled);
        ++x;
        stoppingX += twoBsquare;
        ellipseError += xChange;
        xChange += twoBsquare;

        if((2 * ellipseError + yChange) > 0)
        {
            --y;
            stoppingY -= twoAsquare;
            ellipseError += yChange;
            yChange += twoAsquare;
        }
    }
}


/*
 * gdi_putch:
 *  Print a single character to the screen
 *******************************************************************************
 */
void gdi_putch(int32 x, int32 y, int32 c, int32 bgCol, int32 fgCol)
{
    int32 y1, y2;

    uint8 line;
    uint8 *fontPtr;

    // Can't print if we're offscreen

    x = ((x < 0) ? 0 : ((x > (maxX - fontWidth)) ? (maxX - fontWidth) : x));
    y = ((y < 0) ? 0 : ((y > (maxY - fontHeight)) ? (maxY - fontHeight) : y));
    c = ((c > 255) ? '?' : c);

    fontPtr = font_8x8 + c * fontHeight;

    for(y1 = 0; y1 < fontHeight; y1++)
    {
        y2 = y + y1;
        line = *fontPtr++;
        gdi_set_point(x + 0, y2, (line & 0x80) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 1, y2, (line & 0x40) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 2, y2, (line & 0x20) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 3, y2, (line & 0x10) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 4, y2, (line & 0x08) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 5, y2, (line & 0x04) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 6, y2, (line & 0x02) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 7, y2, (line & 0x01) == 0 ? bgCol : fgCol);
    }
}

/*
 * gdi_puts:
 *  Send a string to the display. Obeys \n and \r formatting
 *******************************************************************************
 */
void gdi_puts(int32 x, int32 y, const char *str, int32 bgCol, int32 fgCol)
{
    int32 c, mx, my;

    mx = x;
    my = y;

    while(*str)
    {
        c = *str++;

        if(c == '\r')
        {
            mx = x;
            continue;
        }

        if(c == '\n')
        {
            my += fontHeight;

            if(my > (maxY - fontHeight))
                return;

            continue;
        }

        gdi_putch(mx, my, c, bgCol, fgCol);

        mx += fontWidth;

        if(mx > (maxX - fontWidth))
        {
            mx = 0;
            my += fontHeight;

            if(my > (maxY - fontHeight))
                return;
        }
    }
}

void gdi_puts_5x7(int32 x, int32 y, const char *str, int32 bgCol, int32 fgCol)
{
    int32 c, mx, my;

    mx = x;
    my = y;

    while(*str)
    {
        c = *str++;

        if(c == '\r')
        {
            mx = x;
            continue;
        }

        if(c == '\n')
        {
            my += font5X7Height;

            if(my > (maxY - font5X7Height))
                return;

            continue;
        }

        gdi_putch_5x7(mx, my, c, bgCol, fgCol);

        mx += font5X7Width;

        if(mx > (maxX - font5X7Width))
        {
            mx = 0;
            my += font5X7Height;

            if(my > (maxY - font5X7Height))
                return;
        }
    }
}

void gdi_putch_5x7(int32 x, int32 y, int32 c, int32 bgCol, int32 fgCol)
{
    int32 y1, y2;

    uint8 line;
    uint8 *fontPtr;

    // Can't print if we're offscreen

    x = ((x < 0) ? 0 : ((x > (maxX - font5X7Width)) ? (maxX - font5X7Width) : x));
    y = ((y < 0) ? 0 : ((y > (maxY - font5X7Height)) ? (maxY - font5X7Height) : y));
    c = ((c > '~') ? '?' : ((c < ' ') ? '?' : c));//min:32,max:126
    c -= ' ';

    fontPtr = font_5x7 + c * font5X7Height;

    for(y1 = 0; y1 < font5X7Height; y1++)
    {
        y2 = y + y1;
        line = *fontPtr++;
        gdi_set_point(x + 0, y2, (line & 0x80) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 1, y2, (line & 0x40) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 2, y2, (line & 0x20) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 3, y2, (line & 0x10) == 0 ? bgCol : fgCol);
        gdi_set_point(x + 4, y2, (line & 0x08) == 0 ? bgCol : fgCol);
    }
}

/*
 * gdi_putbmp:
 *  Send a picture to the display.
 *******************************************************************************
 */
void gdi_putbmp(int32 x0, int32 y0, int32 with, int32 height, uint8* bmp)
{
    int32 x = 0, y = 0;

    for(y = y0; y < (height); y++)
    {
        for(x = x0; x < with; x++)
        {
            SCREEN_BUFF[y][x] = ((*bmp++) ? COL_BLACK : COL_WHITE);
        }
    }
}


/*
 * gdi_setup:
 *  Initialise the display and GPIO.
 *******************************************************************************
 */
int32 gdi_setup(void)
{
#if 0//def LCD_GDI_DEBUG_LOG

    if(gdi_dbg_openlog() < 0)
    {
        return 0;
    }

#endif // LCD_GDI_DEBUG_LOG
    gdi_set_orientation(0);
    gdi_clear(0);
    gdi_update();
    return 0;
}

#if 0//def LCD_GDI_DEBUG_LOG
int32 gdi_close(void)
{
    gdi_dbg_closelog();
    return 0;
}
#endif
