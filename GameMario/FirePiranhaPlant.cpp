#include "FirePiranhaPlant.h"

#include "Mario.h"

#include "Goombas.h"
#include <algorithm>
#include "synchapi.h"
#include "Road.h"
#include "Pipe.h"
#include "TransObject.h"
#include "Game.h"
#include "Koopas.h"
#include "Utils.h"
#include "FirePlantBullet.h"

CFirePiranhaPlant::CFirePiranhaPlant(CGameObject* mario)
{
	check_y_limit = false;
	found_player = false;
	SetState(FIREPIRANHAPLANT_STATE_HIDE);
	player = mario;
}

void CFirePiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FIREPIRANHAPLANT_STATE_DESTROY || state == FIREPIRANHAPLANT_STATE_HIDE)
	{
		left = x;
		top = y;
		right = 0;
		bottom = 0;
	}
	else
	{
		left = x;
		top = y;
		right = x + FIREPIRANHAPLANT_BBOX_WIDTH;
		bottom = y + FIREPIRANHAPLANT_BBOX_HEIGHT;
	}

}


void CFirePiranhaPlant::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;
	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (dynamic_cast<CMario*>(c->obj)) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}
	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CFirePiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state != FIREPIRANHAPLANT_STATE_DESTROY)
	{
		if (check_y_limit == false)
		{
			y_limit = y - FIREPIRANHAPLANT_BBOX_HEIGHT;
			check_y_limit = true;
		}

		if (y >= y_limit)
			y += dy;
		else y = y_limit;

		sx = x - player->x;
		sy = y - player->y;
		tan = sx / sy;


		if (abs(x - player->x) < 150)
		{
			if (state == FIREPIRANHAPLANT_STATE_HIDE && tan > 1.0f || state == FIREPIRANHAPLANT_STATE_HIDE && tan < -1.0f)
				found_player = true;
		}

		//Update state
		if (found_player)
		{
			if (hide_state)
			{
				move_up_state = 1;
				move_up_time = GetTickCount();
			}

			if (move_up_state)
			{
				if (GetTickCount() - move_up_time < 920)
					SetState(FIREPIRANHAPLANT_STATE_MOVE_UP);
				else SetState(FIREPIRANHAPLANT_STATE_APPEARANCE);
			}
			if (appearance_state)
			{
				if (GetTickCount() - move_up_time < 3000)
					SetState(FIREPIRANHAPLANT_STATE_APPEARANCE);
				if (GetTickCount() - move_up_time > 2000 && fire_plant_bullet->GetState() == FIREPLANTBULLET_TRANSPARENT_STATE)
					ShootFirePlantBullet();
				if (GetTickCount() - move_up_time > 3500)
					SetState(FIREPIRANHAPLANT_STATE_MOVE_DOWN);
			}
			if (move_down_state)
			{
				if (GetTickCount() - move_up_time < 4420)
					SetState(FIREPIRANHAPLANT_STATE_MOVE_DOWN);
				else
				{
					SetState(FIREPIRANHAPLANT_STATE_HIDE);
					found_player = false;
				}
			}
		}


		// Check direction
		if (y - player->y < 0)
		{
			if (x - player->x < 0)
			{
				nx = 1;
				down_right_state = 1;
				top_right_state = 0;
				down_left_state = 0;
				top_left_state = 0;
			}
			else
			{
				nx = 0;
				down_left_state = 1;
				top_left_state = 0;
				down_right_state = 0;
				top_right_state = 0;
			}

		}
		else
		{
			if ((x - player->x < 0))
			{
				nx = 1;
				down_right_state = 0;
				top_right_state = 1;
				down_left_state = 0;
				top_left_state = 0;
			}
			else
			{
				nx = 0;
				top_left_state = 1;
				down_left_state = 0;
				down_right_state = 0;
				top_right_state = 0;
			}
		}
	}

}

