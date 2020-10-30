#include "Koopas.h"
#include "Road.h"
#include "Pipe.h"
#include "ColorBrick.h"
#include "QuestionBlock.h"
#include "TransObject.h"
#include "Utils.h"
#include "Goombas.h"

CKoopa::CKoopa() {
	SetState(KOOPA_STATE_WALKING_LEFT);
}
void CKoopa::Render()
{
	int ani = KOOPA_ANI_WALKING_RIGHT;
	if (vx < 0 && state != KOOPA_STATE_SPIN_LEFT && state != KOOPA_STATE_SPIN_RIGHT)
		ani = KOOPA_ANI_WALKING_LEFT;
	else if (state == KOOPA_STATE_HIDE)
		ani = KOOPA_ANI_HIDE;
	else if (state == KOOPA_STATE_SPIN_LEFT || state == KOOPA_STATE_SPIN_RIGHT)
		ani = KOOPA_ANI_SPIN;
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
		if (dynamic_cast<CColorBrick*>(c->obj) || dynamic_cast<CGoomba*>(c->obj)) {}
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
		//if (rdx != 0 && rdx != dx)
		//	x += nx * abs(rdx);
		DebugOut(L"coEventResult : %d\n", coEventsResult.size());
		DebugOut(L"x : %f\n", x);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0) vy = 0;
		//if (nx != 0) vx = 0;
		DebugOut(L"nx : %f\n", nx);
		DebugOut(L"vx : %f\n", vx);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)
			{
				if (dynamic_cast<CTransObject*>(e->obj))
				{
					//CTransObject* trans = dynamic_cast<CTransObject*>(e->obj);
					//DebugOut(L"e->nx: %f\n", e->nx);
					if (e->nx > 0) {

						//vx = KOOPA_WALKING_SPEED;
						SetState(KOOPA_STATE_WALKING_RIGHT);
					}
					else if (e->nx < 0) SetState(KOOPA_STATE_WALKING_LEFT);
				}
			}
		//	DebugOut(L"coenventobject: %d\n", coEventsResult.size());
			if (state == KOOPA_STATE_SPIN_LEFT)
			{
				if (dynamic_cast<CPipe*>(e->obj) || dynamic_cast<CQuestionBlock*>(e->obj) || dynamic_cast<CHeadRoad*>(e->obj))
				{

					if (e->nx > 0) {
						SetState(KOOPA_STATE_SPIN_RIGHT);
						//DebugOut(L"e->nx left: %f\n", e->nx);
					}
				}

			}
			else if (state == KOOPA_STATE_SPIN_RIGHT)
			{
				if (dynamic_cast<CPipe*>(e->obj) || dynamic_cast<CQuestionBlock*>(e->obj) || dynamic_cast<CHeadRoad*>(e->obj))
				{
					if (e->nx < 0) {
						DebugOut(L"e->nx right: %f\n", e->nx);
						SetState(KOOPA_STATE_SPIN_LEFT);
					}
				}

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
	}
}
int CKoopa::GetState() {
	return CGameObject::GetState();
}