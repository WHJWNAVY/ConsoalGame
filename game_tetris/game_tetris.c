/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include "game_tetris.h"

/*----------------------------------------------*
* �궨��                                       *
*----------------------------------------------*/
//#define GAME_MIRROR_XY        1//����xy����
#ifdef GAME_MIRROR_XY
#define GAME_SCREEN_L         (SCREEN_Y)//��Ļ����
#define GAME_SCREEN_H         (SCREEN_X)//��Ļ���
#else
#define GAME_SCREEN_L         (SCREEN_X-20)//��Ļ����
#define GAME_SCREEN_H         (SCREEN_Y)//��Ļ���
#endif
#define GAME_POINT_SIZE       1//���С����λ:���أ���Ϊ������

#define GAME_POINT_L          (GAME_POINT_SIZE)//���С����λ:���أ���Ϊ������
#define GAME_POINT_H          (GAME_POINT_SIZE)
#define GAME_MAX_X            ((GAME_SCREEN_L) / (GAME_POINT_L))//�ƶ�����
#define GAME_MAX_Y            ((GAME_SCREEN_H) / (GAME_POINT_H))//�ƶ�����

#define MAX_BSC_SHAPE_CNT     7//7�ֻ�����״
#define MAX_EXT_SHAPE_CNT     4//4�ֱ任��״
#define MAX_SHAPE_CNT         (MAX_BSC_SHAPE_CNT*MAX_EXT_SHAPE_CNT)//�ܹ���״����
#define SHAPE_PNT_CNT         4//ÿ����״���ĸ��㹹��

#define GAME_MAX_SPEED        10//�����Ϸ�ٶ�
#define GAME_MIN_SPEED        1 //��С��Ϸ�ٶ�
#define GAME_SPEED_STEP       10//ÿ��10����Ϸ�ٶ�+1

game_shape_t glGameShape;
int32        glGameSCore;
int32        glGameSpeed;
int32        glGameLife;

/*����˹���鹲��7�ֻ�����״��ÿ�ֻ�����״����ת4�Σ�ÿ����״
��4��С������ɡ���������ÿ�ֻ�����״����һ��4x4�ľ����
��һ������ȥ��¼ÿ��С��������ھ������Ͻǵ�λ��*/
game_point_t GAME_SHAPE_BOX[MAX_SHAPE_CNT][SHAPE_PNT_CNT] =
{
    //I///
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 2, 0, TRUE }, { 3, 0, TRUE } },//I0
    { { 0, 0, TRUE }, { 0, 1, TRUE }, { 0, 2, TRUE }, { 0, 3, TRUE } },//I1
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 2, 0, TRUE }, { 3, 0, TRUE } },//I2
    { { 0, 0, TRUE }, { 0, 1, TRUE }, { 0, 2, TRUE }, { 0, 3, TRUE } }, //I3
    ///J///
    { { 0, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE }, { 2, 1, TRUE } },//J0
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 0, 1, TRUE }, { 0, 2, TRUE } },//J1
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 2, 0, TRUE }, { 2, 1, TRUE } },//J2
    { { 1, 0, TRUE }, { 1, 1, TRUE }, { 0, 2, TRUE }, { 1, 2, TRUE } }, //J3
    ///L///
    { { 2, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE }, { 2, 1, TRUE } },//L0
    { { 0, 0, TRUE }, { 0, 1, TRUE }, { 0, 2, TRUE }, { 1, 2, TRUE } },//L1
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 2, 0, TRUE }, { 0, 1, TRUE } },//L2
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 1, 1, TRUE }, { 1, 2, TRUE } }, //L3
    ///O///
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE } },//O0
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE } },//O1
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE } },//O2
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE } }, //O3
    ///S
    { { 1, 0, TRUE }, { 2, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE } },//S0
    { { 0, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE }, { 1, 2, TRUE } },//S1
    { { 1, 0, TRUE }, { 2, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE } },//S2
    { { 0, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE }, { 1, 2, TRUE } }, //S3
    ///T
    { { 1, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE }, { 2, 1, TRUE } },//T0
    { { 0, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE }, { 0, 2, TRUE } },//T1
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 2, 0, TRUE }, { 1, 1, TRUE } },//T2
    { { 1, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE }, { 1, 2, TRUE } }, //T3
    ///Z
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 1, 1, TRUE }, { 2, 1, TRUE } },//Z0
    { { 1, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE }, { 0, 2, TRUE } },//Z1
    { { 0, 0, TRUE }, { 1, 0, TRUE }, { 1, 1, TRUE }, { 2, 1, TRUE } },//Z2
    { { 1, 0, TRUE }, { 0, 1, TRUE }, { 1, 1, TRUE }, { 0, 2, TRUE } }  //Z3

};

