#include "Koopas.h"
#include <algorithm>
#include "Road.h"
#include "Pipe.h"
#include "ColorBrick.h"
#include "QuestionBlock.h"
#include "TransObject.h"
#include "Utils.h"
#include "Goombas.h"
#include "Game.h"
#include "FireBullet.h"
#include "Brick.h"
#include "Mario.h"
#include "Leaf.h"

CKoopa::CKoopa(int form)
{
	SetForm(form);
	SetState(KOOPA_STATE_WALKING_LEFT);
	intro_state = 0;
	create_time = GetTickCount64();
}
void CKoopa::Render()
{
	if (hiden_state) return;
	int ani = KOOPA_ANI_RED_WALKING_RIGHT;
	if (form == KOOPA_RED_FORM)
	{
		if (vx < 0 && state != KOOPA_STATE_SPIN_LEFT && state != KOOPA_STATE_SPIN_RIGHT)
			ani = KOOPA_ANI_RED_WALKING_LEFT;
		else if (state == KOOPA_STATE_HIDE)
			ani = KOOPA_ANI_RED_HIDE;
		else if (state == KOOPA_STATE_SPIN_LEFT || state == KOOPA_STATE_SPIN_RIGHT)
			ani = KOOPA_ANI_RED_SPIN;
		else if (state == KOOPA_STATE_TAKEN)
			ani = KOOPA_ANI_RED_TAKEN;
	}
	else if(form == KOOPA_GREEN_FORM)
	{
		if (intro_state && state == KOOPA_STATE_TAKEN || intro_state && state == KOOPA_STATE_HIDE)
			ani = KOOPA_ANI_GREEN_TAKEN;
		else if (vx < 0 && state != KOOPA_STATE_SPIN_LEFT && state != KOOPA_STATE_SPIN_RIGHT)
			ani = KOOPA_ANI_GREEN_WALKING_LEFT;
		else if (state == KOOPA_STATE_HIDE)
			ani = KOOPA_ANI_GREEN_HIDE;
		else if (state == KOOPA_STATE_SPIN_LEFT || state == KOOPA_STATE_SPIN_RIGHT)
			ani = KOOPA_ANI_GREEN_SPIN;
		else if (state == KOOPA_STATE_TAKEN)
			ani = KOOPA_ANI_GREEN_TAKEN;
		else  ani = KOOPA_ANI_GREEN_WALKING_RIGHT;
	}
	else if (form == PARAKOOPA_GREEN_FORM)
	{
		if (vx < 0) ani = PARAKOOPA_ANI_GREEN_JUMPING_LEFT;
		else ani = PARAKOOPA_ANI_GREEN_JUMPING_RIGHT;
	}

	animation_set->at(ani)->Render(x, y);
}


