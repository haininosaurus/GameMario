#include "OverworldMap.h"

#include "IntroScene.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Animations.h"
#include "GameObject.h"

#include "Game.h"


using namespace std;

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

COverworldMap::COverworldMap(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;

	time = NULL;
	score = NULL;
	arrows = NULL;
	coinPlay = NULL;
	lives = NULL;
	sb = NULL;
	for (unsigned int i = 0; i < CARD_AMOUNT; i++)
	{
		cards[i] = NULL;
	}
	cardT = NULL;
	key_handler = new COverworldMapScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)2
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN					-1
#define SCENE_SECTION_TEXTURES					2
#define SCENE_SECTION_SPRITES					3
#define SCENE_SECTION_ANIMATIONS				4
#define SCENE_SECTION_ANIMATION_SETS			5
#define SCENE_SECTION_OBJECTS					6
#define SCENE_SECTION_NODES						7

#define OBJECT_TYPE_WORLDMAP1				1
#define OBJECT_TYPE_SCOREBOARD				2
#define OBJECT_TYPE_BACKGROUND				3
#define OBJECT_TYPE_MARIOOVERWORLD			4
#define	OBJECT_TYPE_TURTLE					5

#define OBJECT_TYPE_SCORE_BOARD				21
#define OBJECT_TYPE_TIME					23
#define OBJECT_TYPE_NUMBER					24
#define OBJECT_TYPE_SCORE					26
#define OBJECT_TYPE_ARROW					27
#define OBJECT_TYPE_ARROWS					28
#define OBJECT_TYPE_COINPLAY				29
#define OBJECT_TYPE_LIVES					30
#define OBJECT_TYPE_CARD					34


#define MAX_SCENE_LINE						1024


void COverworldMap::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void COverworldMap::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void COverworldMap::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (unsigned int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void COverworldMap::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (unsigned int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void COverworldMap::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;


	switch (object_type)
	{
	case OBJECT_TYPE_MARIOOVERWORLD:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMarioOverworld();
		player = (CMarioOverworld*)obj;
		break;
	case OBJECT_TYPE_WORLDMAP1:
		obj = new CMap1();
		break;
	case OBJECT_TYPE_SCOREBOARD:
		obj = new CScoreBoard();
		break;
	case OBJECT_TYPE_BACKGROUND:
		obj = new CBackgroundObject();
		break;
	case OBJECT_TYPE_TURTLE:
		obj = new CTurtle();
		break;
	case OBJECT_TYPE_CARD:
		obj = new CCard();
		{
			int type = atoi(tokens[4].c_str());
			if (type == 0)
			{
				for (int i = 0; i < CARD_AMOUNT; i++)
				{
					if (cards[i] == NULL)
					{
						cards[i] = (CCard*)obj;
						break;
					}
				}
			}
			else if (type == 1)
			{
				cardT = (CCard*)obj;
			}
		}

		break;
	case OBJECT_TYPE_SCORE_BOARD:
		obj = new CScoreBoard();
		sb = (CScoreBoard*)obj;
		sb->SetTime(time);
		sb->SetScore(score);
		sb->SetArrows(arrows);
		sb->SetCoinPlay(coinPlay);
		sb->SetLives(lives);
		sb->SetCards(cards);
		break;
	case OBJECT_TYPE_NUMBER:
	{
		int type = atoi(tokens[4].c_str());
		obj = new CNumber();
		if (type == 0)
			num.push_back((CNumber*)obj);
		if (type == 1)
			numScore.push_back((CNumber*)obj);
		if (type == 2)
			numCoin.push_back((CNumber*)obj);
		if (type == 3)
			numLives.push_back((CNumber*)obj);
		break;
	}
	case OBJECT_TYPE_TIME:
		obj = new CTime(num);
		time = (CTime*)obj;
		break;
	case OBJECT_TYPE_SCORE:
		obj = new CScore(numScore);
		score = (CScore*)obj;
		break;
	case OBJECT_TYPE_ARROW:
	{
		int type = atoi(tokens[4].c_str());
		obj = new CArrow(type);
		arrow.push_back((CArrow*)obj);
		break;
	}
	break;
	case OBJECT_TYPE_ARROWS:
		obj = new CArrows(arrow);
		arrows = (CArrows*)obj;
		break;
	case OBJECT_TYPE_COINPLAY:
		obj = new CCoinPlay(numCoin);
		coinPlay = (CCoinPlay*)obj;
		break;
	case OBJECT_TYPE_LIVES:
		obj = new CLives(numLives);
		lives = (CLives*)obj;
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}


	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);

}

void COverworldMap::_ParseSection_NODES(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 5) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float l = (float)atof(tokens[1].c_str());
	float t = (float)atof(tokens[2].c_str());
	float r = (float)atof(tokens[3].c_str());
	float b = (float)atof(tokens[4].c_str());

	int state = atoi(tokens[5].c_str());

	CNode* node = new CNode(l, t, r, b, state);
	player->PushNode(node);
}



void COverworldMap::Load()
{

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[NODES]") {
			section = SCENE_SECTION_NODES; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_NODES: _ParseSection_NODES(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	//DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void COverworldMap::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}


	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);

	}

	CGame* game = CGame::GetInstance();

	for (int i = 0; i < 3; i++)
	{
		cards[i]->SetState(game->GetItem(i));
	}
}
void COverworldMap::Render()
{

	for (int i = objects.size() - 1; i >= 0; i--)
	{
		objects[i]->Render();
	}
}

/*
	Unload current scene
*/
void COverworldMap::Unload()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	player = NULL;
	num.clear();
	numScore.clear();
	numCoin.clear();
	numLives.clear();
	arrow.clear();
	time = NULL;
	score = NULL;
	arrows = NULL;
	coinPlay = NULL;
	lives = NULL;
	sb = NULL;
	cardT = NULL;

	for (int i = 0; i < CARD_AMOUNT; i++)
		cards[i] = NULL;
}

void COverworldMapScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CMarioOverworld* mariooverworld = ((COverworldMap*)scence)->GetPlayer();

	if (game->IsKeyDown(DIK_X))
	{
		if(mariooverworld->GetTypeCurrentNode() == 1 || mariooverworld->GetTypeCurrentNode() == 4)
			CGame::GetInstance()->SwitchScene(mariooverworld->GetTypeCurrentNode());
	}
	else if (game->IsKeyDown(DIK_RIGHT) && !mariooverworld->GetIsMoving())
		mariooverworld->SetState(MARIO_STATE_MOVING_RIGHT);
	else if(game->IsKeyDown(DIK_UP) && !mariooverworld->GetIsMoving())
		mariooverworld->SetState(MARIO_STATE_MOVING_UP);
	else if (game->IsKeyDown(DIK_LEFT) && !mariooverworld->GetIsMoving())
		mariooverworld->SetState(MARIO_STATE_MOVING_LEFT);
	else if (game->IsKeyDown(DIK_DOWN) && !mariooverworld->GetIsMoving())
		mariooverworld->SetState(MARIO_STATE_MOVING_DOWN);
}
void COverworldMapScenceKeyHandler::OnKeyUp(int KeyCode)
{


}

void COverworldMapScenceKeyHandler::KeyState(BYTE* states)
{

}
