#include "function.h"
#include "player.h"
#include "boss.h"
#include "shot2.h"

//������
void InitPlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss, Player& player)
{
	//------�v���C���[�V���b�g�֘A------//
	//�v���C���[�V���b�g�̃��[�h
	playershot2.graph = LoadGraph("data/texture/playershot5.png");

	//�v���C���[�V���b�g�̃T�C�Y�𓾂�
	GetGraphSize(playershot2.graph, &playershot2.w, &playershot2.h);

	//�v���C���[�V���b�g�̏����ʒu
	playershot2.x = (player.x + player.w);
	playershot2.y = (player.y + player.h);

	//�v���C���[�V���b�g�̑��x
	playershot2.vy = -20;
	playershot2.playerShotFlag = false;

	//�X�R�A�̏�����
	playershot2.score = 0;

	//�v���C���[�V���b�g�̌��ʉ������[�h
	playershot2.soundEffect = LoadSoundMem("data/sound/playerEffect.mp3");
	playershot2.soundExplosion = LoadSoundMem("data/sound/playerExplosion.mp3");
	//�{�X�_���[�W�J�E���g�̏�����
	boss.damageCount = 0;
}

//�A�b�v�f�[�g
void UpdatePlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player)
{
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && playershot2.playerShotFlag == 0 || input.Buttons[12] && playershot2.playerShotFlag == 0)
	{
		//�v���C���[�ƒe�̉摜�̃T�C�Y�𓾂�
		for (size_t i = 0; i < 4; i++)
		{
			GetGraphSize(player.graph[i], &player.w, &player.h);
		}
		//�摜�T�C�Y�𓾂�
		GetGraphSize(playershot2.graph, &playershot2.w, &playershot2.h);

		// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���		
		playershot2.x = (player.w - playershot2.w) / 2 + player.x;
		playershot2.y = (player.h - playershot2.h) / 2 + player.y;

		// �e�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
		playershot2.playerShotFlag = 1;

		//�V���b�g���ʉ���炷
		PlaySoundMem(playershot2.soundEffect, DX_PLAYTYPE_BACK);
	}
	// ���@�̒e�̔��ˏ���
	if (playershot2.playerShotFlag == 1)
	{
		// �e���ړ�
		playershot2.y += playershot2.vy;

		//�{�X�ƃv���C���[�V���b�g�̓����蔻��
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
				//��e����炷
				PlaySoundMem(playershot2.soundExplosion, DX_PLAYTYPE_BACK);
			}
		}


		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ��ɂO(���݂��Ȃ�)��������
		if (playershot2.y < -80)
		{
			playershot2.playerShotFlag = 0;
		}
	}

}

//�`��
void DrawPlayerShot(Playershot2& playershot2, XINPUT_STATE &input, Boss& boss,Player& player)
{
	//------------�V���b�g�֘A�̕`��--------------//
	//�v���C���[�V���b�g�̕`��
	if (playershot2.playerShotFlag == 1)
	{
		// ��ʂɒei��`�悷��
		DrawGraph(playershot2.x, playershot2.y, playershot2.graph, TRUE);
	}

}

