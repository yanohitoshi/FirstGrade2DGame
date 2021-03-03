#include "Dxlib.h"
#include "BackGraund.h"

//初期化
void InitBG(Bg& bg)
{
	//グラフィックのロード
	bg.graph = LoadGraph("data/texture/haikei2.png");
	bg.x = 0;
	bg.y = 0;
}
//描画
void DrawBG(Bg& bg)
{
	DrawGraph(bg.x, bg.y, bg.graph, TRUE);
}

