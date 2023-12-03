#pragma once
#include <Windows.h>
#include <time.h>
#include "resource.h"

extern HBITMAP h0, h2, h4, h8, h16, h32, h64, h128, h256, h512, h1024, h2048;

extern HDC hdc, hBlank, hpen, hTempDc;

void display(HWND hwnd,int arr[4][4]);

void initl(int arr[4][4]);

void RandHapped(int arr[4][4]);

int  move(int arr[4][4], char a);

int Gameover(int map[4][4]);

int UpMove(int map[4][4]);

int DownMove(int map[4][4]);

int LeftMove(int map[4][4]);


