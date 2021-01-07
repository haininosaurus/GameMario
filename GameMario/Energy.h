#pragma once
#include "GameObject.h"

#define DARK_ENERGY_STATE_HIDEN		0
#define DARK_ENERGY_STATE_DISPLAY	1


class CDarkEnergy : public CGameObject
{
	DWORD create_start;
public:
	void SetState(int state) {
		CGameObject::SetState(state);
	}
	virtual void Render() {
		if (state == DARK_ENERGY_STATE_HIDEN) return;
		else
			animation_set->at(0)->Render(x, y);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects){}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b){}
};

