#include "Camera.h"


void CCamera::UpdateCam() {
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	if (cx < 0)	player->SetPosition(0, cy);
	if (cx > 2816) player->SetPosition(2816, cy);

	else if (player->GetLevel() == MARIO_LEVEL_TAIL && cy < game->GetScreenHeight() / 2 && cx > game->GetScreenWidth() / 2) {
		cx -= game->GetScreenWidth() / 2;
		cy -= game->GetScreenHeight() / 2;
		CGame::GetInstance()->SetCamPos(round(cx), round(cy) - 10.0f);
		SetCamPosition(round(cx), round(cy) - 10.0f);
	}
	else if (cx > game->GetScreenWidth() / 2 && cy > 165)
	{
		cx -= game->GetScreenWidth() / 2 - 40;
		cy -= game->GetScreenHeight() / 2;
		CGame::GetInstance()->SetCamPos(round(cx), 240.0f);
		SetCamPosition(round(cx), 240.0f);
	}

	else if (cx > game->GetScreenWidth() / 2)
	{
		cx -= game->GetScreenWidth() / 2;
		cy -= game->GetScreenHeight() / 2;
		CGame::GetInstance()->SetCamPos(round(cx), -10.0f);
		SetCamPosition(round(cx), - 10.0f);
	}
	else {
		if (player->GetLevel() == MARIO_LEVEL_TAIL && cy < game->GetScreenHeight() / 2)
		{
			cy -= game->GetScreenHeight() / 2;
			CGame::GetInstance()->SetCamPos(0.0f, round(cy) - 10.0f);
			SetCamPosition(round(cx), round(cy) - 10.0f);
		}
		else
		{
			CGame::GetInstance()->SetCamPos(0.0f, -10.0f);
			SetCamPosition(0.0f, - 10.0f);
		}
	}
	
}