#include "Camera.h"
#include "Utils.h"


void CCamera::UpdateCam() {
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	if (cx < 0)	player->SetPosition(0, cy);
	if (cx > 2816) player->SetPosition(2816, cy);

	else if (player->GetLevel() == MARIO_LEVEL_TAIL && cy < game->GetScreenHeight() / 2 && cx > game->GetScreenWidth() / 2) {
		cx -= round(game->GetScreenWidth() / 2);
		cy -= round(game->GetScreenHeight() / 2);
		CGame::GetInstance()->SetCamPos(cx, cy);
		SetCamPosition(cx, cy);
	}
	else if (cx > game->GetScreenWidth() / 2 && cy > 165)
	{
		cx -= round(game->GetScreenWidth() / 2 - 40);
		cy -= round(game->GetScreenHeight() / 2);
		CGame::GetInstance()->SetCamPos(cx, 240.0f);
		SetCamPosition(cx, 240.0f);
	}

	else if (cx > game->GetScreenWidth() / 2)
	{
		cx -= round(game->GetScreenWidth() / 2);
		cy -= round(game->GetScreenHeight() / 2);
		SetCamPosition(round(cx), 0.0f);
		CGame::GetInstance()->SetCamPos(round(cx), 0.0f);

	}
	else {
		if (player->GetLevel() == MARIO_LEVEL_TAIL && cy < game->GetScreenHeight() / 2)
		{
			cy -= game->GetScreenHeight() / 2;
			CGame::GetInstance()->SetCamPos(0.0f, round(cy));
			SetCamPosition(round(cx), round(cy));
		}
		else
		{
			CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
			SetCamPosition(0.0f, 0.0f);
		}
	}
	
}