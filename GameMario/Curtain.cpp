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
	if (GetTickCount64() - create_time < CURTAIN_MOVE_END && GetTickCount64() - create_time > CURTAIN_MOVE_START)
		vy = -SPEED_Y;
}