#pragma once
#include "Cell.h"
#include "Utils.h"
#include "Game.h"
#include <iostream>
#include <fstream>



#define IN_USE_WIDTH	200
#define IN_USE_HEIGHT	200

#define GRID_SECTION_SETTINGS		1
#define GRID_SECTION_OBJECTS		2
#define GRID_SECTION_ITEM_OBJECTS	3
#define GRID_SECTION_ENEMIES		4

#define MAX_GRID_LINE 1024

#define QUESTIONBLOCK_AMOUNT		9
#define ITEM_QUESTIONBLOCK_AMOUNT	9
#define BRICK_AMOUNT				20
#define ITEM_BRICK_AMOUNT			20

class CGrid
{
	int numRow, numCol;
	int cellWidth;
	int  cellHeight;
	Cell** cells;


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
