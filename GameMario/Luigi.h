#pragma once
#include "GameObject.h"
#include "Collision.h"


#define LUIGI_WALKING_SPEED								0.1f 
#define LUIGI_RUNNING_SPEED								0.15f
#define LUIGI_RUNNING_FAST_SPEED						0.2f

#define LUIGI_JUMP_SPEED_Y								0.15f
#define LUIGI_FLYING_SPEED_Y							0.03f
#define LUIGI_JUMP_DEFLECT_SPEED						0.2f
#define LUIGI_GRAVITY									0.001f
#define LUIGI_DIE_DEFLECT_SPEED							0.5f

#define LUIGI_STATE_IDLE								0
#define LUIGI_STATE_WALKING_RIGHT						100
#define LUIGI_STATE_WALKING_LEFT						110
#define LUIGI_STATE_JUMP								200
#define LUIGI_STATE_DIE									300
#define LUIGI_STATE_RUNNING_RIGHT						400
#define LUIGI_STATE_RUNNING_LEFT						410
#define LUIGI_STATE_JUMP_RIGHT							210
#define LUIGI_STATE_JUMP_LEFT							220
#define LUIGI_STATE_KICK								500
#define LUIGI_STATE_TAKE_TORTOISESHELL_RIGHT			600
#define LUIGI_STATE_TAKE_TORTOISESHELL_LEFT				610
#define LUIGI_STATE_TURN_LEFT							700
#define LUIGI_STATE_TURN_RIGHT							710
#define LUIGI_STATE_FIGHT								800
#define LUIGI_STATE_RUNNING_RIGHT_FAST					420
#define LUIGI_STATE_RUNNING_LEFT_FAST					430
#define LUIGI_STATE_FLYING_LOW_RIGHT					900
#define LUIGI_STATE_FLYING_LOW_LEFT						910
#define LUIGI_STATE_FLYING_HIGH_RIGHT					920
#define LUIGI_STATE_FLYING_HIGH_LEFT					930
#define LUIGI_STATE_SIT									940
#define LUIGI_STATE_SHOOT_FIRE_BULLET_RIGHT				950
#define LUIGI_STATE_SHOOT_FIRE_BULLET_LEFT				960



#define LUIGI_ANI_SMALL_IDLE_RIGHT						0
#define LUIGI_ANI_SMALL_IDLE_LEFT						1
#define LUIGI_ANI_BIG_IDLE_RIGHT						2
#define LUIGI_ANI_BIG_IDLE_LEFT							3
#define LUIGI_ANI_TAIL_IDLE_RIGHT						8
#define LUIGI_ANI_TAIL_IDLE_LEFT						9

#define LUIGI_ANI_SMALL_WALKING_RIGHT					4
#define LUIGI_ANI_SMALL_WALKING_LEFT					5
#define LUIGI_ANI_BIG_WALKING_RIGHT						6
#define LUIGI_ANI_BIG_WALKING_LEFT						7
#define LUIGI_ANI_TAIL_WALKING_RIGHT					10
#define LUIGI_ANI_TAIL_WALKING_LEFT						11

#define LUIGI_ANI_SMALL_RUNNING_RIGHT					12
#define LUIGI_ANI_SMALL_RUNNING_LEFT					13
#define LUIGI_ANI_BIG_RUNNING_RIGHT						14
#define LUIGI_ANI_BIG_RUNNING_LEFT						15
#define LUIGI_ANI_TAIL_RUNNING_RIGHT					16
#define LUIGI_ANI_TAIL_RUNNING_LEFT						17

#define LUIGI_ANI_SMALL_JUMPING_RIGHT					18
#define LUIGI_ANI_SMALL_JUMPING_LEFT					19
#define LUIGI_ANI_BIG_JUMPING_RIGHT						20
#define LUIGI_ANI_BIG_JUMPING_LEFT						21
#define LUIGI_ANI_TAIL_JUMPING_RIGHT					22
#define LUIGI_ANI_TAIL_JUMPING_LEFT						23

#define LUIGI_ANI_SMALL_KICK_RIGHT						24
#define LUIGI_ANI_SMALL_KICK_LEFT						25
#define LUIGI_ANI_BIG_KICK_RIGHT						26
#define LUIGI_ANI_BIG_KICK_LEFT							27
#define LUIGI_ANI_TAIL_KICK_RIGHT						28
#define LUIGI_ANI_TAIL_KICK_LEFT						29

