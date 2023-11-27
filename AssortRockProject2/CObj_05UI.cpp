#include "pch.h"
#include "CObj_05UI.h"
CObj_05UI::CObj_05UI(bool _bCamRender)
	: m_pParentUI(nullptr)
	, m_bCamRender(_bCamRender) //기본은 false가 맞음
	, m_bCursorOn(false)
{
}

CObj_05UI::CObj_05UI(const CObj_05UI& _origin)
	: CObj(_origin)
	, m_pParentUI(nullptr)
	, m_bCamRender(_origin.m_bCamRender)
	, m_bCursorOn(false)
	, m_bPrevLbtnDown(false)
{//자식복사해오기
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		addChild(_origin.m_vecChildUI[i]->clone());
	}
}

CObj_05UI::~CObj_05UI()
{
	Freq_clearVec(m_vecChildUI);
}

void CObj_05UI::update()
{
	updateChild();
}
void CObj_05UI::updateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CObj_05UI::finalupdate()
{
	CObj::finalupdate();

	m_vAccPos = Obj_getPos();
	if (getParent()){
		Vec2 vParentPos = getParent()->getAccPos();
		m_vAccPos += vParentPos;
	}
	checkCursorOn();

	finalupdateChild();
}
void CObj_05UI::finalupdateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CObj_05UI::render(HDC _dc)
{
	Vec2 vPos = getAccPos();
	Vec2 vScale = Obj_getScale();
	if (m_bCamRender)
	{
		vPos = mgr_Cam::GetInst()->getRenderPos(vPos); //ex몬스터HP바 
	}

	if (m_bPrevLbtnDown)
	{
		CMdl_01SltGDI select(_dc, PEN_TYPE::GREEN); //초록팬
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}

	renderChild(_dc);
}
void CObj_05UI::renderChild(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CObj_05UI::checkCursorOn()
{
	Vec2 vCursorPos = CURSOR_POS;
	Vec2 vScale = Obj_getScale();

	if (m_bCamRender)
	{
		vCursorPos = mgr_Cam::GetInst()->getRealPos(vCursorPos);
	}

	if (m_vAccPos.x <= vCursorPos.x && vCursorPos.x <= m_vAccPos.x + vScale.x
		&& m_vAccPos.y <= vCursorPos.y && vCursorPos.y <= m_vAccPos.y + vScale.y)
	{
		m_bCursorOn = true;
	}
	else
	{
		m_bCursorOn = false;
	}
}
void CObj_05UI::cursorOn()
{
}

void CObj_05UI::cursorLbtnDown()
{
}

void CObj_05UI::cursorLbtnUp()
{
}

void CObj_05UI::cursorLbtnDownUp()
{
}
