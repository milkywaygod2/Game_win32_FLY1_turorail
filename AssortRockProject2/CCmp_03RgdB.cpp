#include "pch.h"
#include "CCmp_03RgdB.h"

CCmp_03RgdB::CCmp_03RgdB()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFric(350.f)
	, m_fSpeedMax(550.f)
{
}

CCmp_03RgdB::~CCmp_03RgdB()
{
}

void CCmp_03RgdB::finalupdate()
{
	m_vForce;
	//float fForce = m_vForce.Length(); //������ ���� ũ��
	//if (0.f != fForce)
	//{
		//m_vForce.Normalize(); //������ ���� ���� (=���ӵ��� ����)
		//float m_fAccel = fForce / m_fMass; //���ӵ��� ũ��(�ӷ�)
	
	m_vAccel = m_vForce / m_fMass;//1.���ӵ��� �ӵ�(����+�ӷ�)
	m_vAccel += m_vAccel_G; //+�߷°��ӵ� ���
	m_vVelo += m_vAccel * fDT; //2.��ü�� �ӵ�
	//}

	if (!m_vVelo.isZero()) //3.������ ����
	{
		Vec2 vVeloDir = m_vVelo; 
		vVeloDir.Normalize();
		Vec2 vFric = -vVeloDir * m_fFric * fDT;
		if (m_vVelo.Length() <= vFric.Length())
		{
			vFric = -m_vVelo;
		}
		m_vVelo += vFric;
	}

	if (m_fSpeedMax < m_vVelo.Length()) //4.�ӵ����Ѱ˻�, ��������¦��
	{
		m_vVelo.Normalize();
		m_vVelo *= m_fSpeedMax;
	}

	moveRgdB(); //�ӵ��� ���� ��ü�� �̵�
	m_vForce = Vec2(0.f, 0.f); //�� �ʱ�ȭ
	m_vAccel_G = Vec2(0.f, 0.f); //�� ������ �߷°��ӵ� �� �� ������ ����
}

void CCmp_03RgdB::moveRgdB()
{
	Vec2 vPos = m_pOwner->Obj_getPos();
	vPos += m_vVelo * fDT;
	m_pOwner->Obj_setPos(vPos);
}
