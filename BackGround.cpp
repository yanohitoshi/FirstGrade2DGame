#include "BackGround.h"



//-----�w�i�֐��Q------//
//������
void InitBG(Bg& bg)
{
	bg.Graph = LoadGraph("data/texture/hamabe.png");
	GetGraphSize(bg.Graph, &bg.w, &bg.h);
}
//�A�b�v�f�[�g
void UpdateBG(Bg)
{

}

//�`��.
void DrawBG(Bg& bg)
{
	DrawGraph(0, 0, bg.Graph, true);
}

