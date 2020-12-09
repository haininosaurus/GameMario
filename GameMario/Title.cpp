#include "Title.h"

CTitle::CTitle() : CGameObject()
{
	create_time = GetTickCount64();
}

void CTitle::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CTitle::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CreateIntroAnimationTitle();
	y += vy * dt;
}

void CTitle::CreateIntroAnimationTitle()
{
	if (GetTickCount64() - create_time < 5000 && GetTickCount64() - create_time > 4800)
		vy = SPEED_Y;
	if (GetTickCount64() - create_time > 5700)
		vy = 0;
}