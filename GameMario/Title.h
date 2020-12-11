#pragma once
#include "GameObject.h"

#define SPEED_Y			0.2f

#define DARK_TITLE		0
#define LIGHT_TITLE		1

class CTitle : public CGameObject
{
	int type;
	DWORD create_time;
public:
	CTitle();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }
	void CreateIntroAnimationTitle();
};

