#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH 16
#define COIN_BBOX_HEIGHT 16

#define COIN_SPEED_Y	0.2f

#define COIN_STATE_HIDEN	0
#define COIN_STATE_EFFECT	1
#define COIN_STATE_NORMAL	2

#define COIN_NORMAL_ANI		0
#define COIN_EFFECT_ANI		1

class CCoin : public CGameObject
{
	int effect_state;
	DWORD effect_time_start;
public:
	CCoin(){}
	CCoin(int stateCoin) { state = stateCoin; }
	void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

