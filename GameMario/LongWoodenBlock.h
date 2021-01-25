#pragma once
#include "GameObject.h"

#define LONG_WOODEN_BLOCK_BBOX_WIDTH 48
#define LONG_WOODEN_BLOCK_BBOX_HEIGHT 16

#define LONG_WOODEN_BLOCK_SPEED_X		0.025f
#define LONG_WOODEN_BLOCK_SPEED_Y		0.05f

#define LONG_WOODEN_BLOCK_STATE_NORMAL		100
#define LONG_WOODEN_BLOCK_STATE_FALL		200

#define LONG_WOODEN_BLOCK_TIME_FALL			400


class CLongWoodenBlock : public CGameObject
{
	bool is_fall;
	DWORD start_fall;
public:
	CLongWoodenBlock() {
		alive = false;
		SetState(LONG_WOODEN_BLOCK_STATE_NORMAL);
	}
	void SetFallTime(DWORD t) { start_fall = t; }
	void SetFall(int s) { is_fall = s; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
};

