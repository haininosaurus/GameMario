#include "Goombas.h"
#include <algorithm>
#include "synchapi.h"
#include "Road.h"
#include "Pipe.h"
#include "TransObject.h"
#include "Game.h"
#include "Koopas.h"
CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else bottom = y + GOOMBA_BBOX_HEIGHT;
}
LPCOLLISIONEVENT CGoomba::SweptAABBEx(LPGAMEOBJECT coO)
{
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
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGoomba::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
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
}

void CGoomba::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;
	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (dynamic_cast<CRoad*>(c->obj) || dynamic_cast<CPipe*>(c->obj)
			|| dynamic_cast<CKoopa*>(c->obj)) {
			if (c->t < min_tx && c->nx != 0) {
				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			}

			if (c->t < min_ty && c->ny != 0) {
				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
			}
		}
		else if (dynamic_cast<CHeadRoad*>(c->obj))
		{
			if (c->t < min_tx && c->nx != 0) {
				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			}
		}
	}
	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects/*, vector<LPGAMEOBJECT>* quesObjects*/)
{
	CGameObject::Update(dt, coObjects);

	if (GetState() != GOOMBA_STATE_DIE && !isDestroy) {
		vy += GOOMBA_GRAVITY * dt;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		if (state != GOOMBA_STATE_DIE && state != GOOMBA_STATE_THROWN)
			CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;

		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			if (ny != 0) vy = 0;
			//if (nx != 0) vx = 0;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CPipe*>(e->obj) || dynamic_cast<CHeadRoad*>(e->obj)) // if e->obj is Goomba 
				{
					if (e->nx > 0)
					{
						vx = +GOOMBA_WALKING_SPEED;
					}
					if (e->nx < 0)
					{
						vx = -GOOMBA_WALKING_SPEED;
					}
				}
				if (dynamic_cast<CKoopa*>(e->obj))
				{
					CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
					if (state != GOOMBA_STATE_THROWN) {
						if (koopa->GetState() == KOOPA_STATE_SPIN_LEFT || koopa->GetState() == KOOPA_STATE_SPIN_RIGHT)
						{
							SetState(GOOMBA_STATE_THROWN);
						}
					}

				}
				//if (dynamic_cast<CRoad*>(e->obj)) // if e->obj is Goomba 
				//{
				//	//CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				//	// jump on top >> kill Goomba and deflect a bit 
				//	if (e->nx > 0)
				//	{
				//		vx = +GOOMBA_WALKING_SPEED;
				//	}
				//	if (e->nx < 0)
				//	{
				//		vx = -GOOMBA_WALKING_SPEED;
				//	}
				//}
			}

		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	

	else if (GetState() == GOOMBA_STATE_DIE && !isDestroy)
	{
		timeDestroy += dt;
		if (timeDestroy >= dt * 15)
		{
			SetPosition(-50, 50);
			isDestroy == true;
		}
	}





}

void CGoomba::Render()
{
		int ani = GOOMBA_ANI_WALKING;
		if (state == GOOMBA_STATE_DIE) {
			ani = GOOMBA_ANI_DIE;
		}
		else if (state == GOOMBA_STATE_THROWN) {
			ani = GOOMBA_ANI_THROWN;
		}


		animation_set->at(ani)->Render(x, y);
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_THROWN:
		//vx = 0;
		vy = -GOONBA_JUMP_DEFLECT_SPEED;
		break;
	}

}

int CGoomba::GetState() {
	return CGameObject::GetState();
}
