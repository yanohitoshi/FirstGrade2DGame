#include "DxLib.h"
#include "function.h"
#include "bossUi.h"

void InitBossUi(BossUi& bossui)
{
	bossui.startTime = GetNowCount();

	bossui.gameOverTime = 60;

}

void UpdataBossUi(BossUi& bossui)
{
	bossui.tempTime = GetNowCount();
	//残り時間を計算
	bossui.countDown = bossui.gameOverTime - (bossui.tempTime - bossui.startTime) / 1000;

}

void DrawBossUi(BossUi& bossui)
{
	//DrawFormatString(850, 20, GetColor(0, 0, 0), "残り　%d　秒", bossui.countDown);

}
