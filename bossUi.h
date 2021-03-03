#pragma once
#pragma once
//プロトタイプ宣言
struct BossUi;

struct BossUi
{
	int countDown;
	int gameOverTime;
	int tempTime;
	int startTime;
};


void InitBossUi(BossUi& bossui);

void UpdataBossUi(BossUi& bossui);

void DrawBossUi(BossUi& bossui);
