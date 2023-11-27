#pragma once
//#include "define.h"

//1.�����ӵ���ȭ : ���� �����Ӿȿ��� ���� Ű�� ���� ������ �̺�Ʈó��
//2.Ű�Է� �̺�Ʈ : ������ �ִ� ����ó�� tap hold away
//3.core.cpp�� Ű��ɺи�


//������ Ű ����
enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY,
};

//������ Ű ����
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

//Ű ���� ���п� ����ü
struct tKeyInfo
{
	KEY_STATE	eState;	//���� Ű ���°�
	bool		bPrevTab;	//���� Ű ����?
};

//Ű �Ŵ��� �̱���, ����<Ű����>+�Լ�����3��
class mgr_Key
{
	SINGLETON(mgr_Key);

private:
	vector<tKeyInfo>	m_vecKey; 
	Vec2				m_vCursorPos;

public:
	void init();						//�Լ�1 : �ʱ�ȭ
	void update();						//�Լ�2 : ������Ʈ

public:
	KEY_STATE getKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; } //�Լ�3 : CCore ȣȯ�� ���̽�ƽ
	Vec2 getCursorPos() { return m_vCursorPos; }
};

