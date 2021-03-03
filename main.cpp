#include "BackGraund.h"
#include "function.h"
#include "Shot.h"
#include "shot2.h"
#include "player.h"
#include "Enemy.h"
#include "boss.h"
#include "object.h"
#include "Ui.h"
#include "bossUi.h"
#include "DxLib.h"

// グローバル変数
int gameStatus;

//winmain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	
	//画像モードの設定
	SetGraphMode(SCREEN_W,SCREEN_H,16);

	//ウィンドウズモード有効化
	ChangeWindowMode(TRUE);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//定義
	Bg bg;
	Player player;
	PlayerShot playershot;
	Playershot2 playershot2;
	Enemy enemy[enemyMax];
	EnemyShot enemyshot[enemyShotMax];
	Object object[objectMax];
	Ui ui;
	Rule rule;
	Boss boss;
	BossUi bossui;
	//PLAYERLIFE playerlife[playerLifeMax];

	//変数
	int startImg;
	int subTitleImg;
	int gameOverImg;
	int gameClearImg;
	int tutorialImg;
	int clearBgm;
	int gameoverBgm;
	int titleBgm;
	int battleBgm;
	//タイトル画像をロード
	startImg = LoadGraph("data/texture/start.png");										
	gameOverImg = LoadGraph("data/texture/gameover.png");
	gameClearImg = LoadGraph("data/texture/gameclear.png");
	tutorialImg = LoadGraph("data/texture/tutorial.png");
	subTitleImg = LoadGraph("data/texture/title1.png");
	//サウンドのロード
	titleBgm = LoadSoundMem("data/sound/title1.mp3");
	clearBgm = LoadSoundMem("data/sound/clear.mp3");
	gameoverBgm = LoadSoundMem("data/sound/gameover.mp3");
	battleBgm = LoadSoundMem("data/sound/battle1.mp3");
	//titleBgm = LoadSoundMem("sound/title.mp3");

	//ゲームステータスの初期化
	gameStatus = INIT;

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	while (true)
	{
		//----------------------------------// 
		//ゲーム初期化
		//----------------------------------//
		while (!ProcessMessage() && gameStatus == INIT) 						//エラーが出ず状態が初期化だったら
		{
			//描画初期化
			ClearDrawScreen();
			//勝利曲を止める
			StopSoundMem(clearBgm);
			//敗北曲を止める
			StopSoundMem(gameoverBgm);
			//タイトル曲を流す
			PlaySoundMem(titleBgm, DX_PLAYTYPE_BACK);
			
				//ゲーム状態をタイトルにする
			gameStatus = TITLE;
			
			//各初期化を呼ぶ
			InitBG(bg);
			InitPlayer(player,input,enemy);
			InitEnemy(enemy);
			InitBoss(boss,player);
			InitShot(playershot, enemyshot, player, enemy, input,boss);
			InitPlayerShot(playershot2, input, boss, player);
			InitObject(object, playershot, enemyshot);
			//画面更新処理
			ScreenFlip();
		}
		//----------------------------------// 
		//タイトル画面
		//----------------------------------//
		while (!ProcessMessage() && gameStatus == TITLE)
		{

			// ステートが切り替わった瞬間はキー離した判定をリセット.
			rule.keyOn = false;
			rule.keyRelease = false;

			//描画初期化
			ClearDrawScreen();
			//ゲームパッド系
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			//背景表示
			DrawGraph(0, 0, startImg, FALSE);

			//フォントサイズ指定
			SetFontSize(24);
			// キー離した瞬間を取る.
			if (rule.keyOn)
			{
				if (CheckHitKey(KEY_INPUT_SPACE) == 0 || input.Buttons[4])
				{
					rule.keyOn = false;
					rule.keyRelease = true;
				}
			}
			else if (rule.prevKeyOn == false && CheckHitKey(KEY_INPUT_SPACE) == 1 || rule.prevKeyOn == false && input.Buttons[4])
			{
				rule.keyRelease = false;
				rule.keyOn = true;
			}
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4])
			{
				rule.prevKeyOn = true;
			}
			else
			{
				rule.prevKeyOn = false;
			}

			if (CheckHitKey(KEY_INPUT_SPACE)||input.Buttons[4])
			{
				////チュートリアルにする
				gameStatus = TUTORIAL;
			}
			//画面更新処理
			ScreenFlip();
		}
		//開始遅延処理
		WaitTimer(STATE_CHANGE_WAIT);
		//-------------------------//
		//チュートリアル
		//-------------------------//
		while (!ProcessMessage() && gameStatus == TUTORIAL)
		{
			// ステートが切り替わった瞬間はキー離した判定をリセット.
			rule.keyOn = false;
			rule.keyRelease = false;

			//描画初期化
			ClearDrawScreen();
			//ゲームパッド系
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			//背景表示
			DrawGraph(0, 0, tutorialImg, FALSE);
			//フォントサイズ指定
			SetFontSize(24);
			// キー離した瞬間を取る.
			if (rule.keyOn)
			{
				if (CheckHitKey(KEY_INPUT_SPACE) == 0 || input.Buttons[4])
				{
					rule.keyOn = false;
					rule.keyRelease = true;
				}
			}
			else if (rule.prevKeyOn == false && CheckHitKey(KEY_INPUT_SPACE) == 1 || rule.prevKeyOn == false && input.Buttons[4])
			{
				rule.keyRelease = false;
				rule.keyOn = true;
			}
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4])
			{
				rule.prevKeyOn = true;
			}
			else
			{
				rule.prevKeyOn = false;
			}

			if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[4])
			{
				//タイトルBGMを止める
				StopSoundMem(titleBgm);
				//ゲームをプレイ状態にする
				gameStatus = PLAY;
				//バトルBGMを再生する
				PlaySoundMem(battleBgm, DX_PLAYTYPE_BACK);
			}
			//画面更新処理
			ScreenFlip();
		}
		//開始遅延処理
		WaitTimer(STATE_CHANGE_WAIT);
		//UIの初期化
		InitUi(ui);
		// ゲームループ.
		while (!ProcessMessage() && gameStatus == PLAY)
		{
			//描画初期化
			ClearDrawScreen();
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			//アップデート
			UpdatePlayer(player, input,enemy);
			UpdateEnemy(enemy);
			UpdateShot(playershot, enemyshot, player, enemy, input, boss);
			UpdateObject(object, playershot, enemyshot);
			UpdataUi(ui);

			//プレイヤーが３回被弾したらゲームオーバー
			if (playerDamageCount == 3 || player.aliveFlag == false)
			{
				gameStatus = OVER;
				//バトルBGMを止める
				StopSoundMem(battleBgm);
				//ゲームオーバーBGMを再生する
				PlaySoundMem(gameoverBgm, DX_PLAYTYPE_BACK);

			}

			//時間が来たらボス戦へ
			if (ui.countDown <= 0)
			{
				gameStatus = TITLE1;
				//バトルBGMを止める
				StopSoundMem(battleBgm);

			}

			//敵がいなくなったらボス戦へ
			if (deathCount == 48)
			{
				gameStatus = TITLE1;
				//バトルBGMを止める
				StopSoundMem(battleBgm);
			}

			// Windows 特有の面倒な処理をＤＸライブラリにやらせる
			// マイナスの値（エラー値）が返ってきたらループを抜ける
			if (ProcessMessage() < 0)
			{
				break;
			}
			// もしＥＳＣキーが押されていたらループから抜ける
			else if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}
			// 画面を初期化(真っ黒にする)
			ClearDrawScreen();
			// 裏画面の内容を表画面にコピーする（描画の確定)
			DrawBG(bg);
			DrawEnemy(enemy);
			DrawPlayer(player, input,enemy);
			DrawShot(playershot, enemyshot, player, enemy, input, boss);
			DrawObject(object, playershot, enemyshot);
			DrawUi(ui);
			ScreenFlip();
		}
		//開始遅延処理
		WaitTimer(STATE_CHANGE_WAIT);
		while (!ProcessMessage() && gameStatus == TITLE1)
		{
			//描画初期化
			ClearDrawScreen();
			//ゲームパッド系
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			//背景表示
			DrawGraph(0, 0, subTitleImg, FALSE);

			//フォントサイズ指定
			SetFontSize(24);
			//バトルBGMを再生する
			PlaySoundMem(battleBgm, DX_PLAYTYPE_BACK);
			gameStatus = BOSS;
			//画面更新処理
			ScreenFlip();
		}
		//開始遅延処理
		WaitTimer(1000);
		//ボス前にプレイヤーの初期化
		InitPlayer(player, input,enemy);

		// ボスゲームループ.
		while (!ProcessMessage() && gameStatus == BOSS)
		{
			//描画初期化
			ClearDrawScreen();
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			InitBossUi(bossui);

			//アップデート
			UpdatePlayer(player, input,enemy);
			UpdateBoss(boss,player);
			UpdatePlayerShot(playershot2,input,boss,player);
			UpdateObject(object, playershot, enemyshot);
			UpdataBossUi(bossui);
			//プレイヤーが３回被弾したらゲームオーバー
			if (player.aliveFlag == false)
			{
				gameStatus = OVER;
				//バトルBGMを止める
				StopSoundMem(battleBgm);
				//ゲームオーバーBGMを再生する
				PlaySoundMem(gameoverBgm, DX_PLAYTYPE_BACK);

			}
			//敵がいなくなったらゲームクリア
			if (boss.aliveFlag == false)
			{
				gameStatus = CLEAR;
				//バトルBGMを止める
				StopSoundMem(battleBgm);
				//クリアBGMを再生する
				PlaySoundMem(clearBgm, DX_PLAYTYPE_BACK);

			}

			// Windows 特有の面倒な処理をＤＸライブラリにやらせる
			// マイナスの値（エラー値）が返ってきたらループを抜ける
			if (ProcessMessage() < 0)
			{
				break;
			}
			// もしＥＳＣキーが押されていたらループから抜ける
			else if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}
			// 画面を初期化(真っ黒にする)
			ClearDrawScreen();
			// 裏画面の内容を表画面にコピーする（描画の確定)
			DrawBG(bg);
			DrawBoss(boss,player);
			DrawPlayer(player, input,enemy);
			DrawPlayerShot(playershot2,input,boss,player);
			DrawObject(object, playershot, enemyshot);
			DrawBossUi(bossui);
			ScreenFlip();
		}

		//----------------------------------//
		//ゲームオーバー画面
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == OVER)
		{
			//描画初期化
			ClearDrawScreen();

			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			//ゲームオーバー画像の描画
			DrawGraph(0, 0, gameOverImg, FALSE);
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4])
			{
				//ゲームを初期化する
				gameStatus = INIT;
			}
			//画面更新処理
			ScreenFlip();
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}

		}
		//開始遅延処理
		WaitTimer(STATE_CHANGE_WAIT);

		//----------------------------------//
		//ゲームクリア画面
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == CLEAR)
		{
			//描画初期化
			ClearDrawScreen();

			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			//ゲームクリアの画像を描画
			DrawGraph(0, 0, gameClearImg, FALSE);

			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4])
			{
				//リターンキーでタイトル
				gameStatus = INIT;
			}
			//画面更新処理
			ScreenFlip();
		}
		//開始遅延処理
		WaitTimer(STATE_CHANGE_WAIT);
	}
	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	// ソフトの終了
	return 0;
}


