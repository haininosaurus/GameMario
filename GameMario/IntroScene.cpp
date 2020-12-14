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

CIntroScene::CIntroScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CIntroScenceKeyHandler(this);
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
#define SCENE_SECTION_ITEM_QUESTION_OBJECTS		7
#define SCENE_SECTION_ENEMIES					8

#define OBJECT_TYPE_MARIO					0
#define OBJECT_TYPE_BRICK					3
#define OBJECT_TYPE_ROAD					2
#define OBJECT_TYPE_QUESTION_BLOCK			4
#define OBJECT_TYPE_BACKGROUND				6
#define OBJECT_TYPE_COLOR_BRICK				5
#define OBJECT_TYPE_PIPE					8
#define OBJECT_TYPE_WOOD_BLOCK				7
#define OBJECT_TYPE_GOOMBA					1
#define OBJECT_TYPE_COLOR_BRICK_TOP			9
#define OBJECT_TYPE_KOOPA					10
#define OBJECT_TYPE_COIN					11
#define OBJECT_TYPE_TRANS					12
#define OBJECT_TYPE_HEADROAD				13
#define OBJECT_TYPE_CLOUD_BRICK				14
#define OBJECT_TYPE_MARIO_FIRE_BULLET		15
#define OBJECT_TYPE_FIREPIRANHAPLANT		16
#define OBJECT_TYPE_FIRE_PLANT_BULLET		17
#define OBJECT_TYPE_MUSHROOM				18
#define OBJECT_TYPE_LEAF					19
#define OBJECT_TYPE_BLUE_BRICK				20
#define OBJECT_TYPE_SCORE_BOARD				21
#define OBJECT_TYPE_PIRANHA_PLANT			22
#define OBJECT_TYPE_LUIGI					23
#define OBJECT_TYPE_CURTAIN					24
#define OBJECT_TYPE_TITLE					25

#define OBJECT_TYPE_PORTAL					50

#define MAX_SCENE_LINE						1024


void CIntroScene::_ParseSection_TEXTURES(string line)
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

void CIntroScene::_ParseSection_SPRITES(string line)
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

void CIntroScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CIntroScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
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
void CIntroScene::_ParseSection_OBJECTS(string line)
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
	case OBJECT_TYPE_MARIO:
		{
			obj = new CMario();
			CMario* mario = dynamic_cast<CMario*>(obj);
			mario->SetIntroState(1);
			break;
		}
	case OBJECT_TYPE_BRICK:
		obj = new CBrick();
		break;
	case OBJECT_TYPE_ROAD:
		{
			int type = atoi(tokens[4].c_str());
			obj = new CRoad(type);
		}
		break;
	case OBJECT_TYPE_BACKGROUND: obj = new CBackgroundObject(); break;
	case OBJECT_TYPE_COLOR_BRICK: obj = new CColorBrick(); break;
	case OBJECT_TYPE_PIPE: obj = new CPipe(); break;
	case OBJECT_TYPE_WOOD_BLOCK: obj = new CWoodBlock(); break;
	case OBJECT_TYPE_COLOR_BRICK_TOP: obj = new CColorBrickTop(); break;
	case OBJECT_TYPE_TRANS: obj = new CTransObject(); break;
	case OBJECT_TYPE_HEADROAD: obj = new CHeadRoad(); break;
	case OBJECT_TYPE_LUIGI: obj = new CLuigi(); break;
	case OBJECT_TYPE_CURTAIN: obj = new CCurtain(); break;
	case OBJECT_TYPE_TITLE: obj = new CTitle(); break;
	case OBJECT_TYPE_LEAF:
		{
			obj = new CLeaf();
			CLeaf* leaf = dynamic_cast<CLeaf*>(obj);
			leaf->SetIntroState(1);
			break;
		}

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


void CIntroScene::_ParseSection_ENEMIES(string line)
{
	vector<string> tokens = split(line);


	if (tokens.size() < 5) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());
	int state = atoi(tokens[4].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_GOOMBA: 
		{
			obj = new CGoomba(state);
			CGoomba* goomba = dynamic_cast<CGoomba*>(obj);
			goomba->SetIntroState(1);
			break;
		}

	case OBJECT_TYPE_KOOPA:
	{
		obj = new CKoopa(state);
		CKoopa* koopa = dynamic_cast<CKoopa*>(obj);
		koopa->SetIntroState(1);
		break;
	}
	default:
		break;
	}
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CIntroScene::Load()
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
		if (line == "[ENEMIES]") {
			section = SCENE_SECTION_ENEMIES; continue;
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
		case SCENE_SECTION_ENEMIES: _ParseSection_ENEMIES(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	//DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CIntroScene::Update(DWORD dt)
{

	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}


	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);

	}
}
void CIntroScene::Render()
{

	for (int i = objects.size() - 1; i >= 0; i--)
	{
		objects[i]->Render();
	}
}

/*
	Unload current scene
*/
void CIntroScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
}

void CIntroScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	if(game->IsKeyDown(DIK_X))
		CGame::GetInstance()->SwitchScene(1);
}
void CIntroScenceKeyHandler::OnKeyUp(int KeyCode)
{

}

void CIntroScenceKeyHandler::KeyState(BYTE* states)
{

}
