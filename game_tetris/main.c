#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "type.h"
#include "lcd_gdi.h"
#include "game_tetris.h"

void _game_key_ctrl(tetris_game_dir_t* oldkey)
{
    *oldkey = DR_UP;

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
        tetris_add_speed();
        break;

    case 'E':
    case 'e':
        tetris_sub_speed();
        break;

    case '\r':
    case '\n':
        tetris_shape_deform();
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

#if 1
int main(void)
{
    tetris_game_dir_t dir = DR_UP;
    tetris_game_life_t game_life = LF_INIT;
    gdi_setup();

    while(TRUE)
    {
        if(LF_INIT == game_life)
        {
            tetris_game_init();
        }

        dir = DR_UP;

        if(_kbhit())
        {
            _game_key_ctrl(&dir);

            if(dir != DR_UP)
            {
                tetris_shape_move(dir);
            }
        }

        game_life = tetris_game_run();

        if(game_life == LF_DIE)
        {
            game_life = LF_INIT;
        }

        gdi_update();
        printf("Tetris Game Score: %-3d | Game Speed: %-2d", tetris_get_score(), tetris_get_speed());
        Sleep(550 - (50 * tetris_get_speed()));
    }

    return 0;
}
#endif
