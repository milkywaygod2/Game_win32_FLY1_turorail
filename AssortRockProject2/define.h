#pragma once
//공통용 잡탕 헤더


//싱글톤 메크로
#define SINGLETON(type)	\
public:	\
		static type* GetInst()\
		{\
			static type mgr;\
			return &mgr;\
		}\
private: \
	type();\
	~type();

#define fDT mgr_Timer::GetInst()->GetfDT()
#define DT mgr_Timer::GetInst()->GetDT()

//Math
#define PI 3.1415926535f

//Tile
#define TILE_SIZE 128

//함수
#define CLONE(type) type* clone() { return new type(*this); }


//Key
#define KEY_CHECK(key, key_state)	mgr_Key::GetInst()->getKeyState(key) == key_state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define CURSOR_POS mgr_Key::GetInst()->getCursorPos()


//클래스도 모든 헤더에 넣고싶으면 이쪽에 ㅋㅋ
enum class OBJ_TYPE
{
	DFT, 	//Default
	TL,		//Tile
	GRD,	//Ground
	MTR,	//Monster
	PLR,	//Player
	MSL_MTR,
	MSL_PLR,	//Missle



	UI = 31,
	objEND = 32,
};

enum class SCN_TYPE
{
	TL,		  //Tool
	STT,	  //Start
	STG_01,	  //Stage01
	STG_02,	  //Stage02
			  
	scnEND,
};

enum class EVT_TYPE
{
	CREATE_OBJ,
	DELETE_OBJ,
	CHANGE_SCN,
	CHANGE_AI_STATE,



	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class MTR_STATE
{
	IDLE,
	PARTROL,
	TRACE,
	ATTACK,
	RUN,
	DEAD,

};