#include "Board.h"
#include "Camera.h"
#include "Mario.h"
#include "Utils.h"

void CScoreBoard::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CScoreBoard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (cam != NULL)
	{
		SetPosition(cam->GetCx() - 8.0f, cam->GetCy() + 165.0f);
		time->SetPositionNumbers(cam->GetCx() + 152.0f, cam->GetCy() + 185.0f);
		score->SetPositionNumbers(cam->GetCx() + 80.0f, cam->GetCy() + 185.0f);
	}
}

void CScoreBoard::GetBoundingBox(float& l, float& t, float& r, float& b) { return; }
