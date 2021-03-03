#pragma once
#define SCREEN_W 1920
#define SCREEN_H 1000
#define PLAYER_SPEED 5
#define ENEMY_SPEED  80
#define PLAYER_SHOT  3
#define STATE_CHANGE_WAIT 500
enum
{
	INIT, TUTORIAL, TITLE,TITLE1, PLAY,PLAY2,BOSS, OVER, CLEAR 									//�Q�[����ԊǗ�
};

extern int gameStatus;													//�Q�[���̏��

//�v���g�^�C�v�錾
struct Rule;

struct Rule
{
	int prevKeyInput = 0;
	bool keyOn = false;
	bool prevKeyOn = false;
	bool keyRelease = false;
};
