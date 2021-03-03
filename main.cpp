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

// �O���[�o���ϐ�
int gameStatus;

//winmain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	
	//�摜���[�h�̐ݒ�
	SetGraphMode(SCREEN_W,SCREEN_H,16);

	//�E�B���h�E�Y���[�h�L����
	ChangeWindowMode(TRUE);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//��`
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

	//�ϐ�
	int startImg;
	int subTitleImg;
	int gameOverImg;
	int gameClearImg;
	int tutorialImg;
	int clearBgm;
	int gameoverBgm;
	int titleBgm;
	int battleBgm;
	//�^�C�g���摜�����[�h
	startImg = LoadGraph("data/texture/start.png");										
	gameOverImg = LoadGraph("data/texture/gameover.png");
	gameClearImg = LoadGraph("data/texture/gameclear.png");
	tutorialImg = LoadGraph("data/texture/tutorial.png");
	subTitleImg = LoadGraph("data/texture/title1.png");
	//�T�E���h�̃��[�h
	titleBgm = LoadSoundMem("data/sound/title1.mp3");
	clearBgm = LoadSoundMem("data/sound/clear.mp3");
	gameoverBgm = LoadSoundMem("data/sound/gameover.mp3");
	battleBgm = LoadSoundMem("data/sound/battle1.mp3");
	//titleBgm = LoadSoundMem("sound/title.mp3");

	//�Q�[���X�e�[�^�X�̏�����
	gameStatus = INIT;

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	while (true)
	{
		//----------------------------------// 
		//�Q�[��������
		//----------------------------------//
		while (!ProcessMessage() && gameStatus == INIT) 						//�G���[���o����Ԃ���������������
		{
			//�`�揉����
			ClearDrawScreen();
			//�����Ȃ��~�߂�
			StopSoundMem(clearBgm);
			//�s�k�Ȃ��~�߂�
			StopSoundMem(gameoverBgm);
			//�^�C�g���Ȃ𗬂�
			PlaySoundMem(titleBgm, DX_PLAYTYPE_BACK);
			
				//�Q�[����Ԃ��^�C�g���ɂ���
			gameStatus = TITLE;
			
			//�e���������Ă�
			InitBG(bg);
			InitPlayer(player,input,enemy);
			InitEnemy(enemy);
			InitBoss(boss,player);
			InitShot(playershot, enemyshot, player, enemy, input,boss);
			InitPlayerShot(playershot2, input, boss, player);
			InitObject(object, playershot, enemyshot);
			//��ʍX�V����
			ScreenFlip();
		}
		//----------------------------------// 
		//�^�C�g�����
		//----------------------------------//
		while (!ProcessMessage() && gameStatus == TITLE)
		{

			// �X�e�[�g���؂�ւ�����u�Ԃ̓L�[��������������Z�b�g.
			rule.keyOn = false;
			rule.keyRelease = false;

			//�`�揉����
			ClearDrawScreen();
			//�Q�[���p�b�h�n
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			//�w�i�\��
			DrawGraph(0, 0, startImg, FALSE);

			//�t�H���g�T�C�Y�w��
			SetFontSize(24);
			// �L�[�������u�Ԃ����.
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
				////�`���[�g���A���ɂ���
				gameStatus = TUTORIAL;
			}
			//��ʍX�V����
			ScreenFlip();
		}
		//�J�n�x������
		WaitTimer(STATE_CHANGE_WAIT);
		//-------------------------//
		//�`���[�g���A��
		//-------------------------//
		while (!ProcessMessage() && gameStatus == TUTORIAL)
		{
			// �X�e�[�g���؂�ւ�����u�Ԃ̓L�[��������������Z�b�g.
			rule.keyOn = false;
			rule.keyRelease = false;

			//�`�揉����
			ClearDrawScreen();
			//�Q�[���p�b�h�n
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			//�w�i�\��
			DrawGraph(0, 0, tutorialImg, FALSE);
			//�t�H���g�T�C�Y�w��
			SetFontSize(24);
			// �L�[�������u�Ԃ����.
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
				//�^�C�g��BGM���~�߂�
				StopSoundMem(titleBgm);
				//�Q�[�����v���C��Ԃɂ���
				gameStatus = PLAY;
				//�o�g��BGM���Đ�����
				PlaySoundMem(battleBgm, DX_PLAYTYPE_BACK);
			}
			//��ʍX�V����
			ScreenFlip();
		}
		//�J�n�x������
		WaitTimer(STATE_CHANGE_WAIT);
		//UI�̏�����
		InitUi(ui);
		// �Q�[�����[�v.
		while (!ProcessMessage() && gameStatus == PLAY)
		{
			//�`�揉����
			ClearDrawScreen();
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			//�A�b�v�f�[�g
			UpdatePlayer(player, input,enemy);
			UpdateEnemy(enemy);
			UpdateShot(playershot, enemyshot, player, enemy, input, boss);
			UpdateObject(object, playershot, enemyshot);
			UpdataUi(ui);

			//�v���C���[���R���e������Q�[���I�[�o�[
			if (playerDamageCount == 3 || player.aliveFlag == false)
			{
				gameStatus = OVER;
				//�o�g��BGM���~�߂�
				StopSoundMem(battleBgm);
				//�Q�[���I�[�o�[BGM���Đ�����
				PlaySoundMem(gameoverBgm, DX_PLAYTYPE_BACK);

			}

			//���Ԃ�������{�X���
			if (ui.countDown <= 0)
			{
				gameStatus = TITLE1;
				//�o�g��BGM���~�߂�
				StopSoundMem(battleBgm);

			}

			//�G�����Ȃ��Ȃ�����{�X���
			if (deathCount == 48)
			{
				gameStatus = TITLE1;
				//�o�g��BGM���~�߂�
				StopSoundMem(battleBgm);
			}

			// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
			// �}�C�i�X�̒l�i�G���[�l�j���Ԃ��Ă����烋�[�v�𔲂���
			if (ProcessMessage() < 0)
			{
				break;
			}
			// �����d�r�b�L�[��������Ă����烋�[�v���甲����
			else if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}
			// ��ʂ�������(�^�����ɂ���)
			ClearDrawScreen();
			// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��)
			DrawBG(bg);
			DrawEnemy(enemy);
			DrawPlayer(player, input,enemy);
			DrawShot(playershot, enemyshot, player, enemy, input, boss);
			DrawObject(object, playershot, enemyshot);
			DrawUi(ui);
			ScreenFlip();
		}
		//�J�n�x������
		WaitTimer(STATE_CHANGE_WAIT);
		while (!ProcessMessage() && gameStatus == TITLE1)
		{
			//�`�揉����
			ClearDrawScreen();
			//�Q�[���p�b�h�n
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			//�w�i�\��
			DrawGraph(0, 0, subTitleImg, FALSE);

			//�t�H���g�T�C�Y�w��
			SetFontSize(24);
			//�o�g��BGM���Đ�����
			PlaySoundMem(battleBgm, DX_PLAYTYPE_BACK);
			gameStatus = BOSS;
			//��ʍX�V����
			ScreenFlip();
		}
		//�J�n�x������
		WaitTimer(1000);
		//�{�X�O�Ƀv���C���[�̏�����
		InitPlayer(player, input,enemy);

		// �{�X�Q�[�����[�v.
		while (!ProcessMessage() && gameStatus == BOSS)
		{
			//�`�揉����
			ClearDrawScreen();
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			InitBossUi(bossui);

			//�A�b�v�f�[�g
			UpdatePlayer(player, input,enemy);
			UpdateBoss(boss,player);
			UpdatePlayerShot(playershot2,input,boss,player);
			UpdateObject(object, playershot, enemyshot);
			UpdataBossUi(bossui);
			//�v���C���[���R���e������Q�[���I�[�o�[
			if (player.aliveFlag == false)
			{
				gameStatus = OVER;
				//�o�g��BGM���~�߂�
				StopSoundMem(battleBgm);
				//�Q�[���I�[�o�[BGM���Đ�����
				PlaySoundMem(gameoverBgm, DX_PLAYTYPE_BACK);

			}
			//�G�����Ȃ��Ȃ�����Q�[���N���A
			if (boss.aliveFlag == false)
			{
				gameStatus = CLEAR;
				//�o�g��BGM���~�߂�
				StopSoundMem(battleBgm);
				//�N���ABGM���Đ�����
				PlaySoundMem(clearBgm, DX_PLAYTYPE_BACK);

			}

			// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
			// �}�C�i�X�̒l�i�G���[�l�j���Ԃ��Ă����烋�[�v�𔲂���
			if (ProcessMessage() < 0)
			{
				break;
			}
			// �����d�r�b�L�[��������Ă����烋�[�v���甲����
			else if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}
			// ��ʂ�������(�^�����ɂ���)
			ClearDrawScreen();
			// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��)
			DrawBG(bg);
			DrawBoss(boss,player);
			DrawPlayer(player, input,enemy);
			DrawPlayerShot(playershot2,input,boss,player);
			DrawObject(object, playershot, enemyshot);
			DrawBossUi(bossui);
			ScreenFlip();
		}

		//----------------------------------//
		//�Q�[���I�[�o�[���
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == OVER)
		{
			//�`�揉����
			ClearDrawScreen();

			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			//�Q�[���I�[�o�[�摜�̕`��
			DrawGraph(0, 0, gameOverImg, FALSE);
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4])
			{
				//�Q�[��������������
				gameStatus = INIT;
			}
			//��ʍX�V����
			ScreenFlip();
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}

		}
		//�J�n�x������
		WaitTimer(STATE_CHANGE_WAIT);

		//----------------------------------//
		//�Q�[���N���A���
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == CLEAR)
		{
			//�`�揉����
			ClearDrawScreen();

			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			//�Q�[���N���A�̉摜��`��
			DrawGraph(0, 0, gameClearImg, FALSE);

			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4])
			{
				//���^�[���L�[�Ń^�C�g��
				gameStatus = INIT;
			}
			//��ʍX�V����
			ScreenFlip();
		}
		//�J�n�x������
		WaitTimer(STATE_CHANGE_WAIT);
	}
	// �c�w���C�u�����g�p�̏I������
	DxLib_End();
	// �\�t�g�̏I��
	return 0;
}


