#pragma once
#include "GameObject.h"
#include "Collision.h"

#define TAIL_BBOX_WIDTH 7
#define TAIL_BBOX_HEIGHT 16

#define TAIL_STATE_HIDEN	100
#define TAIL_STATE_FIGHT	200

#define TAIL_FIGHT_SPEED	0.001f

class CTail : public CollisionObject
{
	DWORD fight_start;
public:
	CTail()
	{
		fight_start = 0;
		state = TAIL_STATE_HIDEN;
	}
	void SetFight(float x, float y, int nx, DWORD t);
	void SetState(int state);
	virtual void Render() {
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox(); };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		top = y;
		right = TAIL_BBOX_WIDTH;
		bottom = TAIL_BBOX_HEIGHT;
		//if (state == TAIL_STATE_HIDEN) return;
		//else {

		//}
	}

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

