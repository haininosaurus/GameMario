#pragma once
#include "GameObject.h"

#define GOALCARD_BBOX_HEIGHT		16
#define GOALCARD_BBOX_WIDTH			16


#define GOALCARD_STATE_HIDEN		0
#define GOALCARD_STATE_STAR			1
#define GOALCARD_STATE_FLOWER		2
#define GOALCARD_STATE_MUSHROOM		3


#define GOALCARD_ANI_STAR			0
#define GOALCARD_ANI_FLOWER			1
#define GOALCARD_ANI_MUSHROOM		2


class CGoalCard : public CGameObject
{
	DWORD create_start;
public:
	CGoalCard() { create_start = GetTickCount64();  state = 0; }
	void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

