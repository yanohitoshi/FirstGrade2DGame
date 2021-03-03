#pragma once
#define SCREEN_W 1920
#define SCREEN_H 1000
#define PLAYER_SPEED 5
#define ENEMY_SPEED  80
#define PLAYER_SHOT  3
#define STATE_CHANGE_WAIT 500
enum
{
	INIT, TUTORIAL, TITLE,TITLE1, PLAY,PLAY2,BOSS, OVER, CLEAR 									//ゲーム状態管理
};

extern int gameStatus;													//ゲームの状態

//プロトタイプ宣言
struct Rule;

struct Rule
{
	int prevKeyInput = 0;
	bool keyOn = false;
	bool prevKeyOn = false;
	bool keyRelease = false;
};
