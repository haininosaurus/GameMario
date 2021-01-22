#include "PlayScence.h"

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
#define OBJECT_TYPE_TIME					23
#define OBJECT_TYPE_NUMBER					24
#define OBJECT_TYPE_SCORE_EFFECT			25
#define OBJECT_TYPE_SCORE					26
#define OBJECT_TYPE_ARROW					27
#define OBJECT_TYPE_ARROWS					28
#define OBJECT_TYPE_COINPLAY				29
#define OBJECT_TYPE_LIVES					30
#define OBJECT_TYPE_SWITCH					31
#define OBJECT_TYPE_GOALCARDS				32
#define OBJECT_TYPE_DARK_ENERGY				33
#define OBJECT_TYPE_CARD					34
#define OBJECT_TYPE_CARDTEXT				35
#define OBJECT_PIECE_BRICK					36
#define OBJECT_TYPE_LONG_WOODEN_BLOCK		37
#define OBJECT_TYPE_BOOMERANG_BRO			38
#define OBJECT_TYPE_BOOMERANG				39

#define OBJECT_TYPE_PORTAL					50

CGrid::CGrid(LPCWSTR filePath)
{
	Load(filePath);
}

void CGrid::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	if (tokens.size() < 4) return; // skip invalid lines

	cellWidth = atoi(tokens[0].c_str());
	cellHeight = atoi(tokens[1].c_str());
	numCol = atoi(tokens[2].c_str());
	numRow = atoi(tokens[3].c_str());

	cells = new LPCELL[numCol];
	for (int i = 0; i < numCol; i++)
	{
		cells[i] = new Cell[numRow];
	}
}

