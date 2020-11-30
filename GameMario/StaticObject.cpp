#include "StaticObject.h"

void CStaticObject::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CStaticObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + STATIC_OBJECT_BBOX_WIDTH;
	b = y + STATIC_OBJECT_BBOX_HEIGHT;
}