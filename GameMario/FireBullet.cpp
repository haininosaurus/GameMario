#include "FireBullet.h"
#include <algorithm>
#include "Game.h"
#include "ColorBrick.h"
#include "TransObject.h"
#include "Road.h"

CFireBullet::CFireBullet()
{
	state = FIREBULLET_TRANSPARENT_STATE;
	vx = 0;
}

void CFireBullet::Render()
{
	if(state == FIREBULLET_SHOOTED_RIGHT_STATE || state == FIREBULLET_SHOOTED_LEFT_STATE)
		animation_set->at(0)->Render(x, y);

}
void CFireBullet::CalcPotentialCollisions(
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

LPCOLLISIONEVENT CFireBullet::SweptAABBEx(LPGAMEOBJECT coO)
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

void CFireBullet::FilterCollision(
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
		else if (dynamic_cast<CTransObject*>(c->obj)) {}
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

void CFireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (state == FIREBULLET_SHOOTED_RIGHT_STATE || state == FIREBULLET_SHOOTED_LEFT_STATE)
	{
		vy += FIRE_BULLET_GRAVITY * dt;
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

			//if (ny != 0) vy = 0;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CRoad*>(e->obj) || dynamic_cast<CColorBrickTop*>(e->obj))
				{
					vy = -FIRE_BULLET_DEFLECT_SPEED;

				}

			}

		}



		if (GetTickCount() - shoot_start > 1000)
		{
			SetState(FIREBULLET_DESTROY_STATE);
		}
	}
	else
	{
		shoot_start = GetTickCount();
	}


}

void CFireBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBULLET_BBOX_WIDTH;
	b = y + FIREBULLET_BBOX_HEIGHT;
}

void CFireBullet::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case FIREBULLET_DESTROY_STATE:
		break;
	case FIREBULLET_SHOOTED_RIGHT_STATE:
		vx = FIRE_BULLET_FLYING_SPEECH;
		break;
	case FIREBULLET_SHOOTED_LEFT_STATE:
		vx = -FIRE_BULLET_FLYING_SPEECH;
		break;
	case FIREBULLET_TRANSPARENT_STATE:
		vx = 0;
		vy = 0;
		break;
	default:
		break;
	}
}