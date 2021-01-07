#pragma once
#include "GameObject.h"
#include "Cards.h"

#define CARDTEXT_STATE_HIDEN		0
#define CARDTEXT_STATE_DISPLAY		1

class CCardText : public CGameObject
{
	CCard* card;
public:
	CCardText(CCard* c) {
		card = c;
		card->SetState(CARD_STATE_HIDEN);
	}
	void SetState(int state)
	{
		CGameObject::SetState(state);
	}
	virtual void Render()
	{
		int ani = CARDTEXT_STATE_HIDEN;
		if (state == CARDTEXT_STATE_HIDEN) return;
		animation_set->at(ani)->Render(x, y);
	}
	CCard* GetCard() { return card; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};

