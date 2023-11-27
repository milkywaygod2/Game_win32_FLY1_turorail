#include "pch.h"
//#include "mgr_Key.h"

//win32API화
int g_arrVK[(int)KEY::keyEND] = {
	VK_UP,		//UP
	VK_DOWN,	//DOWN
	VK_RIGHT,	//RIGHT
	VK_LEFT,	//LEFT
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',

	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	VK_MENU,//ALT,
	VK_CONTROL,//CTRL,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,

	VK_LBUTTON,
	VK_RBUTTON,
	VK_TAB,

	//keyEND,

}; 

//생성소멸자
mgr_Key::mgr_Key(){}
mgr_Key::~mgr_Key(){}

//초기화 : 백터<키상태> 
void mgr_Key::init()
{
	for (int i = 0; i < (int)KEY::keyEND; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });

	}
}

//업데이트 : 포커싱+업데이트 조건부 백터 갱신 
void mgr_Key::update()
{
	//윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->getMainHwnd(); //게임프로그램에서 윈도우를 더 쓰는 경우
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		//포커싱중 일 때
		for (int i = 0; i < (int)KEY::keyEND; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevTab)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevTab = true;
			}
			else
			{
				if (m_vecKey[i].bPrevTab)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevTab = false;
			}
		}
		//커서 위치계산
		POINT csPos = {};
		GetCursorPos(&csPos); //윈도우기준 좌표소환
		ScreenToClient(CCore::GetInst()->getMainHwnd(), &csPos); //응용프로그램기준 차이계산
		m_vCursorPos = Vec2((float)csPos.x, (float)csPos.y);
	}
	//포커싱 해제상태
	else
	{
		for (int i = 0; i < (int)KEY::keyEND; ++i)
		{
			m_vecKey[i].bPrevTab = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
	
}