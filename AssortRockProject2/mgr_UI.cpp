#include "mgr_UI.h"
#include "pch.h"
mgr_UI::mgr_UI():m_pFocusedUI(nullptr) {}
mgr_UI::~mgr_UI() {}

void mgr_UI::update()
{
	//1 FocusedUI ����?
	m_pFocusedUI = getFocusedUI();
	if (!m_pFocusedUI) //����ȭ�ڵ�
		return;

	//2 FocusedUI ������, ���� Ÿ���� �ڽ� ã��
	CObj_05UI* pTargetUI = getTargetUI(m_pFocusedUI);


	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	if (nullptr != pTargetUI) //UI������?
	{
		pTargetUI->cursorOn();
		if (bLbtnTap) //UI����
		{
			pTargetUI->cursorLbtnDown();
			pTargetUI->m_bPrevLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->cursorLbtnUp(); //UI��

			if (pTargetUI->m_bPrevLbtnDown) //UI����+UI��
			{
				pTargetUI->cursorLbtnDownUp();
			}

			pTargetUI->m_bPrevLbtnDown = false; //�۴���+UI��
		}
	}
}

void mgr_UI::setFocusedUI(CObj_05UI* _pUI)
{
	//�̹� ��Ŀ�� or ��Ŀ�� ������Ȳ
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	m_pFocusedUI = _pUI;
	CScn* pCurScn = mgr_Scn::GetInst()->getCurScn();
	vector<CObj*>& vecUI = pCurScn->Scn_getObjGroup_UI();

	//��Ŀ���� UI ã��
	vector<CObj*>::iterator Iter = vecUI.begin();
	for (; Iter != vecUI.end(); ++Iter)
	{
		if (m_pFocusedUI == *Iter){break;}
	}

	//�ش� UI���� �ǵڷ�
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
	//���ʹ�ư��������, ���� �ڽ� ����
	vector<CObj*>::iterator targetIter = vecUI.end();
	vector<CObj*>::iterator Iter = vecUI.begin();
	for (; Iter != vecUI.end(); ++Iter)
	{
		if (((CObj_05UI*)*Iter)->isCursorOn()) {
			targetIter = Iter;
		}
	}
	//��Ŀ���� UI�� ���� ���(���Ŭ��)
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}
	pFocusedUI = (CObj_05UI*)*targetIter;

	//�ش� Ÿ�� ������, �迭 �������� �߰�
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);
	return pFocusedUI;
}

CObj_05UI* mgr_UI::getTargetUI(CObj_05UI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CObj_05UI* pTargetUI = nullptr;

	static list<CObj_05UI*> listQueue; //���Լ���
	static vector<CObj_05UI*> vecNoneTargetUI; //Ÿ��UI�ƴ� �ֵ� ���

	listQueue.clear();
	vecNoneTargetUI.clear();//���ʹ� Ŭ�����ص� �����Ҵ� ������ ������� ����

	listQueue.push_back(_pParentUI);

	while (!listQueue.empty())
	{
		CObj_05UI* pUI = listQueue.front();

		listQueue.pop_front(); //������ ������ ����

		//���������켱
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

	if (bLbtnAway) //UI����+�۶� ����
	{
		for (size_t i = 0; i < vecNoneTargetUI.size(); ++i)
		{vecNoneTargetUI[i]->m_bPrevLbtnDown = false;}
	}

	return pTargetUI;
}
