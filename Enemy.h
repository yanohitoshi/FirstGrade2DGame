#pragma once
//変数
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
	//生存フラグ
	bool aliveFlag;
};

const int enemyMax = 48;

//初期化
void InitEnemy(Enemy enemy[] );
//アップデート
void UpdateEnemy(Enemy enemy[]);
//描画
void DrawEnemy(Enemy enemy[]);


