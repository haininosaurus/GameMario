#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Mario.h"
#include "Brick.h"
#include "Textures.h"
#include "QuestionBlock.h"
#define WINDOW_CLASS_NAME L"Game Window"
#define MAIN_WINDOW_TITLE L"Game Mario"
#define WINDOW_ICON_PATH L"brick.ico"

#define BRICK_TEXTURE_PATH L"Textures\\brick.png"
#define MARIO_TEXTURE_PATH L"Textures\\mario.png"
#define TILE_4_PATH L"Textures\\tiles-4.png"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


using namespace std;

CMario *mario;
#define MARIO_START_X 10.0f
#define MARIO_START_Y 130.0f
#define MARIO_START_VX 0.2f
#define ID_TEX_MARIO 0

CBrick *brick;
#define BRICK_X 10.0f
#define BRICK_Y 10.0f

CQuestionBlock* questionBlock;
#define QUESTION_BLOCK_X 30.0f
#define QUESTION_BLOCK_Y 30.0f
#define ID_TEX_QUESTIONBLOCK 1


LPDIRECT3DTEXTURE9 texMario = NULL;
LPDIRECT3DTEXTURE9 texBrick = NULL;
LPDIRECT3DTEXTURE9 texQuestionBlock = NULL;

//vector<LPGAMEOBJECT> objects;  

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources. In this example, create a brick object and mario object
*/
void LoadResources()
{
	CGame* game = CGame::GetInstance();
	texBrick = game->LoadTexture(BRICK_TEXTURE_PATH);
	brick = new CBrick(BRICK_X, BRICK_Y, texBrick);

	CTextures* textures = CTextures::GetInstance();
	textures->Add(ID_TEX_MARIO, MARIO_TEXTURE_PATH, D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_QUESTIONBLOCK, TILE_4_PATH, D3DCOLOR_XRGB(176, 224, 248));
	CSprites* sprites = CSprites::GetInstance();

	texMario = textures->Get(ID_TEX_MARIO);
	texQuestionBlock = textures->Get(ID_TEX_QUESTIONBLOCK);

	sprites->Add(10001, 215, 88, 229, 105, texMario);
	sprites->Add(10002, 254, 88, 272, 105, texMario);
	//sprites->Add(10003, 135, 154, 151, 181, texMario);

	sprites->Add(1003, 135, 88, 151, 105, texMario);
	sprites->Add(1004, 175, 88, 191, 105, texMario);
	//sprites->Add(10013, 135, 154, 140, 181, texMario);

	sprites->Add(1005, 120, 52, 135, 67, texQuestionBlock);
	sprites->Add(1006, 137, 52, 152, 67, texQuestionBlock);
	sprites->Add(1007, 154, 52, 169, 67, texQuestionBlock);
	sprites->Add(1008, 171, 52, 186, 67, texQuestionBlock);


	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	//ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(1003);
	ani->Add(1004);
	//ani->Add(10013);
	animations->Add(501, ani);
	
	ani = new CAnimation(101);
	ani->Add(1005, 500);
	ani->Add(1006);
	ani->Add(1007);
	ani->Add(1008);
	//ani->Add(10013);
	animations->Add(502, ani);

	mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_START_VX);
	questionBlock = new CQuestionBlock(QUESTION_BLOCK_X, QUESTION_BLOCK_Y);

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
	
}

/*
	Render a frame 
*/
void Render()
{
	CGame * game = CGame::GetInstance();
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		mario->Render();
		brick->Render();
		questionBlock->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	//wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame * game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();

	Run();

	return 0;
}