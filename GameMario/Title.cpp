#include "Title.h"

CTitle::CTitle() : CGameObject()
{
	create_time = GetTickCount64();
}

void CTitle::Render()
{
	animation_set->at(type)->Render(x, y);
}

void CTitle::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CreateIntroAnimationTitle();
	y += vy * dt;
}

void CTitle::CreateIntroAnimationTitle()
{
	if (GetTickCount64() - create_time < 5000 && GetTickCount64() - create_time > 4800) {
		vy = SPEED_Y;
		type = 0;
	}

	if (GetTickCount64() - create_time > 5700 && GetTickCount64() - create_time < 7000)
		vy = 0;
	if (GetTickCount64() - create_time > 7000)
	{
		y = 0;
		x = 0;
		type = 1;
	}

}