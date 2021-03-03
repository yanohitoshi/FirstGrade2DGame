#pragma once
#include "DxLib.h"

//プロトタイプ宣言
struct Player;
struct Boss;

struct Boss
{
	int graph[4];
	int x;
	int y;
	int w;
	int h;
	int vx;
	int vy;
	int vx2;
	//生存フラグ
	bool aliveFlag;
	int animationIndex = 0;
	int count = 0;
	int damageCount;
};

//初期化
void InitBoss(Boss& boss,Player& player);
//アップデート
void UpdateBoss(Boss& boss,Player& player);
//描画
void DrawBoss(Boss& boss,Player& player);
