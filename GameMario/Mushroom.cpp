#include "Mushroom.h"
#include "Animations.h"
#include <algorithm>
#include "Game.h"
#include "ColorBrick.h"

void CMushroom::Render()
{
	int ani = MUSHROOM_RED_ANI;
	if (GetState() == MUSHROOM_STATE_HIDEN || hiden_state) return;
	animation_set->at(ani)->Render(x, y);
}

void CMushroom::CalcPotentialCollisions(
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

LPCOLLISIONEVENT CMushroom::SweptAABBEx(LPGAMEOBJECT coO)
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

void CMushroom::FilterCollision(
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
		if (dynamic_cast<CColorBrick*>(c->obj)) {}
		else if (dynamic_cast<CColorBrickTop*>(c->obj)) {
			if (c->ny < 0) {
				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
			}
		}
		else if (dynamic_cast<CColorBrickTop*>(c->obj)) {
			if (c->ny < 0) {
				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
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

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == MUSHROOM_STATE_NORMAL)
	{
		vy += MUSHROOM_GRAVITY * dt;
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

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			if (ny != 0) vy = 0;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

	if (state == EFFECT_STATE)
	{
		if (GetTickCount() - effect_time_start < 1010)
		{
			if (GetTickCount() - effect_time_start > 200)
			{
				hiden_state = 0;
				vy = -MUSHROOM_SPEED_Y;
				y += dy;
			}
		}
		else SetState(MUSHROOM_STATE_NORMAL);
	}
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;

	if (state == MUSHROOM_STATE_HIDEN)
	{
		r = 0;
		b = 0;
	}
	else
	{
		r = x + MUSHROOM_BBOX_WIDTH;
		b = y + MUSHROOM_BBOX_HEIGHT;
	}
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EFFECT_STATE:
		if (effect_state == 0)
		{
			effect_state = 1;
			effect_time_start = GetTickCount();
		}
		break;
	case MUSHROOM_STATE_HIDEN:
		hiden_state = 1;
		effect_state = 0;
		break;
	case MUSHROOM_STATE_NORMAL:
		effect_state = 0;
		vx = -MUSHROOM_SPEED_X;
		break;
	default:
		break;
	}
}