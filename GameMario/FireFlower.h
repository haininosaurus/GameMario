#pragma once
#include "GameObject.h"

#define FIRE_FLOWER_BBOX_WIDTH 16
#define FIRE_FLOWER_BBOX_HEIGHT 16

#define FIRE_FLOWER_STATE_HIDEN		0
#define EFFECT_STATE				1
#define FIRE_FLOWER_STATE_NORMAL	2

class CFireFlower : public CGameObject
{
public:
	void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

