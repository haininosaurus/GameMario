#pragma once
#include "Collision.h"

#define BOOMERANG_BBOX_WIDTH				15
#define BOOMERANG_BBOX_HEIGHT				16

#define BOOMERANG_FLYING_SPEECH				0.08f
#define BOOMERANG_GRAVITY					0.015f

#define BOOMERANG_STATE_HIDEN				100
#define BOOMERANG_STATE_FLYING_RIGHT		200
#define BOOMERANG_STATE_FLYING_LEFT			300
#define BOOMERANG_STATE_APPEAR				400

#define BOOMERANG_ANI_FLYING				0
#define BOOMERANG_ANI_APPEAR				1


class CBoomerang : public CollisionObject
{
	DWORD shoot_start;
	bool isFly;
public:
	CBoomerang();

	void SetShootStart(DWORD t) { shoot_start = t; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	virtual void SetState(int s);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);
};

