/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include <windows.h>
#include <string.h>
#include "lcd_snake.h"

/*----------------------------------------------*
 * 自定义数据类型                               *
 *----------------------------------------------*/
typedef enum snake_propy//属性
{
    PR_FOOD = 0,        //0食物
    PR_HEAD,            //1蛇头
    PR_BODY,            //2身体
    PR_WALL,            //3墙壁
    PR_NULL             //空白
} SNAKE_PROPY;

typedef enum snake_col//颜色
{
    COL_BLACK = 0,      //0黑色表示不显示
    COL_WHITE,          //1白色表示显示
} SNAKE_COL;

typedef struct snake_point//位置
{
    int32               PT_LOCX;//X坐标
    int32               PT_LOCY;//Y坐标
    SNAKE_COL           PT_COLOR;
} SNAKE_POINT;

typedef struct snake//蛇
{
    SNAKE_POINT         S_POINT;//坐标
    SNAKE_PROPY         S_PROPERTY;//属性
} SNAKE;

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define SnakeMaxX       (SCREEN_X)//屏幕长度
#define SnakeMaxY       (SCREEN_Y)//屏幕宽度
#define SnakePtSize     1//蛇身点大小，单位:像素，蛇身点为正方形
#define SNAKE_MAX_SPEED 10
#define SNAKE_MIN_SPEED 1

#define SnakePointX     (SnakePtSize)//蛇身点大小，单位:像素，蛇身点为正方形
#define SnakePointY     (SnakePointX)//蛇身点大小
#define SnakeStepX      ((SnakeMaxX) / (SnakePointX))//移动步数
#define SnakeStepY      ((SnakeMaxY) / (SnakePointY))//移动步数
#define SnakeMaxLen     ((SnakeStepX) * (SnakeStepY) / 2)//蛇身最大长度

/*----------------------------------------------*
 * 内部静态变量                                 *
 *----------------------------------------------*/
static SNAKE        SNAKE_FOOD;//食物
static SNAKE        GAME_SNAKE[SnakeMaxLen];//蛇
//static SNAKE        GAME_MAP[SnakeMaxLen];//地图
static int32        SnakeCount = 2;//蛇身长度
static SNAKE_DIR    SnakeDir = DR_RIGHT;//蛇头移动方向
static SNAKE_LIFE   SnakeLife = LF_LIVE;//游戏进程
static int32        SnakeScore = 0;//得分
static int32        SnakeSpeed = SNAKE_MIN_SPEED;//速度
static int32        SCORE_STEP = 10;//每吃到10个食物速度加快一级
static int32        SCROSS_WALL = TRUE;//允许越界

/*****************************************************************************
 函 数 名  : snake_draw_point
 功能描述  : 使用缩放过后的DPI绘制一个蛇身点
 输入参数  : SNAKE_POINT* s_point
 输出参数  : 无
 返 回 值  : 成功返回0，失败返回1
 函数说明  :
 *****************************************************************************/
int32 snake_draw_point(const SNAKE_POINT* const s_point)
{
    int32 x = 0, y = 0, col = 0;

    if(s_point == RTN_NULL)
        return RTN_ERR;

    x = s_point->PT_LOCX;
    y = s_point->PT_LOCY;
    col = s_point->PT_COLOR;

    x = ((x < 0) ? 0 : ((x >= SnakeStepX) ? (SnakeStepX - 1) : x));
    y = ((y < 0) ? 0 : ((y >= SnakeStepY) ? (SnakeStepY - 1) : y));
    x = x * SnakePointX;
    y = y * SnakePointY;

    if(SnakePointX != 1) //画一个矩形代表缩放过后的点
        gdi_rectangle(x, y, x + SnakePointX - 1, y + SnakePointY - 1, col, 1);
    else//为了加快速度，宽度为1不缩放，直接画点
        gdi_set_point(x, y, col);

    return RTN_OK;
}

/*****************************************************************************
 函 数 名  : snake_get_point
 功能描述  : 获取屏幕上某个点的颜色
 输入参数  : SNAKE_POINT* s_point
 输出参数  : 无
 返 回 值  : 返回指定的点的颜色(1或0)
 函数说明  :
 *****************************************************************************/
