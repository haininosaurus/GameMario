#include "Koopas.h"

CKoopa::CKoopa() {
	SetState(KOOPA_STATE_WALKING_LEFT);
}
void CKoopa::Render()
{
	int ani = KOOPA_ANI_WALKING_RIGHT;
	if (vx < 0 && GetState() != KOOPA_STATE_SPIN_LEFT && state != KOOPA_STATE_SPIN_RIGHT)
		ani = KOOPA_ANI_WALKING_LEFT;
	else if (state == KOOPA_STATE_HIDE)
		ani = KOOPA_ANI_HIDE;
	else if (state == KOOPA_STATE_SPIN_LEFT || state == KOOPA_STATE_SPIN_RIGHT)
		ani = KOOPA_ANI_SPIN;
	animation_set->at(ani)->Render(x, y);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPA_BBOX_WIDTH;
	bottom = y + KOOPA_BBOX_HEIGHT;
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_WALKING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_HIDE:
		if(isSpin == 0)	y += KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HIDE_HEIGHT + 1;
		vx = 0;
		vy = 0;
		isSpin = 0;
		break;
	case KOOPA_STATE_SPIN_RIGHT:
		//y += KOOPA_BBOX_HEIGHT - KOOPA_BBOX_SPIN_HEIGHT + 1;
		isSpin = 1;
		vx = KOOPA_SPINNING_SPEED;
		break;
	case KOOPA_STATE_SPIN_LEFT:
		//y += KOOPA_BBOX_HEIGHT - KOOPA_BBOX_SPIN_HEIGHT + 1;
		isSpin = 1;
		vx = - KOOPA_SPINNING_SPEED;
		break;
	}
}
int CKoopa::GetState() {
	return CGameObject::GetState();
}