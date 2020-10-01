#pragma once
#include"GameObject.h"

#define MARIO_WALKING_SPEECH 0.15f

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

class CMario:public CGameObject
{
	float start_x;
	float start_y;

public:
	CMario() {};
	CMario(float x, float y) { start_x = x; start_y = y; };
	virtual void Render();
	virtual void Update(DWORD dt);

};

