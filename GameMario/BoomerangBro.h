#pragma once
#include "Collision.h"
#include "PlayScence.h"

#define BOOMERANGBRO_BBOX_WIDTH		16
#define BOOMERANGBRO_BBOX_HEIGHT	24

#define BOOMERANG_WALKING_SPEED			0.02f

#define BOOMERANGBRO_STATE_WALKING		100
#define BOOMERANGBRO_STATE_THROWING		200
#define BOOMERANGBRO_STATE_DIE			300

#define BOOMERANGBRO_ANI_WALKING_LEFT		0
#define BOOMERANGBRO_ANI_WALKING_RIGHT		1
#define BOOMERANGBRO_ANI_THROWING_LEFT		2
#define BOOMERANGBRO_ANI_THROWING_RIGHT		3
#define BOOMERANGBRO_ANI_DIE_LEFT			4
#define BOOMERANGBRO_ANI_DIE_RIGHT			5

#define BOOMERANGBRO_GRAVITY				0.0005f


class CBoomerangBro : public CollisionObject
{
	CBoomerang* boomerang[2];
	DWORD time_start;
	bool found_player;
	bool is_idle;
	bool is_back;
	bool is_shoot;
	bool is_right;
public:
	CBoomerangBro(CBoomerang* boomerang[2]);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);
	void SetState(int state);
};

