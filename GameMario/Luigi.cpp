#include "Luigi.h"

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
#include "FireBullet.h"
#include "FirePlantBullet.h"
#include "Mushroom.h"
#include "Leaf.h"

CLuigi::CLuigi(float x, float y) : CGameObject()
{
	level = LUIGI_LEVEL_TAIL;
	is_high = 0;
	untouchable = 0;
	run_state = 0;
	jump_state = 0;
	kick_state = 0;
	turn_state = 0;
	run_fast_state = 0;
	fall_state = 0;
	pcy = 0;
	walking_right_speech = 0;
	walking_right_speech = 0;
	take_tortoistate_state = 0;
	tortoiseshell = NULL;
	for (int i = 0; i < 2; i++)
		fire_bullet[i] = NULL;

	SetState(LUIGI_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}
int CLuigi::GetCurrentWidthLuigi()
{
	if (level == LUIGI_LEVEL_SMALL)
		return LUIGI_SMALL_BBOX_WIDTH;
	else if (level == LUIGI_LEVEL_BIG)
		return LUIGI_BIG_BBOX_WIDTH;
	else if (level == LUIGI_LEVEL_TAIL)
		return LUIGI_TAIL_BBOX_WIDTH;
	else return 0;
}
LPCOLLISIONEVENT CLuigi::SweptAABBEx(LPGAMEOBJECT coO)
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
void CLuigi::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t >= 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CLuigi::FilterCollision(
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

		if (dynamic_cast<CColorBrickTop*>(c->obj))
		{
			if (c->ny < 0 && c->t < 1.0f)
			{
				min_ty = c->t; ny = c->ny; rdy = c->dy;
				coEventsResult.push_back(coEvents[i]);
			}
		}
		else if (!dynamic_cast<CColorBrick*>(c->obj) && !dynamic_cast<CTransObject*>(c->obj) && !dynamic_cast<CFireBullet*>(c->obj))
		{
			if (c->nx != 0 && c->t < 1.0f)
			{
				min_tx = c->t; nx = c->nx; rdx = c->dx;
				coEventsResult.push_back(coEvents[i]);
			}

			if (c->ny != 0 && c->t < 1.0f)
			{
				min_ty = c->t; ny = c->ny; rdy = c->dy;
				coEventsResult.push_back(coEvents[i]);
			}

		}

	}
}

