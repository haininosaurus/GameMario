#pragma once
#include "Cell.h"
#include <iostream>
#include <fstream>

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
#include "Mushroom.h"
#include "Leaf.h"
#include "BlueBrick.h"
#include "Camera.h"
#include "Board.h"
#include "PiranhaPlant.h"
#include "TimePlay.h"
#include "Number.h"
#include "ScoreEffect.h"
#include "Score.h"
#include "Arrow.h"
#include "CoinPlay.h"
#include "Lives.h"
#include "Switch.h"
#include "GoalCard.h"
#include "Energy.h"
#include "Cards.h"
#include "CardText.h"
#include "PieceBrick.h"
#include "Map.h"
#include "LongWoodenBlock.h"
#include "Boomerang.h"
#include "BoomerangBro.h"

#include "Brick.h"
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
#include "Switch.h"
#include "GoalCard.h"
#include "Energy.h"
#include "Cards.h"
#include "CardText.h"
#include "LongWoodenBlock.h"
#include "Boomerang.h"
#include "BoomerangBro.h"

#include "Cell.h"

#define QUESTIONBLOCK_AMOUNT		10
#define ITEM_QUESTIONBLOCK_AMOUNT	10
#define BRICK_AMOUNT				20
#define ITEM_BRICK_AMOUNT			20

#define GRID_SECTION_SETTINGS		1
#define GRID_SECTION_OBJECTS		2
#define GRID_SECTION_ITEM_OBJECTS	3
#define GRID_SECTION_ENEMIES		4

#define IN_USE_WIDTH	200
#define IN_USE_HEIGHT	200

#define MAX_GRID_LINE 1024

class CGrid
{
	int numRow, numCol;
	int cellWidth;
	int  cellHeight;
	Cell** cells;


	vector<CGameObject*> objects;

	CFirePiranhaPlant* firePiranhaPlant[2];
	CFirePlantBullet* firePlantBullet[2];
	CBoomerang* boomerang[2];
	CQuestionBlock* questionBlock[QUESTIONBLOCK_AMOUNT];
	CBrick* brick[BRICK_AMOUNT];
	CGameObject* itemQuestionBlock[ITEM_QUESTIONBLOCK_AMOUNT];
	CGameObject* itemBrick[ITEM_BRICK_AMOUNT];
	CCard* cards[3];
	CCard* cardT;
	CCardText* cardText;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_ITEM_OBJECTS(string line);
	void _ParseSection_ENEMIES(string line);

public:
	CGrid(LPCWSTR filePath);
	void GetObjects(vector<LPGAMEOBJECT>& listObject, int playerX, int playerY);
	void Load(LPCWSTR filePath);
	void Unload();
};


class CPlayScene : public CScene
{
protected:
	Map* map;

	CMario* player;
	CCamera* cam;
	vector<CNumber*> num;
	vector<CNumber*> numScore;
	vector<CNumber*> numCoin;
	vector<CNumber*> numLives;
	vector<CArrow*> arrow;
	vector<CCoin*> coin;
	CTime* time;
	CScore* score;
	CArrows* arrows;
	CCoinPlay* coinPlay;
	CDarkEnergy* darkEnergy;
	CLives* lives;
	CScoreBoard* sb;
	CBoomerang* boomerang[2];

	CCard* cards[3];
	CCard* cardT;
	CCardText* cardText;

	CGrid* grid;

	CPieceBrick* pieceBrick[16];

	CScoreEffect* scoreEffect[3];

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> effectObjects;
	vector<LPGAMEOBJECT> ListObjects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_ENEMIES(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_GRID(string line);


public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();

	void AddEffectObject(CGameObject* obj) { effectObjects.push_back(obj); }
	virtual void Unload();

	CMario* GetPlayer() { return player; }
	CCamera* GetCamera() { return cam; }
	virtual bool IsInUseArea(float x, float y);

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

