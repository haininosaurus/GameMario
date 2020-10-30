#include "Coin.h"
#include "Animations.h"


void CCoin::Render()
{
	if(GetState() == COIN_STATE_NORMAL)
		animation_set->at(0)->Render(x, y);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;

}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	if (GetState() == COIN_STATE_NORMAL)
	{

	}
}
//
//void CCoin::CreateCoin(int x, int y) {
//	CCoin* coin = new CCoin();
//
//	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
//	LPANIMATION_SET ani_set = animation_sets->Get(11);
//
//	coin->SetAnimationSet(ani_set);
//}