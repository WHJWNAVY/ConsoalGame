#if 0

#include <windows.h> //为了使用API函数
#include <time.h> //为了使用定时器
#include <stdlib.h>  //为了使用随机数

#define bool            int
#define true            1
#define false           0
#define inline

#define BLOCKWIDTH      20  //单个方块大小
#define NUMLINEBLOCKS   18  //行数
#define NUMCOLUMNBLOCKS 10  //列数
#define ID_TIMER        1   //定时器ID
#define BLOCKSTYLES     (sizeof (Blocks) / sizeof (Blocks[0]))  //方块的种类数

//游戏区各方格顶点布尔值，代表该方格是否有方块
bool    GameClient[NUMCOLUMNBLOCKS][NUMLINEBLOCKS];
static int      F, S, cF, cS;   //随机方块图形对应的第一、二纬
static int      Score;  //得分

//定义各方块形状，以点表示
struct
{
    POINT   pt[4];
}
Blocks[][4] =
{
    //正7
    0, 0, 1, 0, 1, 1, 1, 2, 2, 0, 0, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 2, 2, 2, 0, 1, 1, 1, 2, 1, 0, 2,
    //反7
    1, 0, 2, 0, 1, 1, 1, 2, 0, 1, 1, 1, 2, 1, 2, 2, 1, 0, 1, 1, 0, 2, 1, 2, 0, 0, 0, 1, 1, 1, 2, 1,
    //1
    1, 0, 1, 1, 1, 2, 1, 3, 0, 1, 1, 1, 2, 1, 3, 1, 1, 0, 1, 1, 1, 2, 1, 3, 0, 1, 1, 1, 2, 1, 3, 1,
    //Z
    0, 0, 1, 0, 1, 1, 2, 1, 2, 0, 1, 1, 2, 1, 1, 2, 0, 0, 1, 0, 1, 1, 2, 1, 2, 0, 1, 1, 2, 1, 1, 2,
    //反Z
    1, 0, 2, 0, 0, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 1, 0, 2, 0, 0, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2,
    //田字
    0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1,
    //尖头
    1, 0, 0, 1, 1, 1, 2, 1, 0, 0, 0, 1, 1, 1, 0, 2, 0, 0, 1, 0, 2, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 2
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wndcls;
    TCHAR szClassName[] = TEXT("Terics"),
                          szWindowName[] = TEXT("Aka's Terics");
    static POINT Block[4];

    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
    wndcls.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wndcls.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wndcls.hInstance = hInstance;
    wndcls.lpfnWndProc = WndProc;
    wndcls.lpszClassName = szClassName;
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wndcls);

    HWND hwnd = CreateWindow(szClassName, szWindowName, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
                             CW_USEDEFAULT, CW_USEDEFAULT, (NUMCOLUMNBLOCKS + 10) * BLOCKWIDTH,
                             (NUMLINEBLOCKS + 3) * BLOCKWIDTH,
                             NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

//随机数函数定制版，用于随机出现的方块
unsigned Random(int n);

//判断是否可以下落，可以则返回true
bool CanDown(POINT pt[]);

//下落实现
void Down(POINT pt[]);

//判断是否可以左移
bool CanLeft(POINT pt[]);

//实现左移
void Left(POINT pt[]);

//判断是否可以右移
bool CanRight(POINT pt[]);

//实现右移
void Right(POINT pt[]);

//判断是否可以变形
bool CanChange(POINT pt[]);

//实现变形
void Change(POINT pt[]);

//消行处理以及分数结算
void DelSqure(HWND);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT       TericsBorder[] = { -1, -1,
                                   NUMCOLUMNBLOCKS * BLOCKWIDTH + 1, NUMLINEBLOCKS * BLOCKWIDTH + 1
                                 };
    HDC         hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC  tm;
    TCHAR       szNextTerics[] = TEXT("下一个："),
                                 szSCore[] = TEXT("得分：");
    static TCHAR szBufferScore[5];
    static int  cxChar, cyChar;
    static POINT Block[4], NextBlock[4];
    int         x, y;
    static bool     pause = false;  //暂停

    switch(message)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);

        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth * 2;
        cyChar = tm.tmExternalLeading + tm.tmHeight;
        SetTimer(hwnd, ID_TIMER, 600, NULL);
        //初始化第一个出现的方块
        cS = Random(4);
        cF = Random(BLOCKSTYLES);

        for(int i = 0; i < 4; ++i)
        {
            Block[i].x = Blocks[cF][cS].pt[i].x + 4;
            Block[i].y = Blocks[cF][cS].pt[i].y;
            GameClient[Block[i].x][Block[i].y] = true;
        }

        S = Random(4);
        F = Random(BLOCKSTYLES);

        for(int i = 0; i < 4; ++i)
        {
            NextBlock[i].x = Blocks[F][S].pt[i].x;
            NextBlock[i].y = Blocks[F][S].pt[i].y;
        }

        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_TIMER:
        if(pause) return 0;

        if(CanDown(Block))
        {
            Down(Block);
        }
        //不能下移，需要处理消行判断（结合分数），还需要处理下一个显示，和当前显示的方块
        else
        {
            DelSqure(hwnd);

            for(int i = 0; i < 4; ++i)
            {
                Block[i].x = NextBlock[i].x + 4;
                Block[i].y = NextBlock[i].y;

                if(GameClient[Block[i].x][Block[i].y])
                {
                    KillTimer(hwnd, ID_TIMER);
                }
                else
                    GameClient[Block[i].x][Block[i].y] = true;
            }

            cS = S;
            cF = F;
            S = Random(4);
            F = Random(BLOCKSTYLES);

            for(int i = 0; i < 4; ++i)
            {
                NextBlock[i].x = Blocks[F][S].pt[i].x;
                NextBlock[i].y = Blocks[F][S].pt[i].y;
            }
        }

        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_KEYDOWN:
        if(pause && wParam != VK_PAUSE) return 0;

        switch(wParam)
        {
        case VK_LEFT:
            if(CanLeft(Block))
                Left(Block);

            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case VK_RIGHT:
            if(CanRight(Block))
                Right(Block);

            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case VK_UP:
            if(CanChange(Block))
                Change(Block);

            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case VK_DOWN:
            while(CanDown(Block))
                Down(Block);

            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case VK_PAUSE:
            pause = !pause;
            break;

        default:
            break;
        }

        return 0;

    case WM_CHAR:
        if(wParam == 'p')
            pause = !pause;
        else if(wParam == 'r')
        {
            Score = 0;

            for(int x = 0; x < NUMCOLUMNBLOCKS; ++x)
            {
                for(int y = 0; y < NUMLINEBLOCKS; ++y)
                    GameClient[x][y] = false;
            }

            cS = Random(4);
            cF = Random(BLOCKSTYLES);

            for(int i = 0; i < 4; ++i)
            {
                Block[i].x = Blocks[cF][cS].pt[i].x + 4;
                Block[i].y = Blocks[cF][cS].pt[i].y;
                GameClient[Block[i].x][Block[i].y] = true;
            }

            S = Random(4);
            F = Random(BLOCKSTYLES);

            for(int i = 0; i < 4; ++i)
            {
                NextBlock[i].x = Blocks[F][S].pt[i].x;
                NextBlock[i].y = Blocks[F][S].pt[i].y;
            }

            pause = false;
            InvalidateRect(hwnd, NULL, TRUE);
        }

        return 0;

    case WM_PAINT:
        //if(pause) return 0;
        hdc = BeginPaint(hwnd, &ps);
        SetViewportOrgEx(hdc, BLOCKWIDTH, BLOCKWIDTH, NULL);
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        SelectObject(hdc, GetStockObject(BLACK_PEN));

        //画俄罗斯方块游戏的边框
        Rectangle(hdc, TericsBorder[0].x, TericsBorder[0].y,
                  TericsBorder[1].x, TericsBorder[1].y);
        //输出“下一个”字符串
        TextOut(hdc, (NUMCOLUMNBLOCKS + 1) * BLOCKWIDTH, 0, szNextTerics, lstrlen(szNextTerics));

        //输出“得分”字符串
        TextOut(hdc, (NUMCOLUMNBLOCKS + 1) * BLOCKWIDTH, cyChar + 5 * BLOCKWIDTH,
                szSCore, lstrlen(szSCore));
        //
        SetTextAlign(hdc, TA_RIGHT | TA_TOP);
        TextOut(hdc, (NUMCOLUMNBLOCKS + 1) * BLOCKWIDTH + 3 * cxChar, 2 * cyChar + 5 * BLOCKWIDTH,
                szBufferScore, wsprintf(szBufferScore, TEXT("%d"), Score));
        SetTextAlign(hdc, TA_LEFT | TA_TOP);

        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
        SelectObject(hdc, GetStockObject(WHITE_PEN));

        //显示游戏区的方块
        for(x = 0; x < NUMCOLUMNBLOCKS; ++x)
        {
            for(y = 0; y < NUMLINEBLOCKS; ++y)
            {
                if(GameClient[x][y])
                {
                    Rectangle(hdc, x * BLOCKWIDTH, y * BLOCKWIDTH,
                              (x + 1) * BLOCKWIDTH, (y + 1) * BLOCKWIDTH);
                }
            }
        }

        //显示下一个方块区域的方块
        for(int i = 0; i < 4; ++i)
        {
            Rectangle(hdc, (NextBlock[i].x + NUMCOLUMNBLOCKS + 2) * BLOCKWIDTH, NextBlock[i].y * BLOCKWIDTH + cyChar,
                      (NextBlock[i].x + NUMCOLUMNBLOCKS + 3) * BLOCKWIDTH, (NextBlock[i].y + 1) * BLOCKWIDTH + cyChar);
        }

        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

