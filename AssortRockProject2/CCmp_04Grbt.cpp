#include "pch.h"
#include "CCmp_04Grbt.h"

CCmp_04Grbt::CCmp_04Grbt()
	: m_pOwner(nullptr)
	, m_bGround(false)
{
}

CCmp_04Grbt::~CCmp_04Grbt()
{
}

void CCmp_04Grbt::finalupdate()
{
	m_pOwner->Obj_getRgdB()->setAccel_G(Vec2(0.f, 800.f));
}
