#include "DxLib.h"
#include "function.h"
#include "boss.h"
#include "player.h"

//初期化
void InitBoss(Boss& boss, Player& player)
{
	//ボスのグラフィックをロード
	LoadDivGraph("data/texture/boss.png", 4, 2, 2, 1200, 2000, boss.graph);
	//ボスの初期位置
	boss.x = 350;
	boss.y = -1500;
	GetGraphSize(boss.graph[0], &boss.w, &boss.h);

	//エネミーのｙ軸の移動速度
	boss.vy = 30;
	//フラグのリセット
	boss.aliveFlag = true;
	player.aliveFlag = true;
}
//アップデート
void UpdateBoss(Boss& boss, Player& player)
{
	//ボスの移動処理
	if (boss.count % 15 == 0)
	{
		boss.y += boss.vy;
	}

	//ボスとプレイヤーショットの当たり判定
	int playerLeft = player.x + 30;
	int playerRight = player.x + player.w - 30;
	int playerTop = player.y + 20;
	int playerBottom = player.y + player.h - 20;

	if (boss.aliveFlag == true)
	{
		if (((playerLeft > boss.x + 400 && playerLeft < boss.x + boss.w - 400) ||
			(boss.x + 400 > playerLeft && boss.x + 400 < playerRight)) &&
			((playerTop > boss.y + 600 && playerTop < boss.y + boss.h - 600) ||
			(boss.y + 600 > playerTop && boss.y - 600 < playerBottom)))
		{
			player.aliveFlag = false;
		}
	}
	if (boss.y > 1080)
	{
		player.aliveFlag = false;

	}


	//アニメーション
	if (boss.count % 8 == 0)
	{
		++boss.animationIndex;
		if (boss.animationIndex >= 4)
		{
			boss.animationIndex = 0;
		}
	}
	++boss.count;

}
//描画
void DrawBoss(Boss& boss, Player& player)
{
	if (boss.aliveFlag == true)
	{
		DrawGraph(boss.x, boss.y, boss.graph[boss.animationIndex], TRUE);
	}
}
