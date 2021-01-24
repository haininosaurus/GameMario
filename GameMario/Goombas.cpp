#include "Goombas.h"
#include <algorithm>
#include "synchapi.h"
#include "Road.h"
#include "Pipe.h"
#include "TransObject.h"
#include "Game.h"
#include "Koopas.h"
#include "FireBullet.h"
#include "Mario.h"
#include "Utils.h"
#include "QuestionBlock.h"
#include "ColorBrick.h"
CGoomba::CGoomba(int form)
{
	SetForm(form);
	intro_state = 0;
	hiden_state = 0;
	time_start = (DWORD)GetTickCount64();
	create_time = (DWORD)GetTickCount64();
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DEFLECT) return;
	left = x;
	top = y;
	if (form == PARAGOOMBA_BROWN_FORM)
	{
		if (jump_state)
		{
			right = x + PARAGOOMBA_JUMPING_BBOX_WIDTH;
			bottom = y + PARAGOOMBA_JUMPING_BBOX_HEIGHT;
		}
		else
		{
			right = x + PARAGOOMBA_BBOX_WIDTH;
			bottom = y + PARAGOOMBA_BBOX_HEIGHT;
		}

	}
	else
	{
		right = x + GOOMBA_BBOX_WIDTH;

		if (state == GOOMBA_STATE_DIE)
			bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
		else bottom = y + GOOMBA_BBOX_HEIGHT;
	}

}


/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/

void CGoomba::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;

	nx = 0.0f;
	ny = 0.0f;
	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];
		if (dynamic_cast<CMario*>(c->obj) && !dynamic_cast<CMario*>(c->obj)->GetUntouchable())
		{
			if (c->nx != 0)
			{
				if (c->t < 1.0f)
				{
					min_tx = c->t; nx = c->nx; rdx = c->dx;
					coEventsResult.push_back(coEvents[i]);
				}
			}

			if (c->ny != 0)
			{
				if (c->t < 1.0f)
				{
					min_ty = c->t; ny = c->ny; rdy = c->dy;
					coEventsResult.push_back(coEvents[i]);
				}
			}
		}
		if (dynamic_cast<CRoad*>(c->obj) || dynamic_cast<CPipe*>(c->obj)
			|| dynamic_cast<CKoopa*>(c->obj) || dynamic_cast<CFireBullet*>(c->obj)
			|| dynamic_cast<CGoomba*>(c->obj)
			|| dynamic_cast<CQuestionBlock*>(c->obj)) {
			if (c->nx != 0)
			{
				if (c->t < 1.0f)
				{
					min_tx = c->t; nx = c->nx; rdx = c->dx;
					coEventsResult.push_back(coEvents[i]);
				}
			}

			if (c->ny != 0)
			{
				if (c->t < 1.0f)
				{
					min_ty = c->t; ny = c->ny; rdy = c->dy;
					coEventsResult.push_back(coEvents[i]);
				}
			}
		}
		if (dynamic_cast<CHeadRoad*>(c->obj))
		{
			if (c->nx != 0) {
				if (c->t < 1.0f)
				{
					min_tx = c->t; nx = c->nx; rdx = c->dx;
					coEventsResult.push_back(coEvents[i]);
				}
			}
		}

	}
	//if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	//if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	CGameObject::Update(dt, coObjects);

	//CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (intro_state) CreateIntroAnimationGoomba();
	if (hiden_state == 1) return;


	if (GetState() != GOOMBA_STATE_DIE && !isDestroy) {
		vy += GOOMBA_GRAVITY * dt;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		if (state != GOOMBA_STATE_DIE && state != GOOMBA_STATE_DEFLECT)
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

			x += min_tx * dx + nx * 0.1f;
			y += min_ty * dy + ny * 0.1f;

			if (ny != 0) vy = 0;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CPipe*>(e->obj) || dynamic_cast<CHeadRoad*>(e->obj) || dynamic_cast<CQuestionBlock*>(e->obj))
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
					if (state != GOOMBA_STATE_DEFLECT) {
						if (koopa->GetState() == KOOPA_STATE_SPIN_LEFT || koopa->GetState() == KOOPA_STATE_SPIN_RIGHT)
						{
							SetState(GOOMBA_STATE_DEFLECT);
						}
					}
				}
				if (dynamic_cast<CFireBullet*>(e->obj)) 
				{
					CFireBullet* bullet = dynamic_cast<CFireBullet*>(e->obj);

					SetState(GOOMBA_STATE_DEFLECT);
					bullet->SetState(FIREBULLET_DESTROY_STATE);
				}

				if (dynamic_cast<CGoomba*>(e->obj))
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
					if (e->nx > 0)
					{
						vx = GOOMBA_WALKING_SPEED;
						goomba->vx = -GOOMBA_WALKING_SPEED;
					}
					if (e->nx < 0)
					{
						vx = -GOOMBA_WALKING_SPEED;
						goomba->vx = GOOMBA_WALKING_SPEED;
					}
				}
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
			isDestroy = true;
		}
	}

	if (form == PARAGOOMBA_BROWN_FORM && state != GOOMBA_STATE_DEFLECT)
	{
		if (GetTickCount64() - time_start < 2000)
		{
			if (GetTickCount64() - time_start < 500)
				SetState(GOOMBA_STATE_JUMPING);
			else SetState(GOOMBA_STATE_WALKING);
		}
		else time_start = (DWORD)GetTickCount64();
	}
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (form == PARAGOOMBA_BROWN_FORM)
	{
		if (mario->x - x >= 18)
		{
			vx = GOOMBA_WALKING_SPEED;
		}
		else if (mario->x - x <= -1)
		{
			vx = -GOOMBA_WALKING_SPEED;
		}
	}

	DebugOut(L"Mario nx: %d\n", nx);
	if (mario->GetFightState() && state != GOOMBA_STATE_DEFLECT)
	{
		if (mario->x - x < 0 && abs(x - mario->x) <= 25)
		{
			SetState(GOOMBA_STATE_DEFLECT);
		}
		else
		{
			if (abs(mario->x - x) <= 25)
				SetState(GOOMBA_STATE_DEFLECT);
		}
	}
}

