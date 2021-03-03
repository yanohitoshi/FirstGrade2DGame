#pragma once
#include "DxLib.h"

//�v���g�^�C�v�錾
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
	//�����t���O
	bool aliveFlag;
	int animationIndex = 0;
	int count = 0;
	int damageCount;
};

//������
void InitBoss(Boss& boss,Player& player);
//�A�b�v�f�[�g
void UpdateBoss(Boss& boss,Player& player);
//�`��
void DrawBoss(Boss& boss,Player& player);
