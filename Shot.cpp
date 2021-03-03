#include "function.h"
#include "Shot.h"
#include "player.h"
#include "Enemy.h"
#include "boss.h"

//�v���C���[�̔�e�J�E���g
int playerDamageCount;
//�V���b�g�n
int shotCount;

//�G�l�~�[�̃J�E���g�n
int deathCount;
bool shotFlag;
bool shotFlag2;
bool shotFlag3;

int attackEnemyNum;
int attackEnemyNum2;
int attackEnemyNum3;

//�v���C���[���C�t�n
const int playerLifeMax = 3;
struct Playerlife
{
	int graph = { -1 };
	int x;
	int y;
};
Playerlife playerlife[3];

XINPUT_STATE input;

//������
void InitShot(PlayerShot &playershot, EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE &input, Boss& boss)
{
	//------�v���C���[�V���b�g�֘A------//
	//�v���C���[�V���b�g�̃��[�h
	playershot.graph = LoadGraph("data/texture/playershot5.png");

	//�v���C���[�V���b�g�̃T�C�Y�𓾂�
	GetGraphSize(playershot.graph, &playershot.w, &playershot.h);

	//�v���C���[�V���b�g�̏����ʒu
	playershot.x = (player.x + player.w);
	playershot.y = (player.y + player.h);

	//�v���C���[�V���b�g�̑��x
	playershot.vy = -20;
	playershot.playerShotFlag = false;
	
	//�v���C���[�V���b�g�̌��ʉ������[�h
	playershot.soundEffect = LoadSoundMem("data/sound/playerEffect.mp3");
	playershot.soundExplosion = LoadSoundMem("data/sound/playerExplosion.mp3");

	//�v���C���[���C�t�摜���[�h
	for (size_t i = 0; i < playerLifeMax; i++)
	{
		playerlife[i].graph = LoadGraph("data/texture/playerlife.png");
	}
	//�v���C���[���C�t�摜�����ʒu
	for (size_t i = 0; i < playerLifeMax; i++)
	{
		playerlife[i].x = (i + 10) * 50;
		playerlife[i].y = 0;
	}
	//------�G�l�~�[�V���b�g�֘A------//
	//�G�l�~�[�V���b�g�̃O���t�B�b�N�����[�h
	for (size_t i = 0; i < enemyShotMax; i++)
	{
		enemyshot[i].graph = LoadGraph("data/texture/enemyshot1.3.png");
	}

	//�G�l�~�[�V���b�g�̃O���t�B�b�N�T�C�Y�𓾂�
	for (size_t i = 0; i < enemyShotMax; i++)
	{
		GetGraphSize(enemyshot[i].graph, &enemyshot[i].w, &enemyshot[i].h);
	}

	//�G�l�~�[�̃V���b�g�t���O��������
	shotFlag = false;
	shotFlag2 = false;
	shotFlag3 = false;

	//�G�l�~�[�V���b�g�J�E���g�̏�����
	shotCount = 0;

	//�G�l�~�[�̎��S�J�E���g�̏�����
	deathCount = 0;

	//�G�l�~�[�V���b�g�̑��x�̏�����
	for(size_t i = 0; i < enemyShotMax; i++)
	{
		enemyshot[i].vy = 20;
		enemyshot[i].vy2 = 35;
		enemyshot[i].vy3 = 85;
	}
	//�v���C���[��e�J�E���g������
	playerDamageCount = 0;
	//�G�l�~�[�V���b�g�̌��ʉ������[�h
	for (size_t i = 0; i < enemyShotMax; i++)
	{
		enemyshot[i].soundEffect = LoadSoundMem("data/sound/enemyEffect.mp3");
		enemyshot[i].soundExplosion = LoadSoundMem("data/sound/enemyExplosion.mp3");
	}
}
//�A�b�v�f�[�g
void UpdateShot(PlayerShot &playershot, EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE &input, Boss& boss)
{
	//------�v���C���[�V���b�g�A�b�v�f�[�g------//
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && playershot.playerShotFlag == 0 || input.Buttons[12] && playershot.playerShotFlag == 0)
	{
		//�v���C���[�ƒe�̉摜�̃T�C�Y�𓾂�
		for (size_t i = 0; i < 4; i++)
		{
			GetGraphSize(player.graph[i], &player.w, &player.h);
		}
		//�摜�T�C�Y�𓾂�
		GetGraphSize(playershot.graph, &playershot.w, &playershot.h);

		// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���		
		playershot.x = (player.w - playershot.w) / 2 + player.x;
		playershot.y = (player.h - playershot.h) / 2 + player.y;

		// �e�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
		playershot.playerShotFlag = 1;
		
		//�V���b�g���ʉ���炷
		PlaySoundMem(playershot.soundEffect, DX_PLAYTYPE_BACK);
	}
	// ���@�̒e�̔��ˏ���
	if (playershot.playerShotFlag == 1)
	{
		// �e���ړ�
		playershot.y += playershot.vy;

		//�G�l�~�[�ƃv���C���[�V���b�g�̓����蔻��
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
					//��e����炷
					PlaySoundMem(playershot.soundExplosion, DX_PLAYTYPE_BACK);
				}
			}
		}

		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ��ɂO(���݂��Ȃ�)��������
		if (playershot.y < -80)
		{
			playershot.playerShotFlag = 0;
		}
	}



	//------�G�l�~�[�V���b�g�A�b�v�f�[�g-------//
	//�G�l�~�[�̃V���b�g�J�E���g���J�E���g
	++shotCount;
	//�G�l�~�[�V���b�g�P
	// �����J�E���^�[�ϐ����������ꍇ�͒e�����������s��
	if (shotCount % 90 == 0)
	{
		//�V���b�g�����G�l�~�[������
		attackEnemyNum = rand() % 49;

		//���G�l�~�[�������Ă��鎞
		if (enemy[attackEnemyNum].aliveFlag == true)
		{
			// �������ɒe���w���ł��Ȃ��x��Ԃ������ꍇ�̂ݔ��ˏ������s��
			if (shotFlag == false)
			{
				//�e�̔��ˈʒu��ݒ肷��
				enemyshot[attackEnemyNum].x = enemy[attackEnemyNum].x + enemy[0].w / 2 - enemyshot[attackEnemyNum].w / 2;
				enemyshot[attackEnemyNum].y = enemy[attackEnemyNum].y + enemy[0].h / 2 - enemyshot[attackEnemyNum].h / 2;

				//�e�̏�Ԃ�ێ�����ϐ��Ɂw���ł���x�������P��������
				shotFlag = true;
				//�G�l�~�[�V���b�g�̌��ʉ����Ȃ炷
				PlaySoundMem(enemyshot[attackEnemyNum].soundExplosion, DX_PLAYTYPE_BACK);
			}
		}
	}
	//�G�l�~�[�V���b�g�̏�Ԃ��w���ł���x�ꍇ�̂ݒe�̈ړ��������s��
	if (shotFlag == true)
	{
		// �������ɂ��炷
		enemyshot[attackEnemyNum].y += enemyshot[attackEnemyNum].vy;
		//�v���C���[�ƃG�l�~�[�V���b�g�̓����蔻��
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

		// �����e����ʉ��[����͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
		// ��\���O�ɂ���
		if (enemyshot[attackEnemyNum].y > SCREEN_H)
		{
			shotFlag = false;
		}
	}
	//�G�l�~�[�V���b�g�Q
	// �����J�E���^�[�ϐ����������ꍇ�͒e�����������s��
	if (shotCount % 120 == 0)
	{
		//�V���b�g�����G�l�~�[������
		attackEnemyNum2 = rand() % 49;

		//���G�l�~�[�������Ă��鎞
		if (enemy[attackEnemyNum2].aliveFlag == true)
		{
			// �������ɒe���w���ł��Ȃ��x��Ԃ������ꍇ�̂ݔ��ˏ������s��
			if (shotFlag2 == false)
			{
				//�e�̔��ˈʒu��ݒ肷��
				enemyshot[attackEnemyNum2].x = enemy[attackEnemyNum2].x + enemy[0].w / 2 - enemyshot[attackEnemyNum2].w / 2;
				enemyshot[attackEnemyNum2].y = enemy[attackEnemyNum2].y + enemy[0].h / 2 - enemyshot[attackEnemyNum2].h / 2;

				//�e�̏�Ԃ�ێ�����ϐ��Ɂw���ł���x�������P��������
				shotFlag2 = true;
				PlaySoundMem(enemyshot[attackEnemyNum2].soundExplosion, DX_PLAYTYPE_BACK);
			}
		}
	}
	//�G�l�~�[�V���b�g�̏�Ԃ��w���ł���x�ꍇ�̂ݒe�̈ړ��������s��
	if (shotFlag2 == true)
	{
		// �������ɂ��炷
		enemyshot[attackEnemyNum2].y += enemyshot[attackEnemyNum2].vy2;
		//�v���C���[�ƃG�l�~�[�V���b�g�̓����蔻��
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

		// �����e����ʉ��[����͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
		// ��\���O�ɂ���
		if (enemyshot[attackEnemyNum2].y > SCREEN_H)
		{
			shotFlag2 = false;
		}
	}
	//�G�l�~�[�V���b�g3
	// �����J�E���^�[�ϐ����������ꍇ�͒e�����������s��
	if (shotCount % 180 == 0)
	{
		//�V���b�g�����G�l�~�[������
		attackEnemyNum3 = rand() % 49;

		//���G�l�~�[�������Ă��鎞
		if (enemy[attackEnemyNum3].aliveFlag == true)
		{
			// �������ɒe���w���ł��Ȃ��x��Ԃ������ꍇ�̂ݔ��ˏ������s��
			if (shotFlag3 == false)
			{
				//�e�̔��ˈʒu��ݒ肷��
				enemyshot[attackEnemyNum3].x = enemy[attackEnemyNum3].x + enemy[0].w / 2 - enemyshot[attackEnemyNum3].w / 2;
				enemyshot[attackEnemyNum3].y = enemy[attackEnemyNum3].y + enemy[0].h / 2 - enemyshot[attackEnemyNum3].h / 2;

				//�e�̏�Ԃ�ێ�����ϐ��Ɂw���ł���x�������P��������
				shotFlag3 = true;
				PlaySoundMem(enemyshot[attackEnemyNum3].soundExplosion, DX_PLAYTYPE_BACK);

			}
		}
	}
	//�G�l�~�[�V���b�g�̏�Ԃ��w���ł���x�ꍇ�̂ݒe�̈ړ��������s��
	if (shotFlag3 == true)
	{
		// �������ɂ��炷
		enemyshot[attackEnemyNum3].y += enemyshot[attackEnemyNum3].vy2;
		//�v���C���[�ƃG�l�~�[�V���b�g�̓����蔻��
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
		// �����e����ʉ��[����͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
		// ��\���O�ɂ���
		if (enemyshot[attackEnemyNum3].y > SCREEN_H)
		{
			shotFlag3 = false;
		}
	}
}
//�`��
void DrawShot(PlayerShot &playershot, EnemyShot enemyshot[], Player &player, Enemy enemy[], XINPUT_STATE& input, Boss& boss)
{
	//------------�V���b�g�֘A�̕`��--------------//
	//�v���C���[�V���b�g�̕`��
	if (playershot.playerShotFlag == 1)
	{
		// ��ʂɒei��`�悷��
		DrawGraph(playershot.x, playershot.y, playershot.graph, TRUE);
	}
	////�X�R�A�̕\��
	//DrawFormatString(1600, 20, GetColor(0, 0, 0), "�X�R�A�@%d", playershot.score);
	//�G�l�~�[�V���b�g�̕`��
	if (shotFlag == true)
	{
		DrawGraph(enemyshot[attackEnemyNum].x, enemyshot[attackEnemyNum].y, enemyshot[attackEnemyNum].graph, TRUE);
	}
	//�G�l�~�[�V���b�g2�̕`��
	if (shotFlag2 == true)
	{
		DrawGraph(enemyshot[attackEnemyNum2].x, enemyshot[attackEnemyNum2].y, enemyshot[attackEnemyNum2].graph, TRUE);
	}
	//�G�l�~�[�V���b�g3�̕`��
	if (shotFlag3 == true)
	{
		DrawGraph(enemyshot[attackEnemyNum3].x, enemyshot[attackEnemyNum3].y, enemyshot[attackEnemyNum3].graph, TRUE);
	}
	//---------------�v���C���[���C�t�֘A------------------//
	//�v���C���[���C�t�摜�̕`��
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



