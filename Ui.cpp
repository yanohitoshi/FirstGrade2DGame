#include "DxLib.h"
#include "function.h"
#include "Ui.h"

//UI������
void InitUi(Ui &ui)
{
	ui.startTime = GetNowCount();
	ui.gameOverTime = 160;
}
//UI�A�b�v�f�[�g
void UpdataUi(Ui &ui)
{
	ui.tempTime = GetNowCount();
	//�c�莞�Ԃ��v�Z
	ui.countDown = ui.gameOverTime - (ui.tempTime - ui.startTime) / 1000;
}
//UI�`��
void DrawUi(Ui &ui)
{
	DrawFormatString(850, 20, GetColor(0, 0, 0), "�c��@%d�@�b", ui.countDown);
}
