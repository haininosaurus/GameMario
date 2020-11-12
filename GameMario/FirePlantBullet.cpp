#include "FirePlantBullet.h"
#include <algorithm>
#include "Game.h"
#include "ColorBrick.h"
#include "TransObject.h"
#include "Road.h"
#include "Mario.h"
#include "Utils.h"

CFirePlantBullet::CFirePlantBullet()
{
	state = FIREPLANTBULLET_TRANSPARENT_STATE;
	vx = 0;
}

void CFirePlantBullet::Render()
{
	if (state != FIREPLANTBULLET_TRANSPARENT_STATE && state != FIREPLANTBULLET_DESTROY_STATE)
		animation_set->at(0)->Render(x, y);

}
void CFirePlantBullet::CalcPotentialCollisions(
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

LPCOLLISIONEVENT CFirePlantBullet::SweptAABBEx(LPGAMEOBJECT coO)
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

void CFirePlantBullet::FilterCollision(
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
		if (dynamic_cast<CMario*>(c->obj)){
		
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

void CFirePlantBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (state != FIREPLANTBULLET_TRANSPARENT_STATE && state != FIREPLANTBULLET_DESTROY_STATE)
	{
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
			//for (UINT i = 0; i < coEventsResult.size(); i++)
			//{
			//	LPCOLLISIONEVENT e = coEventsResult[i];

			//	if (dynamic_cast<CRoad*>(e->obj))
			//	{

			//	}

			//}

		}
		if (GetTickCount() - shoot_start > 2000)
		{
			SetState(FIREPLANTBULLET_DESTROY_STATE);
		}
	}
	else
	{
		shoot_start = GetTickCount();
	}


}

void CFirePlantBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREPLANTBULLET_BBOX_WIDTH;
	b = y + FIREPLANTBULLET_BBOX_HEIGHT;
}

void CFirePlantBullet::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case FIREPLANTBULLET_DESTROY_STATE:
		break;
	case FIREPLANTBULLET_SHOOTED_LEFT_30_STATE:
		vx = -FIRE_PLANT_BULLET_FLYING_SPEECH_X + 0.01f;
		vy = FIRE_PLANT_BULLET_FLYING_SPEECH_Y;
		break;
	case FIREPLANTBULLET_SHOOTED_LEFT_60_STATE:
		vx = -FIRE_PLANT_BULLET_FLYING_SPEECH_X - 0.01f;
		vy = FIRE_PLANT_BULLET_FLYING_SPEECH_Y - 0.05f;
		break;
	case FIREPLANTBULLET_SHOOTED_LEFT_120_STATE:
		vx = -FIRE_PLANT_BULLET_FLYING_SPEECH_X;
		vy = -FIRE_PLANT_BULLET_FLYING_SPEECH_Y;
		break;
	case FIREPLANTBULLET_SHOOTED_LEFT_150_STATE:
		vx = -FIRE_PLANT_BULLET_FLYING_SPEECH_X + 0.01f;
		vy = -FIRE_PLANT_BULLET_FLYING_SPEECH_Y + 0.05f;
		break;
	case FIREPLANTBULLET_SHOOTED_RIGHT_30_STATE:
		DebugOut(L"da vao right 30\n");
		vx = FIRE_PLANT_BULLET_FLYING_SPEECH_X - 0.01f;
		vy = FIRE_PLANT_BULLET_FLYING_SPEECH_Y;
		break;
	case FIREPLANTBULLET_SHOOTED_RIGHT_60_STATE:
		DebugOut(L"da vao right 60\n");
		vx = FIRE_PLANT_BULLET_FLYING_SPEECH_X + 0.01f;
		vy = FIRE_PLANT_BULLET_FLYING_SPEECH_Y - 0.05f;
		break;
	case FIREPLANTBULLET_SHOOTED_RIGHT_120_STATE:
		vx = FIRE_PLANT_BULLET_FLYING_SPEECH_X;
		vy = -FIRE_PLANT_BULLET_FLYING_SPEECH_Y;
		break;
	case FIREPLANTBULLET_SHOOTED_RIGHT_150_STATE:
		vx = FIRE_PLANT_BULLET_FLYING_SPEECH_X - 0.01f;
		vy = -FIRE_PLANT_BULLET_FLYING_SPEECH_Y + 0.05f;
		break;
	case FIREPLANTBULLET_TRANSPARENT_STATE:
		vx = 0;
		vy = 0;
		break;
	default:
		break;
	}
}