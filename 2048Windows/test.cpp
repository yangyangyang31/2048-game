#include "test.h"

HBITMAP h0 = NULL, h2 = NULL, h4 = NULL, h8 = NULL, h16 = NULL, h32 = NULL, h64 = NULL, h128 = NULL, h256 = NULL, h512 = NULL, h1024 = NULL, 
h2048 = NULL; HDC hdc = NULL, hBlank = NULL;

HDC hTempDc = NULL;

void display(HWND hwnd, int arr[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			switch (arr[i][j]) 
			{
			case 0:
				::SelectObject(hBlank, h0);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 2:
				::SelectObject(hBlank, h2);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 4:
				::SelectObject(hBlank, h4);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 8:
				::SelectObject(hBlank, h8);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 16:
				::SelectObject(hBlank, h16);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 32:
				::SelectObject(hBlank, h32);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 64:
				::SelectObject(hBlank, h64);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 128:
				::SelectObject(hBlank, h128);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 256:
				::SelectObject(hBlank, h256);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 512:
				::SelectObject(hBlank, h512);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 1024:
				::SelectObject(hBlank, h1024);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			case 2048:
				::SelectObject(hBlank, h2048);
				BitBlt(hTempDc, 90 * j, 90 * i, 90, 90, hBlank, 0, 0, SRCCOPY);
				break;
			}
		}
	}
}

void initl(int arr[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			arr[i][j] = 0;
	}
}

void RandHapped(int arr[4][4])
{
	while (1)
	{
		int x = rand() % 4;
		int y = rand() % 4;
		if (arr[x][y] == 0)
		{
			int a = rand() % 4;
			if (a == 0)
				arr[x][y] = 4;
			else
				arr[x][y] = 2;
			break;
		}
	}
}

int Gameover(int map[4][4])
{
	int i, j, a = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (map[i][j] == 2048)
				return 1;     //成功
			if (map[i][j] == 0)
				a++;
		}
	}
	if (a >= 1)    //继续
		return 0;
	return -1;   //失败
}

int UpMove(int map[4][4])
{
	int i, j, flat = -1;
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4; i++)
		{
			if (map[i][j] != 0)
			{
				for (int k = i + 1; k < 4; k++)
				{
					if (map[k][j] != 0)
					{
						if (map[i][j] == map[k][j])
						{
							map[i][j] += map[k][j];
							map[k][j] = 0;
							k = 4;
							flat = 0;
						}
						break;
					}
				}
			}
		}
	}


	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4; i++)
		{
			if (map[i][j] == 0)
			{
				for (int k = i + 1; k < 4; k++)
				{
					if (map[k][j] != 0)
					{
						map[i][j] = map[k][j];
						map[k][j] = 0;
						k = 4;
						flat = 0;
					}
				}
			}
		}
	}
	int a = Gameover(map);
	if (a == 0)
		return flat;            //继续
	else if (a == 1)         
		return 10;           //成功
	else
		return -10;             //失败
}

int DownMove(int map[4][4])
{
	int i, j, flat = -1;
	for (j = 0; j < 4; j++)
	{
		for (i = 3; i >= 0; i--)
		{
			if (map[i][j] != 0)
			{
				for (int k = i - 1; k >= 0; k--)
				{
					if (map[k][j] != 0)
					{
						if (map[i][j] == map[k][j])
						{
							map[i][j] += map[k][j];
							map[k][j] = 0;
							k = -1;
							flat = 0;
						}
						break;
					}
				}
			}
		}
	}


	for (j = 0; j < 4; j++)
	{
		for (i = 3; i >= 0; i--)
		{
			if (map[i][j] == 0)
			{
				for (int k = i - 1; k >= 0; k--)
				{
					if (map[k][j] != 0)
					{
						map[i][j] = map[k][j];
						map[k][j] = 0;
						k = -1;
						flat = 0;
					}
				}
			}
		}
	}
	int a = Gameover(map);
	if (a == 0)
		return flat;
	else if (a == 1)
		return 10;
	else
		return -10;
}

int LeftMove(int map[4][4])
{
	int i, j, flat = -1;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (map[i][j] != 0)
			{
				for (int k = j + 1; k < 4; k++)
				{
					if (map[i][k] != 0)
					{
						if (map[i][k] == map[i][j])
						{
							map[i][j] += map[i][k];
							map[i][k] = 0;
							k = 4;
							flat = 0;
						}
						break;
					}
				}
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)
			{
				for (int k = j + 1; k < 4; k++)
				{
					if (map[i][k] != 0)
					{
						map[i][j] = map[i][k];
						map[i][k] = 0;
						k = 4;
						flat = 0;
					}
				}
			}
		}
	}
	int a = Gameover(map);
	if (a == 0)
		return flat;
	else if (a == 1)
		return 10;
	else
		return -10;
}

int RightMove(int map[4][4])
{
	int i, j, flat = -1;
	for (i = 0; i < 4; i++)
	{
		for (j = 3; j >= 0; j--)
		{
			if (map[i][j] != 0)
			{
				for (int k = j - 1; k >= 0; k--)
				{
					if (map[i][k] != 0)
					{
						if (map[i][k] == map[i][j])
						{
							map[i][j] += map[i][k];
							map[i][k] = 0;
							k = -1;
							flat = 0;
						}
						break;
					}
				}
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 3; j >= 0; j--)
		{
			if (map[i][j] == 0)
			{
				for (int k = j - 1; k >= 0; k--)
				{
					if (map[i][k] != 0)
					{
						map[i][j] = map[i][k];
						map[i][k] = 0;
						k = -1;
						flat = 0;
					}
				}
			}
		}
	}
	int a = Gameover(map);
	if (a == 0)
		return flat;
	else if (a == 1)
		return 10;
	else
		return -10;
}

int move(int arr[4][4], char a)
{
	int x=-1;
	switch(a)
	{
	case 'A':
	case 'a':
		x=LeftMove(arr);
		break;
	case 'W':
	case 'w':
		x=UpMove(arr);
		break;
	case 'S':
	case 's':
		x=DownMove(arr);
		break;
	case 'D':
	case 'd':
		x=RightMove(arr);
		break;
	}
	return x;
}