#include "pch.h"
//#include "mgr_Key.h"

//win32APIȭ
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

//�����Ҹ���
mgr_Key::mgr_Key(){}
mgr_Key::~mgr_Key(){}

//�ʱ�ȭ : ����<Ű����> 
void mgr_Key::init()
{
	for (int i = 0; i < (int)KEY::keyEND; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });

	}
}

//������Ʈ : ��Ŀ��+������Ʈ ���Ǻ� ���� ���� 
void mgr_Key::update()
{
	//������ ��Ŀ�� �˾Ƴ���
	//HWND hMainWnd = CCore::GetInst()->getMainHwnd(); //�������α׷����� �����츦 �� ���� ���
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		//��Ŀ���� �� ��
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
		//Ŀ�� ��ġ���
		POINT csPos = {};
		GetCursorPos(&csPos); //��������� ��ǥ��ȯ
		ScreenToClient(CCore::GetInst()->getMainHwnd(), &csPos); //�������α׷����� ���̰��
		m_vCursorPos = Vec2((float)csPos.x, (float)csPos.y);
	}
	//��Ŀ�� ��������
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