void CGrid::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	if (tokens.size() < 4) return; // skip invalid lines

	int x = atoi(tokens[1].c_str());
	int y = atoi(tokens[2].c_str());

	int cellX = (x / cellWidth);
	int cellY = (y / cellHeight);

	int type = atoi(tokens[0].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CGameObject* obj = NULL;

	switch (type)
	{
	case OBJECT_TYPE_BRICK:
		obj = new CBrick();
		for (int i = 0; i < BRICK_AMOUNT; i++)
		{
			if (brick[i] == NULL)
			{
				brick[i] = (CBrick*)obj;
				break;
			}
		}
		break;
	case OBJECT_TYPE_ROAD:
	{
		int type = atoi(tokens[4].c_str());
		obj = new CRoad(type);
	}
	break;
	case OBJECT_TYPE_BACKGROUND: obj = new CBackgroundObject(); break;
	case OBJECT_TYPE_QUESTION_BLOCK:
	{
		int form = atoi(tokens[4].c_str());
		obj = new CQuestionBlock(form);
		for (int i = 0; i < QUESTIONBLOCK_AMOUNT; i++)
		{
			if (questionBlock[i] == NULL)
			{
				questionBlock[i] = (CQuestionBlock*)obj;
				break;
			}
		}
		break;
	}
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
	case OBJECT_TYPE_COLOR_BRICK: obj = new CColorBrick(); break;
	case OBJECT_TYPE_PIPE:
	{
		int type = atoi(tokens[4].c_str());
		obj = new CPipe(type);
	}
	break;
	case OBJECT_TYPE_WOOD_BLOCK: obj = new CWoodBlock(); break;
	case OBJECT_TYPE_COLOR_BRICK_TOP: obj = new CColorBrickTop(); break;
	case OBJECT_TYPE_TRANS: obj = new CTransObject(); break;
	case OBJECT_TYPE_HEADROAD: obj = new CHeadRoad(); break;
	case OBJECT_TYPE_CLOUD_BRICK: obj = new CCloudBrick(); break;
	case OBJECT_TYPE_BLUE_BRICK: obj = new CBlueBrick(); break;
	case OBJECT_TYPE_LONG_WOODEN_BLOCK: obj = new CLongWoodenBlock(); break;
	case OBJECT_TYPE_BOOMERANG:

		obj = new CBoomerang();
		for (int i = 0; i < 2; i++)
		{
			if (boomerang[i] == NULL)
			{
				DebugOut(L"da tao dan cho rua\n");
				boomerang[i] = (CBoomerang*)obj;
				break;
			}
		}
		break;
	case OBJECT_TYPE_BOOMERANG_BRO:
		DebugOut(L"da tao rua\n");
		obj = new CBoomerangBro(boomerang);
		break;
	case OBJECT_TYPE_GOALCARDS:
		obj = new CGoalCard(cardText);

		break;
	case OBJECT_TYPE_CARDTEXT:
		obj = new CCardText(cardT);
		cardText = (CCardText*)obj;

		break;

	case OBJECT_TYPE_FIREPIRANHAPLANT:
		DebugOut(L"da tai fire plant\n");
		obj = new CFirePiranhaPlant(((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer());
		for (int i = 0; i < 2; i++)
		{
			if (firePiranhaPlant[i] == NULL) {
				firePiranhaPlant[i] = (CFirePiranhaPlant*)obj;
				break;
			}
		}
		break;
	case OBJECT_TYPE_PIRANHA_PLANT:
		obj = new CPiranhaPlant(((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer());
		break;
	case OBJECT_TYPE_FIRE_PLANT_BULLET:
		obj = new CFirePlantBullet();
		for (int i = 0; i < 2; i++)
		{
			if (firePlantBullet[i] == NULL) {
				firePlantBullet[i] = (CFirePlantBullet*)obj;
				firePiranhaPlant[i]->CreateFirePlantBullet(firePlantBullet[i]);
				break;
			}
		}
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", type);
		return;
	}

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	if (obj != NULL)
	{
		int add = 0;
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		obj->SetOrigin(x, y, obj->GetState());
		cells[cellX][cellY].Add(obj);
	}
}


void CGrid::_ParseSection_ITEM_OBJECTS(string line)
{
	vector<string> tokens = split(line);


	if (tokens.size() < 6) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());


	int cellX = (x / cellWidth);
	int cellY = (y / cellHeight);

	int ani_set_id = atoi(tokens[3].c_str());
	int state = atoi(tokens[4].c_str());
	int item_object = atoi(tokens[5].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_COIN:
		obj = new CCoin();
		obj->SetState(state);
		if (state == 0)
		{
			for (int i = 0; i < ITEM_QUESTIONBLOCK_AMOUNT; i++)
			{
				if (itemQuestionBlock[i] == NULL)
				{
					itemQuestionBlock[i] = (CCoin*)obj;
					for (int j = 0; j < item_object; j++) {
						DebugOut(L"da them coin\n");
						questionBlock[i]->AddItemQuestionBlock(itemQuestionBlock[i]);
						if (i > 0 && questionBlock[i - 1] == NULL) 	DebugOut(L"chua them coin\n");
					}

					break;
				}
			}
		}

		if (state == 1)
		{
			if (item_object == 1) {
				for (int i = 0; i < ITEM_BRICK_AMOUNT; i++)
				{
					if (itemBrick[i] == NULL)
					{
						itemBrick[i] = (CCoin*)obj;
						brick[i]->AddItemBrick(itemBrick[i]);
						break;
					}
				}
			}
		}
		break;
	case OBJECT_TYPE_MUSHROOM:
		obj = new CMushroom();
		obj->SetState(state);
		if (state == 0)
		{
			for (int i = 0; i < ITEM_QUESTIONBLOCK_AMOUNT; i++)
			{
				if (itemQuestionBlock[i] == NULL)
				{
					itemQuestionBlock[i] = (CSwitch*)obj;
					questionBlock[i]->AddItemQuestionBlock(itemQuestionBlock[i]);
					break;
				}
			}
		}
		break;
	case OBJECT_TYPE_LEAF:
		obj = new CLeaf();
		obj->SetState(state);
		if (state == 0)
		{
			for (int i = 0; i < ITEM_QUESTIONBLOCK_AMOUNT; i++)
			{
				if (itemQuestionBlock[i] == NULL)
				{
					itemQuestionBlock[i] = (CLeaf*)obj;
					questionBlock[i]->AddItemQuestionBlock(itemQuestionBlock[i]);
					break;
				}
			}
		}
		break;
	case OBJECT_TYPE_SWITCH:
		obj = new CSwitch(brick);
		obj->SetState(state);
		if (state == 0)
		{
			for (int i = 0; i < ITEM_QUESTIONBLOCK_AMOUNT; i++)
			{
				if (itemQuestionBlock[i] == NULL)
				{
					itemQuestionBlock[i] = (CSwitch*)obj;
					questionBlock[i]->AddItemQuestionBlock(itemQuestionBlock[i]);
					break;
				}
			}
		}
		break;
	default:
		break;
	}

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	if (obj != NULL)
	{
		int add = 0;
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		obj->SetOrigin(x, y, obj->GetState());
		cells[cellX][cellY].Add(obj);
	}
}


void CGrid::_ParseSection_ENEMIES(string line)
{
	vector<string> tokens = split(line);


	if (tokens.size() < 5) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	int cellX = (x / cellWidth);
	int cellY = (y / cellHeight);

	int ani_set_id = atoi(tokens[3].c_str());
	int state = atoi(tokens[4].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_GOOMBA:
	{
		obj = new CGoomba(state);
		break;
	}

	case OBJECT_TYPE_KOOPA: obj = new CKoopa(state); break;
	default:
		break;
	}

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	if (obj != NULL)
	{
		int add = 0;
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		obj->SetOrigin(x, y, obj->GetState());
		cells[cellX][cellY].Add(obj);
	}
}

void CGrid::Load(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading grid resources from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	// current resource section flag
	int section;

	char str[MAX_GRID_LINE];
	while (f.getline(str, MAX_GRID_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") {
			section = GRID_SECTION_SETTINGS; continue;
		}
		if (line == "[OBJECTS]") {
			section = GRID_SECTION_OBJECTS; continue;
		}
		if (line == "[ITEM_QUESTION_OBJECTS]") {
			section = GRID_SECTION_ITEM_OBJECTS; continue;
		}
		if (line == "[ENEMIES]") {
			section = GRID_SECTION_ENEMIES; continue;
		}
		//
		// data section
		//
		switch (section)
		{
		case GRID_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GRID_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case GRID_SECTION_ITEM_OBJECTS: _ParseSection_ITEM_OBJECTS(line); break;
		case GRID_SECTION_ENEMIES: _ParseSection_ENEMIES(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene resources %s\n", filePath);
}


void CGrid::GetObjects(vector<LPGAMEOBJECT>& listObject, int CamX, int CamY)
{
	//listObject.clear();

	int left, top, right, bottom;
	int i, j, k;

	left = ((CamX) / cellWidth);
	right = (CamX + IN_USE_WIDTH) / cellWidth;
	if (((CamX + IN_USE_WIDTH) % cellWidth) != 0)
		right++;
	top = (CamY) / cellHeight;
	bottom = (CamY + IN_USE_HEIGHT) / cellHeight;

	LPGAMEOBJECT obj;

	if (right < 0 || left > numCol || bottom < 0 && top > numRow)
	{
		return;
	}

	if (right > numCol)
	{
		right = numCol;
	}
	if (bottom > numRow)
	{
		bottom = numRow;
	}
	if (left < 0)
	{
		left = 0;
	}
	if (top < 0)
	{
		top = 0;
	}

	for (i = left; i <= right; i++)
	{
		for (j = top; j <= bottom; j++)
		{
			if (!cells[i][j].GetListObjects().empty())
			{
				for (k = 0; k < cells[i][j].GetListObjects().size(); k++)
				{
					if (!cells[i][j].GetListObjects().at(k)->Actived)
					{
						float Ox, Oy;
						cells[i][j].GetListObjects().at(k)->GetOriginLocation(Ox, Oy);
						if (!((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->IsInUseArea(Ox, Oy) && cells[i][j].GetListObjects().at(k)->GetState() > 10)
							cells[i][j].GetListObjects().at(k)->reset();

							listObject.push_back(cells[i][j].GetListObjects().at(k));
						cells[i][j].GetListObjects().at(k)->SetActive(true);
					}
				}
			}
		}

	}

}

void CGrid::Unload()
{
	if (this != nullptr)
		if (cells)
		{
			for (int i = 0; i < numCol; i++)
			{
				for (int j = 0; j < numRow; j++)
				{
					cells[i][j].Unload();
				}
			}
			delete cells;
			cells = NULL;
		}
}