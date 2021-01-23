#pragma once
#include "GameObject.h"
#include "Brick.h"

#define SWITCH_STATE_HIDEN	0
#define EFFECT_STATE	1
#define SWITCH_STATE_ACTIVE	2

#define SWITCH_ANI_NORMAL	0
#define SWITCH_ANI_ACTIVE	1



class CSwitch : public CGameObject
{
	CBrick* brick[19];
	DWORD switch_time;
public:

	CSwitch(CBrick* b[19])
	{
		switch_time = 0;
		for (int i = 0; i < 19; i++)
		{
			brick[i] = b[i];
		}
	}
	void SetState(int state)
	{
		CGameObject::SetState(state);
	}
	void SetSwitch() {
		for (int i = 0; i < 18; i++)
		{
			if (brick[i]->GetState() == BRICK_STATE_NORMAL)
			{
				brick[i]->SetState(1);
				brick[i]->SetItem();
			}

		}
	}
	void ResetItem() {
		for (int i = 0; i < 18; i++)
		{
			if (brick[i]->GetItem()->GetState() == 2)
			{
				brick[i]->SetState(0);
				brick[i]->GetItem()->SetState(0);
			}

		}
	}
	void SetSwitchTime(DWORD t) { switch_time = t; }
	virtual void Render() {
		int ani;
		if (state == SWITCH_STATE_HIDEN) return;
		else if (state == EFFECT_STATE) ani = SWITCH_ANI_NORMAL;
		else ani = SWITCH_ANI_ACTIVE;

		animation_set->at(ani)->Render(x, y);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
	{
		if (state == SWITCH_STATE_ACTIVE)
		{
			if (GetTickCount64() - switch_time > 5000)
				ResetItem();
		}
	}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		if (state == 0) return;
		if (state == EFFECT_STATE)
		{
			l = x;
			t = y;
			r = x + 16;
			b = y + 16;
		}
		else if (state == SWITCH_STATE_ACTIVE)
		{
			l = x;
			t = y;
			r = x + 16;
			b = y + 8;
		}

	}
};