int32 snake_get_point(const SNAKE_POINT* const s_point)
{
    int32 x = 0, y = 0;

    if(s_point == RTN_NULL)
        return RTN_ERR;

    x = s_point->PT_LOCX;
    y = s_point->PT_LOCY;

    x = ((x < 0) ? 0 : ((x >= SnakeStepX) ? (SnakeStepX - 1) : x));
    y = ((y < 0) ? 0 : ((y >= SnakeStepY) ? (SnakeStepY - 1) : y));

    x = x * SnakePointX;
    y = y * SnakePointY;

    return(((gdi_get_point(x, y)) == TRUE) ? COL_WHITE : COL_BLACK);
}

int32 snake_clear_allpnt(SNAKE_COL col)
{
    gdi_clear(col);
    return RTN_OK;
}

/*****************************************************************************
 函 数 名  : snake_get_randxy
 功能描述  : 生成一个随机的坐标点
 输入参数  : SNAKE_POINT* s_point
 输出参数  : 无
 返 回 值  : 成功返回改点，失败返回NULL
 函数说明  :
 *****************************************************************************/
void* snake_get_randxy(SNAKE_POINT* s_point)
{
    static uint32 sseed = 0;
    srand(sseed);

    if(s_point == RTN_NULL)
        return RTN_NULL;

    s_point->PT_LOCX = rand() % SnakeStepX;
    s_point->PT_LOCY = rand() % SnakeStepY;
    sseed = (s_point->PT_LOCX) * (s_point->PT_LOCX);
    return s_point;
}

/*****************************************************************************
 函 数 名  : snake_create_food
 功能描述  : 产生一个点，点的位置是随机的，并且该位置未被占用
 输入参数  : SNAKE* food:要生成的点
 SNAKE_PROPY spropy:指定要产生的点的属性(食物?蛇头?蛇身?)
 输出参数  : 无
 返 回 值  :
 函数说明  :
 *****************************************************************************/
void* snake_create_food(SNAKE* food, SNAKE_PROPY spropy)
{
    SNAKE_POINT foodxy;

    int32 n = 1;

    if(food == RTN_NULL)
        return RTN_NULL;

    while(n++) //寻找可以放置食物的随机点
    {
        snake_get_randxy(&foodxy);//生成一个随机点

        if(snake_get_point(&foodxy) == COL_BLACK)
        {
            break;//食物不在蛇身或者围墙上
        }

        if(n > SnakeStepX * SnakeStepY)
        {
            n = 0;
            return RTN_NULL;//尝试完所有的点之后次任然不成功则退出
        }
    }

    foodxy.PT_COLOR = COL_WHITE;
    food->S_POINT.PT_LOCX = foodxy.PT_LOCX;
    food->S_POINT.PT_LOCY = foodxy.PT_LOCY;
    food->S_POINT.PT_COLOR = foodxy.PT_COLOR;
    food->S_PROPERTY = spropy;

    snake_draw_point(&foodxy);

    return food;
}

/*****************************************************************************
 函 数 名  : snake_game_init
 功能描述  : 贪吃蛇游戏初始化
 输入参数  : int32 scnt:初始的蛇身长度
 SNAKE_DIR sdir:初始的蛇头方向
 int32 sstep:得分速度
 int32 speed:速度
 输出参数  : 无
 返 回 值  :
 函数说明  :
 *****************************************************************************/
