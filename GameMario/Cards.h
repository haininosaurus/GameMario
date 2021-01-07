#pragma once
#include "GameObject.h"

#define CARD_STATE_HIDEN			-1
#define CARD_STATE_EMPTY			0
#define CARD_STATE_STAR				1
#define CARD_STATE_FLOWER			2
#define CARD_STATE_MUSHROOM			3

#define CARD_ANI_EMPTY				0
#define CARD_ANI_STAR				1
#define CARD_ANI_FLOWER				2
#define CARD_ANI_MUSHROOM			3


class CCard : public CGameObject
{

public:
	void SetState(int state)
	{
		CGameObject::SetState(state);
	}
	virtual void Render()
	{
		int ani = CARD_ANI_EMPTY;
		if (state == CARD_STATE_HIDEN) return;
		if (state == CARD_STATE_EMPTY) ani = CARD_ANI_EMPTY;
		else if (state == CARD_STATE_STAR) ani = CARD_ANI_STAR;
		else if (state == CARD_STATE_FLOWER) ani = CARD_ANI_FLOWER;
		else if (state == CARD_STATE_MUSHROOM) ani = CARD_ANI_MUSHROOM;

		animation_set->at(ani)->Render(x, y);
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects){}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b){}
};

