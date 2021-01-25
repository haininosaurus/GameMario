#include "Boomerang.h"
#include "Mario.h"

CBoomerang::CBoomerang()
{
	shoot_start = 0;
	isFly = 0;
	state = BOOMERANG_STATE_HIDEN;
	vx = 0;
}

void CBoomerang::Render()
{
	int ani = BOOMERANG_ANI_FLYING;
	if(state == BOOMERANG_STATE_HIDEN) return;
	if (isFly) ani = BOOMERANG_ANI_FLYING;


	animation_set->at(ani)->Render(x, y);


}

void CBoomerang::FilterCollision(
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
		if (dynamic_cast<CMario*>(c->obj)) {

			if (c->t < min_tx && c->nx != 0) {
				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			}
			if (c->t < min_ty && c->ny != 0) {
				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
			}
			nx = 0;
		}

	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

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

	}

	if (isFly && state == BOOMERANG_STATE_FLYING_LEFT)
	{
		if (GetTickCount64() - shoot_start < BOOMERANG_FLYING_STATE_1_TIME) {
			vx = -BOOMERANG_FLYING_SPEECH;
			vy = -BOOMERANG_GRAVITY;
		}
		else if (GetTickCount64() - shoot_start < BOOMERANG_FLYING_STATE_2_TIME)
		{
			vx = -BOOMERANG_FLYING_SPEECH + BOOMERANG_SPEED_X_PLUS;
			vy = BOOMERANG_GRAVITY + BOOMERANG_SPEED_Y_PLUS;
		}
		else if (GetTickCount64() - shoot_start < BOOMERANG_FLYING_STATE_3_TIME)
		{
			vx = BOOMERANG_FLYING_SPEECH;
			vy = 0;
		}
		else
		{
			SetState(BOOMERANG_STATE_HIDEN);
		}
	}

	if (isFly && state == BOOMERANG_STATE_FLYING_RIGHT)
	{
		if (GetTickCount64() - shoot_start < BOOMERANG_FLYING_STATE_1_TIME) {
			vx = BOOMERANG_FLYING_SPEECH;
			vy = -BOOMERANG_GRAVITY;
		}
		else if (GetTickCount64() - shoot_start < BOOMERANG_FLYING_STATE_2_TIME)
		{
			vx = BOOMERANG_FLYING_SPEECH - BOOMERANG_SPEED_X_PLUS;
			vy = BOOMERANG_GRAVITY + BOOMERANG_SPEED_Y_PLUS;
		}
		else if (GetTickCount64() - shoot_start < BOOMERANG_FLYING_STATE_3_TIME)
		{
			vx = -BOOMERANG_FLYING_SPEECH;
			vy = 0;
		}
		else
		{
			SetState(BOOMERANG_STATE_HIDEN);
		}
	}

}

void CBoomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == BOOMERANG_STATE_HIDEN) return;
	else
	{
		l = x;
		t = y;
		r = x + BOOMERANG_BBOX_WIDTH;
		b = y + BOOMERANG_BBOX_HEIGHT;
	}
}

void CBoomerang::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BOOMERANG_STATE_FLYING_LEFT:
		isFly = 1;
		break;
	case BOOMERANG_STATE_FLYING_RIGHT:
		isFly = 1;
		break;
	default:
		break;
	}
}