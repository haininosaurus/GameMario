#pragma once
#include "GameObject.h"

#define SPEED_Y		0.08f

#define CURTAIN_MOVE_START		1000
#define CURTAIN_MOVE_END		1500

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

