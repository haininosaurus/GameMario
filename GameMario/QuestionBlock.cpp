#include "QuestionBlock.h"

//CQuestionBlock::CQuestionBlock(float x, float y) :CGameObject(x, y) {}

void CQuestionBlock::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QUESTIONBLOCK_BBOX_WIDTH;
	b = y + QUESTIONBLOCK_BBOX_HEIGHT;

}