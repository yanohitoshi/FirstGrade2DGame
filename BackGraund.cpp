#include "Dxlib.h"
#include "BackGraund.h"

//������
void InitBG(Bg& bg)
{
	//�O���t�B�b�N�̃��[�h
	bg.graph = LoadGraph("data/texture/haikei2.png");
	bg.x = 0;
	bg.y = 0;
}
//�`��
void DrawBG(Bg& bg)
{
	DrawGraph(bg.x, bg.y, bg.graph, TRUE);
}

