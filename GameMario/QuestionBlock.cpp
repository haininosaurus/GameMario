#include "QuestionBlock.h"
#include "Coin.h"
#include "Utils.h"


//CQuestionBlock::CQuestionBlock(int ques_id)
//{
//	if (ques_id == 0) {
//		quesObj = new CCoin();
//
//	}
//	DebugOut(L"quesid: %d\n", ques_id);
//}

void CQuestionBlock::Render()
{
	if (state == QUESTIONBLOCK_ITEM_STATE) 
		animation_set->at(0)->Render(x, y);
	else animation_set->at(1)->Render(x, y);
}

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (!check_init_location)
	{
		init_location_y = y;
		check_init_location = true;
		DebugOut(L"init location y: %d\n", init_location_y);
	}

	if (state != QUESTIONBLOCK_ITEM_STATE)
	{
		if (state == QUESTIONBLOCK_DEFLECT_STATE)
		{
			if (y > init_location_y - 8) y += dy;
			else
			{
				SetState(QUESTIONBLOCK_FALL_STATE);
				if (y < init_location_y) {
					y = init_location_y;
					SetState(QUESTIONBLOCK_NORMAL_STATE);
				}
				else y += dy;
			}
		}
		else SetState(QUESTIONBLOCK_NORMAL_STATE);
	}

	
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QUESTIONBLOCK_BBOX_WIDTH;
	b = y + QUESTIONBLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case QUESTIONBLOCK_ITEM_STATE:
		vy = 0;
		break;
	case QUESTIONBLOCK_DEFLECT_STATE:
		vy = -QUESTIONBLOCK_DEFLECT_SPEECH;
		break;
	case QUESTIONBLOCK_FALL_STATE:
		vy = QUESTIONBLOCK_FALL_SPEECH;
		break;
	case QUESTIONBLOCK_NORMAL_STATE:
		vy = 0;
		break;
	default:
		break;
	}
}