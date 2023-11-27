#pragma once
class CObj_05UI;


class mgr_UI
{
	SINGLETON(mgr_UI);

private:
	CObj_05UI* m_pFocusedUI;

public:
	void update();

	void setFocusedUI(CObj_05UI* _pUI);

private:
	CObj_05UI* getFocusedUI();
	CObj_05UI* getTargetUI(CObj_05UI* _pParentUI);

};