int32 GAME_SHAPE_SIZE[MAX_SHAPE_CNT][2] =
{
    {4, 1}, {1, 4}, {4, 1}, {1, 4}, //I
    {3, 2}, {2, 3}, {3, 2}, {2, 3}, //J
    {3, 2}, {2, 3}, {3, 2}, {2, 3}, //L
    {2, 2}, {2, 2}, {2, 2}, {2, 2}, //O
    {3, 2}, {2, 3}, {3, 2}, {2, 3}, //S
    {3, 2}, {2, 3}, {3, 2}, {2, 3}, //T
    {3, 2}, {2, 3}, {3, 2}, {2, 3}  //Z
};

/*****************************************************************************
�� �� ��  : game_draw_point
��������  : ʹ�����Ź����DPI����һ�������
�������  : game_point_t* s_point
�������  : ��
�� �� ֵ  : �ɹ�����0��ʧ�ܷ���1
����˵��  :
*****************************************************************************/
int32 game_draw_point(const game_point_t* const s_point)
{
    int32 x = 0, y = 0, col = 0;
    #ifdef GAME_MIRROR_XY
    int32 yt = 0;
    #endif

    if(s_point == RTN_NULL)
        return RTN_ERR;

    x = s_point->x;
    y = s_point->y;
    col = s_point->col;

    //x = ((x < 0) ? 0 : ((x >= GAME_MAX_X) ? (GAME_MAX_X - 1) : x));
    //y = ((y < 0) ? 0 : ((y >= GAME_MAX_Y) ? (GAME_MAX_Y - 1) : y));
    if((x < 0) || (x >= GAME_MAX_X) ||
       (y < 0) || (y >= GAME_MAX_Y))
    {
        return RTN_ERR;
    }

    #ifdef GAME_MIRROR_XY
    yt = y;
    y = x * GAME_POINT_L;
    x = yt * GAME_POINT_H;
    #else
    x = x * GAME_POINT_L;
    y = y * GAME_POINT_H;
    #endif

    if(GAME_POINT_SIZE != 1) //��һ�����δ������Ź���ĵ�
        gdi_rectangle(x, y, x + GAME_POINT_L - 1, y + GAME_POINT_H - 1, col, 1);
    else//Ϊ�˼ӿ��ٶȣ����Ϊ1�����ţ�ֱ�ӻ���
        gdi_set_point(x, y, col);

    return RTN_OK;
}

/*****************************************************************************
�� �� ��  : game_get_point
��������  : ��ȡ��Ļ��ĳ�������ɫ
�������  : game_point_t* s_point
�������  : ��
�� �� ֵ  : ����ָ���ĵ����ɫ(1��0)
����˵��  :
*****************************************************************************/
int32 game_get_point(const game_point_t* const s_point)
{
    int32 x = 0, y = 0;
    #ifdef GAME_MIRROR_XY
    int32 yt = 0;
    #endif

    if(s_point == RTN_NULL)
        return RTN_ERR;

    x = s_point->x;
    y = s_point->y;

    //x = ((x < 0) ? 0 : ((x >= GAME_MAX_X) ? (GAME_MAX_X - 1) : x));
    //y = ((y < 0) ? 0 : ((y >= GAME_MAX_Y) ? (GAME_MAX_Y - 1) : y));
    if((x < 0) || (x >= GAME_MAX_X) ||
       (y < 0) || (y >= GAME_MAX_Y))
    {
        return FALSE;
    }

    #ifdef GAME_MIRROR_XY
    yt = y;
    y = x * GAME_POINT_L;
    x = yt * GAME_POINT_H;
    #else
    x = x * GAME_POINT_L;
    y = y * GAME_POINT_H;
    #endif

    return((gdi_get_point(x, y)) ? TRUE : FALSE);
}

