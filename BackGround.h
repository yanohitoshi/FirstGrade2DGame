#pragma once
#include "Dxlib.h"
#include "All.h"
//-------”wŒi•Ï”--------//
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
