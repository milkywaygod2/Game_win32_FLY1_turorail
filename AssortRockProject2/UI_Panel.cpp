#include "UI_Panel.h"
#include "pch.h"


UI_Panel::UI_Panel()
	:CObj_05UI(false)
{
}

UI_Panel::~UI_Panel()
{
}

void UI_Panel::update()
{
}

void UI_Panel::render(HDC _dc)
{
	CObj_05UI::render(_dc);
}

void UI_Panel::cursorOn()
{
	if (isLbtnOn())
	{
		Vec2 vDiff = CURSOR_POS - m_vDragStart;
		Vec2 vPanelPos = Obj_getPos();
		vPanelPos += vDiff;
		Obj_setPos(vPanelPos);
		m_vDragStart = CURSOR_POS;
	}
}

void UI_Panel::cursorLbtnDown()
{
	m_vDragStart = CURSOR_POS;
}

void UI_Panel::cursorLbtnUp()
{
}