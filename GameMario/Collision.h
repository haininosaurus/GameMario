#pragma once
#include "GameObject.h"
#include "Game.h"
#include <algorithm>


struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
public:
	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class CollisionObject : public CGameObject
{
public:
	virtual LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO) {
		float sl, st, sr, sb;		// static object bbox
		float ml, mt, mr, mb;		// moving object bbox
		float t, nx, ny;

		coO->GetBoundingBox(sl, st, sr, sb);

		// deal with moving object: m speed = original m speed - collide object speed
		float svx, svy;
		coO->GetSpeed(svx, svy);

		float sdx = svx * dt;
		float sdy = svy * dt;

		// (rdx, rdy) is RELATIVE movement distance/velocity 
		float rdx = this->dx - sdx;
		float rdy = this->dy - sdy;

		GetBoundingBox(ml, mt, mr, mb);

		CGame::SweptAABB(
			ml, mt, mr, mb,
			rdx, rdy,
			sl, st, sr, sb,
			t, nx, ny
		);
		CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
		return e;
		return 0;
	};

	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents) {
		{
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

				if (e->t > 0 && e->t <= 1.0f)
					coEvents.push_back(e);
				else
					delete e;
			}

			std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
		};
	}

	virtual void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy) {};
};