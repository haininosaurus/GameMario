#pragma once
#include "GameObject.h"
#include "Collision.h"

#define FIREBULLET_BBOX_WIDTH 8
#define FIREBULLET_BBOX_HEIGHT 8

#define FIRE_BULLET_FLYING_SPEECH			0.2f
#define FIRE_BULLET_DEFLECT_SPEED			0.2f
#define FIRE_BULLET_GRAVITY					0.001f

#define FIREBULLET_DESTROY_STATE			100
#define FIREBULLET_SHOOTED_RIGHT_STATE		200
#define FIREBULLET_SHOOTED_LEFT_STATE		300
#define FIREBULLET_TRANSPARENT_STATE		400

class CFireBullet : public CGameObject
{
	DWORD shoot_start;
public:
	CFireBullet();

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
	virtual LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	
};

