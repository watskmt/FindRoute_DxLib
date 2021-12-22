// FindRoute.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "FindRoute.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FINDROUTE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FINDROUTE));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FINDROUTE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FINDROUTE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
#include "DxLib.h"
#include <math.h>
#include <time.h>

#define PI    3.1415926535897932384626433832795f

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024
#define SIZEX 50
#define SIZEY 50

typedef struct Point
{
	int x;
	int y;
}Point;

int ShowStatus(int state[SIZEY][SIZEX], Point p);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int GHandle;
	int GHandle1;


	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	GHandle = LoadGraph((TCHAR *)"d:\\download\\space.jpg");
	GHandle1 = LoadGraph((TCHAR *)"d:\\download\\apple.png");


	int i;
	char key = 0;
	int state[SIZEY][SIZEX];
	
	Point route[SIZEX*SIZEY];
	int steps = 0;

	Point current;
	current.x = 0;
	current.y = 0;
	route[steps++] = current;

	srand(time(NULL));
	for (int y = 0; y < SIZEY; y++)
		for (int x = 0; x < SIZEX; x++)
			state[y][x] = (rand() % 10 > 6 ) ? 1 : 0;

	
	ShowStatus(state, current);

	while (1)
	{
		clsDx();
		// 通ってきた道をマーク（-1）
		state[current.y][current.x] = -1;

		// 右から初めて右回りに探索
		if (current.x != SIZEX-1 && state[current.y][current.x + 1] == 0)
		{
			current.x++;
			route[steps++] = current;
		}
		else if (current.y != SIZEY-1 && state[current.y + 1][current.x] == 0)
		{
			current.y++;
			route[steps++] = current;
		}
		else if (current.x != 0 && state[current.y][current.x - 1] == 0)
		{
			current.x--;
			route[steps++] = current;
		}
		else if (current.y != 0 && state[current.y - 1][current.x] == 0)
		{
			current.y--;
			route[steps++] = current;
		}
		else
		{
			if (steps > 0)
				current = route[--steps];
			else
				break;
		}


		ShowStatus(state, current);
		if (current.x == SIZEX-1 && current.y == SIZEY-1)
		{
			printf("Goal\n");
			break;
		}
		else if (steps == 0)
		{
			printf("Failed\n");
			break;
		}
		Sleep(50);
		// 画面表示待ち（OSに処理を返す）
		if (ProcessMessage() == -1)
		{
			break;        // エラーが起きたらループを抜ける
		}
	}

	// 読み込んだ画像のグラフィックハンドルを削除

	WaitKey();        // 結果を見るためにキー待ち(『WaitKey』を使用)
	DeleteGraph(GHandle);
	DxLib_End();        // ＤＸライブラリ使用の終了処理

	return 0;        // ソフトの終了
}

int ShowStatus(int state[SIZEY][SIZEX], Point p)
{
	int i, j;
	int boxSizeX = WINDOW_WIDTH / SIZEX;
	int boxSizeY = WINDOW_HEIGHT / SIZEY;

	int colWall = GetColor(255, 255, 255);
	int colMe = GetColor(255, 100, 100);
	int colProhibit = GetColor(50, 50, 50);
	
	for (i = 0; i < SIZEY; i++)
	{
		for (j = 0; j < SIZEX; j++)
		{
			if (j == p.x && i == p.y)
				DrawCircle(boxSizeX * j+ boxSizeX/2, boxSizeY * i + boxSizeY/2, (boxSizeY > boxSizeX ? boxSizeX : boxSizeY)/2, colMe, 1);
			else
			{
				int col;
				switch (state[i][j])
				{
				case 0:
					col =0;
					break;
				case -1:
					col = colProhibit;
					break;
				case 1:
					col = colWall;
					break;
				default:
					col=0;
					break;
				}
				DrawBox(boxSizeX * j, boxSizeY * i, boxSizeX * (j + 1) - 1, boxSizeY * (i + 1) - 1, col, 1);
			}
		}
	}
	return 0;
}
