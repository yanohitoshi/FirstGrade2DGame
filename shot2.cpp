#include "function.h"
#include "player.h"
#include "boss.h"
#include "shot2.h"

//初期化
void InitPlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss, Player& player)
{
	//------プレイヤーショット関連------//
	//プレイヤーショットのロード
	playershot2.graph = LoadGraph("data/texture/playershot5.png");

	//プレイヤーショットのサイズを得る
	GetGraphSize(playershot2.graph, &playershot2.w, &playershot2.h);

	//プレイヤーショットの初期位置
	playershot2.x = (player.x + player.w);
	playershot2.y = (player.y + player.h);

	//プレイヤーショットの速度
	playershot2.vy = -20;
	playershot2.playerShotFlag = false;

	//スコアの初期化
	playershot2.score = 0;

	//プレイヤーショットの効果音をロード
	playershot2.soundEffect = LoadSoundMem("data/sound/playerEffect.mp3");
	playershot2.soundExplosion = LoadSoundMem("data/sound/playerExplosion.mp3");
	//ボスダメージカウントの初期化
	boss.damageCount = 0;
}

//アップデート
void UpdatePlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player)
{
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && playershot2.playerShotFlag == 0 || input.Buttons[12] && playershot2.playerShotFlag == 0)
	{
		//プレイヤーと弾の画像のサイズを得る
		for (size_t i = 0; i < 4; i++)
		{
			GetGraphSize(player.graph[i], &player.w, &player.h);
		}
		//画像サイズを得る
		GetGraphSize(playershot2.graph, &playershot2.w, &playershot2.h);

		// 弾の位置をセット、位置はプレイヤーの中心にする		
		playershot2.x = (player.w - playershot2.w) / 2 + player.x;
		playershot2.y = (player.h - playershot2.h) / 2 + player.y;

		// 弾は現時点を持って存在するので、存在状態を保持する変数に１を代入する
		playershot2.playerShotFlag = 1;

		//ショット効果音を鳴らす
		PlaySoundMem(playershot2.soundEffect, DX_PLAYTYPE_BACK);
	}
	// 自機の弾の発射処理
	if (playershot2.playerShotFlag == 1)
	{
		// 弾を移動
		playershot2.y += playershot2.vy;

		//ボスとプレイヤーショットの当たり判定
		int playerShotLeft = playershot2.x + 50;
		int playerShotRight = playershot2.x + playershot2.w - 50;
		int playerShotTop = playershot2.y + 50;
		int playerShotBottom = playershot2.y + playershot2.h - 50;

		if (boss.aliveFlag == true)
		{
			if (((playerShotLeft > boss.x + 400 && playerShotLeft < boss.x + boss.w - 400) ||
				(boss.x + 400 > playerShotLeft && boss.x + 400 < playerShotRight)) &&
				((playerShotTop > boss.y + 500 && playerShotTop < boss.y + boss.h - 500) ||
				(boss.y + 500 > playerShotTop && boss.y - 500 < playerShotBottom)))
			{
				playershot2.playerShotFlag = 0;
				++boss.damageCount;
				if (boss.damageCount > 20)
				{
					boss.aliveFlag = false;
				}
				playershot2.score += 300;
				//被弾音を鳴らす
				PlaySoundMem(playershot2.soundExplosion, DX_PLAYTYPE_BACK);
			}
		}


		// 画面外に出てしまった場合は存在状態を保持している変数に０(存在しない)を代入する
		if (playershot2.y < -80)
		{
			playershot2.playerShotFlag = 0;
		}
	}

}

//描画
void DrawPlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player)
{
	//------------ショット関連の描画--------------//
	//プレイヤーショットの描画
	if (playershot2.playerShotFlag == 1)
	{
		// 画面に弾iを描画する
		DrawGraph(playershot2.x, playershot2.y, playershot2.graph, TRUE);
	}

}

