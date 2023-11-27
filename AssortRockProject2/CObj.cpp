#include "pch.h"
#include "CObj.h"


CObj::CObj()
	:	m_vPos{}
	,	m_vScale{}
	,	m_pCldr(nullptr)
	,	m_pAmtr(nullptr)
	,	m_pGrbt(nullptr)
	,	m_pRgdB(nullptr)
	,	m_bAlive(true)
{}
CObj::CObj(const CObj& _origin) //���� ���� �ݸ��� ����
	: m_objName(_origin.m_objName)
	, m_vPos{ _origin .m_vPos}
	, m_vScale{ _origin .m_vScale}
	, m_pCldr(nullptr)
	, m_pAmtr(nullptr)
	, m_pGrbt(nullptr)
	, m_pRgdB(nullptr)
	, m_bAlive(true)
{
	if (_origin.m_pCldr)
	{
		m_pCldr = new CCmp_01Cldr(*_origin.m_pCldr); //* ���������
		m_pCldr->m_pOwner = this;
	}
	if (_origin.m_pAmtr)
	{
		m_pAmtr = new CCmp_02Amtr(*_origin.m_pAmtr);
		m_pAmtr->m_pOwner = this;
	}	
	if (_origin.m_pGrbt)
	{
		m_pGrbt = new CCmp_04Grbt(*_origin.m_pGrbt);
		m_pGrbt->m_pOwner = this;
	}
	if (_origin.m_pRgdB)
	{
		m_pRgdB = new CCmp_03RgdB(*_origin.m_pRgdB);
		m_pRgdB->m_pOwner = this;
	}
}
CObj::~CObj()
{
	if (nullptr != m_pCldr)
		delete m_pCldr;
	if (nullptr != m_pAmtr)
		delete m_pAmtr;
	if (nullptr != m_pRgdB)
		delete m_pRgdB;
	if (nullptr != m_pGrbt)
		delete m_pGrbt;
}


void CObj::Obj_createCldr()
{
	m_pCldr = new CCmp_01Cldr;
	m_pCldr->m_pOwner = this;
}

void CObj::Obj_createAmtr()
{
	m_pAmtr = new CCmp_02Amtr;
	m_pAmtr->m_pOwner = this;
}

void CObj::Obj_createRgdB()
{
	m_pRgdB = new CCmp_03RgdB;
	m_pRgdB->m_pOwner = this;
}

void CObj::Obj_createGrbt()
{
	m_pGrbt = new CCmp_04Grbt;
	m_pGrbt->m_pOwner = this;
}

void CObj::Obj_renderCmp(HDC _dc)
{
	if (nullptr != m_pCldr)
	{
		m_pCldr->render(_dc);
	}
	if (nullptr != m_pAmtr)
	{
		m_pAmtr->render(_dc);
	}
}

void CObj::finalupdate()
{
	if (m_pAmtr)
		m_pAmtr->finalupdate();
	if (m_pGrbt)
		m_pGrbt->finalupdate();
	if (m_pRgdB)
		m_pRgdB->finalupdate();
	if (m_pCldr)
		m_pCldr->finalupdate(); //�����߿�

}

void CObj::render(HDC _dc) //���� ������Ʈ���� �������̵��ؼ� �����..
{
	Vec2 vRenderPos = mgr_Cam::GetInst()->getRenderPos(m_vPos);
		Rectangle(_dc
			, (int)(vRenderPos.x - m_vScale.x / 2.f)
			, (int)(vRenderPos.y - m_vScale.y / 2.f)
			, (int)(vRenderPos.x + m_vScale.x / 2.f)
			, (int)(vRenderPos.y + m_vScale.y / 2.f));
	Obj_renderCmp(_dc);
}