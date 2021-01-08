#include "Brick.h"
#include "Utils.h"
#include "Coin.h"
#include "Animations.h"
#include "PlayScence.h"
#include "Game.h"

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

void CBrick::createEffectDestroy()
{
	//CGameObject* obj[4];
	//for (int i = 0; i < 4; i++)
	//	obj[i] = new CPieceBrick();

	//obj[0]->SetPosition(x, y);
	//obj[1]->SetPosition(x + PIECE_BBOX_WIDTH + 1, y);
	//obj[2]->SetPosition(x, y + PIECE_BBOX_HEIGHT + 1);
	//obj[3]->SetPosition(x + PIECE_BBOX_WIDTH + 1, y + PIECE_BBOX_HEIGHT + 1);

	//CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	//LPANIMATION_SET ani_set = animation_sets->Get(PIECE_BRICK_ANIMATIONSET);

	//LPSCENE scene = CGame::GetInstance()->GetCurrentScene();

	//for(int i = 0; i < 4; i++)
	//	obj[i]->SetAnimationSet(ani_set);
	//for (int i = 0; i < 4; i++)
	//	CPlayScene::AddEffectObject(obj[i]);
}
