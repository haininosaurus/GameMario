#include "Number.h"

void CNumber::Render()
{
	int ani = NUMBER_ANI_0;
	if (number == NUMBER_STATE_1) ani = NUMBER_ANI_1;
	else if (number == NUMBER_STATE_2) ani = NUMBER_ANI_2;
	else if (number == NUMBER_STATE_3) ani = NUMBER_ANI_3;
	else if (number == NUMBER_STATE_4) ani = NUMBER_ANI_4;
	else if (number == NUMBER_STATE_5) ani = NUMBER_ANI_5;
	else if (number == NUMBER_STATE_6) ani = NUMBER_ANI_6;
	else if (number == NUMBER_STATE_7) ani = NUMBER_ANI_7;
	else if (number == NUMBER_STATE_8) ani = NUMBER_ANI_8;
	else if (number == NUMBER_STATE_9) ani = NUMBER_ANI_9;

	animation_set->at(ani)->Render(x, y);
}

void CNumber::SetState(int state)
{
	CGameObject::SetState(state);
	number = state;
}
