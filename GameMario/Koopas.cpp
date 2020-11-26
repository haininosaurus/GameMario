#include "Koopas.h"
#include <algorithm>
#include "Road.h"
#include "Pipe.h"
#include "ColorBrick.h"
#include "QuestionBlock.h"
#include "TransObject.h"
#include "Utils.h"
#include "Goombas.h"
#include "Game.h"
#include "FireBullet.h"

CKoopa::CKoopa(int form) : CGameObject::CGameObject()
{
	SetForm(form);
	SetState(KOOPA_STATE_WALKING_LEFT);
}
void CKoopa::Render()
{
	int ani = KOOPA_ANI_RED_WALKING_RIGHT;
	if (form == KOOPA_RED_FORM)
	{
		if (vx < 0 && state != KOOPA_STATE_SPIN_LEFT && state != KOOPA_STATE_SPIN_RIGHT)
			ani = KOOPA_ANI_RED_WALKING_LEFT;
		else if (state == KOOPA_STATE_HIDE)
			ani = KOOPA_ANI_RED_HIDE;
		else if (state == KOOPA_STATE_SPIN_LEFT || state == KOOPA_STATE_SPIN_RIGHT)
			ani = KOOPA_ANI_RED_SPIN;
		else if (state == KOOPA_STATE_TAKEN)
			ani = KOOPA_ANI_RED_TAKEN;
	}
	else if(form == KOOPA_GREEN_FORM)
	{
		if (vx < 0 && state != KOOPA_STATE_SPIN_LEFT && state != KOOPA_STATE_SPIN_RIGHT)
			ani = KOOPA_ANI_GREEN_WALKING_LEFT;
		else if (state == KOOPA_STATE_HIDE)
			ani = KOOPA_ANI_GREEN_HIDE;
		else if (state == KOOPA_STATE_SPIN_LEFT || state == KOOPA_STATE_SPIN_RIGHT)
			ani = KOOPA_ANI_GREEN_SPIN;
		else if (state == KOOPA_STATE_TAKEN)
			ani = KOOPA_ANI_GREEN_TAKEN;
		else ani = KOOPA_ANI_GREEN_WALKING_RIGHT;
	}
	else if (form == PARAKOOPA_GREEN_FORM)
	{
		if (vx < 0) ani = PARAKOOPA_ANI_GREEN_JUMPING_LEFT;
		else ani = PARAKOOPA_ANI_GREEN_JUMPING_RIGHT;
	}

	animation_set->at(ani)->Render(x, y);
}

LPCOLLISIONEVENT CKoopa::SweptAABBEx(LPGAMEOBJECT coO)
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
void CKoopa::CalcPotentialCollisions(
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

void CKoopa::FilterCollision(
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
		if (dynamic_cast<CColorBrick*>(c->obj) || dynamic_cast<CGoomba*>(c->obj)) {}
		else if(dynamic_cast<CTransObject*>(c->obj) && state == KOOPA_STATE_SPIN_LEFT ||
			dynamic_cast<CTransObject*>(c->obj) && state == KOOPA_STATE_SPIN_RIGHT){ }
		else if (dynamic_cast<CColorBrickTop*>(c->obj)) {
			if (c->ny < 0) {
				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
			}
		}
		else if (dynamic_cast<CHeadRoad*>(c->obj)) {
			if (c->t < min_tx && c->nx != 0) {
				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			}
		}
		else {
			
			if (c->t < min_tx && c->nx != 0) {
				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			}

			if (c->t < min_ty && c->ny != 0) {
				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
			}
		}

	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if(state != KOOPA_STATE_TAKEN)
		vy += KOOPA_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

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

		CKoopa::FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy + ny * 0.2f;

		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (form != PARAKOOPA_GREEN_FORM)
			{
				if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)
				{
					if (dynamic_cast<CTransObject*>(e->obj))
					{
						if (e->nx > 0) {

							SetState(KOOPA_STATE_WALKING_RIGHT);
						}
						else if (e->nx < 0) SetState(KOOPA_STATE_WALKING_LEFT);

					}

					if (dynamic_cast<CFireBullet*>(e->obj))
					{
						CFireBullet* bullet = dynamic_cast<CFireBullet*>(e->obj);
						SetState(KOOPA_STATE_HIDE);
						bullet->SetState(FIREBULLET_DESTROY_STATE);
					}
				}
				if (state == KOOPA_STATE_SPIN_LEFT)
				{
					if (dynamic_cast<CPipe*>(e->obj) || dynamic_cast<CQuestionBlock*>(e->obj) || dynamic_cast<CHeadRoad*>(e->obj))
					{

						if (e->nx > 0) {
							SetState(KOOPA_STATE_SPIN_RIGHT);
						}
					}


				}
				else if (state == KOOPA_STATE_SPIN_RIGHT)
				{
					if (dynamic_cast<CPipe*>(e->obj) || dynamic_cast<CQuestionBlock*>(e->obj) || dynamic_cast<CHeadRoad*>(e->obj))
					{
						if (e->nx < 0) {
							SetState(KOOPA_STATE_SPIN_LEFT);
						}
					}
				}
			}
			else
			{
				if (e->ny < 0)
					vy = -PARAKOOPA_JUMP_SPEED;
			}
			
		}
	}



	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

			

}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (state == KOOPA_STATE_HIDE)
	{
		right = x + KOOPA_BBOX_HIDE_WIDTH;
		bottom = y + KOOPA_BBOX_HIDE_HEIGHT;
	}
	else if (state == KOOPA_STATE_SPIN_RIGHT || state == KOOPA_STATE_SPIN_LEFT)
	{
		right = x + KOOPA_BBOX_SPIN_WIDTH;
		bottom = y + KOOPA_BBOX_SPIN_HEIGHT;
	}
	else
	{
		right = x + KOOPA_BBOX_WIDTH;
		bottom = y + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_WALKING_RIGHT:
		isSpin = 0;
		vx = KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_WALKING_LEFT:
		isSpin = 0;
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_HIDE:
		vx = 0;
		vy = 0;
		isSpin = 0;
		break;
	case KOOPA_STATE_SPIN_RIGHT:
		isSpin = 1;
		vx = KOOPA_SPINNING_SPEED;
		break;
	case KOOPA_STATE_SPIN_LEFT:
		isSpin = 1;
		vx = - KOOPA_SPINNING_SPEED;
		break;
	case KOOPA_STATE_TAKEN:
		vx = 0;
		vy = 0;
		isSpin = 0;
		break;
		
	}
}
int CKoopa::GetState() {
	return CGameObject::GetState();
}