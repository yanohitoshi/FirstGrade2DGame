#pragma once
#include "DxLib.h"

//�v���g�^�C�v�錾
struct player;
struct Playershot2;
struct Boss;
//�v���C���[�V���b�g�\����
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

//������
void InitPlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player);

//�A�b�v�f�[�g
void UpdatePlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player);

//�`��
void DrawPlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player);
