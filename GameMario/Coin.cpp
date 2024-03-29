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

	if (state == EFFECT_STATE)
	{
		if (GetTickCount64() - effect_time_start < COIN_EFFECT_TIME)
		{
			if (GetTickCount64() - effect_time_start < COIN_EFFECT_MOVE_TIME)
				vy = -COIN_SPEED_Y;
			else vy = COIN_SPEED_Y;
			y += dy;
		}
		else
		{
			if (effect_state)
			{
				SetState(COIN_STATE_HIDEN);
				//scoreEffect->DisplayScore(score, x, y, GetTickCount64());
			}
		}

	}

}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;

	if (state == COIN_STATE_HIDEN)
	{
		r = 0;
		b = 0;
	}
	else
	{
		r = x + COIN_BBOX_WIDTH;
		b = y + COIN_BBOX_HEIGHT;
	}
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EFFECT_STATE:
		if (effect_state == 0)
		{
			effect_state = 1;
			effect_time_start = (DWORD)GetTickCount64();
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
