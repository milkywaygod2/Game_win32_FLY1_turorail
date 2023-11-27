#include "pch.h"
#include "UI_Btn.h"



UI_Btn::UI_Btn()
	: CObj_05UI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pScnFunc(nullptr)
	, m_pScnInst(nullptr)
{

}

UI_Btn::~UI_Btn()
{
}

void UI_Btn::cursorOn()
{
}

void UI_Btn::cursorLbtnDown()
{

}

void UI_Btn::cursorLbtnUp()
{
}

void UI_Btn::cursorLbtnDownUp()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}

	if (m_pScnInst && m_pScnFunc)
	{
		((*m_pScnInst).*m_pScnFunc)(); 
	}
}

void UI_Btn::setBtnCallBack(CScn* _pScn, SCN_FUNC _pScnFunc)
{
	m_pScnInst = _pScn;
	m_pScnFunc = _pScnFunc;
}