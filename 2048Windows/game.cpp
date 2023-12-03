#include "test.h"

int arr[4][4];
int x = -1,  a;
HFONT hfont;
RECT rect;
HBITMAP hb;

LRESULT WINAPI Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		x = move(arr, wParam);
		if(x!=-1&&x!=-10&&x!=10)
			RandHapped(arr);
		InvalidateRect(hwnd, &rect, false);
		break;
	}
	case WM_CREATE:
		RandHapped(arr);
		break;
	case WM_CLOSE:
		::DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		HDC dc;
		GetClientRect(hwnd, &rect);
		PAINTSTRUCT ps;
		dc = ::BeginPaint(hwnd, &ps);
		display(hwnd, arr);
		BitBlt(dc, 0, 0, 375, 400, hTempDc, 0, 0, SRCCOPY);
			if (x == -10)
			{
				a=MessageBox(hwnd, "你输了,想再试一次吗", "gameover", MB_RETRYCANCEL);
				switch (a)
				{
				case IDTRYAGAIN:
				case IDRETRY:
					initl(arr);
					RandHapped(arr);
					display(hwnd, arr);
					BitBlt(dc, 0, 0, 375, 400, hTempDc, 0, 0, SRCCOPY);
					break;
				case IDCANCEL:
					::PostQuitMessage(0);
					break;
				}
			}
			else if (x == 10)
			{
				MessageBox(hwnd, "恭喜你，得到2048", NULL, MB_RETRYCANCEL);
				::PostQuitMessage(0);
			}
		::EndPaint(hwnd, &ps);
		break;
	}

	default:
		return DefWindowProcA(hwnd, msg, wParam, lParam);
		break;
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR cmd, int nshow)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = ::CreateSolidBrush(RGB(255, 255, 255));;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);;
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = Proc;
	wc.lpszClassName = "game";
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	srand((unsigned int)time(NULL));

	h0 = (HBITMAP)::LoadImageA(NULL, "0.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h2 = (HBITMAP)::LoadImageA(NULL, "2.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h4 = (HBITMAP)::LoadImageA(NULL, "4.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h8 = (HBITMAP)::LoadImageA(NULL, "8.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h16 = (HBITMAP)::LoadImageA(NULL, "16.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h32 = (HBITMAP)::LoadImageA(NULL, "32.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h64 = (HBITMAP)::LoadImageA(NULL, "64.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h128 = (HBITMAP)::LoadImageA(NULL, "128.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h256 = (HBITMAP)::LoadImageA(NULL, "256.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h512 = (HBITMAP)::LoadImageA(NULL, "512.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h1024 = (HBITMAP)::LoadImageA(NULL, "1024.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	h2048 = (HBITMAP)::LoadImageA(NULL, "2048.bmp", IMAGE_BITMAP, 90, 90, LR_LOADFROMFILE);
	hfont = ::CreateFont(35, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "楷体");

	::RegisterClass(&wc);

	HWND hwnd = ::CreateWindow("game", "2048小游戏", WS_OVERLAPPEDWINDOW, 500, 200, 375, 400, NULL, NULL, hInstance, NULL);
	hdc = ::GetDC(hwnd);
	hBlank = ::CreateCompatibleDC(hdc);
	hTempDc = ::CreateCompatibleDC(hdc);
	hb = ::CreateCompatibleBitmap(hdc, 375, 400);
	::SelectObject(hTempDc, hb);

	::ShowWindow(hwnd, SW_SHOWNORMAL);
	::UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return 0;
}
