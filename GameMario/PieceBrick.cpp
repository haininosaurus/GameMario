#include "PieceBrick.h"


void CPieceBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	y += vy * dt;
	x += vx * dt;

	if (state == PIECEBRICK_STATE_DISPLAY && GetTickCount64() - display_start > 400)
	{
		SetState(PIECEBRICK_STATE_HIDEN);
	}

}

void CPieceBrick::Render()
{
	if (state == PIECEBRICK_STATE_HIDEN) return;
	animation_set->at(0)->Render(x, y);
}