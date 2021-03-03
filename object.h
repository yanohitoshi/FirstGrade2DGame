#pragma once
#include "Shot.h"

//è·äQï®ç\ë¢ëÃ
typedef struct Object
{
	static int graph[3];
	int x;
	int y;
	int w;
	int h;
	int vx;

}Object;

const int objectMax = 5;

void InitObject(Object object[], PlayerShot &playershot, EnemyShot enemyshot[]);

void UpdateObject(Object object[], PlayerShot &playershot, EnemyShot enemyshot[]);

void DrawObject(Object object[], PlayerShot &playershot, EnemyShot enemyshot[]);
