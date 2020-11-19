#include "Leaf.h"

#include "Animations.h"



void CLeaf::Render()
{
	int ani = isRight;
	if (GetState() == LEAF_STATE_HIDEN) return;
	if (isRight) ani = LEAF_EFFECT_RIGHT_ANI;
	else ani = LEAF_EFFECT_LEFT_ANI;
	animation_set->at(ani)->Render(x, y);
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == EFFECT_STATE)
	{
		if (!effect_left_time_start && !effect_right_time_start)
		{
			if (GetTickCount() - effect_time_start < 300)
			{
				isRight = 1;
				vy = -LEAF_SPEED_Y;
			}
			else
			{
				effect_right_time_start = GetTickCount();
			}
		}


		if (GetTickCount() - effect_right_time_start < EFFECT_LIMIT_TIME && effect_right_time_start != 0)
		{
			isRight = 1;
			vy = LEAF_GRAVITY_Y;
			vx = LEAF_SPEED_X;
		}
		else if (GetTickCount() - effect_right_time_start >= EFFECT_LIMIT_TIME && effect_right_time_start != 0)
		{
			effect_right_time_start = 0;
			effect_left_time_start = GetTickCount();
		}

		if (GetTickCount() - effect_left_time_start < EFFECT_LIMIT_TIME && effect_left_time_start != 0)
		{
			isRight = 0;
			vy = LEAF_GRAVITY_Y;
			vx = -LEAF_SPEED_X;
		}
		else if (GetTickCount() - effect_left_time_start >= EFFECT_LIMIT_TIME && effect_left_time_start != 0)
		{
			effect_left_time_start = 0;
			effect_right_time_start = GetTickCount();
		}
		
		y += dy;
		x += dx;
		



	}

}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;

	if (state == LEAF_STATE_HIDEN)
	{
		r = 0;
		b = 0;
	}
	else
	{
		r = x + LEAF_BBOX_WIDTH;
		b = y + LEAF_BBOX_HEIGHT;
	}
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EFFECT_STATE:
		if (effect_state == 0)
		{
			effect_state = 1;
			effect_time_start = GetTickCount();
		}
		break;
	case LEAF_STATE_HIDEN:
		effect_state = 0;
		break;
	case LEAF_STATE_NORMAL:
		effect_state = 0;
		break;
	default:
		break;
	}
}
