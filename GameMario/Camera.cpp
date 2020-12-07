#include "Camera.h"
#include "Utils.h"


void CCamera::UpdateCam() {
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	if (cx < WIDTH_MIN_MAP_1) {
		player->SetPosition(CAM_X_MIN, cy);
		SetCamPosition(CAM_X_MIN, 0.0f);
	}

	if (cx > NEAR_WIDTH_LIMIT_MAP_1)
	{
		if (cx > WIDTH_MAX_MAP_1) player->SetPosition(WIDTH_MAX_MAP_1, cy);
		cx = CAM_X_MAX;
		SetCamPosition(cx, 0.0f);
	}

	else if (player->GetLevel() == MARIO_LEVEL_TAIL && cy < game->GetScreenHeight() / 2 && cx > game->GetScreenWidth() / 2) {
		cx -= game->GetScreenWidth() / 2;
		cy -= game->GetScreenHeight() / 2;
		CGame::GetInstance()->SetCamPos(round(cx), round(cy));
		SetCamPosition(round(cx), round(cy));
	}
	else if (cx > game->GetScreenWidth() / 2 && cy > UNDERGROUND_Y)
	{
		cx -= game->GetScreenWidth() / 2;
		cy -= game->GetScreenHeight() / 2;
		CGame::GetInstance()->SetCamPos(round(cx), CAM_Y_UNDERGROUND);
		SetCamPosition(round(cx), CAM_Y_UNDERGROUND);
	}

	else if (cx > game->GetScreenWidth() / 2)
	{
		cx -= game->GetScreenWidth() / 2;
		cy -= game->GetScreenHeight() / 2;
		SetCamPosition(round(cx), 0.0f);
		CGame::GetInstance()->SetCamPos(round(cx), 0.0f);
	}
	else {
		if (player->GetLevel() == MARIO_LEVEL_TAIL && cy < game->GetScreenHeight() / 2)
		{
			cy -= game->GetScreenHeight() / 2;
			CGame::GetInstance()->SetCamPos(0.0f, round(cy));
			SetCamPosition(0.0f, round(cy));
		}
		else
		{
			CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
			SetCamPosition(0.0f, 0.0f);
		}
	}	
}