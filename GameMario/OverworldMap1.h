#pragma once
#include "GameObject.h"
#include "Scence.h"
#include "Game.h"

#include "Map1.h"
#include "Board.h"
#include "BackgroundObject.h"
#include "MarioOverworld.h"
#include "Turtle.h"

class COverworldMap1 : public CScene
{
	CMarioOverworld* player;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_NODES(string line);

public:
	COverworldMap1(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();


	CMarioOverworld* GetPlayer() { return player; }

	friend class COverworldMapScenceKeyHandler;
};


class  COverworldMapScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	COverworldMapScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};