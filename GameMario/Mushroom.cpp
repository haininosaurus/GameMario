#include "Mushroom.h"
#include "Animations.h"
#include <algorithm>
#include "Game.h"
#include "ColorBrick.h"
#include "Utils.h"

CMushroom::CMushroom()
{
	intro_state = 0;
	create_time = GetTickCount64();
}

void CMushroom::Render()
{
	int ani = MUSHROOM_RED_ANI;
	if (GetState() == MUSHROOM_STATE_HIDEN || hiden_state) return;
	animation_set->at(ani)->Render(x, y);
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
	if (intro_state) CreateIntroAnimationMushroom();
	if (state == MUSHROOM_STATE_HIDEN) return;


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
		if (GetTickCount64() - effect_time_start < 1010)
		{
			if (GetTickCount64() - effect_time_start > 200)
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
			effect_time_start = GetTickCount64();
		}
		break;
	case MUSHROOM_STATE_HIDEN:
		hiden_state = 1;
		effect_state = 0;
		break;
	case MUSHROOM_STATE_NORMAL:
		hiden_state = 0;
		effect_state = 0;
		vx = -MUSHROOM_SPEED_X;
		break;
	default:
		break;
	}
}

void CMushroom::CreateIntroAnimationMushroom()
{
	if (GetTickCount64() - create_time < 6500) SetState(MUSHROOM_STATE_HIDEN);
	if (GetTickCount64() - create_time > 6500 && GetTickCount64() - create_time < 7000) {
		DebugOut(L"da vao intro\n");
		SetState(MUSHROOM_STATE_NORMAL);
		vx = 0;
	}
	if (GetTickCount64() - create_time > 7000 && GetTickCount64() - create_time < 9000) {
		SetState(MUSHROOM_STATE_NORMAL);
	}
}