void CFirePiranhaPlant::Render()
{

	if (hide_state) return;
	else if (state == FIREPIRANHAPLANT_STATE_DESTROY) return;
	else {
		int ani = FIREPIRANHAPLANT_ANI_DOWN_LEFT;

		if (down_left_state) ani = FIREPIRANHAPLANT_ANI_DOWN_LEFT;
		else if (down_right_state) ani = FIREPIRANHAPLANT_ANI_DOWN_RIGHT;
		else if (top_right_state) ani = FIREPIRANHAPLANT_ANI_TOP_RIGHT;
		else ani = FIREPIRANHAPLANT_ANI_TOP_LEFT;

		animation_set->at(ani)->Render(x, y);
	}

}

void CFirePiranhaPlant::CreateFirePlantBullet(CGameObject* fireplantbullet)
{
	if (fire_plant_bullet == NULL)
		fire_plant_bullet = fireplantbullet;
	else if (fire_plant_bullet->GetState() == FIREPLANTBULLET_DESTROY_STATE)
		fire_plant_bullet->SetState(FIREPLANTBULLET_TRANSPARENT_STATE);
}

void CFirePiranhaPlant::ShootFirePlantBullet()
{
	if (fire_plant_bullet->GetState() == FIREPLANTBULLET_TRANSPARENT_STATE)
	{

		if (nx > 0)
		{
			fire_plant_bullet->SetPosition(x + 20, y);
			if (tan > 0 && tan < 1.7)
			{
				fire_plant_bullet->SetState(FIREPLANTBULLET_SHOOTED_RIGHT_30_STATE);
			}
			else if (tan > 1.7)
			{
				fire_plant_bullet->SetState(FIREPLANTBULLET_SHOOTED_RIGHT_60_STATE);
			}
			else if (tan < 0 && tan > -1.7f)
			{
				fire_plant_bullet->SetState(FIREPLANTBULLET_SHOOTED_RIGHT_120_STATE);
			}
			else
			{
				fire_plant_bullet->SetState(FIREPLANTBULLET_SHOOTED_RIGHT_150_STATE);
			}

		}

		else
		{
			fire_plant_bullet->SetPosition(x, y);
			if (tan > 0 && tan < 1.7)
			{
				fire_plant_bullet->SetState(FIREPLANTBULLET_SHOOTED_LEFT_120_STATE);
			}
			else if (tan > 1.7)
			{
				fire_plant_bullet->SetState(FIREPLANTBULLET_SHOOTED_LEFT_150_STATE);
			}
			else if (tan < 0 && tan > -1.7f)
			{
				fire_plant_bullet->SetState(FIREPLANTBULLET_SHOOTED_LEFT_30_STATE);
			}
			else
			{
				fire_plant_bullet->SetState(FIREPLANTBULLET_SHOOTED_LEFT_60_STATE);
			}


		}
	}

}

void CFirePiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREPIRANHAPLANT_STATE_DESTROY:
		break;
	case FIREPIRANHAPLANT_STATE_MOVE_UP:
		//appearance_state = 0;
		hide_state = 0;
		move_up_state = 1;
		//DebugOut(L"da vao move up\n");
		vy = -FIREPIRANHAPLANT_SPEECH_Y;
		break;
	case FIREPIRANHAPLANT_STATE_MOVE_DOWN:
		hide_state = 0;
		move_down_state = 1;
		vy = FIREPIRANHAPLANT_SPEECH_Y;
		break;
	case FIREPIRANHAPLANT_STATE_HIDE:
		CreateFirePlantBullet(NULL);
		//DebugOut(L"da vao hiden\n");
		is_shoot = 0;
		hide_state = 1;
		appearance_state = 0;
		move_up_state = 0;
		move_down_state = 0;
		vy = 0;
		break;
	case FIREPIRANHAPLANT_STATE_APPEARANCE:
		//DebugOut(L"da vao appearance\n");
		appearance_state = 1;
		hide_state = 0;
		move_up_state = 0;
		move_down_state = 0;
		vy = 0;
		break;
	default:
		break;
	}
}

int CFirePiranhaPlant::GetState() {
	return CGameObject::GetState();
}