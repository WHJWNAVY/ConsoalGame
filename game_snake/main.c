#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "type.h"
#include "lcd_gdi.h"
#include "lcd_snake.h"

#if 0
void _game_delay_ms(uint64 sec)
{
    uint64 i = 0, j = sec * 300000;

    while(j--)
        i++;
}
#endif

void _game_key_ctrl(SNAKE_DIR* oldkey)
{
    switch(_getch())
    {
    case 'W':
    case 'w':
        *oldkey = DR_UP;
        break;

    case 'S':
    case 's':
        *oldkey = DR_DOWN;
        break;

    case 'A':
    case 'a':
        *oldkey = DR_LEFT;
        break;

    case 'D':
    case 'd':
        *oldkey = DR_RIGHT;
        break;

    case 'Q':
    case 'q':
        snake_sub_speed();
        break;

    case 'E':
    case 'e':
        snake_add_speed();
        break;

    case ' ':
        while(TRUE)
        {
            if(_getch() == ' ')
                break;
        }

        break;

    default:
        break;
    }
}

int8* _dir_tostring(SNAKE_DIR dir)
{
    switch(dir)
    {
    case DR_UP:
        return  "UP";

    case DR_DOWN:
        return "DOWN";

    case DR_LEFT:
        return "LEFT";

    default:
        return "RIGHT";
    }
}

void game_start_disp(void)
{
    system("cls");
    gdi_setup();//初始化显示
    gdi_puts(0, 0, "  SNAKE\r\nReady Go!", FALSE, TRUE);
    gdi_update();
    printf("By: WHJWNAVY(www.wnavy.com). \"WSAD\" for Direction. \"QE\" for Speed.");
}

void game_over_disp(SNAKE_LIFE lf)
{
    system("cls");
    gdi_setup();//初始化显示

    switch(lf)
    {
    case LF_DIE:
        gdi_puts(0, 0, "  GAME\r\n  OVER  ", FALSE, TRUE);
        break;

    case LF_WIN:
        gdi_puts(0, 0, "  GAME\r\n  WIN!  ", FALSE, TRUE);
        break;

    default:
        gdi_puts(0, 0, "  GAME\r\n  LIVE  ", FALSE, TRUE);
        break;
    }

    gdi_update();
    printf("Press any key to play again!");
}

int main(void)
{
    static SNAKE_DIR KEY = DR_RIGHT;
    int32 game_speed = 0;
    int32 snake_lf = LF_LIVE;

    while(TRUE)
    {
        game_start_disp();
        //_game_delay_ms(5000);
        Sleep(3000);
        KEY = DR_RIGHT;
        snake_game_init(3, DR_RIGHT, 10, TRUE);//贪吃蛇初始化

        while(TRUE)
        {
            if(_kbhit())
                _game_key_ctrl(&KEY);

            snake_move_control(KEY);
            gdi_update();

            game_speed = snake_get_speed();
            printf("Snake Dir:%-5s | Game Score: %-3d | Game Speed: %-2d",
                   _dir_tostring(snake_get_dir()), snake_get_score(), game_speed);

            snake_lf = snake_get_life();

            if(snake_lf != LF_LIVE) //游戏结束
                break;

            //_game_delay_ms(1000 / game_speed);
            game_speed = (1000 - (game_speed * 100));
            Sleep((game_speed <= 0) ? 10 : game_speed);
        }

        game_over_disp(snake_lf);
        getchar();
    }

    return 0;
}
