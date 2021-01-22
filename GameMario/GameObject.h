#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	float origin_x, origin_y;

	int origin_state;

	bool isOriginObj = false;

	int state;

	int alive = true;

	int Actived = false;

	DWORD dt;

	LPANIMATION_SET animation_set;

public:
	void SetisOriginObj(bool value)
	{
		isOriginObj = value;
	}
	bool GetisOriginObj()
	{
		return isOriginObj;
	}
	void reset()
	{
		SetState(origin_state);
		x = origin_x;
		y = origin_y;
	}

	void GetOriginLocation(float& x, float& y)
	{
		x = origin_x;
		y = origin_y;
	}

	float GetOriginLocationY() { return origin_y; }
	void SetActive(bool value)
	{
		Actived = value;
	}

	bool GetActive()
	{
		return	Actived;
	}

	bool GetAlive() { return alive; }
	void SetAlive(int s) { alive = s; }

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void SetOrigin(float x, float y, int state) { this->origin_x = x, this->origin_y = y; this->origin_state = state; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }


	CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }


	~CGameObject();
};

