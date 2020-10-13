#include "Goombas.h"
#include "Game.h"

//CGoombas::CGoombas(float x, float y, float vx) :CGameObject(x, y)
//{
//	this->vx = vx;
//};

void CGoombas::Update(DWORD dt)
{
	//x += vx * dt;

	//int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	//if (x <= 0 || x >= BackBufferWidth - GOOMBAS_WIDTH) {

	//	vx = -vx;

	//	if (x <= 0)
	//	{
	//		x = 0;
	//	}
	//	else if (x >= BackBufferWidth - GOOMBAS_WIDTH)
	//	{
	//		x = (float)(BackBufferWidth - GOOMBAS_WIDTH);
	//	}
	//}
}

void CGoombas::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	ani = CAnimations::GetInstance()->Get(503);


	ani->Render(x, y);
}