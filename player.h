#pragma once

#include "DxLib.h"
struct Enemy;

//プレイヤー変数
struct Player
{
	int graph[4];
	int x;
	int y;
	int w;
	int h;
	bool damegeFlag;
	bool aliveFlag;

	//アニメーション系
	int count = 0;
	int animationIndex = 0;
};

//初期化
void InitPlayer(Player &player, XINPUT_STATE &input,Enemy enemy[]);
//アップデート
void UpdatePlayer(Player &player, XINPUT_STATE &input, Enemy enemy[]);
//描画
void DrawPlayer(Player &player, XINPUT_STATE &input, Enemy enemy[]);

