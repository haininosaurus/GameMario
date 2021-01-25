#include "Title.h"

CTitle::CTitle(int f) : CGameObject()
{
	form = f;
	if (form)
	{
		type = HIDEN_TITLE;
	}
	create_time = (DWORD)GetTickCount64();
}

void CTitle::Render()
{
	if (type == HIDEN_TITLE) return;
	animation_set->at(type)->Render(x, y);
}

void CTitle::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (!form)
	{
		CreateIntroAnimationTitle();
		y += vy * dt;
	}

}

void CTitle::CreateIntroAnimationTitle()
{
	if (GetTickCount64() - create_time < TITLE_MOVE_END && GetTickCount64() - create_time > TITLE_MOVE_START) {
		vy = TITLE_SPEED_Y;
		type = 0;
	}

	if (GetTickCount64() - create_time > TITLE_STOP_START && GetTickCount64() - create_time < TITLE_STOP_END)
		vy = 0;
	if (GetTickCount64() - create_time > TITLE_STOP_END)
	{
		y = 0;
		x = 0;
		type = 1;
	}

}