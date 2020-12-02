#include "ScoreBoard.h"
#include "Camera.h"
#include "Mario.h"

void CScoreBoard::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CScoreBoard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if(cam != NULL)
		SetPosition(cam->GetCx()-8.0f, cam->GetCy() + 165.0f);
}

void CScoreBoard::GetBoundingBox(float& l, float& t, float& r, float& b) { return; }
