#pragma once
#include "Game.h"
#include "Scence.h"

#include "Textures.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Road.h"
#include "QuestionBlock.h"
#include "ColorBrick.h"
#include "Pipe.h"
#include "WoodBlock.h"
#include "Goombas.h"
#include "Koopas.h"
#include "Coin.h"
#include "TransObject.h"
#include "BackgroundObject.h"
#include "FirePiranhaPlant.h"
#include "FirePlantBullet.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Luigi.h"
#include "Curtain.h"
#include "Title.h"

#define QUESTIONBLOCK_AMOUNT		8
#define ITEM_QUESTIONBLOCK_AMOUNT	8
#define BRICK_AMOUNT				20
#define ITEM_BRICK_AMOUNT			20

class CIntroScene : public CScene
{
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_ENEMIES(string line);

public:
	CIntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	friend class CIntroScenceKeyHandler;
};

class CIntroScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CIntroScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

