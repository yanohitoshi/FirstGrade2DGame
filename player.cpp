#include "Enemy.h"
#include "player.h"
#include "function.h"

//������
void InitPlayer(Player &player, XINPUT_STATE& input, Enemy enemy[])
{
	//�v���C���[�̃O���t�B�b�N�����[�h
	LoadDivGraph("data/texture/player1.png", 4, 2, 2, 75, 100, player.graph);
	//��ʂ̔����i�����j�̈ʒu
	player.x = SCREEN_W / 2;
	//��ʂ̉�-100�̈ʒu
	player.y = SCREEN_H - 100;
	for (size_t i = 0; i < 4; i++)
	{
		GetGraphSize(player.graph[i], &player.w, &player.h);
	}
	//�J�E���^�[���Z�b�g
	player.count = 0;
	player.animationIndex = 0;
	//�t���O������
	player.damegeFlag = false;
}
//�A�b�v�f�[�g
void UpdatePlayer(Player &player, XINPUT_STATE &input, Enemy enemy[])
{
	// ���L�[�������Ă�����v���C���[���ړ�������
	if (CheckHitKey(KEY_INPUT_LEFT) == 1 || input.Buttons[2])
	{
		player.x -= PLAYER_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || input.Buttons[3])
	{
		player.x += PLAYER_SPEED;
	}
	//�v���C���[����ʂ���͂ݏo�������ɂȂ����Ƃ��߂�
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
	//�G�l�~�[�ƃv���C���[�̓����蔻��

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

	//�A�j���[�V����
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
//�`��
void DrawPlayer(Player &player, XINPUT_STATE &input, Enemy enemy[])
{
	DrawGraph(player.x, player.y, player.graph[player.animationIndex], TRUE);
}

