#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH 16
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_NORMAL 0
#define COIN_STATE_HIDE	1
#define COIN_STATE_EFFECT	2

class CCoin : public CGameObject
{
public:
	CCoin(){}
	CCoin(int stateCoin) { state = stateCoin; }
	//void CreateCoin(int x, int y);
	void SetState(int state);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