/*****************************************************************************
 �� �� ��  : game_clear_screen
 ��������  : ָ����ɫ�����Ļ
 �������  : int32 col  ָ����ɫ
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void game_clear_screen(int32 col)
{
    gdi_clear(col);
}

/*****************************************************************************
 �� �� ��  : game_point_cmp
 ��������  : ����Ա�
 �������  : game_point_t* s1  Ҫ�Աȵĵ�һ����
             game_point_t* s2  Ҫ�Աȵĵڶ�����
 �������  : ��
 �� �� ֵ  : TRUE:��ͬ, FALSE:��ͬ
*****************************************************************************/
int32 game_point_cmp(game_point_t* s1, game_point_t* s2)
{
#if 0

    if(memcmp(s1, s2, sizeof(game_point_t)) == 0)
#else
    if((s1->x == s2->x) && (s1->y == s2->y) && (s1->col == s2->col))
#endif
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : game_show_shpe
 ��������  : ��ʾһ��shape
 �������  : game_shape_t* _shape  
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�, RTN_ERR:ʧ��
*****************************************************************************/
int32 game_show_shpe(game_shape_t* _shape)
{
    int i = 0;
    game_point_t shape_pnt;

    for(i = 0; i < SHAPE_PNT_CNT; i++)
    {
        shape_pnt.x = (GAME_SHAPE_BOX[_shape->index][i]).x + (_shape->point).x;
        shape_pnt.y = (GAME_SHAPE_BOX[_shape->index][i]).y + (_shape->point).y;
        shape_pnt.col = /*(_shape->point).col*/TRUE;

        if((shape_pnt.x < 0) || (shape_pnt.x >= GAME_MAX_X) ||
           (shape_pnt.y < 0) || (shape_pnt.y >= GAME_MAX_Y))
        {
            //return RTN_ERR;
            continue;
        }

        if(game_draw_point(&shape_pnt) != RTN_OK)
        {
            //return RTN_ERR;
            continue;
        }
    }

    return RTN_OK;
}

/*****************************************************************************
 �� �� ��  : game_clear_shpe
 ��������  : ���ָ����shape
 �������  : game_shape_t* _shape  Ҫ�����shape��ָ��
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�, RTN_ERR:ʧ��
*****************************************************************************/
int32 game_clear_shpe(game_shape_t* _shape)
{
    int i = 0;
    game_point_t shape_pnt;

    for(i = 0; i < SHAPE_PNT_CNT; i++)
    {
        shape_pnt.x = (GAME_SHAPE_BOX[_shape->index][i]).x + (_shape->point).x;
        shape_pnt.y = (GAME_SHAPE_BOX[_shape->index][i]).y + (_shape->point).y;
        shape_pnt.col = FALSE;

        if((shape_pnt.x < 0) || (shape_pnt.x >= GAME_MAX_X) ||
           (shape_pnt.y < 0) || (shape_pnt.y >= GAME_MAX_Y))
        {
            //return RTN_ERR;
            continue;
        }

        if(game_draw_point(&shape_pnt) != RTN_OK)
        {
            //return RTN_ERR;
            continue;
        }
    }

    return RTN_OK;
}

/*****************************************************************************
 �� �� ��  : game_clear_line
 ��������  : ���ָ����
 �������  : int32 row  Ҫ�������
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�, RTN_ERR:ʧ��
*****************************************************************************/
int32 game_clear_line(int32 row)
{
    int32 x = 0;
    game_point_t pnt;
    //row = ((row < 0) ? 0 : ((row >= GAME_MAX_Y) ? (GAME_MAX_Y - 1) : row));
    if((row < 0) || (row >= GAME_MAX_Y))
    {
        return RTN_ERR;
    }

    pnt.y = row;
    pnt.col = FALSE;

    for(x = 0; x < GAME_MAX_X; x++)
    {
        pnt.x = x;

        if(game_draw_point(&pnt) != RTN_OK)
        {
            //return RTN_ERR;
            continue;
        }
    }

    return RTN_OK;
}

/*****************************************************************************
 �� �� ��  : game_get_rshape_idx
 ��������  : ���һ������Ļ�����״(��shape box�е�����)
 �������  : void  
 �������  : ��
 �� �� ֵ  : index:��ȡ����shape��shapebox�е�����
*****************************************************************************/
int32 game_get_rshape_idx(void)
{
    static uint32 sseed = 0;
    int32 index = 0;
    srand(sseed);
    index = rand() % (MAX_SHAPE_CNT-1);//0-27
    sseed = index;
    return index;
}

/*****************************************************************************
 �� �� ��  : game_line_isfull
 ��������  : �ж�ĳһ���ǲ����Ѿ�����
 �������  : int32 row  Ҫ�жϵ���
 �������  : ��
 �� �� ֵ  : TRUE:����, FALSE:δ��
*****************************************************************************/
int32 game_line_isfull(int32 row)
{
    int32 x = 0, row_cnt = 0;
    game_point_t pnt;
    //row = ((row < 0) ? 0 : ((row >= GAME_MAX_Y) ? (GAME_MAX_Y - 1) : row));
    if((row < 0) || (row >= GAME_MAX_Y))
    {
        return FALSE;
    }
    pnt.y = row;
    pnt.col = TRUE;

    for(x = 0; x < GAME_MAX_X; x++)
    {
        pnt.x = x;

        if(game_get_point(&pnt) == TRUE)
            row_cnt++;
        else
            break;
    }
    DEBUG_LOG();
    return ((row_cnt == GAME_MAX_X) ? TRUE : FALSE);
}

/*****************************************************************************
 �� �� ��  : game_pnt_is_shape
 ��������  : �ж�һ�����Ƿ���shape��
 �������  : game_point_t* pnt    
             game_shape_t* shape  
 �������  : ��
 �� �� ֵ  : TRUE:��, FALSE:����
*****************************************************************************/
int32 game_pnt_is_shape(game_point_t* pnt, game_shape_t* shape)
{
    int32 i = 0;
    game_point_t pnt_t = {0};

    for(i = 0; i < SHAPE_PNT_CNT; i++)
    {
        pnt_t.x = (shape->point).x + (GAME_SHAPE_BOX[shape->index][i]).x;
        pnt_t.y = (shape->point).y + (GAME_SHAPE_BOX[shape->index][i]).y;
        pnt_t.col = (GAME_SHAPE_BOX[shape->index][i]).col;

        if(game_point_cmp(pnt, &pnt_t) == TRUE)
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*****************************************************************************
 �� �� ��  : game_get_maxh_stack
 ��������  : ��õ�ǰ���ѵ��߶�
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��õ�ǰ���ѵ��߶�,���ʧ��,�򷵻�RTN_ERR
*****************************************************************************/
int32 game_get_maxh_stack(void)
{
    game_point_t pnt;
    pnt.col = TRUE;
    for(pnt.y=0; pnt.y<GAME_MAX_Y; pnt.y++)
    {
        for(pnt.x=0; pnt.x<GAME_MAX_X; pnt.x++)
        {//�������,�����ߵ��Ǹ��㲻Ϊ��,���������ǵ�ǰ���߶�
            if(game_get_point(&pnt) == TRUE)
            {
                return (GAME_MAX_Y - 1 - pnt.y);
            }
        }
    }

    return RTN_ERR;
}

/*****************************************************************************
 �� �� ��  : game_get_shape_size
 ��������  : ��ȡshape�Ĵ�С
 �������  : game_shape_t* shape  ����ȡ��С��shape
             int32 flag          flag=0->��ȡx,flag=1->��ȡy 
 �������  : ��
 �� �� ֵ  : shape�Ĵ�С
*****************************************************************************/
int32 game_get_shape_size(game_shape_t* shape, int32 flag)
{
    int32 idx = ((flag == 0) ? 0 : 1);
    if((shape == NULL) || (shape->index >= MAX_SHAPE_CNT))
    {
        return RTN_ERR;
    }

    return(GAME_SHAPE_SIZE[shape->index][idx]);
}

#if 0
/*****************************************************************************
 �� �� ��  : game_point_can_down
 ��������  : �ж�ĳһ�����Ƿ��ܹ�����
 �������  : game_point_t* pnt  ���жϵĵ�
 �������  : ��
 �� �� ֵ  : RTN_OK:������,RTN_ERR:��������
*****************************************************************************/
int32 game_point_can_down(game_point_t* pnt)
{
    game_point_t pnt_t;
    if((pnt == NULL) ||
       (pnt->x < 0) || (pnt->x >= (GAME_MAX_X - 1)) ||
       (pnt->y < 0) || (pnt->y >= (GAME_MAX_Y - 1)))
    {
        return RTN_ERR;
    }


    pnt_t.x = pnt->x;
    pnt_t.y = pnt->y + 1;
    return ((game_get_point(&pnt_t) == FALSE) ? RTN_OK : RTN_ERR);
}
#endif

/*****************************************************************************
 �� �� ��  : game_shape_can_move
 ��������  : �ж�ָ����shape�Ƿ��ܹ�����,����,�����ƶ�
 �������  : game_shape_t* shape  ���жϵ�shape
             game_dir_t dir       shape�ƶ��ķ���
 �������  : ��
 �� �� ֵ  : TRUE:�����ƶ�, FALSE:�������ƶ�
*****************************************************************************/
int32 game_shape_can_move(game_shape_t* shape, game_dir_t dir)
{
    int32 i = 0, dx = 0, dy = 0;
    game_point_t pnt_t = {0};

    DEBUG_LOG();

    switch(dir)
    {
        case DR_DOWN:
            dx = 0;
            dy = 1;
            break;
        case DR_LEFT:
            dx = -1;
            dy = 0;
            break;
        case DR_RIGHT:
            dx = 1;
            dy = 0;
            break;
        default:
            return FALSE;
    }

    for(i = 0; i < SHAPE_PNT_CNT; i++)
    {//����shape�е��ĸ���
        //shape����һ����
        pnt_t.x = (shape->point).x + (GAME_SHAPE_BOX[shape->index][i]).x + dx;
        pnt_t.y = (shape->point).y + (GAME_SHAPE_BOX[shape->index][i]).y + dy;
        pnt_t.col = (shape->point).col;

        if((pnt_t.x < 0) || (pnt_t.x >= GAME_MAX_X) ||
           (pnt_t.y < 0) || (pnt_t.y >= GAME_MAX_Y))
        {
            return FALSE;
        }

        //���shape��ĳ�������һ���㲻�ǿյ�,���������û��shape��,
        //������Ѿ�û������Ŀռ�,�����������
        if((game_get_point(&pnt_t) != FALSE) &&
            (game_pnt_is_shape(&pnt_t, shape) != TRUE))
        {
            DEBUG_LOG("pnt_t,i=%d, x=%d,y=%d,col=%d\n",i, pnt_t.x, pnt_t.y, pnt_t.col);
            return FALSE;
        }
    }

      DEBUG_LOG();

    return TRUE;
}

/*****************************************************************************
 �� �� ��  : game_shape_down
 ��������  : �ж�ȫ��shape�Ƿ��ܹ���������,�������ֱ����ʾ,��������������
 �������  : game_shape_t* _shape  
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�, RTN_ERR:ʧ��
*****************************************************************************/
int32 game_shape_down(game_shape_t* _shape)
{
    if(_shape == NULL)
    {
        return RTN_ERR;
    }

    DEBUG_LOG("idx=%d,x=%d,y=%d,col=%d\n",
        _shape->index, _shape->point.x,
        _shape->point.y, _shape->point.col);

    if(game_shape_can_move(_shape, DR_DOWN) != TRUE)
    {//�Ѿ�û������ռ�,ֱ����ʾ
        DEBUG_LOG("game_shape_down FALSE\n");

        game_show_shpe(_shape);//��ʾ
        return RTN_ERR;
    }
    else
    {//��������ռ�,�����������ʾ
        game_clear_shpe(_shape);
        _shape->point.y += 1;//��������
        game_show_shpe(_shape);
    }

    DEBUG_LOG("idx=%d,x=%d,y=%d,col=%d\n",
        _shape->index, _shape->point.x,
        _shape->point.y, _shape->point.col);

    return RTN_OK;
}

/*****************************************************************************
 �� �� ��  : game_shape_init
 ��������  : ��������һ��ȫ��shape
 �������  : void  
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�
*****************************************************************************/
int32 game_shape_init(void)
{
    glGameShape.point.x = ((GAME_MAX_X-1)/2);
    glGameShape.point.y = 0;
    glGameShape.point.col = TRUE;
    glGameShape.index = game_get_rshape_idx();
    return RTN_OK;
}

/*****************************************************************************
 �� �� ��  : tetris_game_init
 ��������  : ��Ϸ��ʼ��
 �������  : void  
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�
*****************************************************************************/
int32 tetris_game_init(void)
{
    game_clear_screen(FALSE);
    glGameSCore = 0;
    glGameSpeed = GAME_MIN_SPEED;
    glGameLife = TRUE;
    game_shape_init();
    game_draw_point(&(glGameShape.point));
    return RTN_OK;
}


/*****************************************************************************
 �� �� ��  : tetris_game_run
 ��������  : ��Ϸ��ʼ����,����������,����,����
 �������  : void  
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�
*****************************************************************************/
int32 tetris_game_run(void)
{//shapeһֱ�½�,ֱ���޷��½�Ϊֹ
    int32 x=0, y=0, y1=0;
    int32 max_stackh = 0;
    int32 max_y = 0;
    game_point_t pnt;

    if(game_shape_down(&glGameShape) != RTN_OK)
    {//��������������,�������,������һ���µ�shape,���¿�ʼ
        max_stackh = game_get_maxh_stack();
        DEBUG_LOG("max_stackh=%d\n", max_stackh);
        if(max_stackh >= GAME_MAX_Y)
        {
            game_clear_screen(FALSE);
            tetris_game_init();//��Ļ��,��Ϸ����
            glGameLife = FALSE;
            return RTN_OK;
        }

        max_y = (GAME_MAX_Y - 1) - max_stackh;
        for(y=(GAME_MAX_Y-1); y>=max_y; y--)
        {//Ѱ���Ƿ�������
            if(game_line_isfull(y) == TRUE)
            {//�����ǰ��������,�������,������ǰ��,����������
                DEBUG_LOG("line %d isfull\n", y);
                glGameSCore++;
                if((glGameSCore % GAME_SPEED_STEP) == 0)
                {
                    if(glGameSpeed < GAME_MAX_SPEED)
                        glGameSpeed++;
                }

                game_clear_line(y);//��������

                //�����ǰ�в��ǵ�һ��,���ϲ����е�����
                if(y > 0)
                {
                    for(y1=y-1; y1>=max_y; y1--)
                    {
                        for(x=0; x<GAME_MAX_X; x++)
                        {
                            //�ѵ�ǰ������ֵ���Ƶ���һ����
                            pnt.x = x;
                            pnt.y = y1;
                            if(game_get_point(&pnt) == TRUE)
                            {
                                //�����ǰ�����
                                pnt.col = FALSE;
                                game_draw_point(&pnt);
                                pnt.col = TRUE;
                                pnt.y = y1 + 1;
                                game_draw_point(&pnt);
                            }
                        }
                    }

                    //��Ϊ�ϲ������ж�������һ��,����Ҫ��
                    //�������¶�λ����ǰ���ٴν����ж�
                    y += 1;
                }
            }
        }


        game_shape_init();//���²���һ��shape
        if((game_get_shape_size(&glGameShape, 1) - 1) >
            (GAME_MAX_X - 1 - max_stackh))//�Ѿ�û�пռ���
        {
            game_clear_screen(FALSE);
        }
    }

    DEBUG_LOG("glGameShape,idx=%d,x=%d,y=%d,col=%d\n\n",
        glGameShape.index, glGameShape.point.x,
        glGameShape.point.y, glGameShape.point.col);

    return RTN_OK;
}

/*****************************************************************************
 �� �� ��  : tetris_shape_deform
 ��������  : ȫ��shape����
 �������  : void  
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�
*****************************************************************************/
int32 tetris_shape_deform(void)
{
    if(game_shape_can_move(&glGameShape, DR_DOWN) != TRUE)
    {
        return RTN_ERR;
    }

    if(game_shape_can_move(&glGameShape, DR_RIGHT) != TRUE)
    {
        return RTN_ERR;
    }

    game_clear_shpe(&glGameShape);
    if((glGameShape.index % 4) <  (MAX_EXT_SHAPE_CNT - 1))
    {
        glGameShape.index += 1;
    }
    else
    {
        glGameShape.index = ((int32)(glGameShape.index / 4) * 4);
    }
    game_show_shpe(&glGameShape);
    return RTN_OK;
}

/*****************************************************************************
 �� �� ��  : tetris_shape_move
 ��������  : ʹȫ��shape��ָ�������ƶ�
 �������  : game_dir_t dir  ȫ��shape�ƶ��ķ���
 �������  : ��
 �� �� ֵ  : RTN_OK:�ɹ�
*****************************************************************************/
int32 tetris_shape_move(game_dir_t dir)
{
    if(game_shape_can_move(&glGameShape, dir) != TRUE)
    {
        return RTN_ERR;
    }

    switch(dir)
    {
        case DR_DOWN:
            game_clear_shpe(&glGameShape);
            glGameShape.point.y += 1;
            break;
        case DR_LEFT:
            if(glGameShape.point.x > 0)
            {
                game_clear_shpe(&glGameShape);
                glGameShape.point.x -= 1;
            }
            break;
        case DR_RIGHT:
            if(glGameShape.point.x < (GAME_MAX_X - 1))
            {
                game_clear_shpe(&glGameShape);
                glGameShape.point.x += 1;
            }
            break;
        default:
            break;
    }

    game_show_shpe(&glGameShape);
    return RTN_OK;
}

/*****************************************************************************
 �� �� ��  : tetris_get_life
 ��������  : ��ȡ��Ϸ����ֵ
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ����ֵ
*****************************************************************************/
int32 tetris_get_life(void)
{
    return glGameLife;
}

/*****************************************************************************
 �� �� ��  : tetris_get_score
 ��������  : �����Ϸ�÷�
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ�÷�
*****************************************************************************/
int32 tetris_get_score(void)
{
    return glGameSCore;
}

/*****************************************************************************
 �� �� ��  : tetris_get_speed
 ��������  : �����Ϸ�ٶ�
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ�ٶ�
*****************************************************************************/
int32 tetris_get_speed(void)
{
    return glGameSpeed;
}

/*****************************************************************************
 �� �� ��  : tetris_add_speed
 ��������  : ��Ϸ�ٶȼӿ�
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ�ٶ�
*****************************************************************************/
int32 tetris_add_speed(void)
{
    if(glGameSpeed < GAME_MAX_SPEED)
        glGameSpeed++;

    return glGameSpeed;
}

/*****************************************************************************
 �� �� ��  : tetris_sub_speed
 ��������  : ��Ϸ�ٶȼ���
 �������  : void  
 �������  : ��
 �� �� ֵ  : ��Ϸ�ٶ�
*****************************************************************************/
int32 tetris_sub_speed(void)
{
    if(glGameSpeed > GAME_MIN_SPEED)
        glGameSpeed--;

    return glGameSpeed;
}