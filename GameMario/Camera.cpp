#include "Camera.h"
#include "Utils.h"


void CCamera::UpdateCam(DWORD dt) {

	if (idScene == ID_SCENE_MAP_4)
	{
		player->GetPosition(cx, cy);
		CGame* game = CGame::GetInstance();

		//Mario chạm biên map bên phải
		if (cam_x < 1743 && auto_cam) {
			
			cam_x += 0.0315f * dt;
			CGame::GetInstance()->SetCamPos(round(cam_x), 267.0f);
			SetCamPosition(round(cam_x), 267.0f);
		}
		else if (auto_cam && cam_x < 2000)
		{
			CGame::GetInstance()->SetCamPos(1743, 267.0f);
			SetCamPosition(1743, 267.0f);
		}
		else if (auto_cam && cam_x > 2000)
		{
			CGame::GetInstance()->SetCamPos(2000, 267.0f);
			SetCamPosition(2000, 267.0f);
		}
		else {
			player->GetPosition(cx, cy);
			CGame* game = CGame::GetInstance();

			//Mario chạm biên map bên phải
			if (cx < WIDTH_MIN_MAP_1) {
				player->SetPosition(CAM_X_MIN, cy);
				SetCamPosition(CAM_X_MIN, 267.0f);
				CGame::GetInstance()->SetCamPos(round(cx), 267.0f);
			}

			//Nếu mario đến gần biên map bên trái
			if (cx > NEAR_WIDTH_LIMIT_MAP_2)
			{
				if (cx > WIDTH_MAX_MAP_2) player->SetPosition(WIDTH_MAX_MAP_2, cy);
				cx = CAM_X_MAX_2;
				SetCamPosition(cx, 267.0f);
				CGame::GetInstance()->SetCamPos(round(cx), 267.0f);
			}

			//Khi mario ở giữa màn hình
			else if (cx > game->GetScreenWidth() / 2)
			{

				cx -= game->GetScreenWidth() / 2;
				cy -= game->GetScreenHeight() / 2;
				SetCamPosition(round(cx), 267.0f);
				CGame::GetInstance()->SetCamPos(round(cx), 267.0f);

			}
			else {

				CGame::GetInstance()->SetCamPos(0.0f, 267.0f);
				SetCamPosition(0.0f, 267.0f);
			}
			cy -= game->GetScreenHeight() / 2;
		}

	}
	else if (idScene == ID_SCENE_MAP_1)
	{
		player->GetPosition(cx, cy);
		CGame* game = CGame::GetInstance();

		//Mario chạm biên map bên phải
		if (cx < WIDTH_MIN_MAP_1) {
			player->SetPosition(CAM_X_MIN, cy);
			SetCamPosition(CAM_X_MIN, 267.0f);
		}

		//Nếu mario đến gần biên map bên trái
		if (cx > NEAR_WIDTH_LIMIT_MAP_1)
		{
			if (cx > WIDTH_MAX_MAP_1) player->SetPosition(WIDTH_MAX_MAP_1, cy);
			cx = CAM_X_MAX;
			SetCamPosition(cx, 267.0f);
		}

		//Nếu Mario có đuôi và ở vị trí giữa màn hình
		//else if (player->GetLevel() == MARIO_LEVEL_TAIL && cy < game->GetScreenHeight() / 2 && cx > game->GetScreenWidth() / 2) {
		//	cx -= game->GetScreenWidth() / 2;
		//	cy -= game->GetScreenHeight() / 2;
		//	CGame::GetInstance()->SetCamPos(round(cx), round(cy));
		//	SetCamPosition(round(cx), round(cy));
		//}

		//Khi mario ở giữa màn hình và ở dưới cống
		else if (cx > game->GetScreenWidth() / 2 && cy > UNDERGROUND_Y)
		{
			cx -= game->GetScreenWidth() / 2;
			cy -= game->GetScreenHeight() / 2;
			CGame::GetInstance()->SetCamPos(round(cx), CAM_Y_UNDERGROUND);
			SetCamPosition(round(cx), CAM_Y_UNDERGROUND);
		}

		//Khi mario ở giữa màn hình
		else if (cx > game->GetScreenWidth() / 2)
		{
			if (player->GetLevel() == MARIO_LEVEL_TAIL)
			{
				cx -= game->GetScreenWidth() / 2;
				cy -= game->GetScreenHeight() / 2 + 20;
				SetCamPosition(round(cx), round(cy));
				CGame::GetInstance()->SetCamPos(round(cx), round(cy));
			}
			else
			{
				cx -= game->GetScreenWidth() / 2;
				cy -= game->GetScreenHeight() / 2;
				SetCamPosition(round(cx), 267.0f);
				CGame::GetInstance()->SetCamPos(round(cx), 267.0f);
			}

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
				CGame::GetInstance()->SetCamPos(0.0f, 267.0f);
				SetCamPosition(0.0f, 267.0f);
			}
		}
		cy -= game->GetScreenHeight() / 2;
	}
}