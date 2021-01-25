#pragma once
#include "GameObject.h"

#define PIECEBRICK_STATE_HIDEN			0
#define PIECEBRICK_STATE_DISPLAY		1

#define PIECEBRICK_STATE_HIDEN_TIME		400

class CPieceBrick : public CGameObject
{
	DWORD display_start;
public:
	//CPieceBrick(float x, float y, float v);
	CPieceBrick() { display_start = 0; }
	void SetDisplay(float x, float y, float vx, float vy, DWORD t)
	{
		SetPosition(x, y);
		this->vx = vx;
		this->vy = vy;
		display_start = t;
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }
};
