#pragma once
#include "GameObject.h"

#define SPEED_Y		0.08f

class CCurtain : public CGameObject
{
	DWORD create_time;
public:
	CCurtain();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }
	void CreateIntroAnimationCurtain();
};

