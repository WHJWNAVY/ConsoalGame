#ifndef __LCD_SNAKE_H_
#define __LCD_SNAKE_H_

#include "type.h"
#include "lcd_gdi.h"

#define RTN_ERR         ERROR//���ش���
#define RTN_OK          OK//����0
#define RTN_NULL        NULL//����NULL

//����
typedef enum snake_dir
{
    DR_UP = 0,          //0��
    DR_DOWN,            //1��
    DR_LEFT,            //2��
    DR_RIGHT            //3��
} SNAKE_DIR;

//����
typedef enum snake_life
{
    LF_LIVE = 0,        //0����
    LF_DIE,             //1����
    LF_WIN,             //2ʤ��
} SNAKE_LIFE;

//��������

/*****************************************************************************
 �� �� ��  : snake_game_init
 ��������  : ̰������Ϸ��ʼ��
 �������  : int32 scnt:��ʼ����������
 SNAKE_DIR sdir:��ʼ����ͷ����
 int32 sstep:�÷��ٶ�
 int32 speed:�ٶ�
 �������  : ��
 �� �� ֵ  :
 ����˵��  :
 *****************************************************************************/
extern int32        snake_game_init(int32 scnt, SNAKE_DIR sdir, int32 sstep, int32 cwall);

/*****************************************************************************
 �� �� ��  : snake_move_control
 ��������  : ���ݰ���ֵ�������ƶ�
 �������  : SNAKE_DIR KEY
 �������  : ��
 �� �� ֵ  : ������ҵ�ǰ������״̬
 ����˵��  : û�е�������Ϸ״̬����������ʹ���߱������Լ����������и���
 �ú������ص�����״̬��������Ϸ����(����˵��SnakeLifeΪLF_DIE��
 ʱ�����ʲô�£���Щ��Ҫ��ʹ�ñ����������Լ����)
 *****************************************************************************/
extern SNAKE_LIFE   snake_move_control(SNAKE_DIR KEY);

/*****************************************************************************
 �� �� ��  : snake_get_score
 ��������  : ��ȡ��ǰ��Ϸ�÷�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��Ϸ�÷�
 ����˵��  :
 *****************************************************************************/
extern int32        snake_get_score(void);

/*****************************************************************************
 �� �� ��  : snake_get_speed
 ��������  : ��ȡ��ǰ�ٶ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ٶ�
 ����˵��  :
 *****************************************************************************/
extern int32        snake_get_speed(void);

/*****************************************************************************
 �� �� ��  : snake_set_speed
 ��������  : ���õ�ǰ�ٶ�
 �������  : int32 speed
 �������  : ��
 �� �� ֵ  : �ٶ�
 ����˵��  :
 *****************************************************************************/
extern int32        snake_set_speed(int32 speed);

/*****************************************************************************
 �� �� ��  : snake_add_speed
 ��������  : ���ٶ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ٶ�
 ����˵��  : ͨ��snake_set_scstep��������һ������ֵSCORE_STEP���ٶ�ÿ������
 SCORE_STEP����λ��
 *****************************************************************************/
extern int32        snake_add_speed(void);

/*****************************************************************************
 �� �� ��  : snake_sub_speed
 ��������  : ���ٶȼ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ٶ�
 ����˵��  : ͨ��snake_set_scstep��������һ������ֵSCORE_STEP���ٶ�ÿ�μ�С
 SCORE_STEP����λ��
 *****************************************************************************/
extern int32        snake_sub_speed(void);

/*****************************************************************************
 �� �� ��  : snake_get_life
 ��������  : ��ȡ��ǰ��Ϸ����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ��Ϸ����ֵ
 ����˵��  :
 *****************************************************************************/
extern SNAKE_LIFE   snake_get_life(void);

/*****************************************************************************
 �� �� ��  : snake_set_scstep
 ��������  : ������Ϸ�÷ֲ���
 �������  : int32 scstep
 �������  : ��
 �� �� ֵ  : ��Ϸ�÷ֲ���
 ����˵��  : ��ֵ���ٶ����ӵĲ���ֵ(ÿ�Ե�һ��ʳ���1�֣��������ӵ�scstep������
 ��֮���ٶȼӿ�scstep����λ)��
 *****************************************************************************/
extern int32        snake_set_scstep(int32 scstep);

/*****************************************************************************
 �� �� ��  : snake_get_dir
 ��������  : ��ȡ��ǰ��ͷ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ��ͷ����
 ����˵��  :
 *****************************************************************************/
extern SNAKE_DIR    snake_get_dir(void);

/*****************************************************************************
 �� �� ��  : snake_set_dir
 ��������  : ���õ�ǰ��ͷ����
 �������  : SNAKE_DIR sdir
 �������  : ��
 �� �� ֵ  : ��ǰ��ͷ����
 ����˵��  :
 *****************************************************************************/
extern SNAKE_DIR    snake_set_dir(SNAKE_DIR sdir);

/*****************************************************************************
 �� �� ��  : snake_set_crosswall
 ��������  : �����Ƿ�����Խ��
 �������  : int32 crosswall
 �������  : ��
 �� �� ֵ  : ��
 ����˵��  : �����ʾ����Խ��
 *****************************************************************************/
extern void         snake_set_crosswall(int32 crosswall);
#endif