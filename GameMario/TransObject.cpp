#include "TransObject.h"

void CTransObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + TRANS_BBOX_WIDTH;
	b = y + TRANS_BBOX_HEIGHT;
}

void CTransObject::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}