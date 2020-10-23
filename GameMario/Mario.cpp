#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"
#include "Utils.h"
#include "Goombas.h"
#include "ColorBrick.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	run_state = 0;
	jump_state = 0;
	SetState(MARIO_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	//DebugOut(L"[INFO] bef-Vy in update %f\n", vy);
	CGameObject::Update(dt);
	// Simple fall down
	vy += MARIO_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		if (vy == 0) jump_state = 0;
		


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			//if (dynamic_cast<CColorBrick*>(e->obj)) {
			//	CColorBrick* colorbrick = dynamic_cast<CColorBrick*>(e->obj);
			//	if(e->ny < 0)
			//}

			//if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			//{
			//	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

			//	// jump on top >> kill Goomba and deflect a bit 
			//	if (e->ny < 0)
			//	{
			//		if (goomba->GetState() != GOOMBA_STATE_DIE)
			//		{
			//			goomba->SetState(GOOMBA_STATE_DIE);
			//			vy = -MARIO_JUMP_DEFLECT_SPEED;
			//		}
			//	}
			//	else if (e->nx != 0)
			//	{
			//		if (untouchable == 0)
			//		{
			//			if (goomba->GetState() != GOOMBA_STATE_DIE)
			//			{
			//				if (level > MARIO_LEVEL_SMALL)
			//				{
			//					level = MARIO_LEVEL_SMALL;
			//					StartUntouchable();
			//				}
			//				else
			//					SetState(MARIO_STATE_DIE);
			//			}
			//		}
			//	}
			//} // if Goomba
			//else if (dynamic_cast<CPortal*>(e->obj))
			//{
			//	CPortal* p = dynamic_cast<CPortal*>(e->obj);
			//	CGame::GetInstance()->SwitchScene(p->GetSceneId());
			//}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			if (vx == 0)
			{
				if (nx > 0) {
					if (jump_state == 1) ani = MARIO_ANI_BIG_JUMPING_RIGHT;
					else ani = MARIO_ANI_BIG_IDLE_RIGHT;
				}
				else {
					if (jump_state == 1) ani = MARIO_ANI_BIG_JUMPING_LEFT;
					else ani = MARIO_ANI_BIG_IDLE_LEFT;
				}
			}
			else if (vx > 0) {
				if (run_state == 0 && jump_state == 0)	ani = MARIO_ANI_BIG_WALKING_RIGHT;
				else if (jump_state == 1) ani = MARIO_ANI_BIG_JUMPING_RIGHT;
				else ani = MARIO_ANI_BIG_RUNNING_RIGHT;
			}
			else {
				if (run_state == 0 && jump_state == 0) ani = MARIO_ANI_BIG_WALKING_LEFT;
				else if (jump_state == 1) ani = MARIO_ANI_BIG_JUMPING_LEFT;
				else ani = MARIO_ANI_BIG_RUNNING_LEFT;
			}
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) {
					if (jump_state == 1) ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
					else ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				}
				else {
					if (jump_state == 1) ani = MARIO_ANI_SMALL_JUMPING_LEFT;
					else ani = MARIO_ANI_SMALL_IDLE_LEFT;
				}
			}
			else if (vx > 0) {
				if (run_state == 0 && jump_state == 0)	ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				else if(jump_state == 1) ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
				else ani = MARIO_ANI_SMALL_RUNNING_RIGHT;
			}
			else {
				if(run_state == 0 && jump_state == 0) ani = MARIO_ANI_SMALL_WALKING_LEFT;
				else if (jump_state == 1) ani = MARIO_ANI_SMALL_JUMPING_LEFT;
				else ani = MARIO_ANI_SMALL_RUNNING_LEFT;
			}
		}
		else if (level == MARIO_LEVEL_TAIL)
		{
			if (vx == 0)
			{
				if (nx > 0) {
					if (jump_state == 1) ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
					else ani = MARIO_ANI_TAIL_IDLE_RIGHT;
				}
				else {
					if (jump_state == 1) ani = MARIO_ANI_TAIL_JUMPING_LEFT;
					else ani = MARIO_ANI_TAIL_IDLE_LEFT;
				}
			}
			else if (vx > 0) {
				if (run_state == 0 && jump_state == 0)	ani = MARIO_ANI_TAIL_WALKING_RIGHT;
				else if (jump_state == 1) ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
				else ani = MARIO_ANI_TAIL_RUNNING_RIGHT;
			}
			else {
				if (run_state == 0 && jump_state == 0) ani = MARIO_ANI_TAIL_WALKING_LEFT;
				else if (jump_state == 1) ani = MARIO_ANI_TAIL_JUMPING_LEFT;
				else ani = MARIO_ANI_TAIL_RUNNING_LEFT;
			}
		}
		else if (level == MARIO_LEVEL_FIRE)
		{
			if (vx == 0)
			{
				if (nx > 0) {
					if (jump_state == 1) ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
					else ani = MARIO_ANI_FIRE_IDLE_RIGHT;
				}
				else {
					if (jump_state == 1) ani = MARIO_ANI_FIRE_JUMPING_LEFT;
					else ani = MARIO_ANI_FIRE_IDLE_LEFT;
				}
			}
			else if (vx > 0) {
				if (run_state == 0 && jump_state == 0)	ani = MARIO_ANI_FIRE_WALKING_RIGHT;
				else if (jump_state == 1) ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
				else ani = MARIO_ANI_FIRE_RUNNING_RIGHT;
			}
			else {
				if (run_state == 0 && jump_state == 0) ani = MARIO_ANI_FIRE_WALKING_LEFT;
				else if (jump_state == 1) ani = MARIO_ANI_FIRE_JUMPING_LEFT;
				else ani = MARIO_ANI_FIRE_RUNNING_LEFT;
			}
		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	//RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		run_state = 0;
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		run_state = 0;
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		jump_state = 1;
		vy = -MARIO_JUMP_SPEED_Y;
		//DebugOut(L"[INFO] Vy %d\n", vy);
		break;
	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		run_state = 1;
		vx = MARIO_RUNNING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		run_state = 1;
		vx = -MARIO_RUNNING_SPEED;
		nx = -1;
		break;
	}

}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		right = x + MARIO_TAIL_BBOX_WIDTH;
		bottom = y + MARIO_TAIL_BBOX_HEIGHT;

	}
	else if (level == MARIO_LEVEL_FIRE)
	{
		right = x + MARIO_FIRE_BBOX_WIDTH;
		bottom = y + MARIO_FIRE_BBOX_HEIGHT;

	}
	else {
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

