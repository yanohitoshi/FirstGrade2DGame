#include "DxLib.h"
#include "function.h"
#include "Enemy.h"
#include "Ui.h"


int Enemy::graph[4] = {-1};

//カウント系
int gameCount;

//アニメーション系
int count;
int animationIndex;

//最大最小
int minX, maxX;
int maxY;

void InitEnemy(Enemy enemy[])
{
	//エネミーのグラフィックをロード
	LoadDivGraph("data/texture/enemy.png", 4, 2, 2, 120, 200, enemy[0].graph);
	//エネミーの初期配置
	for (size_t i = 0; i < 6; i++)     //エネミー1の初期配置
	{
		for (size_t j = 0; j < 8; j++)
		{
			enemy[ i * 8 + j  ].x = j * 120;
			enemy[ i * 8 + j ].y = i * 80;
		}
	}
	int w, h;
	//エネミーのグラフィックサイズを得る
	GetGraphSize(enemy[0].graph[0], &w, &h);
	for (size_t i = 0; i < enemyMax; i++)                              
	{
		enemy[i].w = w;
		enemy[i].h = h;
	}

	// カウンタリセット
	count = 0;
	animationIndex = 0;
	for (size_t i = 0; i < enemyMax; i++)
	{
		//エネミーのｘ軸移動速度
		enemy[i].vx = 40;
		enemy[i].vx2 = 80;
		enemy[i].vx3 = 100;
		//エネミーのｙ軸の移動速度
		enemy[i].vy = 30;
		//フラグのリセット
		enemy[i].aliveFlag = true;
	}
}

//アップデート
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
					//反転
					enemy[i].vx *= -1;
					//y軸の移動
					enemy[i].y = enemy[i].y + enemy[i].vy;
				}
			}
			for (int i = 0; i < enemyMax; i++)
			{
				//敵移動処理	
				enemy[i].x += enemy[i].vx;
			}
		}
		if (maxY >= 460)
		{
			if (maxX >= SCREEN_W - enemy[0].w || minX < 0)
			{
				for (int i = 0; i < enemyMax; i++)
				{
					//反転
					enemy[i].vx2 *= -1;
					//y軸の移動
					enemy[i].y = enemy[i].y + enemy[i].vy;
				}
			}

			for (int i = 0; i < enemyMax; i++)
			{
				//敵移動処理	
				enemy[i].x += enemy[i].vx2;
			}
		}
		if (maxY >= 520)
		{
			if (maxX >= SCREEN_W - enemy[0].w || minX < 0)
			{
				for (int i = 0; i < enemyMax; i++)
				{
					//反転
					enemy[i].vx3 *= -1;
					//y軸の移動
					enemy[i].y = enemy[i].y + enemy[i].vy;
				}
			}

			for (int i = 0; i < enemyMax; i++)
			{
				//敵移動処理	
				enemy[i].x += enemy[i].vx3;
			}
		}
	}

	//アニメーション
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

//描画
void DrawEnemy(Enemy enemy[])
{
	//エネミーの描画	
	for (size_t i = 0; i < enemyMax; i++)
	{
		if (enemy[i].aliveFlag == true)
		{
			DrawGraph(enemy[i].x, enemy[i].y, enemy[i].graph[animationIndex], TRUE);
		}
	}
}
