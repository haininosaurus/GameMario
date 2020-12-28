#include "ScoreEffect.h"
#include "Utils.h"

void CScoreEffect::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SCORE_STATE_HIDEN:
		display_state = 0;
		break;
	default:
		display_state = 1;
		break;
	}
}

void CScoreEffect::Render()
{
	int ani = SCORE_ANI_100;
	if (state == SCORE_STATE_HIDEN) return;
	else if (state == SCORE_STATE_200) ani = SCORE_ANI_200;
	else if (state == SCORE_STATE_400) ani = SCORE_ANI_400;
	else if (state == SCORE_STATE_800) ani = SCORE_ANI_800;
	else if (state == SCORE_STATE_1000) ani = SCORE_ANI_1000;
	else if (state == SCORE_STATE_2000) ani = SCORE_ANI_2000;
	else if (state == SCORE_STATE_4000) ani = SCORE_ANI_4000;
	else if (state == SCORE_STATE_8000) ani = SCORE_ANI_8000;
	else if (state == SCORE_STATE_LEVELUP) ani = SCORE_ANI_LEVELUP;

	animation_set->at(ani)->Render(x, y);
}

void CScoreEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == SCORE_STATE_HIDEN) return;
	else
	{
		if (GetTickCount64() - display_start < 500)
		{
			y += vy * dt;
		}
		else SetState(SCORE_STATE_HIDEN);

	}

}


void CScoreEffect::DisplayScore(int s, float x, float y, DWORD t)
{
	SetState(s);
	SetPosition(x, y);
	display_start = t;
	vy = -SCORE_SPEED_Y;

	DebugOut(L"state score %d\n", state);

	if (state == SCORE_STATE_100)
	{
		DebugOut(L"da cong 100 d %d\n", state);
		AddScorePlay(100);
	}
	else if (state == SCORE_STATE_200) AddScorePlay(200);
	else if (state == SCORE_STATE_400) AddScorePlay(400);
	else if (state == SCORE_STATE_800) AddScorePlay(800);
	else if (state == SCORE_STATE_1000) AddScorePlay(1000);
	else if (state == SCORE_STATE_2000) AddScorePlay(2000);
	else if (state == SCORE_STATE_4000) AddScorePlay(4000);
	else if (state == SCORE_STATE_8000) AddScorePlay(8000);



}


