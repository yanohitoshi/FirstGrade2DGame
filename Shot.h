#pragma once

#include "DxLib.h"

// プロトタイプ宣言
struct Boss;
struct Enemy;
struct EnemyShot;
struct Player;

//エネミーショット構造体
typedef struct EnemyShot
{
	int	graph;
	int	x;
	int	y;
	int	w;
	int	h;
	int vy;
	int vy2;
	int vy3;
	int soundEffect;
	int soundExplosion;
}EnemyShot;
const int enemyShotMax = 48;
extern bool shotFlag;
extern bool shotFlag2;
extern bool shotFlag3;

extern int attackEnemyNum;
extern int attackEnemyNum2;
extern int attackEnemyNum3;

//プレイヤーの被弾カウント
extern int playerDamageCount;

extern XINPUT_STATE input;

//プレイヤーショット構造体
typedef struct Playershot
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
}PlayerShot;
extern int deathCount;


//初期化
void InitShot(PlayerShot &playershot,EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE &input,Boss& boss);

//アップデート
void UpdateShot(PlayerShot &playershot,EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE &input,Boss& boss);

//描画
void DrawShot(PlayerShot &playershot,EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE& input, Boss& boss);

