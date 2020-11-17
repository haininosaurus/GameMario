#include "Coin.h"
#include "Animations.h"



void CCoin::Render()
{
	int ani = COIN_EFFECT_ANI;
	if (GetState() == COIN_STATE_NORMAL)
		ani = COIN_NORMAL_ANI;
	if (GetState() == COIN_STATE_HIDEN) return;
	animation_set->at(ani)->Render(x, y);
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == COIN_STATE_EFFECT)
	{
		if (GetTickCount() - effect_time_start < 500)
		{
			if (GetTickCount() - effect_time_start < 300)
				vy = -COIN_SPEED_Y;
			else vy = COIN_SPEED_Y;
			y += dy;
		}
		else SetState(COIN_STATE_HIDEN);

	}

}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;

}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_EFFECT:
		if (effect_state == 0)
		{
			effect_state = 1;
			effect_time_start = GetTickCount();
		}
		break;
	case COIN_STATE_HIDEN:
		effect_state = 0;
		break;
	case COIN_STATE_NORMAL:
		effect_state = 0;
		break;
	default:
		break;
	}
}
