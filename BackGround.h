#pragma once
#include "Dxlib.h"
#include "All.h"
//-------�w�i�ϐ�--------//
struct Bg
{
	int Graph;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

};

void InitBG(Bg& bg);
void DrawBG(Bg& bg);
