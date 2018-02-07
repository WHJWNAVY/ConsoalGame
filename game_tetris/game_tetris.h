#ifndef __LCD_SNAKE_H_
#define __LCD_SNAKE_H_

#include "lcd_gdi.h"

#define RTN_ERR         (/*ERROR*/-1)//返回错误
#define RTN_OK          (/*OK*/0)//返回0
#define RTN_NULL        (/*NULL*/0)//返回NULL

typedef enum game_dir_e
{
    DR_UP = 0,          // 0
    DR_DOWN,            // 1
    DR_LEFT,            // 2
    DR_RIGHT            // 3
} game_dir_t;

typedef struct game_point_s
{
    int32       x;
    int32       y;
    int32       col;
} game_point_t;

typedef struct game_shape_s
{
    int32           index;
    game_point_t    point;
} game_shape_t;

/*****************************************************************************
 函 数 名  : tetris_game_init
 功能描述  : 游戏初始化
 输入参数  : void  
 输出参数  : 无
 返 回 值  : RTN_OK:成功
*****************************************************************************/
extern int32 tetris_game_init(void);

/*****************************************************************************
 函 数 名  : tetris_game_run
 功能描述  : 游戏开始运行,并处理满行,消行,分数
 输入参数  : void  
 输出参数  : 无
 返 回 值  : RTN_OK:成功
*****************************************************************************/
extern int32 tetris_game_run(void);

/*****************************************************************************
 函 数 名  : tetris_shape_deform
 功能描述  : 全局shape变形
 输入参数  : void  
 输出参数  : 无
 返 回 值  : RTN_OK:成功
*****************************************************************************/
extern int32 tetris_shape_deform(void);

/*****************************************************************************
 函 数 名  : tetris_shape_move
 功能描述  : 使全局shape按指定方向移动
 输入参数  : game_dir_t dir  全局shape移动的方向
 输出参数  : 无
 返 回 值  : RTN_OK:成功
*****************************************************************************/
extern int32 tetris_shape_move(game_dir_t dir);

/*****************************************************************************
 函 数 名  : tetris_get_life
 功能描述  : 获取游戏生命值
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 游戏生命值
*****************************************************************************/
extern int32 tetris_get_life(void);

/*****************************************************************************
 函 数 名  : tetris_get_score
 功能描述  : 获得游戏得分
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 游戏得分
*****************************************************************************/
extern int32 tetris_get_score(void);

/*****************************************************************************
 函 数 名  : tetris_get_speed
 功能描述  : 获得游戏速度
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 游戏速度
*****************************************************************************/
extern int32 tetris_get_speed(void);

/*****************************************************************************
 函 数 名  : tetris_add_speed
 功能描述  : 游戏速度加快
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 游戏速度
*****************************************************************************/
extern int32 tetris_add_speed(void);
/*****************************************************************************
 函 数 名  : tetris_sub_speed
 功能描述  : 游戏速度减慢
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 游戏速度
*****************************************************************************/
extern int32 tetris_sub_speed(void);

#endif
