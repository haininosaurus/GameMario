#include "Curtain.h"

CCurtain::CCurtain() : CGameObject()
{
	create_time = (DWORD)GetTickCount64();
}

void CCurtain::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CCurtain::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CreateIntroAnimationCurtain();
	y += vy * dt;
}

void CCurtain::CreateIntroAnimationCurtain()
{
	if (GetTickCount64() - create_time < 1500 && GetTickCount64() - create_time > 1000)
		vy = -SPEED_Y;
}