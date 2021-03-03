#include "DxLib.h"
#include "function.h"
#include "Ui.h"

//UI初期化
void InitUi(Ui &ui)
{
	ui.startTime = GetNowCount();
	ui.gameOverTime = 160;
}
//UIアップデート
void UpdataUi(Ui &ui)
{
	ui.tempTime = GetNowCount();
	//残り時間を計算
	ui.countDown = ui.gameOverTime - (ui.tempTime - ui.startTime) / 1000;
}
//UI描画
void DrawUi(Ui &ui)
{
	DrawFormatString(850, 20, GetColor(0, 0, 0), "残り　%d　秒", ui.countDown);
}
