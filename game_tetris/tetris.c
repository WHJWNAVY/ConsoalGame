#if 0

#include <windows.h> //Ϊ��ʹ��API����
#include <time.h> //Ϊ��ʹ�ö�ʱ��
#include <stdlib.h>  //Ϊ��ʹ�������

#define bool            int
#define true            1
#define false           0
#define inline

#define BLOCKWIDTH      20  //���������С
#define NUMLINEBLOCKS   18  //����
#define NUMCOLUMNBLOCKS 10  //����
#define ID_TIMER        1   //��ʱ��ID
#define BLOCKSTYLES     (sizeof (Blocks) / sizeof (Blocks[0]))  //�����������

//��Ϸ�������񶥵㲼��ֵ������÷����Ƿ��з���
bool    GameClient[NUMCOLUMNBLOCKS][NUMLINEBLOCKS];
static int      F, S, cF, cS;   //�������ͼ�ζ�Ӧ�ĵ�һ����γ
static int      Score;  //�÷�

//�����������״���Ե��ʾ
struct
{
    POINT   pt[4];
}
Blocks[][4] =
{
    //��7
    0, 0, 1, 0, 1, 1, 1, 2, 2, 0, 0, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 2, 2, 2, 0, 1, 1, 1, 2, 1, 0, 2,
    //��7
    1, 0, 2, 0, 1, 1, 1, 2, 0, 1, 1, 1, 2, 1, 2, 2, 1, 0, 1, 1, 0, 2, 1, 2, 0, 0, 0, 1, 1, 1, 2, 1,
    //1
    1, 0, 1, 1, 1, 2, 1, 3, 0, 1, 1, 1, 2, 1, 3, 1, 1, 0, 1, 1, 1, 2, 1, 3, 0, 1, 1, 1, 2, 1, 3, 1,
    //Z
    0, 0, 1, 0, 1, 1, 2, 1, 2, 0, 1, 1, 2, 1, 1, 2, 0, 0, 1, 0, 1, 1, 2, 1, 2, 0, 1, 1, 2, 1, 1, 2,
    //��Z
    1, 0, 2, 0, 0, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 1, 0, 2, 0, 0, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2,
    //����
    0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1,
    //��ͷ
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

//������������ư棬����������ֵķ���
unsigned Random(int n);

//�ж��Ƿ�������䣬�����򷵻�true
bool CanDown(POINT pt[]);

//����ʵ��
void Down(POINT pt[]);

//�ж��Ƿ��������
bool CanLeft(POINT pt[]);

//ʵ������
void Left(POINT pt[]);

//�ж��Ƿ��������
bool CanRight(POINT pt[]);

//ʵ������
void Right(POINT pt[]);

//�ж��Ƿ���Ա���
bool CanChange(POINT pt[]);

//ʵ�ֱ���
void Change(POINT pt[]);

//���д����Լ���������
void DelSqure(HWND);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT       TericsBorder[] = { -1, -1,
                                   NUMCOLUMNBLOCKS * BLOCKWIDTH + 1, NUMLINEBLOCKS * BLOCKWIDTH + 1
                                 };
    HDC         hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC  tm;
    TCHAR       szNextTerics[] = TEXT("��һ����"),
                                 szSCore[] = TEXT("�÷֣�");
    static TCHAR szBufferScore[5];
    static int  cxChar, cyChar;
    static POINT Block[4], NextBlock[4];
    int         x, y;
    static bool     pause = false;  //��ͣ

    switch(message)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);

        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth * 2;
        cyChar = tm.tmExternalLeading + tm.tmHeight;
        SetTimer(hwnd, ID_TIMER, 600, NULL);
        //��ʼ����һ�����ֵķ���
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
        //�������ƣ���Ҫ���������жϣ���Ϸ�����������Ҫ������һ����ʾ���͵�ǰ��ʾ�ķ���
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

        //������˹������Ϸ�ı߿�
        Rectangle(hdc, TericsBorder[0].x, TericsBorder[0].y,
                  TericsBorder[1].x, TericsBorder[1].y);
        //�������һ�����ַ���
        TextOut(hdc, (NUMCOLUMNBLOCKS + 1) * BLOCKWIDTH, 0, szNextTerics, lstrlen(szNextTerics));

        //������÷֡��ַ���
        TextOut(hdc, (NUMCOLUMNBLOCKS + 1) * BLOCKWIDTH, cyChar + 5 * BLOCKWIDTH,
                szSCore, lstrlen(szSCore));
        //
        SetTextAlign(hdc, TA_RIGHT | TA_TOP);
        TextOut(hdc, (NUMCOLUMNBLOCKS + 1) * BLOCKWIDTH + 3 * cxChar, 2 * cyChar + 5 * BLOCKWIDTH,
                szBufferScore, wsprintf(szBufferScore, TEXT("%d"), Score));
        SetTextAlign(hdc, TA_LEFT | TA_TOP);

        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
        SelectObject(hdc, GetStockObject(WHITE_PEN));

        //��ʾ��Ϸ���ķ���
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

        //��ʾ��һ����������ķ���
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

