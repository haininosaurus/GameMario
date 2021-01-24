#include "Tail.h"
#include "Brick.h"
#include "Goombas.h"

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	if (state == TAIL_STATE_HIDEN) return;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);

				brick->SetState(BRICK_STATE_HIDEN);
			}

			if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				goomba->SetState(GOOMBA_STATE_DEFLECT);
			}

		}
	}

	if (GetTickCount64() - fight_start > 300) {
		SetState(TAIL_STATE_FIGHT);
	}
	else SetState(TAIL_STATE_HIDEN);
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);

}

void CTail::SetFight(float Mx, float My, int Mnx, DWORD t)
{
	if (Mnx > 0)
	{
		vx = TAIL_FIGHT_SPEED;
		SetPosition(Mx + 14, My + 20);
		fight_start = t;
	}
	else {
		vx = -TAIL_FIGHT_SPEED;
		SetPosition(Mx, My + 20);
		fight_start = t;
	}

}

void CTail::FilterCollision(
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

		if (!dynamic_cast<CMario*>(c->obj))
		{
			if (c->t < min_tx && c->nx != 0) {
				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			}

			if (c->t < min_ty && c->ny != 0) {
				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
			}
		}



	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}