#include "pch.h"
#include "mgr_Cam.h"

mgr_Cam::mgr_Cam()
	: m_vPsyLookat(Vec2(640.f, 384.f))
	, m_pPlrPos(Vec2(640.f, 384.f))
	, m_pTargetObj(nullptr)
	, m_fTime(0.2f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.f)
	, m_pVeilTxr(nullptr)
{
}
mgr_Cam::~mgr_Cam(){}


void mgr_Cam::init()
{
	Vec2 vResolution = CCore::GetInst()->getResolution();
	m_pVeilTxr = mgr_Rsc::GetInst()->createTxr(L"Cam_Veil",(UINT)vResolution.x, (UINT)vResolution.y);
}

void mgr_Cam::update()
{
	//Ÿ���ִ� ���
	if (m_pTargetObj)
	{
		if (m_pTargetObj->Obj_isDlt()) { m_pTargetObj = nullptr; }
		else { m_vPsyLookat = m_pTargetObj->Obj_getPos(); }
	}
	else
	{
		//ī�޶� ����Ű ����
		if (KEY_HOLD(KEY::LEFT) ||
			KEY_HOLD(KEY::RIGHT) ||
			KEY_HOLD(KEY::UP) ||
			KEY_HOLD(KEY::DOWN))
		{

			if (KEY_HOLD(KEY::LEFT)) { m_vPsyLookat.x -= 600.f * fDT; }
			if (KEY_HOLD(KEY::RIGHT)) { m_vPsyLookat.x += 600.f * fDT; }
			if (KEY_HOLD(KEY::UP)) { m_vPsyLookat.y -= 600.f * fDT; }
			if (KEY_HOLD(KEY::DOWN)) { m_vPsyLookat.y += 600.f * fDT; }
		}
		//ī�޶� ���콺 ����
		else if (KEY_HOLD(KEY::RBTN))
		{
			Vec2 vPsyLookat = mgr_Cam::GetInst()->getRealPos(CURSOR_POS);
			mgr_Cam::GetInst()->setPsyLookat(vPsyLookat);
		}
		//�÷��̾� ��ġ ����
		else
		{
			//���������� �÷��̾� ��ġ��ô �ϸ� �ȵ�.
			CScn* pCurScn = mgr_Scn::GetInst()->getCurScn();
			CScn_00TL* pIsToolScn = dynamic_cast<CScn_00TL*>(pCurScn); //�����ٿ� ĳ����, �����ϸ� nullptr��ȯ
			if (!(pIsToolScn))
				mgr_Cam::GetInst()->setPsyLookat(m_pPlrPos);
		}
	}
	calculateDiff();	
}

void mgr_Cam::calculateDiff()
{
	m_fAccTime += fDT;
	if (m_fAccTime <= m_fTime)
	{
		Vec2 vLookDir = m_vPsyLookat - m_vPrevLookat;
		if (!vLookDir.isZero())
		{
			m_vCurLookat = m_vPrevLookat + vLookDir.Normalize() * m_fSpeed * fDT;
		}
	}
	else
	{
		m_vCurLookat = m_vPsyLookat;
	}

	Vec2 vResolution = CCore::GetInst()->getResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookat - vCenter;//-->��ī�޶� ��ġ�� �����Ǵ� ���� ���� ���尡 �����Ǵ� ��.

	m_vPrevLookat = m_vCurLookat;
}

void mgr_Cam::render(HDC _dc)
{
	if (m_listEffectCam.empty())
		return;

	tEffect_Cam& ef = m_listEffectCam.front();
	ef.fCurTime += fDT;

	float fRatio = 0.f;
	fRatio = ef.fCurTime / ef.fDuration;
	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	if (EFFECT_CAM::FADE_OUT == ef.eEffect)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (EFFECT_CAM::FADE_IN == ef.eEffect)
	{
		iAlpha = (int)(255.f * (1.f-fRatio));
	}

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc, 0, 0, 
		(int)m_pVeilTxr->Width(), 
		(int)m_pVeilTxr->Height(), 
		m_pVeilTxr->getDC(), 
		0, 0, 
		(int)m_pVeilTxr->Width(), 
		(int)m_pVeilTxr->Height(), 
		bf);


	if (ef.fDuration < ef.fCurTime)
	{
		m_listEffectCam.pop_front();
	}
}
	

