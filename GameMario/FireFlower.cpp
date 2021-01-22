#include "FireFlower.h"

void CFireFlower::Render()
{
	if (GetState() == FIRE_FLOWER_STATE_HIDEN) return;
	animation_set->at(0)->Render(x, y);
}

void CFireFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);


}

void CFireFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;

	if (state == FIRE_FLOWER_STATE_HIDEN)
	{
		r = 0;
		b = 0;
	}
	else
	{
		r = x + FIRE_FLOWER_BBOX_WIDTH;
		b = y + FIRE_FLOWER_BBOX_HEIGHT;
	}
}

void CFireFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	default:
		break;
	}
}
