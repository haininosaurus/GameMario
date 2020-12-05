#include "Brick.h"
#include "Utils.h"
#include "Coin.h"

void CBrick::Render()
{
	if (state == BRICK_STATE_HIDEN) return;
	else animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == BRICK_STATE_HIDEN) return;
	else
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}

}

void CBrick::AddItemBrick(CGameObject* obj)
{
	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		if (item[i] == NULL)
		{
			item[i] = obj;
			return;
		}
	}
}