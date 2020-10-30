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
	if (state == QUESTIONBLOCK_STATE_QUESTION) {
		animation_set->at(0)->Render(x, y);

	}

	else {
		animation_set->at(1)->Render(x, y);
	}
}


void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QUESTIONBLOCK_BBOX_WIDTH;
	b = y + QUESTIONBLOCK_BBOX_HEIGHT;
}