void CGoomba::Render()
{
	if (hiden_state) return;
	int ani = GOOMBA_ANI_YELLOW_WALKING;
	if (form == GOOMBA_YELLOW_FORM)
	{
		if (state == GOOMBA_STATE_DIE) {
			ani = GOOMBA_ANI_YELLOW_DIE;
		}
		else if (state == GOOMBA_STATE_DEFLECT) {
			ani = GOOMBA_ANI_DEFLECT;
		}
		else if (state == GOOMBA_STATE_IDLE) {
			ani = GOOMBA_ANI_YELLOW_IDLE;
		}
	}
	else if (form == GOOMBA_BROWN_FORM)
	{
		if (state == GOOMBA_STATE_DIE) {
			ani = GOOMBA_ANI_BROWN_DIE;
		}
		else if (state == GOOMBA_STATE_DEFLECT) {
			ani = GOOMBA_ANI_DEFLECT;
		}
		else ani = GOOMBA_ANI_BROWN_WALKING;
	}
	else if (form == PARAGOOMBA_BROWN_FORM)
	{
		if (!jump_state)
			ani = PARAGOOMBA_ANI_BROWN_WALKING;
		else ani = PARAGOOMBA_ANI_BROWN_JUMPING;
	}
	animation_set->at(ani)->Render(x, y);
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		hiden_state = 0;
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		hiden_state = 0;
		jump_state = 0;
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_DEFLECT:
		alive = 0;
		hiden_state = 0;
		vy = -GOONBA_JUMP_DEFLECT_SPEED;
		break;
	case GOOMBA_STATE_JUMPING:
		hiden_state = 0;
		if (!jump_state)
		{
			y = y - 5;
			jump_state = 1;
		}

		vy = -GOONBA_JUMP_SPEED;
		break;
	case GOOMBA_STATE_HIDEN:
		hiden_state = 1;
		break;
	case GOOMBA_STATE_IDLE:
		hiden_state = 0;
		vx = 0;
		break;
	}

}

void CGoomba::CreateIntroAnimationGoomba()
{
	if (GetTickCount64() - create_time < 6500) SetState(GOOMBA_STATE_HIDEN);
	if (GetTickCount64() - create_time > 6500 && GetTickCount64() - create_time < 10800) {
		SetState(GOOMBA_STATE_IDLE);
	}
	if (GetTickCount64() - create_time > 10800 && GetTickCount64() - create_time < 11000) {
		SetState(GOOMBA_STATE_WALKING);
	}	
	//if (GetTickCount64() - create_time > 11000 && GetTickCount64() - create_time < 11500) {
	//	SetState(GOOMBA_STATE_DIE);
	//}
}

int CGoomba::GetState() {
	return CGameObject::GetState();
}
