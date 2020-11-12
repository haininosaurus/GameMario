#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN				-1
#define SCENE_SECTION_TEXTURES				2
#define SCENE_SECTION_SPRITES				3
#define SCENE_SECTION_ANIMATIONS			4
#define SCENE_SECTION_ANIMATION_SETS		5
#define SCENE_SECTION_OBJECTS				6
#define SCENE_SECTION_QUESTION_OBJECTS		7

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

#define OBJECT_TYPE_PORTAL					50

#define MAX_SCENE_LINE						1024


void CPlayScene::_ParseSection_TEXTURES(string line)
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

void CPlayScene::_ParseSection_SPRITES(string line)
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

void CPlayScene::_ParseSection_ANIMATIONS(string line)
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

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
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
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;


	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_KOOPA: obj = new CKoopa(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_ROAD: obj = new CRoad(); break;
	case OBJECT_TYPE_BACKGROUND: obj = new CBackgroundObject(); break;
	case OBJECT_TYPE_QUESTION_BLOCK: obj = new CQuestionBlock(); break;
	case OBJECT_TYPE_COLOR_BRICK: obj = new CColorBrick(); break;
	case OBJECT_TYPE_PIPE: obj = new CPipe(); break;
	case OBJECT_TYPE_WOOD_BLOCK: obj = new CWoodBlock(); break;
	case OBJECT_TYPE_COLOR_BRICK_TOP: obj = new CColorBrickTop(); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(); break;
	case OBJECT_TYPE_TRANS: obj = new CTransObject(); break;
	case OBJECT_TYPE_HEADROAD: obj = new CHeadRoad(); break;
	case OBJECT_TYPE_CLOUD_BRICK: obj = new CCloudBrick(); break;
	case OBJECT_TYPE_MARIO_FIRE_BULLET:		
		obj = new CFireBullet();
		player->CreateFireBullet(obj);
		break;

	case OBJECT_TYPE_FIREPIRANHAPLANT:
		obj = new CFirePiranhaPlant(player);
		for (int i = 0; i < 2; i++)
		{
			if (firePiranhaPlant[i] == NULL) {
				firePiranhaPlant[i] = (CFirePiranhaPlant*)obj;
				break;
			}
		}
		break;
	case OBJECT_TYPE_FIRE_PLANT_BULLET:
		DebugOut(L"da tao bullet\n");
		obj = new CFirePlantBullet();
		for (int i = 0; i < 1; i++)
		{
			if (firePlantBullet[i] == NULL) {
				firePlantBullet[i] = (CFirePlantBullet*)obj;
				firePiranhaPlant[i]->CreateFirePlantBullet(firePlantBullet[i]);
				break;
			}
		}
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
//
//void CPlayScene::_ParseSection_QUESTION_OBJECTS(string line)
//{
//	vector<string> tokens = split(line);
//
//	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());
//
//	if (tokens.size() < 5) return; // skip invalid lines - an object set must have at least id, x, y
//
//	int object_type = atoi(tokens[0].c_str());
//	float x = atof(tokens[1].c_str());
//	float y = atof(tokens[2].c_str());
//
//	int ani_set_id = atoi(tokens[3].c_str());
//	int state = atoi(tokens[4].c_str());
//
//	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
//	CGameObject* obj = new CQuestionBlock(state);
//
//	obj->SetPosition(x, y);
//
//	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
//
//	obj->SetAnimationSet(ani_set);
//	objects.push_back(obj);
//}


void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

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
		if (line == "[QUESTION_OBJECTS]") {
			section = SCENE_SECTION_QUESTION_OBJECTS; continue;
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
		//case SCENE_SECTION_QUESTION_OBJECTS: _ParseSection_QUESTION_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{

	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	//vector<LPGAMEOBJECT> quesObjects;

	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	//for (size_t i = 1; i < questionBlocks.size(); i++)
	//{
	//	quesObjects.push_back(questionBlocks[i]);
	//}


	//for (size_t i = 0; i < questionBlocks.size(); i++)
	//{

	//	questionBlocks[i]->Update(dt, NULL, &quesObjects);

	//}
	//DebugOut(L"questionblocks: %d\n", questionBlocks.size());
	for (size_t i = 0; i < objects.size(); i++)
	{

		objects[i]->Update(dt, &coObjects);

	}



	//// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	 
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	if (cx < 0)	player->SetPosition(0, cy);
	if (cx > 2816) player->SetPosition(2816, cy);

	else if (player->GetLevel() == MARIO_LEVEL_TAIL && cy < game->GetScreenHeight() / 2 && cx > game->GetScreenWidth()/2) {
		cx -= game->GetScreenWidth() / 2;
		cy -= game->GetScreenHeight() / 2;
		CGame::GetInstance()->SetCamPos(round(cx), round(cy) - 10.0f);

	}

	else if (cx > game->GetScreenWidth() / 2)
	{
		cx -= game->GetScreenWidth() / 2;
		cy -= game->GetScreenHeight() / 2;
		CGame::GetInstance()->SetCamPos(round(cx), -10.0f);
		
	}
	else {
		if (player->GetLevel() == MARIO_LEVEL_TAIL && cy < game->GetScreenHeight() / 2)
		{
			cy -= game->GetScreenHeight() / 2;
			CGame::GetInstance()->SetCamPos(0.0f, round(cy) - 10.0f);
		}
		else CGame::GetInstance()->SetCamPos(0.0f, -10.0f);
	}
}

void CPlayScene::Render()
{

	for (int i = objects.size()-1; i >= 0 ; i--)
		objects[i]->Render();
	//for (int i = questionBlocks.size() - 1; i >= 0; i--)
	//	questionBlocks[i]->Render();
	//player->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_X:

		if (mario->GetJumpState() == 0 && mario->GetKickState() == 0 && mario->GetFlyLowState() == 0) {
			mario->SetJumpStart(GetTickCount());
			//DebugOut(L"da vao\n");
			//mario->SetState(MARIO_STATE_JUMP);
		}
		if (mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			if (mario->GetState() == MARIO_STATE_RUNNING_RIGHT_FAST
				|| mario->GetState() == MARIO_STATE_FLYING_HIGH_RIGHT
				|| mario->GetState() == MARIO_STATE_RUNNING_LEFT_FAST
				|| mario->GetState() == MARIO_STATE_FLYING_HIGH_LEFT)
			{
				mario->SetFlyHighStart(GetTickCount());
				if(mario->nx > 0)
					mario->SetState(MARIO_STATE_FLYING_HIGH_RIGHT);
				else mario->SetState(MARIO_STATE_FLYING_HIGH_LEFT);
			}

			else if (mario->vy != 0 && mario->GetJumpState())
			{
				mario->SetFlyLowStart(GetTickCount());
				if (mario->nx > 0)
					mario->SetState(MARIO_STATE_FLYING_LOW_RIGHT);
				else mario->SetState(MARIO_STATE_FLYING_LOW_LEFT);
			}

		}		
		break;
	case DIK_Z:
		if (mario->GetLevel() == MARIO_LEVEL_TAIL && mario->GetFightState() == 0 &&
			GetTickCount() - mario->GetFightStart() > 500)
		{
			mario->SetFightStart(GetTickCount());
			mario->SetState(MARIO_STATE_FIGHT);
		}
		if (mario->GetLevel() == MARIO_LEVEL_FIRE && !mario->GetShootFireBulletState())
		{
			mario->SetShootFireBulletStart(GetTickCount());
			mario->ShootFireBullet();
			if(mario->nx > 0)
				mario->SetState(MARIO_STATE_SHOOT_FIRE_BULLET_RIGHT);
			else mario->SetState(MARIO_STATE_SHOOT_FIRE_BULLET_LEFT);
		}
		break;
	case DIK_S:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
			mario->SetPosition(mario->x, mario->y - MARIO_SMALL_BBOX_HEIGHT);
			mario->SetLevel(MARIO_LEVEL_BIG);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_BIG) {
			mario->SetPosition(mario->x, mario->y - 1);
			mario->SetLevel(MARIO_LEVEL_TAIL);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_TAIL) {
			mario->SetPosition(mario->x, mario->y - MARIO_SMALL_BBOX_HEIGHT);
			mario->SetLevel(MARIO_LEVEL_FIRE);
		}
		else mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_A:
		mario->Reset();
		break;
	case DIK_RIGHT:
		if (mario->GetWalkingRightSpeech() != 0) mario->ResetWalkingRightSpeech();
		if (mario->GetSlidingTimeRight() != 0) mario->ResetSlidingTimeRight();
		break;
	case DIK_LEFT:
		if (mario->GetWalkingLeftSpeech() != 0) mario->ResetWalkingLeftSpeech();
		if (mario->GetSlidingTimeLeft() != 0) mario->ResetSlidingTimeLeft();
		break;
		
	}
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_Z:
		if (mario->GetStateTakeTortoiseshell() == 1)
		{
			mario->SetKickStart(GetTickCount());
			mario->SetState(MARIO_STATE_KICK);
		}
		break;
	case DIK_X:
		mario->SetJumpState(-1);
		break;
	case DIK_DOWN:
		if (mario->GetSitState())
		{
			mario->y -= 10;
			mario->SetSitState(0);
		}
		break;
	default:
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	//Mario sit
	if (game->IsKeyDown(DIK_DOWN))
	{
		if (mario->GetLevel() != MARIO_LEVEL_SMALL &&
			mario->GetState() == MARIO_STATE_IDLE)
		{
			mario->SetState(MARIO_STATE_SIT);
			
		}
	}
	//if key right is down, disable key left and key down
	if (game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_LEFT))
	{
		mario->SetWalkRightTime(GetTickCount());
		//mario doesn't turn left
		if (GetTickCount() - mario->GetWalkLeftTime() > 200)
		{
			//mario runs right or runs fast right
			if (game->IsKeyDown(DIK_Z) || game->IsKeyDown(DIK_Z) && game->IsKeyDown(DIK_X))
			{
				//mario run fast right
				if (GetTickCount() - mario->GetRunningRightTime() > 1000 && mario->GetRunningRightTime() != -1)
					mario->SetState(MARIO_STATE_RUNNING_RIGHT_FAST);
				else mario->SetState(MARIO_STATE_RUNNING_RIGHT); 					//mario run right
			}
			else //mario walks right
			{
				mario->ResetWalkingLeftSpeech();
				if (mario->GetWalkingRightSpeech() < MARIO_WALKING_SPEED)
					mario->SetWalkingRightSpeech();
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
			}
			mario->ResetSlidingTimeLeft();
			if (mario->GetSlidingTimeRight() <= 500)
				mario->SetSlidingTimeRight();
		}
		else mario->SetState(MARIO_STATE_TURN_LEFT); 			//mario turns left

	}
	//if key left is down, disable key right and key down
	else if (game->IsKeyDown(DIK_LEFT) && !game->IsKeyDown(DIK_RIGHT))
	{
		mario->SetWalkLeftTime(GetTickCount());
		if (GetTickCount() - mario->GetWalkRightTime() > 200)
		{
			if (game->IsKeyDown(DIK_Z) || game->IsKeyDown(DIK_Z) && game->IsKeyDown(DIK_X))
			{
				if (GetTickCount() - mario->GetRunningLeftTime() > 1000 && mario->GetRunningLeftTime() != -1)
					mario->SetState(MARIO_STATE_RUNNING_LEFT_FAST);
				else mario->SetState(MARIO_STATE_RUNNING_LEFT);
			}
			else
			{
				mario->ResetWalkingRightSpeech();
				if (mario->GetWalkingLeftSpeech() < MARIO_WALKING_SPEED)
					mario->SetWalkingLeftSpeech();
				mario->SetState(MARIO_STATE_WALKING_LEFT);
			}
			mario->ResetSlidingTimeRight();
			if (mario->GetSlidingTimeLeft() <= 500)
				mario->SetSlidingTimeLeft();
		}
		else mario->SetState(MARIO_STATE_TURN_RIGHT);
	}
	else if (!mario->GetSlideState()) mario->SetState(MARIO_STATE_IDLE);

	if (game->IsKeyDown(DIK_X)) {

		if (GetTickCount() - mario->GetJumpStart() < 380)
		{
			if (mario->GetSpeechJump() < 0.2)
				mario->SetSpeechJump();
			if (mario->GetJumpState() != -1) mario->SetState(MARIO_STATE_JUMP);
		}
	}
}
