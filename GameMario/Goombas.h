#pragma once
#include "GameObject.h"
#define GOOMBAS_WIDTH 24
class CGoombas : public CGameObject
{
protected:
	float vx;
public:
	CGoombas(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

