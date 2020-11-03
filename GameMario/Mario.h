#pragma once
#include "GameObject.h"
#include "Collision.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_RUNNING_SPEED		0.3f
//0.1f
#define MARIO_JUMP_SPEED_Y		0.2f
#define MARIO_JUMP_DEFLECT_SPEED 0.3f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE								0
#define MARIO_STATE_WALKING_RIGHT						100
#define MARIO_STATE_WALKING_LEFT						110
#define MARIO_STATE_JUMP								200
#define MARIO_STATE_DIE									300
#define MARIO_STATE_RUNNING_RIGHT						400
#define MARIO_STATE_RUNNING_LEFT						410
#define MARIO_STATE_JUMP_RIGHT							210
#define MARIO_STATE_JUMP_LEFT							220
#define MARIO_STATE_KICK								500
#define MARIO_STATE_TAKE_TORTOISESHELL_RIGHT			600
#define MARIO_STATE_TAKE_TORTOISESHELL_LEFT				610
#define MARIO_STATE_TURN_LEFT							700
#define MARIO_STATE_TURN_RIGHT							710




#define MARIO_ANI_SMALL_IDLE_RIGHT						0
#define MARIO_ANI_SMALL_IDLE_LEFT						1
#define MARIO_ANI_BIG_IDLE_RIGHT						2
#define MARIO_ANI_BIG_IDLE_LEFT							3
#define MARIO_ANI_TAIL_IDLE_RIGHT						8
#define MARIO_ANI_TAIL_IDLE_LEFT						9
#define MARIO_ANI_FIRE_IDLE_RIGHT						12
#define MARIO_ANI_FIRE_IDLE_LEFT						13

#define MARIO_ANI_SMALL_WALKING_RIGHT					4
#define MARIO_ANI_SMALL_WALKING_LEFT					5
#define MARIO_ANI_BIG_WALKING_RIGHT						6
#define MARIO_ANI_BIG_WALKING_LEFT						7
#define MARIO_ANI_TAIL_WALKING_RIGHT					10
#define MARIO_ANI_TAIL_WALKING_LEFT						11
#define MARIO_ANI_FIRE_WALKING_RIGHT					14
#define MARIO_ANI_FIRE_WALKING_LEFT						15

#define MARIO_ANI_SMALL_RUNNING_RIGHT					16
#define MARIO_ANI_SMALL_RUNNING_LEFT					17
#define MARIO_ANI_BIG_RUNNING_RIGHT						18
#define MARIO_ANI_BIG_RUNNING_LEFT						19
#define MARIO_ANI_TAIL_RUNNING_RIGHT					20
#define MARIO_ANI_TAIL_RUNNING_LEFT						21
#define MARIO_ANI_FIRE_RUNNING_RIGHT					22
#define MARIO_ANI_FIRE_RUNNING_LEFT						23

#define MARIO_ANI_SMALL_JUMPING_RIGHT					24
#define MARIO_ANI_SMALL_JUMPING_LEFT					25
#define MARIO_ANI_BIG_JUMPING_RIGHT						26
#define MARIO_ANI_BIG_JUMPING_LEFT						27
#define MARIO_ANI_TAIL_JUMPING_RIGHT					28
#define MARIO_ANI_TAIL_JUMPING_LEFT						29
#define MARIO_ANI_FIRE_JUMPING_RIGHT					30
#define MARIO_ANI_FIRE_JUMPING_LEFT						31

#define MARIO_ANI_SMALL_KICK_RIGHT						32
#define MARIO_ANI_SMALL_KICK_LEFT						33
#define MARIO_ANI_BIG_KICK_RIGHT						34
#define MARIO_ANI_BIG_KICK_LEFT							35
#define MARIO_ANI_TAIL_KICK_RIGHT						36
#define MARIO_ANI_TAIL_KICK_LEFT						37
#define MARIO_ANI_FIRE_KICK_RIGHT						38
#define MARIO_ANI_FIRE_KICK_LEFT						39

#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_RIGHT	40
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_LEFT	41
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_RIGHT		42
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_LEFT			43
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_JUMP_RIGHT	44
#define MARIO_ANI_SMALL_TAKE_TORTOISESHELL_JUMP_LEFT	45

#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_IDLE_RIGHT		46
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_IDLE_LEFT		47
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_RIGHT			48
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_LEFT			49
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_JUMP_RIGHT		50
#define MARIO_ANI_BIG_TAKE_TORTOISESHELL_JUMP_LEFT		51

#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_RIGHT	52
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_LEFT		53
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_RIGHT			54
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_LEFT			55
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_JUMP_RIGHT	56
#define MARIO_ANI_TAIL_TAKE_TORTOISESHELL_JUMP_LEFT		57

#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_IDLE_RIGHT	58
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_IDLE_LEFT		59
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_RIGHT			60
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_LEFT			61
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_JUMP_RIGHT	62
#define MARIO_ANI_FIRE_TAKE_TORTOISESHELL_JUMP_LEFT		63

#define MARIO_ANI_SMALL_TURN_LEFT						64
#define MARIO_ANI_SMALL_TURN_RIGHT						65
#define MARIO_ANI_BIG_TURN_LEFT							66
#define MARIO_ANI_BIG_TURN_RIGHT						67
#define MARIO_ANI_TAIL_TURN_LEFT						68
#define MARIO_ANI_TAIL_TURN_RIGHT						69
#define MARIO_ANI_FIRE_TURN_LEFT						70
#define MARIO_ANI_FIRE_TURN_RIGHT						71

#define MARIO_ANI_DIE									72

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL	3
#define MARIO_LEVEL_FIRE	 4

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_TAIL_BBOX_WIDTH 21
#define MARIO_TAIL_BBOX_HEIGHT 28

#define MARIO_FIRE_BBOX_WIDTH 14
#define MARIO_FIRE_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  12
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_SLIDE_WALKING_TIME 300



class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	int run_state;
	int jump_state;
	int kick_state;
	int turn_state;
	int take_tortoistate_state;

	CGameObject* tortoiseshell;
	DWORD jump_start;
	DWORD kick_start;
	DWORD walking_time_right;
	DWORD walking_time_left;

	float speech_Jump;

public:
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL/*, vector<LPGAMEOBJECT>* quesObjects = NULL*/);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }

	int GetLevel() { return level; }
	int GetJumpState() { return jump_state; }
	int GetStateTakeTortoiseshell(){ return take_tortoistate_state; }
	int GetKickState() { return kick_state; }
	float GetSpeechJump() { return speech_Jump; }
	DWORD GetWalkRightTime() { return walking_time_right; }
	DWORD GetWalkLeftTime() { return walking_time_left; }
	DWORD GetJumpStart() { return jump_start; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void SettJumpStart(){ jump_start = GetTickCount(); }
	void SetJumpState() { jump_state = 1; }
	void SetWalkRightTime(DWORD t) { walking_time_right = t; }
	void SetWalkLeftTime(DWORD t) { walking_time_left = t; }
	void SetSpeechJump() { speech_Jump += 0.0025; }


	int GetCurrentWidthMario();

	void Reset();

	virtual void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);
	virtual LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};