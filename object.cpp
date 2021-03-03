#include "DxLib.h"
#include "function.h"
#include "player.h"
#include "Enemy.h"
#include "Shot.h"
#include "object.h"

int Object::graph[3] = { -1 };

//�A�j���[�V�����n
int objectcount;
int objectanimationIndex;

//��Q��������
void InitObject(Object object[], PlayerShot &playershot,EnemyShot enemyshot[])
{
	//�O���t�B�b�N�̃��[�h
	LoadDivGraph("data/texture/cat.png", 3, 2, 2, 100, 100, object[0].graph);
	for (size_t i = 0; i < 5; i++)
	{
		object[i].x = SCREEN_W + i * 350;
		object[i].y = SCREEN_H - 200;
	}
	int w, h;
	GetGraphSize(object[0].graph[0], &w, &h);
	//�T�C�Y�𓾂�
	for (size_t i = 0; i < objectMax; i++)
	{
		object[i].w = w;
		object[i].h = h;
	}
	// �J�E���^���Z�b�g
	objectcount = 0;
	objectanimationIndex = 0;
	for (size_t i = 0; i < objectMax; i++)
	{
		//�I�u�W�F�N�g�̂����ړ����x
		object[i].vx = 15;
	}
}
//��Q���A�b�v�f�[�g
void UpdateObject(Object object[], PlayerShot &playershot, EnemyShot enemyshot[])
{
	//------��Q���A�b�v�f�[�g------//
	//��Q���ړ�����
	for (size_t i = 0; i < objectMax; i++)
	{
		object[i].x -= object[i].vx;
	}
	if (object[4].x < 0)
	{
		for (size_t i = 0; i < 5; i++)
		{
			object[i].x = SCREEN_W + i * 300;
			object[i].y = SCREEN_H - 200;
		}
	}
	//�v���C���[�V���b�g�Ə�Q�������蔻��
	int playerShotLeft = playershot.x + 50;
	int playerShotRight = playershot.x + playershot.w - 50;
	int playerShotTop = playershot.y + 50;
	int playerShotBottom = playershot.y + playershot.h - 50;
	for (size_t i = 0; i < objectMax; i++)
	{
		if (((playerShotLeft > object[i].x  && playerShotLeft < object[i].x + object[i].w ) ||
			(object[i].x > playerShotLeft && object[i].x < playerShotRight)) &&
			((playerShotTop > object[i].y && playerShotTop < object[i].y + object[i].h) ||
			(object[i].y > playerShotTop && object[i].y < playerShotBottom)))
		{
			playershot.playerShotFlag = 0;
		}	
	}
	//��Q���ƃG�l�~�[�V���b�g�̓����蔻��
	int enemyShotLeft = enemyshot[attackEnemyNum].x + 10;
	int enemyShotRight = enemyshot[attackEnemyNum].x + enemyshot[attackEnemyNum].w - 10;
	int enemyShotTop = enemyshot[attackEnemyNum].y;
	int enemyShotBottom = enemyshot[attackEnemyNum].y + enemyshot[attackEnemyNum].h;
	for (size_t i = 0; i < objectMax; i++)
	{
		if (((enemyShotLeft > object[i].x + 30 && enemyShotLeft < object[i].x + object[i].w - 30 ) ||
			(object[i].x + 30 > enemyShotLeft && object[i].x + 30 < enemyShotRight)) &&
			((enemyShotTop > object[i].y + 20 && enemyShotTop < object[i].y + object[i].h - 30) ||
			(object[i].y + 20 > enemyShotTop && object[i].y + 20 < enemyShotBottom)))
		{
			shotFlag = false;
		}
	}
	//��Q���ƃG�l�~�[�V���b�g2�̓����蔻��
	int enemyShotLeft2 = enemyshot[attackEnemyNum2].x + 10;
	int enemyShotRight2 = enemyshot[attackEnemyNum2].x + enemyshot[attackEnemyNum2].w - 10;
	int enemyShotTop2 = enemyshot[attackEnemyNum2].y;
	int enemyShotBottom2 = enemyshot[attackEnemyNum2].y + enemyshot[attackEnemyNum2].h;
	for (size_t i = 0; i < objectMax; i++)
	{
		if (((enemyShotLeft2 > object[i].x + 30 && enemyShotLeft2 < object[i].x + object[i].w - 30) ||
			(object[i].x + 30 > enemyShotLeft2 && object[i].x + 30 < enemyShotRight2)) &&
			((enemyShotTop2 > object[i].y + 20 && enemyShotTop2 < object[i].y + object[i].h - 30 ) ||
			(object[i].y + 20 > enemyShotTop2 && object[i].y + 20 < enemyShotBottom2)))
		{
			shotFlag2 = false;
		}
	}
	//�A�j���[�V����
	if (objectcount % 12 == 0)
	{
		++objectanimationIndex;
		if (objectanimationIndex >= 3)
		{
			objectanimationIndex = 0;
		}
	}
	++objectcount;
}
//��Q���`��
void DrawObject(Object object[], PlayerShot &playershot, EnemyShot enemyshot[])
{
	for (size_t i = 0; i < objectMax; i++)
	{
			DrawGraph(object[i].x, object[i].y, Object::graph[objectanimationIndex], TRUE);
	}
}
