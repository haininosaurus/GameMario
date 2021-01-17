#include "LongWoodenBlock.h"

void CLongWoodenBlock::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CLongWoodenBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + LONG_WOODEN_BLOCK_BBOX_WIDTH;
	b = y + LONG_WOODEN_BLOCK_BBOX_HEIGHT;
}