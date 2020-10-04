#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Textures.h"

//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 16
//
//#define ID_TEX_BRICK 0
//#define BRICK_TEXTURE_PATH L"brick.png"
class CBrick : public CGameObject
{
public:
	CBrick(float x, float y, LPDIRECT3DTEXTURE9 texBrick);
	virtual void Render();
};

