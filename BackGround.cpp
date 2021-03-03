#include "BackGround.h"



//-----背景関数群------//
//初期化
void InitBG(Bg& bg)
{
	bg.Graph = LoadGraph("data/texture/hamabe.png");
	GetGraphSize(bg.Graph, &bg.w, &bg.h);
}
//アップデート
void UpdateBG(Bg)
{

}

//描画.
void DrawBG(Bg& bg)
{
	DrawGraph(0, 0, bg.Graph, true);
}

