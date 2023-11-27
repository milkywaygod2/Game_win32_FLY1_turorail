#include "pch.h"
#include "CObj_03MSL.h"


CObj_03MSL::CObj_03MSL()
	: m_fThetaMSL(PI/2.f)
	, m_vDirMSL(Vec2(1.f,1.f))
{
	m_vDirMSL.Normalize();
	Obj_createCldr();
	Obj_getCldr()->Cldr_setScale(Vec2(16.f,8.f));	
}
CObj_03MSL::~CObj_03MSL(){}

void CObj_03MSL::update()
{
	Vec2 vPos = Obj_getPos();

	//�ﰢ�Լ��� �̵���ġ(�ӵ�)���ϱ� : �� �̰� �ﰢ���϶�, ��������� (cos��,sin��) tan�ȴ� ����(�̺�)
	//vPos.x += 600.f * fDT * cosf(m_fThetaMSL);
	//vPos.y -= 600.f * fDT * sinf(m_fThetaMSL);

	vPos.x += 1500.f * fDT * m_vDirMSL.x;
	vPos.y += 1500.f * fDT * m_vDirMSL.y;

	//[����] ȭ��ǥ�� �߻���� �ٲٰ�ʹ� �̤�
	/*if (KEY_HOLD(KEY::LEFT)) { m_fThetaMSL += 1.f * fDT; }
	if (KEY_HOLD(KEY::RIGHT)) { m_fThetaMSL -= 1.f * fDT; }
	vPos.x += 600.f * fDT * cosf(m_fThetaMSL);
	vPos.y -= 600.f * fDT * sinf(m_fThetaMSL);*/
	Obj_setPos(vPos);
}

void CObj_03MSL::render(HDC _dc)
{
	Vec2 vPos = Obj_getPos();
	Vec2 vRenderPos = mgr_Cam::GetInst()->getRenderPos(vPos);
	Vec2 vScale = Obj_getScale();
	Ellipse(_dc
		, (int)(vRenderPos.x - vScale.x / 4.f)
		, (int)(vRenderPos.y - vScale.y / 4.f)
		, (int)(vRenderPos.x + vScale.x / 4.f)
		, (int)(vRenderPos.y + vScale.y / 4.f));
	
	Obj_renderCmp(_dc);

}

void CObj_03MSL::Obj_onCllsEnter(CCmp_01Cldr* _pOther)
{
	CObj* pOtherObj = _pOther->Cldr_getOtherObj();

	if (pOtherObj->Obj_getName() == L"MTR")
	{
		Evt_deleteObj(this,OBJ_TYPE::MSL_PLR);
	}
}
