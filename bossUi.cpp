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
	//�c�莞�Ԃ��v�Z
	bossui.countDown = bossui.gameOverTime - (bossui.tempTime - bossui.startTime) / 1000;

}

void DrawBossUi(BossUi& bossui)
{
	//DrawFormatString(850, 20, GetColor(0, 0, 0), "�c��@%d�@�b", bossui.countDown);

}
