#include "LongWoodenBlock.h"

void CLongWoodenBlock::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CLongWoodenBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + LONG_WOODEN_BLOCK_BBOX_WIDTH;
	b = y + LONG_WOODEN_BLOCK_BBOX_HEIGHT;
}

void CLongWoodenBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += vx * dt;
	y += vy * dt;

	if (is_fall)
	{
		if (GetTickCount64() - start_fall > 300)
		{
			SetState(LONG_WOODEN_BLOCK_STATE_FALL);
		}
	}

}

void CLongWoodenBlock::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case LONG_WOODEN_BLOCK_STATE_NORMAL:
		vy = 0;
		vx = -LONG_WOODEN_BLOCK_SPEED_X;
		break;
	case LONG_WOODEN_BLOCK_STATE_FALL:
		vy = LONG_WOODEN_BLOCK_SPEED_Y;
		vx = 0;
		break;
	default:
		break;
	}
}