//判断方块是否可以下落
bool CanDown(POINT pt[])
{
    bool result = true;

    //将方块所在格子先假设指定为无方块
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = false;

    for(int i = 0; i < 4; ++i)
    {
        //假如继续落下超过下底边界，返回false；或者假如该小方块下落一格已经有方块，结果为false
        if(pt[i].y + 1 == NUMLINEBLOCKS || GameClient[pt[i].x][pt[i].y + 1])
        {
            result = false;
            break;
        }
    }

    //恢复方块所在格子为有方块
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = true;

    return result;
}


//判断是否可以左移
bool CanLeft(POINT pt[])
{
    bool result = true;

    //将方块所在格子先假设指定为无方块
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = false;

    for(int i = 0; i < 4; ++i)
    {
        //假如继续左移超过左边边界，返回false；或者假如该小方块左移一格已经有方块，结果为false
        if(!pt[i].x || GameClient[pt[i].x - 1][pt[i].y])
        {
            result = false;
            break;
        }
    }

    //恢复方块所在格子为有方块
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = true;

    return result;
}

//判断是否可以右移
bool CanRight(POINT pt[])
{
    bool result = true;

    //将方块所在格子先假设指定为无方块
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = false;

    for(int i = 0; i < 4; ++i)
    {
        //假如继续左移超过左边边界，返回false；或者假如该小方块左移一格已经有方块，结果为false
        if(pt[i].x + 1 == NUMCOLUMNBLOCKS || GameClient[pt[i].x + 1][pt[i].y])
        {
            result = false;
            break;
        }
    }

    //恢复方块所在格子为有方块
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = true;

    return result;
}

