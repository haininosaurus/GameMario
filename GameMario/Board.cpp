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
		SetPosition(cam->GetCx() - BOARD_CAM_X_PLUS, cam->GetCy() + BOARD_CAM_Y_PLUS);
		time->SetPositionNumbers(cam->GetCx() + BOARD_TIME_X_PLUS, cam->GetCy() + BOARD_TIME_Y_PLUS);
		score->SetPositionNumbers(cam->GetCx() + BOARD_SCORE_X_PLUS, cam->GetCy() + BOARD_SCORE_Y_PLUS);
		arrows->SetPositionArrows(cam->GetCx() + BOARD_ARROW_X_PLUS, cam->GetCy() + BOARD_ARROW_Y_PLUS);
		coin->SetPositionNumbers(cam->GetCx() + BOARD_COIN_X_PLUS, cam->GetCy() + BOARD_COIN_Y_PLUS);
		lives->SetPositionNumbers(cam->GetCx() + BOARD_LIVE_X_PLUS, cam->GetCy() + BOARD_LIVE_Y_PLUS);
		card[0]->SetPosition(cam->GetCx() + BOARD_CARD_1_X_PLUS, cam->GetCy() + BOARD_CARD_Y_PLUS);
		card[1]->SetPosition(cam->GetCx() + BOARD_CARD_2_X_PLUS, cam->GetCy() + BOARD_CARD_Y_PLUS);
		card[2]->SetPosition(cam->GetCx() + BOARD_CARD_3_X_PLUS, cam->GetCy() + BOARD_CARD_Y_PLUS);

	}
}

void CScoreBoard::GetBoundingBox(float& l, float& t, float& r, float& b) { return; }
