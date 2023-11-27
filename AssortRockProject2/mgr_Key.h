#pragma once
//#include "define.h"

//1.프레임동기화 : 동일 프레임안에서 같은 키에 대해 동일한 이벤트처리
//2.키입력 이벤트 : 누르고 있는 상태처리 tap hold away
//3.core.cpp내 키기능분리


//지원할 키 상태
enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY,
};

//지원할 키 종류
enum class KEY 
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,

	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,
	TAB,

	keyEND,
};

//키 상태 구분용 구조체
struct tKeyInfo
{
	KEY_STATE	eState;	//현재 키 상태값
	bool		bPrevTab;	//이전 키 눌림?
};

//키 매니저 싱글톤, 백터<키상태>+함수선언3종
class mgr_Key
{
	SINGLETON(mgr_Key);

private:
	vector<tKeyInfo>	m_vecKey; 
	Vec2				m_vCursorPos;

public:
	void init();						//함수1 : 초기화
	void update();						//함수2 : 업데이트

public:
	KEY_STATE getKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; } //함수3 : CCore 호환용 조이스틱
	Vec2 getCursorPos() { return m_vCursorPos; }
};

