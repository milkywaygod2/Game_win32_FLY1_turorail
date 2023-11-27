#include "pch.h"
//#include "mgr_Scn.h"

mgr_Scn::mgr_Scn()
	: m_pCurScn(nullptr)
	, m_arrScn()
{}
mgr_Scn::~mgr_Scn()
{
	//�� ���� ����
	for (UINT i = 0; i < (UINT)SCN_TYPE::scnEND; ++i)
	{
		if (nullptr != m_arrScn[i]) 
		{
			delete m_arrScn[i];
		}
	}
}

void mgr_Scn::mgrScn_changeScn(SCN_TYPE _eScnType) //@����������׷��̵�
{ 
	m_pCurScn->Exit(); 
	m_pCurScn = m_arrScn[(UINT)_eScnType];
	m_pCurScn->Enter();
		
}

void mgr_Scn::init()
{
	//�� �ʱ�ȭ (����)

	m_arrScn[(UINT)SCN_TYPE::TL] = new CScn_00TL;
	m_arrScn[(UINT)SCN_TYPE::TL]->SetName(L"CScn_00TL");
	m_arrScn[(UINT)SCN_TYPE::STT] = new CScn_01STT;
	m_arrScn[(UINT)SCN_TYPE::STT]->SetName(L"CScn_01STT");
		//m_arrScn[(UINT)SCN_TYPE::STAGE_01] = new CScn_02STAGE_01;
		//m_arrScn[(UINT)SCN_TYPE::STAGE_01]->SetName(L"CScn_02STAGE_01");
		//m_arrScn[(UINT)SCN_TYPE::STAGE_02] = new CScn_03STAGE_02;
		//m_arrScn[(UINT)SCN_TYPE::STAGE_02]->SetName(L"CScn_03STAGE_02");

	//���� �� ����
	m_pCurScn = m_arrScn[(UINT)SCN_TYPE::STT]; //CScn.h
	m_pCurScn->Enter();

}

void mgr_Scn::update()
{
	m_pCurScn->update();
	m_pCurScn->finalupdate();

}

//�غ�ȭ�鿡 �׸���
void mgr_Scn::render(HDC _dc)
{
	m_pCurScn->render(_dc);
}
