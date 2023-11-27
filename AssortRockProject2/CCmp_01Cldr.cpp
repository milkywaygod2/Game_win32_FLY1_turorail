#include "pch.h"
#include "CCmp_01Cldr.h"
UINT CCmp_01Cldr::g_iNextID = 0;
CCmp_01Cldr::CCmp_01Cldr()
	:	m_pOwner(nullptr)
	,	m_iID(g_iNextID++)
	, 	m_iOnCdlr(0)
	,	m_bActive(true)
	//,	m_vOffsetPos(0)
	//,	m_vCldrPos(0)
	//,	m_vScale(0)
{}
CCmp_01Cldr::CCmp_01Cldr(const CCmp_01Cldr& _origin) //��������ڷ� Cldr�� ����Ǵ��� ����ID ������
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_vOffsetPos(_origin.m_vOffsetPos) // &��� *�� ���� m_vOffsetPos(_origin->m_vOffsetPos) �̷������� �ص���
	//,	m_vCldrPos(0)
	, m_vScale(_origin.m_vScale)
	, m_bActive(_origin.m_bActive)
{}
CCmp_01Cldr::~CCmp_01Cldr(){}

void CCmp_01Cldr::finalupdate()
{
	Vec2 vObjPos = m_pOwner->Obj_getPos();
	m_vCldrPos = vObjPos + m_vOffsetPos;
}

void CCmp_01Cldr::render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	
	if (!(m_iOnCdlr == 0))
	{
		--m_iOnCdlr;
	}

	assert(m_iOnCdlr >= 0); //�����ϸ� ����
	if (m_iOnCdlr) //0=false, ���̻� �� true
		ePen = PEN_TYPE::RED;

	CMdl_01SltGDI tPen(_dc, ePen); //�ӽð�ü, �������������� render ����Ǹ� ���� �Ҹ�
	CMdl_01SltGDI tBrush(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = mgr_Cam::GetInst()->getRenderPos(m_vCldrPos);
		Rectangle(_dc
			, (int)(vRenderPos.x - m_vScale.x / 2.f)
			, (int)(vRenderPos.y - m_vScale.y / 2.f)
			, (int)(vRenderPos.x + m_vScale.x / 2.f)
			, (int)(vRenderPos.y + m_vScale.y / 2.f));
	
}

void CCmp_01Cldr::Cldr_onClls(CCmp_01Cldr* _pOther) //���ڴ� ���� Cldr
{	
	//++m_iOnCdlr;
	m_pOwner->Obj_onClls(_pOther);
}
void CCmp_01Cldr::Cldr_onCllsEnter(CCmp_01Cldr* _pOther) 
{
	m_iOnCdlr +=1800;
	m_pOwner->Obj_onCllsEnter(_pOther); //��ü���� �浹�̺�Ʈ�� ��� �ٸ��Ƿ� ��ȣ �Ѱ���
}
void CCmp_01Cldr::Cldr_onCllsExit(CCmp_01Cldr* _pOther) 
{ 
	//--m_iOnCdlr; 
	m_pOwner->Obj_onCllsExit(_pOther);
}
void CCmp_01Cldr::Cldr_nonClls(CCmp_01Cldr* _pOther) //���浹��
{
	
}
