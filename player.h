#pragma once

#include "DxLib.h"
struct Enemy;

//�v���C���[�ϐ�
struct Player
{
	int graph[4];
	int x;
	int y;
	int w;
	int h;
	bool damegeFlag;
	bool aliveFlag;

	//�A�j���[�V�����n
	int count = 0;
	int animationIndex = 0;
};

//������
void InitPlayer(Player &player, XINPUT_STATE &input,Enemy enemy[]);
//�A�b�v�f�[�g
void UpdatePlayer(Player &player, XINPUT_STATE &input, Enemy enemy[]);
//�`��
void DrawPlayer(Player &player, XINPUT_STATE &input, Enemy enemy[]);