int32 snake_game_init(int32 scnt, SNAKE_DIR sdir, int32 sstep, int32 cwall)
{
    int32 dx = 0, dy = 0, i = 0;

    scnt = ((scnt < 3) ? 3 : ((scnt > SnakeMaxLen) ? (SnakeMaxLen) : scnt));

    SnakeLife = LF_LIVE;//游戏进程
    SnakeCount = scnt - 1;//蛇身长度
    SnakeScore = 0;//得分
    snake_set_dir(sdir);//蛇头移动方向
    snake_set_scstep(sstep);//步进单位
    snake_set_speed(SNAKE_MIN_SPEED);
    snake_set_crosswall(cwall);

    memset(GAME_SNAKE, 0, sizeof(GAME_SNAKE));

    //随机产生一个蛇头
    if(snake_create_food(&(GAME_SNAKE[0]), PR_HEAD) == RTN_NULL)
        return RTN_ERR;//生成蛇头失败

    switch(snake_get_dir())
    {
    case DR_UP://上
    {
        dx = 0;
        dy = 1;
        break;
    }

    case DR_DOWN://下
    {
        dx = 0;
        dy = -1;
        break;
    }

    case DR_LEFT://左
    {
        dx = 1;
        dy = 0;
        break;
    }

    default://右
    {
        dx = -1;
        dy = 0;
        break;
    }
    }

    //绘制蛇身
    for(i = 1; i <= SnakeCount; i++)
    {
        GAME_SNAKE[i].S_POINT.PT_LOCX = \
                                        GAME_SNAKE[i - 1].S_POINT.PT_LOCX + dx;
        GAME_SNAKE[i].S_POINT.PT_LOCY = \
                                        GAME_SNAKE[i - 1].S_POINT.PT_LOCY + dy;
        GAME_SNAKE[i].S_POINT.PT_COLOR = COL_WHITE;
        GAME_SNAKE[i].S_PROPERTY = PR_BODY;
        snake_draw_point(&(GAME_SNAKE[i].S_POINT));
    }

    //产生一个食物
    if(snake_create_food(&SNAKE_FOOD, PR_FOOD) == RTN_NULL)
        return RTN_ERR;

    return RTN_OK;
}

static void __snake_copy_body(SNAKE* dst, SNAKE* src)
{
#if 1
    memcpy(dst, src, sizeof(SNAKE));
#else
    dst->S_POINT.PT_LOCX = src->S_POINT.PT_LOCX;
    dst->S_POINT.PT_LOCY  = src->S_POINT.PT_LOCY;
    dst->S_POINT.PT_COLOR = src->S_POINT.PT_COLOR;
    dst->S_PROPERTY       = src->S_PROPERTY;
#endif
}

static int32 __snake_redraw_body(void)
{
    int32 i = 0;
    snake_clear_allpnt(COL_BLACK);

    for(i = 0; i <= SnakeCount; i++)
    {
        if(snake_draw_point(&(GAME_SNAKE[i].S_POINT)) != RTN_OK)
            return RTN_ERR;
    }

    if(snake_draw_point(&(SNAKE_FOOD.S_POINT)) != RTN_OK)
        return RTN_ERR;

    return RTN_OK;
}

