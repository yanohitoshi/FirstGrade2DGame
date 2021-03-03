#pragma once
#include "DxLib.h"

//プロトタイプ宣言
struct player;
struct Playershot2;
struct Boss;
//プレイヤーショット構造体
struct Playershot2
{
	int	graph;
	int	x;
	int	y;
	int	w;
	int	h;
	int vy;
	bool playerShotFlag;
	int score;
	int soundEffect;
	int soundExplosion;
};

//初期化
void InitPlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player);

//アップデート
void UpdatePlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player);

//描画
void DrawPlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player);
