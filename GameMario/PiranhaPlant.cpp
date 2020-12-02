#include "PiranhaPlant.h"
#include "Game.h"
#include <algorithm>
#include "Mario.h"

CPiranhaPlant::CPiranhaPlant(CGameObject* mario) : CGameObject()
{
	check_y_limit = false;
	found_player = false;
	SetState(PIRANHAPLANT_STATE_HIDE);
	player = mario;
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PIRANHAPLANT_BBOX_WIDTH;
	bottom = y + PIRANHAPLANT_BBOX_HEIGHT;
}
LPCOLLISIONEVENT CPiranhaPlant::SweptAABBEx(LPGAMEOBJECT coO)
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


void CPiranhaPlant::CalcPotentialCollisions(
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

void CPiranhaPlant::FilterCollision(
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
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}
	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (check_y_limit == false)
	{
		y_limit = y - PIRANHAPLANT_BBOX_HEIGHT;
		check_y_limit = true;
	}

	if (y >= y_limit)
		y += dy;
	else y = y_limit;

	sx = x - player->x;
	sy = y - player->y;
	tan = sx / sy;


	if (abs(x - player->x) < 150)
	{
		if (state == PIRANHAPLANT_STATE_HIDE && tan > 1.0f || state == PIRANHAPLANT_STATE_HIDE && tan < -1.0f)
			found_player = true;
	}

	//Update state
	if (found_player)
	{
		if (hide_state)
		{
			move_up_state = 1;
			move_up_time = GetTickCount();
		}

		if (move_up_state)
		{
			if (GetTickCount() - move_up_time < 920)
				SetState(PIRANHAPLANT_STATE_MOVE_UP);
			else SetState(PIRANHAPLANT_STATE_APPEARANCE);
		}
		if (appearance_state)
		{
			if (GetTickCount() - move_up_time < 2000)
				SetState(PIRANHAPLANT_STATE_APPEARANCE);
			if (GetTickCount() - move_up_time > 2500)
				SetState(PIRANHAPLANT_STATE_MOVE_DOWN);
		}
		if (move_down_state)
		{
			if (GetTickCount() - move_up_time < 3420)
				SetState(PIRANHAPLANT_STATE_MOVE_DOWN);
			else
			{
				SetState(PIRANHAPLANT_STATE_HIDE);
				found_player = false;
			}
		}
	}
	
}

void CPiranhaPlant::Render()
{
	if (hide_state) return;
	else animation_set->at(0)->Render(x, y);

}

void CPiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHAPLANT_STATE_MOVE_UP:
		hide_state = 0;
		move_up_state = 1;
		vy = -PIRANHAPLANT_SPEECH_Y;
		break;
	case PIRANHAPLANT_STATE_MOVE_DOWN:
		hide_state = 0;
		move_down_state = 1;
		vy = PIRANHAPLANT_SPEECH_Y;
		break;
	case PIRANHAPLANT_STATE_HIDE:
		hide_state = 1;
		appearance_state = 0;
		move_up_state = 0;
		move_down_state = 0;
		vy = 0;
		break;
	case PIRANHAPLANT_STATE_APPEARANCE:
		appearance_state = 1;
		hide_state = 0;
		move_up_state = 0;
		move_down_state = 0;
		vy = 0;
		break;
	default:
		break;
	}
}

int CPiranhaPlant::GetState() {
	return CGameObject::GetState();
}