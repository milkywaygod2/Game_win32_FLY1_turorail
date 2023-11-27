#include "mgr_UI.h"
#include "pch.h"
mgr_UI::mgr_UI():m_pFocusedUI(nullptr) {}
mgr_UI::~mgr_UI() {}

void mgr_UI::update()
{
	//1 FocusedUI 누구?
	m_pFocusedUI = getFocusedUI();
	if (!m_pFocusedUI) //최적화코드
		return;

	//2 FocusedUI 내에서, 실제 타게팅 자식 찾기
	CObj_05UI* pTargetUI = getTargetUI(m_pFocusedUI);


	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	if (nullptr != pTargetUI) //UI범위안?
	{
		pTargetUI->cursorOn();
		if (bLbtnTap) //UI누름
		{
			pTargetUI->cursorLbtnDown();
			pTargetUI->m_bPrevLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->cursorLbtnUp(); //UI땜

			if (pTargetUI->m_bPrevLbtnDown) //UI누름+UI떔
			{
				pTargetUI->cursorLbtnDownUp();
			}

			pTargetUI->m_bPrevLbtnDown = false; //밖누름+UI떔
		}
	}
}

void mgr_UI::setFocusedUI(CObj_05UI* _pUI)
{
	//이미 포커싱 or 포커싱 해제상황
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	m_pFocusedUI = _pUI;
	CScn* pCurScn = mgr_Scn::GetInst()->getCurScn();
	vector<CObj*>& vecUI = pCurScn->Scn_getObjGroup_UI();

	//포커스할 UI 찾기
	vector<CObj*>::iterator Iter = vecUI.begin();
	for (; Iter != vecUI.end(); ++Iter)
	{
		if (m_pFocusedUI == *Iter){break;}
	}

	//해당 UI순번 맨뒤로
	if (vecUI.end() != Iter)
	{
		vecUI.erase(Iter);
		vecUI.push_back(m_pFocusedUI);
	}
}

CObj_05UI* mgr_UI::getFocusedUI()
{
	CScn* pCurScn = mgr_Scn::GetInst()->getCurScn();
	vector<CObj*>& vecUI = pCurScn->Scn_getObjGroup_UI();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	CObj_05UI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}
	//왼쪽버튼눌렸을때, 최종 자식 선별
	vector<CObj*>::iterator targetIter = vecUI.end();
	vector<CObj*>::iterator Iter = vecUI.begin();
	for (; Iter != vecUI.end(); ++Iter)
	{
		if (((CObj_05UI*)*Iter)->isCursorOn()) {
			targetIter = Iter;
		}
	}
	//포커스된 UI가 없는 경우(허공클릭)
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}
	pFocusedUI = (CObj_05UI*)*targetIter;

	//해당 타겟 삭제후, 배열 마지막에 추가
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);
	return pFocusedUI;
}

CObj_05UI* mgr_UI::getTargetUI(CObj_05UI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CObj_05UI* pTargetUI = nullptr;

	static list<CObj_05UI*> listQueue; //선입선출
	static vector<CObj_05UI*> vecNoneTargetUI; //타겟UI아닌 애들 모아

	listQueue.clear();
	vecNoneTargetUI.clear();//벡터는 클리어해도 동적할당 공간이 사라지진 않음

	listQueue.push_back(_pParentUI);

	while (!listQueue.empty())
	{
		CObj_05UI* pUI = listQueue.front();

		listQueue.pop_front(); //꺼내온 데이터 삭제

		//낮은계층우선
		if (pUI->isCursorOn())
		{
			if (nullptr != pTargetUI){vecNoneTargetUI.push_back(pTargetUI);}

			pTargetUI = pUI;
		}
		else{vecNoneTargetUI.push_back(pUI);}

		const vector<CObj_05UI*>& vecChild = pUI->getChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{listQueue.push_back(vecChild[i]);}
	}

	if (bLbtnAway) //UI누름+밖땜 포함
	{
		for (size_t i = 0; i < vecNoneTargetUI.size(); ++i)
		{vecNoneTargetUI[i]->m_bPrevLbtnDown = false;}
	}

	return pTargetUI;
}