void CKoopa::FilterCollision(
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
		if (dynamic_cast<CColorBrick*>(c->obj) || dynamic_cast<CGoomba*>(c->obj) || dynamic_cast<CLeaf*>(c->obj)) {}
		else if(dynamic_cast<CTransObject*>(c->obj) && state == KOOPA_STATE_SPIN_LEFT ||
			dynamic_cast<CTransObject*>(c->obj) && state == KOOPA_STATE_SPIN_RIGHT){ }
		else if (dynamic_cast<CColorBrickTop*>(c->obj)) {
			if (c->ny < 0) {
				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
			}
		}
		else if (dynamic_cast<CHeadRoad*>(c->obj)) {
			if (c->t < min_tx && c->nx != 0) {
				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
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

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);


	if (intro_state) CreateIntroAnimationKoopa();
	if (hiden_state) return;
	if(state != KOOPA_STATE_TAKEN)
		vy += KOOPA_GRAVITY * dt;
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

		CKoopa::FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy + ny * 0.2f;

		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (form != PARAKOOPA_GREEN_FORM)
			{
				if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)
				{
					if (dynamic_cast<CTransObject*>(e->obj))
					{
						if (e->nx > 0) {

							SetState(KOOPA_STATE_WALKING_RIGHT);
						}
						else if (e->nx < 0) SetState(KOOPA_STATE_WALKING_LEFT);

					}

					if (dynamic_cast<CFireBullet*>(e->obj))
					{
						CFireBullet* bullet = dynamic_cast<CFireBullet*>(e->obj);
						SetState(KOOPA_STATE_HIDE);
						bullet->SetState(FIREBULLET_DESTROY_STATE);
					}
				}
				if (e->ny != 0 && intro_state)
				{
					if (dynamic_cast<CMario*>(e->obj)) {
						CMario* mario = dynamic_cast<CMario*>(e->obj);
						mario->SetState(MARIO_STATE_DEFLECT);
						vy = -KOOPA_JUMP_DEFLECT_SPEED;
						vx = -0.05;
					}
				}
				if (state == KOOPA_STATE_SPIN_LEFT)
				{
					if (dynamic_cast<CPipe*>(e->obj) || dynamic_cast<CQuestionBlock*>(e->obj) || dynamic_cast<CHeadRoad*>(e->obj) || dynamic_cast<CBrick*>(e->obj))
					{
						if (e->nx > 0) {
							if (dynamic_cast<CBrick*>(e->obj))
							{
								CBrick* brick = dynamic_cast<CBrick*>(e->obj);
								brick->SetState(BRICK_STATE_HIDEN);
							}

							if (dynamic_cast<CQuestionBlock*>(e->obj))
							{
								CQuestionBlock* quesBlock = dynamic_cast<CQuestionBlock*>(e->obj);
								quesBlock->SetState(QUESTIONBLOCK_DEFLECT_STATE);
								quesBlock->SetStateItem(EFFECT_STATE);

							}
							SetState(KOOPA_STATE_SPIN_RIGHT);
						}
					}



				}
				else if (state == KOOPA_STATE_SPIN_RIGHT)
				{
					if (dynamic_cast<CPipe*>(e->obj) || dynamic_cast<CQuestionBlock*>(e->obj) || dynamic_cast<CHeadRoad*>(e->obj) || dynamic_cast<CBrick*>(e->obj))
					{
						if (e->nx < 0) {
							if (dynamic_cast<CBrick*>(e->obj))
							{
								CBrick* brick = dynamic_cast<CBrick*>(e->obj);
								brick->SetState(BRICK_STATE_HIDEN);
								brick->createEffectDestroy();
							}

							if (dynamic_cast<CQuestionBlock*>(e->obj))
							{
								CQuestionBlock* quesBlock = dynamic_cast<CQuestionBlock*>(e->obj);
								quesBlock->SetState(QUESTIONBLOCK_DEFLECT_STATE);
								quesBlock->SetStateItem(EFFECT_STATE);

							}
							SetState(KOOPA_STATE_SPIN_LEFT);
						}
					}
				}
			}
			else
			{
				if (e->ny < 0)
					vy = -PARAKOOPA_JUMP_SPEED;
			}
			
		}
	}



	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

			

}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (state == KOOPA_STATE_HIDE)
	{
		right = x + KOOPA_BBOX_HIDE_WIDTH;
		bottom = y + KOOPA_BBOX_HIDE_HEIGHT;
	}
	else if (state == KOOPA_STATE_SPIN_RIGHT || state == KOOPA_STATE_SPIN_LEFT)
	{
		right = x + KOOPA_BBOX_SPIN_WIDTH;
		bottom = y + KOOPA_BBOX_SPIN_HEIGHT;
	}
	else
	{
		right = x + KOOPA_BBOX_WIDTH;
		bottom = y + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_WALKING_RIGHT:
		isSpin = 0;
		vx = KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_WALKING_LEFT:
		isSpin = 0;
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_HIDE:
		vx = 0;
		vy = 0;
		hiden_state = 0;
		isSpin = 0;
		break;
	case KOOPA_STATE_SPIN_RIGHT:
		isSpin = 1;
		vx = KOOPA_SPINNING_SPEED;
		break;
	case KOOPA_STATE_SPIN_LEFT:
		isSpin = 1;
		vx = - KOOPA_SPINNING_SPEED;
		break;
	case KOOPA_STATE_TAKEN:
		vx = 0;
		vy = 0;
		isSpin = 0;
		break;
	case KOOPA_STATE_HIDEN:
		hiden_state = 1;
		break;
	}
}

void CKoopa::CreateIntroAnimationKoopa()
{
	if (GetTickCount64() - create_time < 6000) SetState(KOOPA_STATE_HIDEN);
	if (GetTickCount64() - create_time > 6000 && GetTickCount64() - create_time < 7500) {
		SetState(KOOPA_STATE_HIDE);
	}
	if (GetTickCount64() - create_time > 8600 && GetTickCount64() - create_time < 10000) {
		SetState(KOOPA_STATE_TAKEN);
	}
	if (GetTickCount64() - create_time > 12800 && GetTickCount64() - create_time < 15000) {
		SetState(KOOPA_STATE_SPIN_RIGHT);
	}

}

int CKoopa::GetState() {
	return CGameObject::GetState();
}