void CLuigi::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (vy > 0) jump_state = 1;
	CGameObject::Update(dt);
	// Simple fall down
	vy += LUIGI_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	//float t;

	// turn off collision when die 
	if (state != LUIGI_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		fall_state = 1;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;
		//DebugOut(L"coevent: %d\n", coEvents.size());
		CLuigi::FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		//DebugOut(L"coeventresult: %d\n\n", coEventsResult.size());
		float remainingTime = 1.0f - min_tx;

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		if (rdx != 0 && rdx != dx)
			x += nx * abs(rdx);

		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy + ny * 0.2f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		if (vy < 0.02 && vy >= 0) {
			jump_state = 0;
			fall_state = 0;
			vy = 0;
		}
		else fall_state = 1;


		// reset untouchable timer if untouchable time has passed
		if (GetTickCount64() - untouchable_start > LUIGI_UNTOUCHABLE_TIME)
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
						if (goomba->GetForm() != PARAGOOMBA_BROWN_FORM)
							goomba->SetState(GOOMBA_STATE_DIE);
						else goomba->SetForm(GOOMBA_BROWN_FORM);
						vy = -LUIGI_JUMP_DEFLECT_SPEED;
						jump_state = 1;
					}
				}

				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > LUIGI_LEVEL_SMALL && !fight_state)
							{
								SetLevel(GetLevel() - 1);
								StartUntouchable();
							}
							else if (fight_state)
							{
								goomba->SetState(GOOMBA_STATE_THROWN);
							}
							else
								SetState(LUIGI_STATE_DIE);
						}
					}
				}
			}

			if (dynamic_cast<CKoopa*>(e->obj)) // if e->obj is Koopa
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
				if (koopa->GetState() != KOOPA_STATE_TAKEN)
				{
					if (e->ny < 0)
					{
						if (koopa->GetState() != KOOPA_STATE_HIDE)
						{
							if (koopa->GetForm() == PARAKOOPA_GREEN_FORM)
								koopa->SetForm(KOOPA_GREEN_FORM);
							else koopa->SetState(KOOPA_STATE_HIDE);
							jump_state = 1;
							vy = -LUIGI_JUMP_DEFLECT_SPEED;
						}
						else if (koopa->GetState() == KOOPA_STATE_HIDE)
						{

							if (round(x + CLuigi::GetCurrentWidthLuigi() / 2) < koopa->x + round(KOOPA_BBOX_WIDTH / 2)) koopa->SetState(KOOPA_STATE_SPIN_RIGHT);
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
								if (level > LUIGI_LEVEL_SMALL)
								{
									level = LUIGI_LEVEL_SMALL;
									StartUntouchable();
								}
								else
									SetState(LUIGI_STATE_DIE);
							}
							else
							{
								if (state != LUIGI_STATE_RUNNING_LEFT && state != LUIGI_STATE_RUNNING_RIGHT)
								{
									kick_start = GetTickCount64();
									if (e->nx < 0)
									{
										SetState(LUIGI_STATE_KICK);

										koopa->SetState(KOOPA_STATE_SPIN_RIGHT);
									}
									else
									{
										SetState(LUIGI_STATE_KICK);
										koopa->SetState(KOOPA_STATE_SPIN_LEFT);
									}
								}
								else
								{
									tortoiseshell = koopa;
									koopa->SetState(KOOPA_STATE_TAKEN);
									if (e->nx < 0) {
										SetState(LUIGI_STATE_TAKE_TORTOISESHELL_RIGHT);
									}
									else SetState(LUIGI_STATE_TAKE_TORTOISESHELL_LEFT);
								}
							}
						}
					}
				}

			}


			if (dynamic_cast<CCoin*>(e->obj)) // if e->obj is Koopa
			{
				CCoin* coin = dynamic_cast<CCoin*>(e->obj);

				if (coin->GetState() == COIN_STATE_NORMAL)
				{
					coin->SetState(COIN_STATE_HIDEN);

				}
			}

			
			if (dynamic_cast<CQuestionBlock*>(e->obj)) // if e->obj is question block
			{
				CQuestionBlock* quesBlock = dynamic_cast<CQuestionBlock*>(e->obj);
				if (e->ny > 0)
				{
					vy = 0;
					if (quesBlock->GetState() == QUESTIONBLOCK_ITEM_STATE)
					{
						quesBlock->SetState(QUESTIONBLOCK_DEFLECT_STATE);
						quesBlock->SetStateItem(EFFECT_STATE);
					}
				}
			}

			if (dynamic_cast<CRoad*>(e->obj))
			{

				CRoad* road = dynamic_cast<CRoad*>(e->obj);
				if (e->ny < 0)
				{
					vy = 0;
					fall_state = 0;
				}
			}

			if (dynamic_cast<CFirePlantBullet*>(e->obj))
			{
				CFirePlantBullet* fireplantbullet = dynamic_cast<CFirePlantBullet*>(e->obj);
				if (fireplantbullet->GetState() != FIREBULLET_DESTROY_STATE && fireplantbullet->GetState() != FIREBULLET_TRANSPARENT_STATE)
				{
					if (level > LUIGI_LEVEL_SMALL)
					{
						SetLevel(GetLevel() - 1);
						fireplantbullet->SetState(FIREBULLET_DESTROY_STATE);
						StartUntouchable();
					}
					else
						SetState(LUIGI_STATE_DIE);
				}
			}

			if (dynamic_cast<CMushroom*>(e->obj))
			{
				CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
				if (!mushroom->IsHidenState())
				{
					mushroom->SetState(MUSHROOM_STATE_HIDEN);
					SetPosition(x, y - 2);
					SetLevel(GetLevel() + 1);
				}

			}
			if (dynamic_cast<CLeaf*>(e->obj))
			{
				CLeaf* mushroom = dynamic_cast<CLeaf*>(e->obj);
				if (!mushroom->IsHidenState())
				{
					mushroom->SetState(LEAF_STATE_HIDEN);
					SetPosition(x, y - 2);
					SetLevel(GetLevel() + 1);
				}

			}
		}
	}

	if (tortoiseshell != NULL) {
		if (level == LUIGI_LEVEL_SMALL)
		{
			if (nx > 0)
			{
				SetState(LUIGI_STATE_TAKE_TORTOISESHELL_RIGHT);
				tortoiseshell->x = x + 10;
				tortoiseshell->y = y - 2;
			}
			else
			{
				SetState(LUIGI_STATE_TAKE_TORTOISESHELL_LEFT);
				tortoiseshell->x = x - 10;
				tortoiseshell->y = y - 2;
			}

		}

		else if (level == LUIGI_LEVEL_BIG)
		{
			if (nx > 0)
			{
				SetState(LUIGI_STATE_TAKE_TORTOISESHELL_RIGHT);
				tortoiseshell->x = x + 10;
				tortoiseshell->y = y + 10;
			}
			else
			{
				SetState(LUIGI_STATE_TAKE_TORTOISESHELL_LEFT);
				tortoiseshell->x = x - 10;
				tortoiseshell->y = y + 10;
			}
		}
		else if (level == LUIGI_LEVEL_TAIL)
		{
			if (nx > 0)
			{
				SetState(LUIGI_STATE_TAKE_TORTOISESHELL_RIGHT);
				tortoiseshell->x = x + 15;
				tortoiseshell->y = y + 10;
			}
			else
			{
				SetState(LUIGI_STATE_TAKE_TORTOISESHELL_LEFT);
				tortoiseshell->x = x - 10;
				tortoiseshell->y = y + 10;
			}
		}
	}

	if (GetTickCount64() - kick_start < 150 && !take_tortoistate_state)
		SetState(LUIGI_STATE_KICK);

	if (GetTickCount64() - fight_start < 300)
		SetState(LUIGI_STATE_FIGHT);
	else fight_state = 0;


	if (state == LUIGI_STATE_RUNNING_RIGHT && running_time_right == -1) running_time_right = (DWORD)GetTickCount64();
	else if (state == LUIGI_STATE_RUNNING_LEFT && running_time_left == -1) running_time_left = (DWORD)GetTickCount64();

	if (GetTickCount64() - GetKickStart() < 200) SetState(LUIGI_STATE_KICK);
	else kick_state = 0;

	if (GetTickCount64() - fly_low_start < 300)
	{
		if (nx > 0) SetState(LUIGI_STATE_FLYING_LOW_RIGHT);
		else SetState(LUIGI_STATE_FLYING_LOW_LEFT);
	}
	else fly_low_state = 0;

	if (GetTickCount64() - fly_high_start < 1000)
	{
		if (nx > 0) SetState(LUIGI_STATE_FLYING_HIGH_RIGHT);
		else SetState(LUIGI_STATE_FLYING_HIGH_LEFT);
	}
	else fly_high_state = 0;

	if (fly_high_state && y < 28) is_high = 1;
	if (y >= 28) is_high = 0;

	if (turn_state == 0 && run_state == 0 && !kick_state)
	{
		if (nx > 0)
		{
			if (GetTickCount64() - GetWalkRightTime() < sliding_time_right)
			{
				SetState(LUIGI_STATE_WALKING_RIGHT);
				slide_state = 1;
			}
			else slide_state = 0;
		}
		else
		{
			if (GetTickCount64() - GetWalkLeftTime() < sliding_time_left)
			{
				SetState(LUIGI_STATE_WALKING_LEFT);
				slide_state = 1;
			}
			else slide_state = 0;
		}
	}
	else if (!turn_state && !run_fast_state && !kick_state)
	{
		if (nx > 0)
		{
			if (GetTickCount64() - GetWalkRightTime() < sliding_time_right)
			{
				SetState(LUIGI_STATE_RUNNING_RIGHT);
				slide_state = 1;
			}
			else slide_state = 0;
		}
		else
		{
			if (GetTickCount64() - GetWalkLeftTime() < sliding_time_left)
			{
				SetState(LUIGI_STATE_RUNNING_LEFT);
				slide_state = 1;
			}
			else slide_state = 0;
		}
	}
	else if (!turn_state && run_state && !kick_state)
	{
		if (nx > 0)
		{
			if (GetTickCount64() - GetWalkRightTime() < sliding_time_right)
			{
				SetState(LUIGI_STATE_RUNNING_RIGHT_FAST);
				slide_state = 1;
			}
			else slide_state = 0;
		}
		else
		{
			if (GetTickCount64() - GetWalkLeftTime() < sliding_time_left)
			{
				SetState(LUIGI_STATE_RUNNING_LEFT_FAST);
				slide_state = 1;
			}
			else slide_state = 0;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}





void CLuigi::Render()
{
	int ani = -1;
	if (state == LUIGI_STATE_DIE)
		ani = LUIGI_ANI_DIE;
	else
		if (level == LUIGI_LEVEL_BIG)
		{
			if (vx == 0)
			{
				if (nx > 0)
				{

					if (kick_state == 1) ani = LUIGI_ANI_BIG_KICK_RIGHT;
					else if (sit_state == 1) ani = LUIGI_ANI_BIG_SIT_RIGHT;
					else if (take_tortoistate_state == 1) ani = LUIGI_ANI_BIG_TAKE_TORTOISESHELL_IDLE_RIGHT;
					else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_BIG_JUMPING_RIGHT;
					else ani = LUIGI_ANI_BIG_IDLE_RIGHT;
				}
				else
				{
					if (kick_state == 1) ani = LUIGI_ANI_BIG_KICK_LEFT;
					else if (sit_state == 1) ani = LUIGI_ANI_BIG_SIT_LEFT;
					else if (take_tortoistate_state == 1) ani = LUIGI_ANI_BIG_TAKE_TORTOISESHELL_IDLE_LEFT;
					else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_BIG_JUMPING_LEFT;
					else ani = LUIGI_ANI_BIG_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (turn_state == 1) ani = LUIGI_ANI_BIG_TURN_LEFT;
				else if (take_tortoistate_state == 1) ani = LUIGI_ANI_BIG_TAKE_TORTOISESHELL_RIGHT;
				else if (kick_state == 1) ani = LUIGI_ANI_BIG_KICK_RIGHT;
				else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_BIG_JUMPING_RIGHT;
				else if (run_fast_state == 1) ani = LUIGI_ANI_BIG_RUNNING_RIGHT_FAST;
				else if (run_state == 1)	ani = LUIGI_ANI_BIG_RUNNING_RIGHT;
				else ani = LUIGI_ANI_BIG_WALKING_RIGHT;
			}
			else
			{
				if (turn_state == 1) ani = LUIGI_ANI_BIG_TURN_RIGHT;
				else if (take_tortoistate_state == 1) ani = LUIGI_ANI_BIG_TAKE_TORTOISESHELL_LEFT;
				else if (kick_state == 1) ani = LUIGI_ANI_BIG_KICK_LEFT;
				else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_BIG_JUMPING_LEFT;
				else if (run_fast_state == 1) ani = LUIGI_ANI_BIG_RUNNING_LEFT_FAST;
				else if (run_state == 1) ani = LUIGI_ANI_BIG_RUNNING_LEFT;
				else ani = LUIGI_ANI_BIG_WALKING_LEFT;
			}
		}
		else if (level == LUIGI_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0)
				{
					if (kick_state == 1) ani = LUIGI_ANI_SMALL_KICK_RIGHT;
					else if (sit_state == 1) ani = LUIGI_ANI_TAIL_SIT_RIGHT;
					else if (take_tortoistate_state == 1) ani = LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_RIGHT;
					else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_SMALL_JUMPING_RIGHT;
					else ani = LUIGI_ANI_SMALL_IDLE_RIGHT;
				}
				else
				{
					if (kick_state == 1) ani = LUIGI_ANI_SMALL_KICK_LEFT;
					else if (sit_state == 1) ani = LUIGI_ANI_TAIL_SIT_LEFT;
					else if (take_tortoistate_state == 1) ani = LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_LEFT;
					else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_SMALL_JUMPING_LEFT;
					else ani = LUIGI_ANI_SMALL_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (turn_state == 1) ani = LUIGI_ANI_SMALL_TURN_LEFT;
				else if (take_tortoistate_state == 1) ani = LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_RIGHT;
				else if (kick_state == 1) ani = LUIGI_ANI_SMALL_KICK_RIGHT;
				else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_SMALL_JUMPING_RIGHT;
				else if (run_fast_state == 1) ani = LUIGI_ANI_SMALL_RUNNING_RIGHT_FAST;
				else if (run_state == 1)	ani = LUIGI_ANI_SMALL_RUNNING_RIGHT;
				else ani = LUIGI_ANI_SMALL_WALKING_RIGHT;
			}
			else
			{
				if (turn_state == 1) ani = LUIGI_ANI_SMALL_TURN_RIGHT;
				else if (take_tortoistate_state == 1) ani = LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_LEFT;
				else if (kick_state == 1) ani = LUIGI_ANI_SMALL_KICK_LEFT;
				else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_SMALL_JUMPING_LEFT;
				else if (run_fast_state == 1) ani = LUIGI_ANI_SMALL_RUNNING_LEFT_FAST;
				else if (run_state == 1) ani = LUIGI_ANI_SMALL_RUNNING_LEFT;
				else ani = LUIGI_ANI_SMALL_WALKING_LEFT;
			}
		}

		else if (level == LUIGI_LEVEL_TAIL)
		{
			if (vx == 0)
			{
				if (nx > 0)
				{
					if (fly_high_state == 1) ani = LUIGI_ANI_FLY_HIGH_RIGHT;
					else if (fly_low_state == 1) ani = LUIGI_ANI_FLY_LOW_RIGHT;
					else if (fight_state == 1) ani = LUIGI_ANI_TAIL_FIGHT;
					else if (sit_state == 1) ani = LUIGI_ANI_TAIL_SIT_RIGHT;
					else if (kick_state == 1) ani = LUIGI_ANI_TAIL_KICK_RIGHT;
					else if (take_tortoistate_state == 1) ani = LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_RIGHT;
					else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_TAIL_JUMPING_RIGHT;
					else ani = LUIGI_ANI_TAIL_IDLE_RIGHT;
				}
				else
				{
					if (fly_high_state == 1) ani = LUIGI_ANI_FLY_HIGH_LEFT;
					else if (fly_low_state == 1) ani = LUIGI_ANI_FLY_LOW_LEFT;
					else if (fight_state == 1) ani = LUIGI_ANI_TAIL_FIGHT;
					else if (sit_state == 1) ani = LUIGI_ANI_TAIL_SIT_LEFT;
					else if (kick_state == 1) ani = LUIGI_ANI_TAIL_KICK_LEFT;
					else if (take_tortoistate_state == 1) ani = LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_LEFT;
					else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_TAIL_JUMPING_LEFT;
					else ani = LUIGI_ANI_TAIL_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (fly_high_state == 1) ani = LUIGI_ANI_FLY_HIGH_RIGHT;
				else if (fly_low_state == 1) ani = LUIGI_ANI_FLY_LOW_RIGHT;
				else if (fight_state == 1) ani = LUIGI_ANI_TAIL_FIGHT;
				else if (turn_state == 1) ani = LUIGI_ANI_TAIL_TURN_LEFT;
				else if (take_tortoistate_state == 1) ani = LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_RIGHT;
				else if (kick_state == 1) ani = LUIGI_ANI_TAIL_KICK_RIGHT;
				else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_TAIL_JUMPING_RIGHT;
				else if (run_fast_state == 1) ani = LUIGI_ANI_TAIL_RUNNING_RIGHT_FAST;
				else if (run_state == 1)	ani = LUIGI_ANI_TAIL_RUNNING_RIGHT;
				else ani = LUIGI_ANI_TAIL_WALKING_RIGHT;
			}
			else
			{
				if (fly_high_state == 1) ani = LUIGI_ANI_FLY_HIGH_LEFT;
				else if (fly_low_state == 1) ani = LUIGI_ANI_FLY_LOW_LEFT;
				else if (fight_state == 1) ani = LUIGI_ANI_TAIL_FIGHT;
				else if (turn_state == 1) ani = LUIGI_ANI_TAIL_TURN_RIGHT;
				else if (take_tortoistate_state == 1) ani = LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_LEFT;
				else if (kick_state == 1) ani = LUIGI_ANI_TAIL_KICK_LEFT;
				else if (jump_state == 1 || jump_state == -1) ani = LUIGI_ANI_TAIL_JUMPING_LEFT;
				else if (run_fast_state == 1) ani = LUIGI_ANI_TAIL_RUNNING_LEFT_FAST;
				else if (run_state == 1) ani = LUIGI_ANI_TAIL_RUNNING_LEFT;
				else ani = LUIGI_ANI_TAIL_WALKING_LEFT;
			}
		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	//RenderBoundingBox();
}

void CLuigi::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case LUIGI_STATE_WALKING_RIGHT:
		run_state = 0;
		sit_state = 0;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		run_fast_state = 0;
		running_time_right = -1;
		running_time_left = -1;
		vx = walking_right_speech;
		nx = 1;
		break;
	case LUIGI_STATE_WALKING_LEFT:
		turn_state = 0;
		sit_state = 0;
		run_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		run_fast_state = 0;
		running_time_right = -1;
		running_time_left = -1;
		vx = -walking_left_speech;
		nx = -1;
		break;
	case LUIGI_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		jump_state = 1;
		fall_state = 0;
		kick_state = 0;
		turn_state = 0;
		fight_state = 0;
		run_fast_state = 0;
		running_time_right = -1;
		running_time_left = -1;
		vy = -LUIGI_JUMP_SPEED_Y - speech_Jump;
		if (slide_state)
		{
			if (nx > 0) vx = walking_right_speech;
			else vx = -walking_left_speech;
		}
		break;
	case LUIGI_STATE_IDLE:
		fly_low_state = 0;
		if (slide_state)
		{
			if (nx > 0) vx = walking_right_speech;
			else vx = -walking_left_speech;
		}
		else vx = 0;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		fight_state = 0;
		run_fast_state = 0;
		running_time_right = -1;
		running_time_left = -1;
		break;
	case LUIGI_STATE_DIE:
		vy = -LUIGI_DIE_DEFLECT_SPEED;
		break;
	case LUIGI_STATE_RUNNING_RIGHT:
		run_state = 1;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		fight_state = 0;
		sit_state = 0;
		run_fast_state = 0;
		vx = LUIGI_RUNNING_SPEED;
		nx = 1;
		break;
	case LUIGI_STATE_RUNNING_LEFT:
		run_state = 1;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		sit_state = 0;
		run_fast_state = 0;
		vx = -LUIGI_RUNNING_SPEED;
		nx = -1;
		break;
	case LUIGI_STATE_KICK:
		fly_high_state = 0;
		fly_low_state = 0;
		kick_state = 1;
		turn_state = 0;
		sit_state = 0;
		run_fast_state = 0;
		if (tortoiseshell != NULL)
		{
			if (nx > 0) {
				tortoiseshell->x = x + GetCurrentWidthLuigi();
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

		if (nx > 0) vx = LUIGI_WALKING_SPEED;
		else vx = -LUIGI_WALKING_SPEED;

		break;
	case LUIGI_STATE_TAKE_TORTOISESHELL_RIGHT:
		fly_high_state = 0;
		fly_low_state = 0;
		take_tortoistate_state = 1;
		turn_state = 0;
		speech_Jump = 0;
		sit_state = 0;
		kick_state = 0;
		fight_state = 0;
		run_fast_state = 0;
		break;
	case LUIGI_STATE_TAKE_TORTOISESHELL_LEFT:
		fly_high_state = 0;
		fly_low_state = 0;
		take_tortoistate_state = 1;
		turn_state = 0;
		speech_Jump = 0;
		sit_state = 0;
		kick_state = 0;
		fight_state = 0;
		run_fast_state = 0;
		break;
	case LUIGI_STATE_TURN_LEFT:
		fly_low_state = 0;
		turn_state = 1;
		running_time_right = -1;
		running_time_left = -1;
		if (run_state == 0)	vx = -walking_left_speech;
		else vx = -LUIGI_RUNNING_SPEED;
		break;
	case LUIGI_STATE_TURN_RIGHT:
		fly_low_state = 0;
		turn_state = 1;
		running_time_right = -1;
		running_time_left = -1;
		if (run_state == 0)	vx = walking_right_speech;
		else vx = LUIGI_RUNNING_SPEED;
		break;
	case LUIGI_STATE_FIGHT:
		fight_state = 1;
		if (nx > 0) vx = LUIGI_WALKING_SPEED;
		else vx = -LUIGI_WALKING_SPEED;
		break;
	case LUIGI_STATE_RUNNING_RIGHT_FAST:
		run_fast_state = 1;
		nx = 1;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		vx = LUIGI_RUNNING_FAST_SPEED;
		break;
	case LUIGI_STATE_RUNNING_LEFT_FAST:
		run_fast_state = 1;
		nx = 0;
		turn_state = 0;
		speech_Jump = 0;
		kick_state = 0;
		vx = -LUIGI_RUNNING_FAST_SPEED;
		break;
	case LUIGI_STATE_FLYING_LOW_RIGHT:
		nx = 1;
		fly_low_state = 1;
		fight_state = 0;
		vy = LUIGI_FLYING_SPEED_Y;

		break;
	case LUIGI_STATE_FLYING_LOW_LEFT:
		nx = 0;
		fly_low_state = 1;
		fight_state = 0;
		vy = LUIGI_FLYING_SPEED_Y;
		break;
	case LUIGI_STATE_FLYING_HIGH_RIGHT:
		nx = 1;
		fly_high_state = 1;
		fly_low_state = 0;
		vy = -LUIGI_FLYING_SPEED_Y;
		break;
	case LUIGI_STATE_FLYING_HIGH_LEFT:
		nx = 0;
		fly_high_state = 1;
		fly_low_state = 0;
		vy = -LUIGI_FLYING_SPEED_Y;
		break;
	case LUIGI_STATE_SIT:
		if (!sit_state)
		{
			y = y + 9;
			sit_state = 1;
		}


		break;
	case LUIGI_STATE_SHOOT_FIRE_BULLET_RIGHT:
		nx = 1;
		shoot_fire_bullet_state = 1;
		break;
	case LUIGI_STATE_SHOOT_FIRE_BULLET_LEFT:
		nx = 0;
		shoot_fire_bullet_state = 1;
		break;
	}

}

void CLuigi::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == LUIGI_LEVEL_BIG)
	{
		if (sit_state)
		{
			right = x + LUIGI_BIG_SIT_BBOX_WIDTH;
			bottom = y + LUIGI_BIG_SIT_BBOX_HEIGHT;
		}
		else
		{
			right = x + LUIGI_BIG_BBOX_WIDTH;
			bottom = y + LUIGI_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == LUIGI_LEVEL_TAIL)
	{
		if (sit_state)
		{
			right = x + LUIGI_TAIL_SIT_BBOX_WIDTH;
			bottom = y + LUIGI_TAIL_SIT_BBOX_HEIGHT;
		}
		else
		{
			right = x + LUIGI_TAIL_BBOX_WIDTH;
			bottom = y + LUIGI_TAIL_BBOX_HEIGHT;
		}
	}
	else
	{
		right = x + LUIGI_SMALL_BBOX_WIDTH;
		bottom = y + LUIGI_SMALL_BBOX_HEIGHT;
	}
}



/*
	Reset Mario status to the beginning state of a scene
*/
void CLuigi::Reset()
{
	SetState(LUIGI_STATE_IDLE);
	SetLevel(LUIGI_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

