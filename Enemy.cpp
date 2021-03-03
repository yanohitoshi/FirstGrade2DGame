#include "DxLib.h"
#include "function.h"
#include "Enemy.h"
#include "Ui.h"


int Enemy::graph[4] = {-1};

//�J�E���g�n
int gameCount;

//�A�j���[�V�����n
int count;
int animationIndex;

//�ő�ŏ�
int minX, maxX;
int maxY;

void InitEnemy(Enemy enemy[])
{
	//�G�l�~�[�̃O���t�B�b�N�����[�h
	LoadDivGraph("data/texture/enemy.png", 4, 2, 2, 120, 200, enemy[0].graph);
	//�G�l�~�[�̏����z�u
	for (size_t i = 0; i < 6; i++)     //�G�l�~�[1�̏����z�u
	{
		for (size_t j = 0; j < 8; j++)
		{
			enemy[ i * 8 + j  ].x = j * 120;
			enemy[ i * 8 + j ].y = i * 80;
		}
	}
	int w, h;
	//�G�l�~�[�̃O���t�B�b�N�T�C�Y�𓾂�
	GetGraphSize(enemy[0].graph[0], &w, &h);
	for (size_t i = 0; i < enemyMax; i++)                              
	{
		enemy[i].w = w;
		enemy[i].h = h;
	}

	// �J�E���^���Z�b�g
	count = 0;
	animationIndex = 0;
	for (size_t i = 0; i < enemyMax; i++)
	{
		//�G�l�~�[�̂����ړ����x
		enemy[i].vx = 40;
		enemy[i].vx2 = 80;
		enemy[i].vx3 = 100;
		//�G�l�~�[�̂����̈ړ����x
		enemy[i].vy = 30;
		//�t���O�̃��Z�b�g
		enemy[i].aliveFlag = true;
	}
}

//�A�b�v�f�[�g
void UpdateEnemy(Enemy enemy[])
{	
	if (count % 30 == 0)
	{
		minX = enemy[48].x;
		maxX = enemy[0].x;
		for (int i = 0; i < enemyMax; i++)
		{
			if (enemy[i].aliveFlag == true)
			{
				if (enemy[i].x > maxX)
				{
					maxX = enemy[i].x;
				}
				if (enemy[i].x < minX)
				{
					minX = enemy[i].x;
				}
			}
		}
		maxY = 0;
		for (int i = 0; i < enemyMax; i++)
		{
			if (enemy[i].aliveFlag == true)
			{
				if (enemy[i].y > maxY)
				{
					maxY = enemy[i].y;
				}
			}
		}
		if (maxY < 450)
		{
			if (maxX >= SCREEN_W - enemy[0].w || minX < 0)
			{
				for (int i = 0; i < enemyMax; i++)
				{
					//���]
					enemy[i].vx *= -1;
					//y���̈ړ�
					enemy[i].y = enemy[i].y + enemy[i].vy;
				}
			}
			for (int i = 0; i < enemyMax; i++)
			{
				//�G�ړ�����	
				enemy[i].x += enemy[i].vx;
			}
		}
		if (maxY >= 460)
		{
			if (maxX >= SCREEN_W - enemy[0].w || minX < 0)
			{
				for (int i = 0; i < enemyMax; i++)
				{
					//���]
					enemy[i].vx2 *= -1;
					//y���̈ړ�
					enemy[i].y = enemy[i].y + enemy[i].vy;
				}
			}

			for (int i = 0; i < enemyMax; i++)
			{
				//�G�ړ�����	
				enemy[i].x += enemy[i].vx2;
			}
		}
		if (maxY >= 520)
		{
			if (maxX >= SCREEN_W - enemy[0].w || minX < 0)
			{
				for (int i = 0; i < enemyMax; i++)
				{
					//���]
					enemy[i].vx3 *= -1;
					//y���̈ړ�
					enemy[i].y = enemy[i].y + enemy[i].vy;
				}
			}

			for (int i = 0; i < enemyMax; i++)
			{
				//�G�ړ�����	
				enemy[i].x += enemy[i].vx3;
			}
		}
	}

	//�A�j���[�V����
	if (count % 8 == 0)
	{
		++animationIndex;
		if (animationIndex >= 4)
		{
			animationIndex = 0;
		}
	}
	++count;
}

//�`��
void DrawEnemy(Enemy enemy[])
{
	//�G�l�~�[�̕`��	
	for (size_t i = 0; i < enemyMax; i++)
	{
		if (enemy[i].aliveFlag == true)
		{
			DrawGraph(enemy[i].x, enemy[i].y, enemy[i].graph[animationIndex], TRUE);
		}
	}
}
