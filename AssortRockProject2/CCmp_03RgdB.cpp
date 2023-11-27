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
	//float fForce = m_vForce.Length(); //순수한 힘의 크기
	//if (0.f != fForce)
	//{
		//m_vForce.Normalize(); //순수한 힘의 방향 (=가속도의 방향)
		//float m_fAccel = fForce / m_fMass; //가속도의 크기(속력)
	
	m_vAccel = m_vForce / m_fMass;//1.가속도의 속도(방향+속력)
	m_vAccel += m_vAccel_G; //+중력가속도 고려
	m_vVelo += m_vAccel * fDT; //2.물체의 속도
	//}

	if (!m_vVelo.isZero()) //3.마찰력 적용
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

	if (m_fSpeedMax < m_vVelo.Length()) //4.속도제한검사, 공기저항짝퉁
	{
		m_vVelo.Normalize();
		m_vVelo *= m_fSpeedMax;
	}

	moveRgdB(); //속도에 따른 물체의 이동
	m_vForce = Vec2(0.f, 0.f); //힘 초기화
	m_vAccel_G = Vec2(0.f, 0.f); //매 프레임 중력가속도 더 할 건지는 재계산
}

void CCmp_03RgdB::moveRgdB()
{
	Vec2 vPos = m_pOwner->Obj_getPos();
	vPos += m_vVelo * fDT;
	m_pOwner->Obj_setPos(vPos);
}
