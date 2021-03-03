#pragma once

#include "DxLib.h"

// �v���g�^�C�v�錾
struct Boss;
struct Enemy;
struct EnemyShot;
struct Player;

//�G�l�~�[�V���b�g�\����
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

//�v���C���[�̔�e�J�E���g
extern int playerDamageCount;

extern XINPUT_STATE input;

//�v���C���[�V���b�g�\����
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


//������
void InitShot(PlayerShot &playershot,EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE &input,Boss& boss);

//�A�b�v�f�[�g
void UpdateShot(PlayerShot &playershot,EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE &input,Boss& boss);

//�`��
void DrawShot(PlayerShot &playershot,EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE& input, Boss& boss);

