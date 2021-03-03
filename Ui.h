#pragma once
typedef struct Ui
{
	int countDown;
	int gameOverTime;
	int tempTime;
	int startTime;
}Ui;


void InitUi(Ui &ui);

void UpdataUi(Ui &ui);

void DrawUi(Ui &ui);