#define LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_RIGHT	30
#define LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_IDLE_LEFT	31
#define LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_RIGHT		32
#define LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_LEFT			33
#define LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_JUMP_RIGHT	34
#define LUIGI_ANI_SMALL_TAKE_TORTOISESHELL_JUMP_LEFT	35

#define LUIGI_ANI_BIG_TAKE_TORTOISESHELL_IDLE_RIGHT		36
#define LUIGI_ANI_BIG_TAKE_TORTOISESHELL_IDLE_LEFT		37
#define LUIGI_ANI_BIG_TAKE_TORTOISESHELL_RIGHT			38
#define LUIGI_ANI_BIG_TAKE_TORTOISESHELL_LEFT			39
#define LUIGI_ANI_BIG_TAKE_TORTOISESHELL_JUMP_RIGHT		40
#define LUIGI_ANI_BIG_TAKE_TORTOISESHELL_JUMP_LEFT		41

#define LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_RIGHT	42
#define LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_IDLE_LEFT		43
#define LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_RIGHT			44
#define LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_LEFT			45
#define LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_JUMP_RIGHT	46
#define LUIGI_ANI_TAIL_TAKE_TORTOISESHELL_JUMP_LEFT		47

#define LUIGI_ANI_SMALL_TURN_LEFT						48
#define LUIGI_ANI_SMALL_TURN_RIGHT						49
#define LUIGI_ANI_BIG_TURN_LEFT							50
#define LUIGI_ANI_BIG_TURN_RIGHT						51
#define LUIGI_ANI_TAIL_TURN_LEFT						52
#define LUIGI_ANI_TAIL_TURN_RIGHT						53

#define LUIGI_ANI_TAIL_FIGHT							54

#define LUIGI_ANI_SMALL_RUNNING_RIGHT_FAST				55
#define LUIGI_ANI_SMALL_RUNNING_LEFT_FAST				56
#define LUIGI_ANI_BIG_RUNNING_RIGHT_FAST				57
#define LUIGI_ANI_BIG_RUNNING_LEFT_FAST					58
#define LUIGI_ANI_TAIL_RUNNING_RIGHT_FAST				59
#define LUIGI_ANI_TAIL_RUNNING_LEFT_FAST				60

#define LUIGI_ANI_FLY_LOW_RIGHT							61
#define LUIGI_ANI_FLY_LOW_LEFT							62

#define LUIGI_ANI_FLY_HIGH_RIGHT						63
#define LUIGI_ANI_FLY_HIGH_LEFT							64

#define LUIGI_ANI_BIG_SIT_RIGHT							65
#define LUIGI_ANI_BIG_SIT_LEFT							66
#define LUIGI_ANI_TAIL_SIT_RIGHT						67
#define LUIGI_ANI_TAIL_SIT_LEFT							68


#define LUIGI_ANI_DIE									69

#define	LUIGI_LEVEL_SMALL	1
#define	LUIGI_LEVEL_BIG		2
#define LUIGI_LEVEL_TAIL	3

#define LUIGI_BIG_BBOX_WIDTH  14
#define LUIGI_BIG_BBOX_HEIGHT 27
#define LUIGI_BIG_SIT_BBOX_WIDTH	14
#define LUIGI_BIG_SIT_BBOX_HEIGHT	18

#define LUIGI_TAIL_BBOX_WIDTH 21
#define LUIGI_TAIL_BBOX_HEIGHT 28
#define LUIGI_TAIL_SIT_BBOX_WIDTH	22
#define LUIGI_TAIL_SIT_BBOX_HEIGHT	18

#define LUIGI_SMALL_BBOX_WIDTH  12
#define LUIGI_SMALL_BBOX_HEIGHT 15

#define LUIGI_UNTOUCHABLE_TIME 5000
#define LUIGI_SLIDE_WALKING_TIME 300



