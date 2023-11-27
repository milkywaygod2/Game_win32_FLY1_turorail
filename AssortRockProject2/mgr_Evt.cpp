#include "pch.h"
#include "mgr_Evt.h"

mgr_Evt::mgr_Evt(){}
mgr_Evt::~mgr_Evt(){}

void mgr_Evt::update()
{
	//삭제 큐 삭제
	for (size_t i = 0; i < m_vecDlt.size(); ++i)
	{
		delete m_vecDlt[i];
	}
	m_vecDlt.clear();

	//실행 큐 실행
	for (size_t i = 0; i < m_vecEvt.size(); ++i)
	{
		excute(m_vecEvt[i]);
	}
	m_vecEvt.clear();
}

void mgr_Evt::excute(const tEvt& _tEvt)
{
	switch (_tEvt.eEvt)
	{
	case EVT_TYPE::CREATE_OBJ:
	{
		// lParam : CObj*
		// wParam : OBJ_TYPE
		CObj* pNewObj = (CObj*)_tEvt.lParam;
		OBJ_TYPE eType = (OBJ_TYPE)_tEvt.wParam;

		mgr_Scn::GetInst()->getCurScn()->Scn_addObj(pNewObj, eType);
	}break;

	case EVT_TYPE::DELETE_OBJ:
	{
		// lParam : CObj*
		// Obj를 Dlt로 변경, 배열에 추가
		CObj* pDltObj = (CObj*)_tEvt.lParam;
		pDltObj->Obj_setDlt();
		m_vecDlt.push_back(pDltObj);
	}break;

	case EVT_TYPE::CHANGE_SCN:

		// lParam : Next Scene Type
		mgr_Scn::GetInst()->mgrScn_changeScn((SCN_TYPE)_tEvt.lParam);
		mgr_UI::GetInst()->setFocusedUI(nullptr);
		break;

	case EVT_TYPE::CHANGE_AI_STATE:
	{
		// lParam : AI
		// wParam : Next Type
		CMdl_02AI* pAI = (CMdl_02AI*)_tEvt.lParam;
		MTR_STATE eNextState = (MTR_STATE)_tEvt.wParam;
		pAI->changeState(eNextState);
	}break;

	}
}
