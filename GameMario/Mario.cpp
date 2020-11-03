#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"
#include "Utils.h"
#include "Goombas.h"
#include "Koopas.h"
#include "ColorBrick.h"
#include "Coin.h"
#include "QuestionBlock.h"
#include "TransObject.h"
#include "Road.h"
#include "Pipe.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	run_state = 0;
	jump_state = 0;
	kick_state = 0;
	turn_state = 0;
	take_tortoistate_state = 0;
	tortoiseshell = NULL;

	SetState(MARIO_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

int CMario::GetCurrentWidthMario()
{
	if (level == MARIO_LEVEL_SMALL)
		return MARIO_SMALL_BBOX_WIDTH;
	else if (level == MARIO_LEVEL_BIG)
		return MARIO_BIG_BBOX_WIDTH;
	else if (level == MARIO_LEVEL_TAIL)
		return MARIO_TAIL_BBOX_WIDTH;
	else if (level == MARIO_LEVEL_FIRE)
		return MARIO_FIRE_BBOX_WIDTH;
}
int CMario::GetCurrentHeightMario()
{
	if (level == MARIO_LEVEL_SMALL)
		return MARIO_SMALL_BBOX_HEIGHT;
	else if (level == MARIO_LEVEL_BIG)
		return MARIO_BIG_BBOX_HEIGHT;
	else if (level == MARIO_LEVEL_TAIL)
		return MARIO_TAIL_BBOX_HEIGHT;
	else if (level == MARIO_LEVEL_FIRE)
		return MARIO_FIRE_BBOX_HEIGHT;
}
LPCOLLISIONEVENT CMario::SweptAABBEx(LPGAMEOBJECT coO)
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




	//float magnitude = sqrt((vx * vx + vy * vy)) * remainingTime; 
	//float dotprod = vx * ny + vy * nx;
	//if (dotprod > 0.0f) 
	//	dotprod = 1.0f;
	//else if (dotprod < 0.0f)    
	//	dotprod = -1.0f; 
	//coO->vx = dotprod * ny * magnitude;
	//coO->vy = dotprod * nx * magnitude;




	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
	return 0;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CMario::CalcPotentialCollisions(
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

void CMario::FilterCollision(
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
		else if (dynamic_cast<CTransObject*>(c->obj)){}
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

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	//DebugOut(L"[INFO] bef-Vy in update %f\n", vy);
	CGameObject::Update(dt);
	// Simple fall down
	vy += MARIO_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coQuesEvents;
	vector<LPCOLLISIONEVENT> coQuesEventsResult;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	//if (coObjects != NULL) {
	//	
	//}
	coEvents.clear();
	float t;

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
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

		// TODO: This is a very ugly designed function!!!!
		CMario::FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		float remainingTime = 1.0f - min_tx;
		//DebugOut(L"x: %f\n", x);
		

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		if (rdx != 0 && rdx != dx)
			x += nx * abs(rdx);



		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		if (vy == 0) jump_state = 0;

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						jump_state = 1;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba

			if (dynamic_cast<CKoopa*>(e->obj)) // if e->obj is Koopa
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
				if (koopa->GetState() != KOOPA_STATE_TAKEN)
				{
					if (e->ny < 0)
					{
						if (koopa->GetState() != KOOPA_STATE_HIDE)
						{
							koopa->SetState(KOOPA_STATE_HIDE);
							jump_state = 1;
							vy = -MARIO_JUMP_DEFLECT_SPEED;
						}            
						else if (koopa->GetState() == KOOPA_STATE_HIDE)
						{

							if (round(x + CMario::GetCurrentWidthMario() / 2) < koopa->x + round(KOOPA_BBOX_WIDTH / 2)) koopa->SetState(KOOPA_STATE_SPIN_RIGHT);
							else koopa->SetState(KOOPA_STATE_SPIN_LEFT);
							jump_state = 1;
						}

					}
					else if (e->nx != 0)
					{
						if (untouchable == 0)
						{
							if (koopa->GetState() != KOOPA_STATE_HIDE)
							{
								if (level > MARIO_LEVEL_SMALL)
								{
									level = MARIO_LEVEL_SMALL;
									StartUntouchable();
								}
								else
									SetState(MARIO_STATE_DIE);
							}
							else
							{
								if (state != MARIO_STATE_RUNNING_LEFT && state != MARIO_STATE_RUNNING_RIGHT)
								{
									kick_start = GetTickCount();
									if (e->nx < 0)
									{
										SetState(MARIO_STATE_KICK);

										koopa->SetState(KOOPA_STATE_SPIN_RIGHT);
									}
									else
									{
										SetState(MARIO_STATE_KICK);
										koopa->SetState(KOOPA_STATE_SPIN_LEFT);
									}
								}
								else
								{
									tortoiseshell = koopa;
									koopa->SetState(KOOPA_STATE_TAKEN);
									if (e->nx < 0) {
										SetState(MARIO_STATE_TAKE_TORTOISESHELL_RIGHT);
									}
									else SetState(MARIO_STATE_TAKE_TORTOISESHELL_LEFT);
								}
							}
						}
					}
				}
				
			}
			

			//if (dynamic_cast<CCoin*>(e->obj)) // if e->obj is Koopa
			//{
			//	CCoin* coin = dynamic_cast<CCoin*>(e->obj);

			//	if (e->ny > 0)
			//	{
			//		if (coin->GetState() == COIN_STATE_HIDE)
			//		{
			//			coin->SetPosition(coin->x, coin->y - 16);
			//			coin->SetState(COIN_STATE_NORMAL);

			//		}
			//	}
			//}
			if (dynamic_cast<CPipe*>(e->obj)) 
			{
				CPipe* pipe = dynamic_cast<CPipe*>(e->obj);

				if (e->nx != 0)
				{
					if (y < 149 - GetCurrentHeightMario() - 5) {
						x += vx * min_tx;
						y += vy;

						vx *= remainingTime;
						vy *= remainingTime;

						if (abs(nx) > 0.0001f)
							vx = -vx;
						if (abs(ny) > 0.0001f)
							vy = -vy;

						float dotprod = (vx * ny + vy * nx) * remainingTime;
						vx = dotprod * ny;
						vy = dotprod * nx;
					}

				}
			}

			if (dynamic_cast<CQuestionBlock*>(e->obj)) // if e->obj is question block
			{
					CQuestionBlock* quesBlock = dynamic_cast<CQuestionBlock*>(e->obj);
					if (e->ny > 0)
					{
						if (quesBlock->GetState() == QUESTIONBLOCK_STATE_QUESTION)
						{
							quesBlock->SetState(QUESTIONBLOCK_STATE_NORMAL);

							//quesBlock->CreateQuestionObject();
						}


					}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];	

	if (tortoiseshell != NULL) {
		if (level == MARIO_LEVEL_SMALL)
		{
			if (nx > 0)
			{
				SetState(MARIO_STATE_TAKE_TORTOISESHELL_RIGHT);
				tortoiseshell->x = x + 10;
				tortoiseshell->y = y - 2;
			}
			else
			{
				SetState(MARIO_STATE_TAKE_TORTOISESHELL_LEFT);
				tortoiseshell->x = x - 10;
				tortoiseshell->y = y - 2;
			}

		}

		else if (level == MARIO_LEVEL_BIG)
		{
			if (nx > 0)
			{
				SetState(MARIO_STATE_TAKE_TORTOISESHELL_RIGHT);
				tortoiseshell->x = x + 10;
				tortoiseshell->y = y + 10;
			}
			else
			{
				SetState(MARIO_STATE_TAKE_TORTOISESHELL_LEFT);
				tortoiseshell->x = x - 10;
				tortoiseshell->y = y + 10;
			}
		}
		else if (level == MARIO_LEVEL_TAIL)
		{
			if (nx > 0)
			{
				SetState(MARIO_STATE_TAKE_TORTOISESHELL_RIGHT);
				tortoiseshell->x = x + 15;
				tortoiseshell->y = y + 10;
			}
			else
			{
				SetState(MARIO_STATE_TAKE_TORTOISESHELL_LEFT);
				tortoiseshell->x = x - 10;
				tortoiseshell->y = y + 10;
			}
		}
		else if (level == MARIO_LEVEL_FIRE)
		{
			if (nx > 0)
			{
				SetState(MARIO_STATE_TAKE_TORTOISESHELL_RIGHT);
				tortoiseshell->x = x + 10;
				tortoiseshell->y = y + 10;
			}
			else
			{
				SetState(MARIO_STATE_TAKE_TORTOISESHELL_LEFT);
				tortoiseshell->x = x - 10;
				tortoiseshell->y = y + 10;
			}
		}
	}

	if (GetTickCount() - kick_start < 150)
		SetState(MARIO_STATE_KICK);

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
				if (nx > 0)
				{
					if (kick_state == 1) ani = MARIO_ANI_BIG_KICK_RIGHT;
					else if (take_tortoistate_state == 1) ani = MARIO_ANI_BIG_TAKE_TORTOISESHELL_IDLE_RIGHT;
					else if (jump_state == 1) ani = MARIO_ANI_BIG_JUMPING_RIGHT;
					else ani = MARIO_ANI_BIG_IDLE_RIGHT;
				}
				else
				{
					if (kick_state == 1) ani = MARIO_ANI_BIG_KICK_LEFT;
					else if (take_tortoistate_state == 1) ani = MARIO_ANI_BIG_TAKE_TORTOISESHELL_IDLE_LEFT;
					else if (jump_state == 1) ani = MARIO_ANI_BIG_JUMPING_LEFT;
					else ani = MARIO_ANI_BIG_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (turn_state == 1) ani = MARIO_ANI_BIG_TURN_LEFT;
				else if (take_tortoistate_state == 1) ani = MARIO_ANI_BIG_TAKE_TORTOISESHELL_RIGHT;
				else if (kick_state == 1) ani = MARIO_ANI_BIG_KICK_RIGHT;
				else if (run_state == 1)	ani = MARIO_ANI_BIG_RUNNING_RIGHT;
				else if (jump_state == 1) ani = MARIO_ANI_BIG_JUMPING_RIGHT;
				else ani = MARIO_ANI_BIG_WALKING_RIGHT;
			}
			else {
				if (turn_state == 1) ani = MARIO_ANI_BIG_TURN_RIGHT;
				else if (take_tortoistate_state == 1) ani = MARIO_ANI_BIG_TAKE_TORTOISESHELL_LEFT;
				else if (kick_state == 1) ani = MARIO_ANI_BIG_KICK_LEFT;
				else if (run_state == 1) ani = MARIO_ANI_BIG_RUNNING_LEFT;
				else if (jump_state == 1) ani = MARIO_ANI_BIG_JUMPING_LEFT;
				else ani = MARIO_ANI_BIG_WALKING_LEFT;
			}
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) {
					if (kick_state == 1) ani = MARIO_ANI_SMALL_KICK_RIGHT;
					else if (take_tortoistate_state == 1) ani = MARIO_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_RIGHT;
					else if (jump_state == 1) ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
					else ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				}
				else {
					if (kick_state == 1) ani = MARIO_ANI_SMALL_KICK_LEFT;
					else if (take_tortoistate_state == 1) ani = MARIO_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_LEFT;
					else if (jump_state == 1) ani = MARIO_ANI_SMALL_JUMPING_LEFT;
					else ani = MARIO_ANI_SMALL_IDLE_LEFT;
				}
			}
			else if (vx > 0) {
				if (turn_state == 1) ani = MARIO_ANI_SMALL_TURN_LEFT;
				else if (take_tortoistate_state == 1) ani = MARIO_ANI_SMALL_TAKE_TORTOISESHELL_RIGHT;
				else if (kick_state == 1) ani = MARIO_ANI_SMALL_KICK_RIGHT;
				else if (run_state == 1)	ani = MARIO_ANI_SMALL_RUNNING_RIGHT;
				else if (jump_state == 1) ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
				else ani = MARIO_ANI_SMALL_WALKING_RIGHT;
			}
			else {
				if (turn_state == 1) ani = MARIO_ANI_SMALL_TURN_RIGHT;
				else if (take_tortoistate_state == 1) ani = MARIO_ANI_SMALL_TAKE_TORTOISESHELL_LEFT;
				else if (kick_state == 1) ani = MARIO_ANI_SMALL_KICK_LEFT;
				else if (run_state == 1) ani = MARIO_ANI_SMALL_RUNNING_LEFT;
				else if (jump_state == 1) ani = MARIO_ANI_SMALL_JUMPING_LEFT;
				else ani = MARIO_ANI_SMALL_WALKING_LEFT;
			}
		}

		else if (level == MARIO_LEVEL_TAIL)
		{
			if (vx == 0)
			{
				if (nx > 0) {
					if (kick_state == 1) ani = MARIO_ANI_TAIL_KICK_RIGHT;
					else if (take_tortoistate_state == 1) ani = MARIO_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_RIGHT;
					else if (jump_state == 1) ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
					else ani = MARIO_ANI_TAIL_IDLE_RIGHT;
				}
				else {
					if (kick_state == 1) ani = MARIO_ANI_TAIL_KICK_LEFT;
					else if (take_tortoistate_state == 1) ani = MARIO_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_LEFT;
					else if (jump_state == 1) ani = MARIO_ANI_TAIL_JUMPING_LEFT;
					else ani = MARIO_ANI_TAIL_IDLE_LEFT;
				}
			}
			else if (vx > 0) {
				if (turn_state == 1) ani = MARIO_ANI_TAIL_TURN_LEFT;
				else if (take_tortoistate_state == 1) ani = MARIO_ANI_TAIL_TAKE_TORTOISESHELL_RIGHT;
				else if (kick_state == 1) ani = MARIO_ANI_TAIL_KICK_RIGHT;
				else if (run_state == 1)	ani = MARIO_ANI_TAIL_RUNNING_RIGHT;
				else if (jump_state == 1) ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
				else ani = MARIO_ANI_TAIL_WALKING_RIGHT;
			}
			else {
				if (turn_state == 1) ani = MARIO_ANI_TAIL_TURN_RIGHT;
				else if (take_tortoistate_state == 1) ani = MARIO_ANI_TAIL_TAKE_TORTOISESHELL_LEFT;
				else if (kick_state == 1) ani = MARIO_ANI_TAIL_KICK_LEFT;
				else if (run_state == 1) ani = MARIO_ANI_TAIL_RUNNING_LEFT;
				else if (jump_state == 1) ani = MARIO_ANI_TAIL_JUMPING_LEFT;
				else ani = MARIO_ANI_TAIL_WALKING_LEFT;
			}
		}
		else if (level == MARIO_LEVEL_FIRE)
		{
			if (vx == 0)
			{
				if (nx > 0) {
					if (kick_state == 1) ani = MARIO_ANI_FIRE_KICK_RIGHT;
					else if (take_tortoistate_state == 1) ani = MARIO_ANI_FIRE_TAKE_TORTOISESHELL_IDLE_RIGHT;
					else if (jump_state == 1) ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
					else ani = MARIO_ANI_FIRE_IDLE_RIGHT;
				}
				else {
					if (kick_state == 1) ani = MARIO_ANI_FIRE_KICK_LEFT;
					else if (take_tortoistate_state == 1) ani = MARIO_ANI_FIRE_TAKE_TORTOISESHELL_IDLE_LEFT;
					else if (jump_state == 1) ani = MARIO_ANI_FIRE_JUMPING_LEFT;
					else ani = MARIO_ANI_FIRE_IDLE_LEFT;
				}
			}
			else if (vx > 0) {
				if (turn_state == 1) ani = MARIO_ANI_FIRE_TURN_LEFT;
				else if (take_tortoistate_state == 1) ani = MARIO_ANI_FIRE_TAKE_TORTOISESHELL_RIGHT;
				else if (kick_state == 1) ani = MARIO_ANI_FIRE_KICK_RIGHT;
				else if (run_state == 1)	ani = MARIO_ANI_FIRE_RUNNING_RIGHT;
				else if (jump_state == 1) ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
				else ani = MARIO_ANI_FIRE_WALKING_RIGHT;
			}
			else {
				if (turn_state == 1) ani = MARIO_ANI_FIRE_TURN_RIGHT;
				else if (take_tortoistate_state == 1) ani = MARIO_ANI_FIRE_TAKE_TORTOISESHELL_LEFT;
				else if (kick_state == 1) ani = MARIO_ANI_FIRE_KICK_LEFT;
				else if (run_state == 1) ani = MARIO_ANI_FIRE_RUNNING_LEFT;
				else if (jump_state == 1) ani = MARIO_ANI_FIRE_JUMPING_LEFT;
				else ani = MARIO_ANI_FIRE_WALKING_LEFT;
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
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		turn_state = 0;
		run_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		//jump_state = 1;
		kick_state = 0;
		turn_state = 0;
		vy = -MARIO_JUMP_SPEED_Y - speech_Jump;
		//DebugOut(L"[INFO] Vy %d\n", vy);
		break;
	case MARIO_STATE_IDLE:
		vx = 0;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		run_state = 1;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		vx = MARIO_RUNNING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		run_state = 1;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		vx = -MARIO_RUNNING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_KICK:
		kick_state = 1;
		turn_state = 0;
		if (tortoiseshell != NULL) 
		{
			if (nx > 0) {
				tortoiseshell->x = x + GetCurrentWidthMario();
				tortoiseshell->SetState(KOOPA_STATE_SPIN_RIGHT);
			}
			else
			{
				tortoiseshell->x = x - KOOPA_BBOX_HIDE_WIDTH;
				tortoiseshell->SetState(KOOPA_STATE_SPIN_LEFT);
			}

			take_tortoistate_state = 0;

			tortoiseshell = NULL;
		}

		if (nx > 0) vx = MARIO_WALKING_SPEED;
		else vx = -MARIO_WALKING_SPEED;

		break;
	case MARIO_STATE_TAKE_TORTOISESHELL_RIGHT:
		take_tortoistate_state = 1;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		break;
	case MARIO_STATE_TAKE_TORTOISESHELL_LEFT:
		take_tortoistate_state = 1;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		break;
	case MARIO_STATE_TURN_LEFT:
		turn_state = 1;
		vx = -MARIO_WALKING_SPEED;
		break;
	case MARIO_STATE_TURN_RIGHT:
		turn_state = 1;
		vx = MARIO_WALKING_SPEED;
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

