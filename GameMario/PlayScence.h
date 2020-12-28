#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
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
#include "CloudBrick.h"
#include "FireBullet.h"
#include "FirePiranhaPlant.h"
#include "FirePlantBullet.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "BlueBrick.h"
#include "Camera.h"
#include "Board.h"
#include "PiranhaPlant.h"
#include "TimePlay.h"
#include "Number.h"
#include "ScoreEffect.h"

#define QUESTIONBLOCK_AMOUNT		8
#define ITEM_QUESTIONBLOCK_AMOUNT	8
#define BRICK_AMOUNT				20
#define ITEM_BRICK_AMOUNT			20

class CPlayScene : public CScene
{
protected:

	CMario* player;
	CCamera* cam;
	vector<CNumber*> num;
	CTime* time;
	CScoreBoard* sb;
	CFirePiranhaPlant* firePiranhaPlant[2];
	CFirePlantBullet* firePlantBullet[2];
	CQuestionBlock* questionBlock[QUESTIONBLOCK_AMOUNT];
	CBrick* brick[BRICK_AMOUNT];
	CGameObject* itemQuestionBlock[ITEM_QUESTIONBLOCK_AMOUNT];
	CGameObject* itemBrick[ITEM_BRICK_AMOUNT];

	CScoreEffect* scoreEffect[100];

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> effectObjects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_ITEM_OBJECTS(string line);
	void _ParseSection_ENEMIES(string line);


public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();

	void AddEffectObject(CGameObject* obj) { effectObjects.push_back(obj); }
	virtual void Unload();

	CMario* GetPlayer() { return player; }

	friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

