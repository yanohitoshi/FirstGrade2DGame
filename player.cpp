#include "Enemy.h"
#include "player.h"
#include "function.h"

//初期化
void InitPlayer(Player &player, XINPUT_STATE& input, Enemy enemy[])
{
	//プレイヤーのグラフィックをロード
	LoadDivGraph("data/texture/player1.png", 4, 2, 2, 75, 100, player.graph);
	//画面の半分（中央）の位置
	player.x = SCREEN_W / 2;
	//画面の下-100の位置
	player.y = SCREEN_H - 100;
	for (size_t i = 0; i < 4; i++)
	{
		GetGraphSize(player.graph[i], &player.w, &player.h);
	}
	//カウンターリセット
	player.count = 0;
	player.animationIndex = 0;
	//フラグ初期化
	player.damegeFlag = false;
}
//アップデート
void UpdatePlayer(Player &player, XINPUT_STATE &input, Enemy enemy[])
{
	// 矢印キーを押していたらプレイヤーを移動させる
	if (CheckHitKey(KEY_INPUT_LEFT) == 1 || input.Buttons[2])
	{
		player.x -= PLAYER_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || input.Buttons[3])
	{
		player.x += PLAYER_SPEED;
	}
	//プレイヤーが画面からはみ出しそうになったとき戻す
	if (player.x < 0)
	{
		player.x = 0;
	}
	if (player.x > SCREEN_W - player.w)
	{
		player.x = SCREEN_W - player.w;
	}
	if (player.y < 0)
	{
		player.y = 0;
	}
	if (player.y > SCREEN_H - player.h)
	{
		player.y = SCREEN_H - player.h;
	}
	//エネミーとプレイヤーの当たり判定

	int playerLeft = player.x;
	int playerRight = player.x + player.w;
	int playerTop = player.y;
	int playerBottom = player.y + player.h;

	for (size_t i = 0; i < enemyMax; i++)
	{
		if (enemy[i].aliveFlag == true)
		{
			if (((playerLeft > enemy[i].x + 30 && playerLeft < enemy[i].x + enemy[i].w - 30) ||
				(enemy[i].x + 30 > playerLeft && enemy[i].x + 30 < playerRight)) &&
				((playerTop > enemy[i].y + 50 && playerTop < enemy[i].y + enemy[i].h - 50) ||
				(enemy[i].y + 50 > playerTop && enemy[i].y - 50 < playerBottom)))
			{
				player.aliveFlag = false;
			}
		}
	}

	//アニメーション
	if (player.count % 8 == 0)
	{
		++player.animationIndex;
		if (player.animationIndex >= 4)
		{
			player.animationIndex = 0;
		}
	}
	++player.count;
}
//描画
void DrawPlayer(Player &player, XINPUT_STATE &input, Enemy enemy[])
{
	DrawGraph(player.x, player.y, player.graph[player.animationIndex], TRUE);
}