class CLuigi : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	bool is_high;
	int run_state;
	int run_fast_state;
	int jump_state;
	int kick_state;
	int turn_state;
	int fight_state;
	int fall_state;
	int fly_low_state;
	int fly_high_state;
	int sit_state;
	int slide_state;
	int shoot_fire_bullet_state;


	float walking_right_speech;
	float walking_left_speech;

	int take_tortoistate_state;

	CGameObject* tortoiseshell;
	CGameObject* fire_bullet[2];
	DWORD jump_start;
	DWORD kick_start;
	DWORD shoot_fire_bullet_start;
	DWORD fight_start;
	DWORD fly_low_start;
	DWORD fly_high_start;
	DWORD running_time_right;
	DWORD running_time_left;
	DWORD walking_time_right;
	DWORD walking_time_left;

	DWORD sliding_time_right;
	DWORD sliding_time_left;


	float speech_Jump;

public:
	float pcy;
	CLuigi(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }

	int GetLevel() { return level; }
	int GetJumpState() { return jump_state; }
	int GetStateTakeTortoiseshell() { return take_tortoistate_state; }
	int GetKickState() { return kick_state; }
	int GetFightState() { return fight_state; }
	int GetRunState() { return run_state; }
	int GetFlyLowState() { return fly_low_state; }
	int GetFlyHighState() { return fly_high_state; }
	int GetSitState() { return sit_state; }
	int GetShootFireBulletState() { return shoot_fire_bullet_state; }
	int GetSlideState() { return slide_state; }
	float GetWalkingRightSpeech() { return walking_right_speech; }
	float GetWalkingLeftSpeech() { return walking_left_speech; }
	int GetFallState() { return fall_state; }
	bool GetIsHigh() { return is_high; }
	float GetSpeechJump() { return speech_Jump; }
	DWORD GetWalkRightTime() { return walking_time_right; }
	DWORD GetWalkLeftTime() { return walking_time_left; }
	DWORD GetRunningRightTime() { return running_time_right; }
	DWORD GetRunningLeftTime() { return running_time_left; }
	DWORD GetJumpStart() { return jump_start; }
	DWORD GetKickStart() { return kick_start; }
	DWORD GetFightStart() { return fight_start; }
	DWORD GetFlyLowStart() { return fly_low_start; }
	DWORD GetFlyHighStart() { return fly_high_start; }
	DWORD GetShootFireBulletStart() { return shoot_fire_bullet_start; }

	void StartUntouchable() { untouchable = 1; untouchable_start = (DWORD)GetTickCount64(); }

	void SetJumpStart(DWORD t) { jump_start = t; }
	void SetKickStart(int t) { kick_start = t; }
	void SetJumpState(int j) { jump_state = j; }
	void SetFightState(int f) { fight_state = f; }
	void SetSitState(int s) { sit_state = s; }
	void SetShootFireBulletState(int s) { shoot_fire_bullet_state = s; }
	void SetWalkRightTime(DWORD t) { walking_time_right = t; }
	void SetWalkLeftTime(DWORD t) { walking_time_left = t; }
	void SetRunningRightTime(DWORD t) { running_time_right = t; }
	void SetRunningLeftTime(DWORD t) { running_time_left = t; }
	void SetWalkingRightSpeech() { walking_right_speech += 0.005f; }
	void ResetWalkingRightSpeech() { walking_right_speech = 0; }
	void ResetWalkingLeftSpeech() { walking_left_speech = 0; }
	void SetWalkingLeftSpeech() { walking_left_speech += 0.005f; }
	void SetSlidingTimeRight() { sliding_time_right += 20; }
	void SetSlidingTimeLeft() { sliding_time_left += 20; }
	DWORD GetSlidingTimeRight() { return sliding_time_right; }
	DWORD GetSlidingTimeLeft() { return sliding_time_left; }
	void ResetSlidingTimeRight() { sliding_time_right = 0; }
	void ResetSlidingTimeLeft() { sliding_time_left = 0; }

	void SetShootFireBulletStart(DWORD t) { shoot_fire_bullet_start = t; }
	void SetSpeechJump() { speech_Jump += 0.0025f; }
	void SetFightStart(DWORD t) { fight_start = t; }
	void SetFlyLowStart(DWORD t) { fly_low_start = t; }
	void SetFlyHighStart(DWORD t) { fly_high_start = t; }

	int GetCurrentWidthLuigi();

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