static int32 _snake_cmp_pntxy(SNAKE_POINT* p0, SNAKE_POINT* p1)
{
    if((p0->PT_LOCX == p1->PT_LOCX) && (p0->PT_LOCY == p1->PT_LOCY))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*****************************************************************************
 函 数 名  : snake_move_step
 功能描述  : 控制蛇向前移动一步，并处理移动过程中需要处理的事件
 输入参数  : SNAKE_DIR Dir
 输出参数  : 无
 返 回 值  : 返回当前的生命状态
 函数说明  :
 *****************************************************************************/
SNAKE_LIFE snake_move_step(SNAKE_DIR Dir)
{
    int32 dx = 0, dy = 0;
    int32 n = 0, i = 0, eatyourself_n = 0;
    SNAKE s_tail;

    //判断移动方向
    if(Dir == DR_UP) //上
    {
        dx = 0;
        dy = -1;
    }
    else if(Dir == DR_DOWN) //下
    {
        dx = 0;
        dy = 1;
    }
    else if(Dir == DR_LEFT) //左
    {
        dx = -1;
        dy = 0;
    }
    else//右
    {
        dx = 1;
        dy = 0;
    }

    //保存蛇尾坐标
    __snake_copy_body(&s_tail, &(GAME_SNAKE[SnakeCount]));

    //更新蛇身坐标
    for(n = SnakeCount; n > 0; n--)
    {
        __snake_copy_body(&(GAME_SNAKE[n]), &(GAME_SNAKE[n - 1]));
    }

    //更新蛇头坐标
    GAME_SNAKE[0].S_POINT.PT_LOCX += dx;
    GAME_SNAKE[0].S_POINT.PT_LOCY += dy;

    //判断蛇的状态:吃到食物?咬到自己?撞到墙?
    if(snake_get_point(&(GAME_SNAKE[0].S_POINT)) == COL_WHITE)
    {
        if(_snake_cmp_pntxy(&(GAME_SNAKE[0].S_POINT), &(SNAKE_FOOD.S_POINT)) == TRUE)
        {
            //吃到食物
            if(snake_create_food(&SNAKE_FOOD, PR_FOOD) != RTN_NULL)
            {
                //产生食物成功
                //蛇身长度增加
                __snake_copy_body(&(GAME_SNAKE[++SnakeCount]), &s_tail);

                if(SnakeCount >= SnakeMaxLen)
                    SnakeLife = LF_WIN;//达到最大长度则通关

                SnakeScore++;//分数增加

                if(SnakeScore % SCORE_STEP == 0)
                {
                    snake_add_speed();
                }
            }
            else//产生食物不成功,说明此时屏幕上几乎没有可用空间了
            {
                SnakeLife = LF_WIN;//这种情况认定为通关
            }
        }
        else if(SnakeCount > 4) //只有长度大于4才可能成环，这样做可以加快速度
        {
            for(i = SnakeCount; i > 0; i--) //从后往前遍历，这样做可以加快速度（也许）
            {
                if(_snake_cmp_pntxy(&(GAME_SNAKE[0].S_POINT), &(GAME_SNAKE[i].S_POINT)) == TRUE)
                {
                    SnakeLife = LF_DIE;//咬到自己或撞到墙则死亡
                    break;
                }
            }
        }
    }

    //越界处理
    if(SCROSS_WALL == TRUE)
    {
        //允许越界
        if(GAME_SNAKE[0].S_POINT.PT_LOCX >= SnakeStepX)
            GAME_SNAKE[0].S_POINT.PT_LOCX = 0;

        if(GAME_SNAKE[0].S_POINT.PT_LOCX < 0)
            GAME_SNAKE[0].S_POINT.PT_LOCX = SnakeStepX - 1;

        if(GAME_SNAKE[0].S_POINT.PT_LOCY >= SnakeStepY)
            GAME_SNAKE[0].S_POINT.PT_LOCY = 0;

        if(GAME_SNAKE[0].S_POINT.PT_LOCY < 0)
            GAME_SNAKE[0].S_POINT.PT_LOCY = SnakeStepY - 1;
    }
    else
    {
        //不允许越界
        if((GAME_SNAKE[0].S_POINT.PT_LOCX >= SnakeStepX) || \
                (GAME_SNAKE[0].S_POINT.PT_LOCX < 0) || \
                (GAME_SNAKE[0].S_POINT.PT_LOCY >= SnakeStepY) || \
                (GAME_SNAKE[0].S_POINT.PT_LOCY < 0))
        {
            if(SnakeLife == LF_LIVE)
                SnakeLife = LF_DIE;//碰到边界则死亡
        }
    }

    //更新显示蛇
    __snake_redraw_body();
    return SnakeLife;
}

/*****************************************************************************
 函 数 名  : snake_move_control
 功能描述  : 根据按键值控制蛇移动
 输入参数  : SNAKE_DIR KEY
 输出参数  : 无
 返 回 值  : 返回玩家当前的生命状态
 函数说明  : 没有单独的游戏状态处理函数，使用者必须在自己的主函数中根据
 该函数返回的生命状态来处理游戏进度(比如说当SnakeLife为LF_DIE的
 时候该做什么事，这些需要有使用本函数的人自己完成)
 *****************************************************************************/
SNAKE_LIFE snake_move_control(SNAKE_DIR KEY)
{
    //只有按下上下左右键才有反应
    if(((KEY == DR_UP) && (SnakeDir != DR_DOWN)) || \
            ((KEY == DR_DOWN) && (SnakeDir != DR_UP)) || \
            ((KEY == DR_LEFT) && (SnakeDir != DR_RIGHT)) || \
            ((KEY == DR_RIGHT) && (SnakeDir != DR_LEFT)))//不能反向移动
    {
        SnakeDir = KEY;//更新移动方向
    }

    return(snake_move_step(SnakeDir));//按照按键方向移动
}

/*****************************************************************************
 函 数 名  : snake_get_score
 功能描述  : 获取当前游戏得分
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 游戏得分
 函数说明  :
 *****************************************************************************/
int32 snake_get_score(void)
{
    return SnakeScore;
}

/*****************************************************************************
 函 数 名  : snake_get_speed
 功能描述  : 获取当前速度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 速度
 函数说明  :
 *****************************************************************************/
int32 snake_get_speed(void)
{
    return SnakeSpeed;
}

/*****************************************************************************
 函 数 名  : snake_set_speed
 功能描述  : 设置当前速度
 输入参数  : int32 speed
 输出参数  : 无
 返 回 值  : 速度
 函数说明  :
 *****************************************************************************/
int32 snake_set_speed(int32 speed)
{
    SnakeSpeed = ((speed < SNAKE_MIN_SPEED) ? SNAKE_MIN_SPEED :
                  ((speed > SNAKE_MAX_SPEED) ? SNAKE_MAX_SPEED : speed));
    return SnakeSpeed;
}

/*****************************************************************************
 函 数 名  : snake_sub_speed
 功能描述  : 让速度减小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 速度
 函数说明  :
 *****************************************************************************/
int32 snake_sub_speed(void)
{
    if(SnakeSpeed > SNAKE_MIN_SPEED)
        SnakeSpeed--;

    return SnakeSpeed;
}

/*****************************************************************************
 函 数 名  : snake_add_speed
 功能描述  : 让速度增大
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 速度
 函数说明  :
 *****************************************************************************/
int32 snake_add_speed(void)
{
    if(SnakeSpeed < SNAKE_MAX_SPEED)
        SnakeSpeed++;

    return SnakeSpeed;
}

/*****************************************************************************
 函 数 名  : snake_get_life
 功能描述  : 获取当前游戏生命值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前游戏生命值
 函数说明  :
 *****************************************************************************/
SNAKE_LIFE snake_get_life(void)
{
    return SnakeLife;
}

/*****************************************************************************
 函 数 名  : snake_set_scstep
 功能描述  : 设置游戏得分步进
 输入参数  : int32 scstep
 输出参数  : 无
 返 回 值  : 游戏得分步进
 函数说明  :
 *****************************************************************************/
int32 snake_set_scstep(int32 scstep)
{
    SCORE_STEP = ((scstep <= 0) ? 10 : scstep);
    return SCORE_STEP;
}

/*****************************************************************************
 函 数 名  : snake_get_dir
 功能描述  : 获取当前蛇头方向
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前蛇头方向
 函数说明  :
 *****************************************************************************/
SNAKE_DIR snake_get_dir(void)
{
    return SnakeDir;
}

/*****************************************************************************
 函 数 名  : snake_set_dir
 功能描述  : 设置当前蛇头方向
 输入参数  : SNAKE_DIR sdir
 输出参数  : 无
 返 回 值  : 当前蛇头方向
 函数说明  :
 *****************************************************************************/
SNAKE_DIR snake_set_dir(SNAKE_DIR sdir)
{
#if 1

    if((sdir == DR_UP) || (sdir == DR_DOWN) || \
            (sdir == DR_LEFT) || (sdir == DR_RIGHT))
        SnakeDir = sdir;

#else
    SnakeDir = ((sdir < DR_UP) ? DR_UP : ((sdir > DR_RIGHT) ? DR_RIGHT : sdir));
#endif
    return SnakeDir;
}

/*****************************************************************************
 函 数 名  : snake_set_crosswall
 功能描述  : 设置是否允许越界
 输入参数  : int32 crosswall
 输出参数  : 无
 返 回 值  : 无
 函数说明  : 非零表示允许越界
 *****************************************************************************/
void snake_set_crosswall(int32 crosswall)
{
    SCROSS_WALL = ((crosswall) ? TRUE : FALSE);
}
