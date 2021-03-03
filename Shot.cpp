#include "function.h"
#include "Shot.h"
#include "player.h"
#include "Enemy.h"
#include "boss.h"

//プレイヤーの被弾カウント
int playerDamageCount;
//ショット系
int shotCount;

//エネミーのカウント系
int deathCount;
bool shotFlag;
bool shotFlag2;
bool shotFlag3;

int attackEnemyNum;
int attackEnemyNum2;
int attackEnemyNum3;

//プレイヤーライフ系
const int playerLifeMax = 3;
struct Playerlife
{
	int graph = { -1 };
	int x;
	int y;
};
Playerlife playerlife[3];

XINPUT_STATE input;

//初期化
void InitShot(PlayerShot &playershot, EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE &input, Boss& boss)
{
	//------プレイヤーショット関連------//
	//プレイヤーショットのロード
	playershot.graph = LoadGraph("data/texture/playershot5.png");

	//プレイヤーショットのサイズを得る
	GetGraphSize(playershot.graph, &playershot.w, &playershot.h);

	//プレイヤーショットの初期位置
	playershot.x = (player.x + player.w);
	playershot.y = (player.y + player.h);

	//プレイヤーショットの速度
	playershot.vy = -20;
	playershot.playerShotFlag = false;
	
	//プレイヤーショットの効果音をロード
	playershot.soundEffect = LoadSoundMem("data/sound/playerEffect.mp3");
	playershot.soundExplosion = LoadSoundMem("data/sound/playerExplosion.mp3");

	//プレイヤーライフ画像ロード
	for (size_t i = 0; i < playerLifeMax; i++)
	{
		playerlife[i].graph = LoadGraph("data/texture/playerlife.png");
	}
	//プレイヤーライフ画像初期位置
	for (size_t i = 0; i < playerLifeMax; i++)
	{
		playerlife[i].x = (i + 10) * 50;
		playerlife[i].y = 0;
	}
	//------エネミーショット関連------//
	//エネミーショットのグラフィックをロード
	for (size_t i = 0; i < enemyShotMax; i++)
	{
		enemyshot[i].graph = LoadGraph("data/texture/enemyshot1.3.png");
	}

	//エネミーショットのグラフィックサイズを得る
	for (size_t i = 0; i < enemyShotMax; i++)
	{
		GetGraphSize(enemyshot[i].graph, &enemyshot[i].w, &enemyshot[i].h);
	}

	//エネミーのショットフラグを初期化
	shotFlag = false;
	shotFlag2 = false;
	shotFlag3 = false;

	//エネミーショットカウントの初期化
	shotCount = 0;

	//エネミーの死亡カウントの初期化
	deathCount = 0;

	//エネミーショットの速度の初期化
	for(size_t i = 0; i < enemyShotMax; i++)
	{
		enemyshot[i].vy = 20;
		enemyshot[i].vy2 = 35;
		enemyshot[i].vy3 = 85;
	}
	//プレイヤー被弾カウント初期化
	playerDamageCount = 0;
	//エネミーショットの効果音をロード
	for (size_t i = 0; i < enemyShotMax; i++)
	{
		enemyshot[i].soundEffect = LoadSoundMem("data/sound/enemyEffect.mp3");
		enemyshot[i].soundExplosion = LoadSoundMem("data/sound/enemyExplosion.mp3");
	}
}
//アップデート
void UpdateShot(PlayerShot &playershot, EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE &input, Boss& boss)
{
	//------プレイヤーショットアップデート------//
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && playershot.playerShotFlag == 0 || input.Buttons[12] && playershot.playerShotFlag == 0)
	{
		//プレイヤーと弾の画像のサイズを得る
		for (size_t i = 0; i < 4; i++)
		{
			GetGraphSize(player.graph[i], &player.w, &player.h);
		}
		//画像サイズを得る
		GetGraphSize(playershot.graph, &playershot.w, &playershot.h);

		// 弾の位置をセット、位置はプレイヤーの中心にする		
		playershot.x = (player.w - playershot.w) / 2 + player.x;
		playershot.y = (player.h - playershot.h) / 2 + player.y;

		// 弾は現時点を持って存在するので、存在状態を保持する変数に１を代入する
		playershot.playerShotFlag = 1;
		
		//ショット効果音を鳴らす
		PlaySoundMem(playershot.soundEffect, DX_PLAYTYPE_BACK);
	}
	// 自機の弾の発射処理
	if (playershot.playerShotFlag == 1)
	{
		// 弾を移動
		playershot.y += playershot.vy;

		//エネミーとプレイヤーショットの当たり判定
		int playerShotLeft = playershot.x + 50;
		int playerShotRight = playershot.x + playershot.w - 50;
		int playerShotTop = playershot.y +50;
		int playerShotBottom = playershot.y + playershot.h - 50;

		for (size_t i = 0; i < enemyMax; i++)
		{
			if (enemy[i].aliveFlag == true)
			{
				if (((playerShotLeft > enemy[i].x + 30 && playerShotLeft < enemy[i].x + enemy[i].w - 30) ||
					(enemy[i].x + 30 > playerShotLeft && enemy[i].x + 30 < playerShotRight)) &&
					((playerShotTop > enemy[i].y + 50 && playerShotTop < enemy[i].y + enemy[i].h - 50) ||
					(enemy[i].y + 50 > playerShotTop && enemy[i].y - 50 < playerShotBottom)))
				{
					playershot.playerShotFlag = 0;
					enemy[i].aliveFlag = false;
					++deathCount;
					//playershot.score += 300;
					//被弾音を鳴らす
					PlaySoundMem(playershot.soundExplosion, DX_PLAYTYPE_BACK);
				}
			}
		}

		// 画面外に出てしまった場合は存在状態を保持している変数に０(存在しない)を代入する
		if (playershot.y < -80)
		{
			playershot.playerShotFlag = 0;
		}
	}



	//------エネミーショットアップデート-------//
	//エネミーのショットカウントをカウント
	++shotCount;
	//エネミーショット１
	// もしカウンター変数がだった場合は弾を撃つ処理を行う
	if (shotCount % 90 == 0)
	{
		//ショットを撃つエネミーを決定
		attackEnemyNum = rand() % 49;

		//撃つエネミーが生きている時
		if (enemy[attackEnemyNum].aliveFlag == true)
		{
			// もし既に弾が『飛んでいない』状態だった場合のみ発射処理を行う
			if (shotFlag == false)
			{
				//弾の発射位置を設定する
				enemyshot[attackEnemyNum].x = enemy[attackEnemyNum].x + enemy[0].w / 2 - enemyshot[attackEnemyNum].w / 2;
				enemyshot[attackEnemyNum].y = enemy[attackEnemyNum].y + enemy[0].h / 2 - enemyshot[attackEnemyNum].h / 2;

				//弾の状態を保持する変数に『飛んでいる』を示す１を代入する
				shotFlag = true;
				//エネミーショットの効果音をならす
				PlaySoundMem(enemyshot[attackEnemyNum].soundExplosion, DX_PLAYTYPE_BACK);
			}
		}
	}
	//エネミーショットの状態が『飛んでいる』場合のみ弾の移動処理を行う
	if (shotFlag == true)
	{
		// 少し下にずらす
		enemyshot[attackEnemyNum].y += enemyshot[attackEnemyNum].vy;
		//プレイヤーとエネミーショットの当たり判定
		int enemyShotLeft = enemyshot[attackEnemyNum].x + 10;
		int enemyShotRight = enemyshot[attackEnemyNum].x + enemyshot[attackEnemyNum].w - 10;
		int enemyShotTop = enemyshot[attackEnemyNum].y;
		int enemyShotBottom = enemyshot[attackEnemyNum].y + enemyshot[attackEnemyNum].h;
		int playerLeft = player.x + 30;
		int playerRight = player.x + player.w - 30;
		int playerTop = player.y + 20;
		int playerBottom = player.y + player.h -20;

		if (((enemyShotLeft > playerLeft && enemyShotLeft < playerRight) ||
			(playerLeft > enemyShotLeft && playerLeft < enemyShotRight)) &&
			((enemyShotTop > playerTop && enemyShotTop < playerBottom) ||
			(playerTop > enemyShotTop && playerTop < enemyShotBottom)))
		{
			shotFlag = false;
			++playerDamageCount;
			PlaySoundMem(enemyshot[attackEnemyNum].soundExplosion, DX_PLAYTYPE_BACK);
			player.damegeFlag = true;
		}

		// もし弾が画面下端からはみ出てしまった場合は弾の状態を『飛んでいない』
		// を表す０にする
		if (enemyshot[attackEnemyNum].y > SCREEN_H)
		{
			shotFlag = false;
		}
	}
	//エネミーショット２
	// もしカウンター変数がだった場合は弾を撃つ処理を行う
	if (shotCount % 120 == 0)
	{
		//ショットを撃つエネミーを決定
		attackEnemyNum2 = rand() % 49;

		//撃つエネミーが生きている時
		if (enemy[attackEnemyNum2].aliveFlag == true)
		{
			// もし既に弾が『飛んでいない』状態だった場合のみ発射処理を行う
			if (shotFlag2 == false)
			{
				//弾の発射位置を設定する
				enemyshot[attackEnemyNum2].x = enemy[attackEnemyNum2].x + enemy[0].w / 2 - enemyshot[attackEnemyNum2].w / 2;
				enemyshot[attackEnemyNum2].y = enemy[attackEnemyNum2].y + enemy[0].h / 2 - enemyshot[attackEnemyNum2].h / 2;

				//弾の状態を保持する変数に『飛んでいる』を示す１を代入する
				shotFlag2 = true;
				PlaySoundMem(enemyshot[attackEnemyNum2].soundExplosion, DX_PLAYTYPE_BACK);
			}
		}
	}
	//エネミーショットの状態が『飛んでいる』場合のみ弾の移動処理を行う
	if (shotFlag2 == true)
	{
		// 少し下にずらす
		enemyshot[attackEnemyNum2].y += enemyshot[attackEnemyNum2].vy2;
		//プレイヤーとエネミーショットの当たり判定
		int enemyShotLeft = enemyshot[attackEnemyNum2].x + 10;
		int enemyShotRight = enemyshot[attackEnemyNum2].x + enemyshot[attackEnemyNum2].w - 10;
		int enemyShotTop = enemyshot[attackEnemyNum2].y;
		int enemyShotBottom = enemyshot[attackEnemyNum2].y + enemyshot[attackEnemyNum2].h;
		int playerLeft = player.x + 30;
		int playerRight = player.x + player.w - 30;
		int playerTop = player.y + 20;
		int playerBottom = player.y + player.h - 20;
		if (((enemyShotLeft > playerLeft && enemyShotLeft < playerRight) ||
			(playerLeft > enemyShotLeft && playerLeft < enemyShotRight)) &&
			((enemyShotTop > playerTop && enemyShotTop < playerBottom) ||
			(playerTop > enemyShotTop && playerTop < enemyShotBottom)))
		{
			shotFlag2 = false;
			++playerDamageCount;
			player.damegeFlag = true;
			PlaySoundMem(enemyshot[attackEnemyNum2].soundExplosion, DX_PLAYTYPE_BACK);
		}

		// もし弾が画面下端からはみ出てしまった場合は弾の状態を『飛んでいない』
		// を表す０にする
		if (enemyshot[attackEnemyNum2].y > SCREEN_H)
		{
			shotFlag2 = false;
		}
	}
	//エネミーショット3
	// もしカウンター変数がだった場合は弾を撃つ処理を行う
	if (shotCount % 180 == 0)
	{
		//ショットを撃つエネミーを決定
		attackEnemyNum3 = rand() % 49;

		//撃つエネミーが生きている時
		if (enemy[attackEnemyNum3].aliveFlag == true)
		{
			// もし既に弾が『飛んでいない』状態だった場合のみ発射処理を行う
			if (shotFlag3 == false)
			{
				//弾の発射位置を設定する
				enemyshot[attackEnemyNum3].x = enemy[attackEnemyNum3].x + enemy[0].w / 2 - enemyshot[attackEnemyNum3].w / 2;
				enemyshot[attackEnemyNum3].y = enemy[attackEnemyNum3].y + enemy[0].h / 2 - enemyshot[attackEnemyNum3].h / 2;

				//弾の状態を保持する変数に『飛んでいる』を示す１を代入する
				shotFlag3 = true;
				PlaySoundMem(enemyshot[attackEnemyNum3].soundExplosion, DX_PLAYTYPE_BACK);

			}
		}
	}
	//エネミーショットの状態が『飛んでいる』場合のみ弾の移動処理を行う
	if (shotFlag3 == true)
	{
		// 少し下にずらす
		enemyshot[attackEnemyNum3].y += enemyshot[attackEnemyNum3].vy2;
		//プレイヤーとエネミーショットの当たり判定
		int enemyShotLeft = enemyshot[attackEnemyNum3].x + 10;
		int enemyShotRight = enemyshot[attackEnemyNum3].x + enemyshot[attackEnemyNum3].w - 10;
		int enemyShotTop = enemyshot[attackEnemyNum3].y;
		int enemyShotBottom = enemyshot[attackEnemyNum3].y + enemyshot[attackEnemyNum3].h;
		int playerLeft = player.x + 30;
		int playerRight = player.x + player.w - 30;
		int playerTop = player.y + 20;
		int playerBottom = player.y + player.h - 20;

		if (((enemyShotLeft > playerLeft && enemyShotLeft < playerRight) ||
			(playerLeft > enemyShotLeft && playerLeft < enemyShotRight)) &&
			((enemyShotTop > playerTop && enemyShotTop < playerBottom) ||
			(playerTop > enemyShotTop && playerTop < enemyShotBottom)))
		{
			shotFlag3 = false;
			++playerDamageCount;
			player.damegeFlag = true;
			PlaySoundMem(enemyshot[attackEnemyNum3].soundExplosion, DX_PLAYTYPE_BACK);
		}
		// もし弾が画面下端からはみ出てしまった場合は弾の状態を『飛んでいない』
		// を表す０にする
		if (enemyshot[attackEnemyNum3].y > SCREEN_H)
		{
			shotFlag3 = false;
		}
	}
}
//描画
void DrawShot(PlayerShot &playershot, EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE& input, Boss& boss)
{
	//------------ショット関連の描画--------------//
	//プレイヤーショットの描画
	if (playershot.playerShotFlag == 1)
	{
		// 画面に弾iを描画する
		DrawGraph(playershot.x, playershot.y, playershot.graph, TRUE);
	}
	////スコアの表示
	//DrawFormatString(1600, 20, GetColor(0, 0, 0), "スコア　%d", playershot.score);
	//エネミーショットの描画
	if (shotFlag == true)
	{
		DrawGraph(enemyshot[attackEnemyNum].x, enemyshot[attackEnemyNum].y, enemyshot[attackEnemyNum].graph, TRUE);
	}
	//エネミーショット2の描画
	if (shotFlag2 == true)
	{
		DrawGraph(enemyshot[attackEnemyNum2].x, enemyshot[attackEnemyNum2].y, enemyshot[attackEnemyNum2].graph, TRUE);
	}
	//エネミーショット3の描画
	if (shotFlag3 == true)
	{
		DrawGraph(enemyshot[attackEnemyNum3].x, enemyshot[attackEnemyNum3].y, enemyshot[attackEnemyNum3].graph, TRUE);
	}
	//---------------プレイヤーライフ関連------------------//
	//プレイヤーライフ画像の描画
	if (playerDamageCount == 0)
	{
		DrawGraph(playerlife[0].x, playerlife[0].y, playerlife[0].graph, TRUE);
		DrawGraph(playerlife[1].x, playerlife[1].y, playerlife[1].graph, TRUE);
		DrawGraph(playerlife[2].x, playerlife[2].y, playerlife[2].graph, TRUE);
	}
	if (playerDamageCount == 1)
	{
		DrawGraph(playerlife[0].x, playerlife[0].y, playerlife[0].graph, TRUE);
		DrawGraph(playerlife[1].x, playerlife[1].y, playerlife[1].graph, TRUE);
	}
	if (playerDamageCount == 2)
	{
		DrawGraph(playerlife[0].x, playerlife[0].y, playerlife[0].graph, TRUE);
	}
}



