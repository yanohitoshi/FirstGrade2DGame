#pragma once
//�ϐ�
struct Enemy;

struct Enemy
{
	static int graph[4] ;
	int x;
	int y;
	int w;
	int h;
	int vx;
	int vy;
	int vx2;
	int vx3;
	//�����t���O
	bool aliveFlag;
};

const int enemyMax = 48;

//������
void InitEnemy(Enemy enemy[] );
//�A�b�v�f�[�g
void UpdateEnemy(Enemy enemy[]);
//�`��
void DrawEnemy(Enemy enemy[]);