//�жϷ����Ƿ��������
bool CanDown(POINT pt[])
{
    bool result = true;

    //���������ڸ����ȼ���ָ��Ϊ�޷���
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = false;

    for(int i = 0; i < 4; ++i)
    {
        //����������³����µױ߽磬����false�����߼����С��������һ���Ѿ��з��飬���Ϊfalse
        if(pt[i].y + 1 == NUMLINEBLOCKS || GameClient[pt[i].x][pt[i].y + 1])
        {
            result = false;
            break;
        }
    }

    //�ָ��������ڸ���Ϊ�з���
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = true;

    return result;
}


//�ж��Ƿ��������
bool CanLeft(POINT pt[])
{
    bool result = true;

    //���������ڸ����ȼ���ָ��Ϊ�޷���
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = false;

    for(int i = 0; i < 4; ++i)
    {
        //����������Ƴ�����߽߱磬����false�����߼����С��������һ���Ѿ��з��飬���Ϊfalse
        if(!pt[i].x || GameClient[pt[i].x - 1][pt[i].y])
        {
            result = false;
            break;
        }
    }

    //�ָ��������ڸ���Ϊ�з���
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = true;

    return result;
}

//�ж��Ƿ��������
bool CanRight(POINT pt[])
{
    bool result = true;

    //���������ڸ����ȼ���ָ��Ϊ�޷���
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = false;

    for(int i = 0; i < 4; ++i)
    {
        //����������Ƴ�����߽߱磬����false�����߼����С��������һ���Ѿ��з��飬���Ϊfalse
        if(pt[i].x + 1 == NUMCOLUMNBLOCKS || GameClient[pt[i].x + 1][pt[i].y])
        {
            result = false;
            break;
        }
    }

    //�ָ��������ڸ���Ϊ�з���
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = true;

    return result;
}

//�ж��Ƿ������ת
bool CanChange(POINT pt[])
{
    bool result = true;

    //���������ڸ����ȼ���ָ��Ϊ�޷���
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = false;

    int t = (cS + 1) % 4;

    for(int k = 0; k < 4; ++k)
    {
        int x = Blocks[cF][t].pt[k].x - Blocks[cF][cS].pt[k].x,
            y = Blocks[cF][t].pt[k].y - Blocks[cF][cS].pt[k].y;

        if(GameClient[pt[k].x + x][pt[k].y + y] ||   //�÷����Ѿ��з���
                pt[k].x + x > NUMCOLUMNBLOCKS - 1 ||  //x���곬Խ���ұ߽�
                pt[k].x + x < 0 ||   //x���곬Խ����߽�
                pt[k].y + y > NUMLINEBLOCKS - 1)  //y���곬Խ���µױ߽�
        {
            result = false;
            break;
        }
    }

    //�ָ��������ڸ���Ϊ�з���
    for(int i = 0; i < 4; ++i)
        GameClient[pt[i].x][pt[i].y] = true;

    return result;
}

//ʵ����ת
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

//ʵ������
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

//ʵ������
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

//ʵ�ַ��������
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

//������������ư�
inline unsigned int Random(int n)
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    srand(st.wMilliseconds);
    return rand() % n;
}

//���д����Լ���������
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

        //�ж��Ƿ��������
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
