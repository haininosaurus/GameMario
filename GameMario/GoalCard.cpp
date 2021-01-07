#include "GoalCard.h"
#include "Utils.h"

void CGoalCard::SetState(int state)
{
	CGameObject::SetState(state);
}

void CGoalCard::Render()
{
	int ani = GOALCARD_ANI_STAR;
	if (state == GOALCARD_STATE_HIDEN) return;
	else if (state == GOALCARD_STATE_FLOWER) ani = GOALCARD_ANI_FLOWER;
	else if (state == GOALCARD_STATE_STAR) ani = GOALCARD_ANI_STAR;
	else if (state == GOALCARD_STATE_MUSHROOM) ani = GOALCARD_ANI_MUSHROOM;

	animation_set->at(ani)->Render(x, y);
}

void CGoalCard::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (GetTickCount64() - create_start > 100 && state != GOALCARD_STATE_HIDEN)
	{
		if(state < 4) state += 1;
		if (state == 4) state = 1;

		create_start = GetTickCount64();
	}
}

void CGoalCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == GOALCARD_STATE_HIDEN) return;
	else
	{
		l = x;
		t = y;
		r = x + GOALCARD_BBOX_WIDTH;
		b = y + GOALCARD_BBOX_HEIGHT;
	}

}