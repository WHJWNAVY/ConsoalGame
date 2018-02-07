#ifndef __LCD_SNAKE_H_
#define __LCD_SNAKE_H_

#include "lcd_gdi.h"

#define RTN_ERR         (/*ERROR*/-1)//���ش���
#define RTN_OK          (/*OK*/0)//����0
#define RTN_NULL        (/*NULL*/0)//����NULL

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
 �� �� ��  : tetris_game_init
 ��������  : ��Ϸ��ʼ��
 �������  : void  
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�
*****************************************************************************/
extern int32 tetris_game_init(void);

/*****************************************************************************
 �� �� ��  : tetris_game_run
 ��������  : ��Ϸ��ʼ����,����������,����,����
 �������  : void  
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�
*****************************************************************************/
extern int32 tetris_game_run(void);

/*****************************************************************************
 �� �� ��  : tetris_shape_deform
 ��������  : ȫ��shape����
 �������  : void  
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�
*****************************************************************************/
extern int32 tetris_shape_deform(void);

/*****************************************************************************
 �� �� ��  : tetris_shape_move
 ��������  : ʹȫ��shape��ָ�������ƶ�
 �������  : game_dir_t dir  ȫ��shape�ƶ��ķ���
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�
*****************************************************************************/
extern int32 tetris_shape_move(game_dir_t dir);

/*****************************************************************************
 �� �� ��  : tetris_get_life
 ��������  : ��ȡ��Ϸ����ֵ
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ����ֵ
*****************************************************************************/
extern int32 tetris_get_life(void);

/*****************************************************************************
 �� �� ��  : tetris_get_score
 ��������  : �����Ϸ�÷�
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ�÷�
*****************************************************************************/
extern int32 tetris_get_score(void);

/*****************************************************************************
 �� �� ��  : tetris_get_speed
 ��������  : �����Ϸ�ٶ�
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ�ٶ�
*****************************************************************************/
extern int32 tetris_get_speed(void);

/*****************************************************************************
 �� �� ��  : tetris_add_speed
 ��������  : ��Ϸ�ٶȼӿ�
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ�ٶ�
*****************************************************************************/
extern int32 tetris_add_speed(void);
/*****************************************************************************
 �� �� ��  : tetris_sub_speed
 ��������  : ��Ϸ�ٶȼ���
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ�ٶ�
*****************************************************************************/
extern int32 tetris_sub_speed(void);

#endif