#include "Goombas.h"
#include "synchapi.h"
#include "Road.h"
CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

//void CGoomba::FilterCollision(
//	vector<LPCOLLISIONEVENT>& coEvents,
//	vector<LPCOLLISIONEVENT>& coEventsResult,
//	float& min_tx, float& min_ty,
//	float& nx, float& ny, float& rdx, float& rdy)
//{
//	min_tx = 1.0f;
//	min_ty = 1.0f;
//	int min_ix = -1;
//	int min_iy = -1;
//
//	nx = 0.0f;
//	ny = 0.0f;
//	coEventsResult.clear();
//
//	for (UINT i = 0; i < coEvents.size(); i++)
//	{
//		LPCOLLISIONEVENT c = coEvents[i];
//
//		if (dynamic_cast<CRoad*>(c->obj)) {
//			if (c->t < min_tx && c->nx != 0) {
//				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
//			}
//
//			if (c->t < min_ty && c->ny != 0) {
//				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
//			}
//		}
//	}
//}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += dx;
	y += dy;
	if (isDead) {
		timeDestroy += dt;
		if (timeDestroy >= dt * 15) SetPosition(-50, 50);
	}
	else {
		if (vx < 0 && x < 0) {
			x = 0; vx = -vx;
		}

		if (vx > 0 && x > 290) {
			x = 290; vx = -vx;
		}
	}


	//// Simple fall down
	//vy += GOOMBA_GRAVITY * dt;
	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//// turn off collision when die 
	//if (state != GOOMBA_STATE_DIE)
	//	CalcPotentialCollisions(coObjects, coEvents);
	//if (isDead) {
	//	timeDestroy += dt;
	//	if (timeDestroy >= dt * 15) SetPosition(-50, 50);
	//}
	//else {
	//	if (coEvents.size() == 0)
	//	{
	//		x += dx;
	//		y += dy;
	//		if (vx < 0 && x < 0) {
	//			x = 0; vx = -vx;
	//		}

	//		if (vx > 0 && x > 290) {
	//			x = 290; vx = -vx;
	//		}

	//	}
	//	else
	//	{
	//		float min_tx, min_ty, nx = 0, ny;
	//		float rdx = 0;
	//		float rdy = 0;

	//		CGoomba::FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//		x += min_tx * dx + nx * 0.4f;
	//		y += min_ty * dy + ny * 0.4f;

	//		if (nx != 0) vx = 0;
	//		if (ny != 0) vy = 0;

	//	}
	//}
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CGoomba::Render()
{
		int ani = GOOMBA_ANI_WALKING;
		if (state == GOOMBA_STATE_DIE) {
			ani = GOOMBA_ANI_DIE;
		}

		animation_set->at(ani)->Render(x, y);
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		isDead = true;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
	}
}