//判断是否可以旋转
bool CanChange(POINT pt[])
{
    bool result = true;

    //将方块所在格子先假设指定为无方块
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = false;

    int t = (cS + 1) % 4;

    for(int k = 0; k < 4; ++k)
    {
        int x = Blocks[cF][t].pt[k].x - Blocks[cF][cS].pt[k].x,
            y = Blocks[cF][t].pt[k].y - Blocks[cF][cS].pt[k].y;

        if(GameClient[pt[k].x + x][pt[k].y + y] ||   //该方格已经有方块
                pt[k].x + x > NUMCOLUMNBLOCKS - 1 ||  //x坐标超越了右边界
                pt[k].x + x < 0 ||   //x坐标超越了左边界
                pt[k].y + y > NUMLINEBLOCKS - 1)  //y坐标超越了下底边界
        {
            result = false;
            break;
        }
    }

    //恢复方块所在格子为有方块
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = true;

    return result;
}

//实现旋转
void Change(POINT pt[])
{
    int t = (cS + 1) % 4;

    for(int i = 0; i < 4; ++i)
    {
        int x = Blocks[cF][t].pt[i].x - Blocks[cF][cS].pt[i].x,
            y = Blocks[cF][t].pt[i].y - Blocks[cF][cS].pt[i].y;
        GameClient[pt[i].x][pt[i].y] = false;
        pt[i].x += x;
        pt[i].y += y;
        GameClient[pt[i].x][pt[i].y] = true;
    }

    cS = t;
}

//实现右移
void Right(POINT pt[])
{
    for(int i = 0; i < 4; ++i)
    {
        GameClient[pt[i].x][pt[i].y] = false;
        ++pt[i].x;
    }

    for(int k = 0; k < 4; ++k)
        GameClient[pt[k].x][pt[k].y] = true;
}

//实现左移
void Left(POINT pt[])
{
    for(int i = 0; i < 4; ++i)
    {
        GameClient[pt[i].x][pt[i].y] = false;
        --pt[i].x;
    }

    for(int k = 0; k < 4; ++k)
        GameClient[pt[k].x][pt[k].y] = true;
}

//实现方块的下落
void Down(POINT pt[])
{
    for(int i = 0; i < 4; ++i)
    {
        GameClient[pt[i].x][pt[i].y] = false;
        ++pt[i].y;
    }

    for(int k = 0; k < 4; ++k)
        GameClient[pt[k].x][pt[k].y] = true;
}

//随机数函数定制版
inline unsigned int Random(int n)
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    srand(st.wMilliseconds);
    return rand() % n;
}

//消行处理以及分数结算
void DelSqure(HWND hwnd)
{
    int line = 0, temp;

    for(int x = NUMLINEBLOCKS - 1; x >= 0; --x)
    {
        bool result = true;

        for(int y = 0; y < NUMCOLUMNBLOCKS; ++y)
        {
            if(!GameClient[y][x])
            {
                result = false;
                break;
            }
        }

        //判断是否可以消行
        if(result)
        {
            temp = x;
            ++line;

            while(x > 0)
            {
                for(int y = 0; y < NUMCOLUMNBLOCKS; ++y)
                {
                    GameClient[y][x] = GameClient[y][x - 1];
                }

                --x;
            }

            for(int y = 0; y < NUMCOLUMNBLOCKS; ++y)
                GameClient[y][0] = false;

            x = temp + 1;
        }
    }

    if(line)
        Score += (line - 1) * 2 + 1;

    InvalidateRect(hwnd, NULL, TRUE);
}

#endif
