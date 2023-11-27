#include "pch.h"
#include "CScn_01STT.h"



CScn_01STT::CScn_01STT()
	: m_bUseForce(false)
	, m_fForceRange(150.f)
	, m_fForceRangeCur(0.f)
	, m_fForce(2000.f)
{}
CScn_01STT::~CScn_01STT(){}

void CScn_01STT::Enter()
{
	//Player추가
	CObj* pPlr = new CObj_01PLR;

	CCmp_02Amtr* pAmtr = pPlr->Obj_getAmtr();
	CCmp_02Amtrn* pAmtrn = pAmtr->findAmtrn(L"FLY1_IDLE_R");
	Vec2 AmtrnSize = pAmtrn->getFrm(0).vImageSize;

	pPlr->Obj_setName(L"PLR");
	pPlr->Obj_setPos(Vec2(640.f, 384.f));
	pPlr->Obj_setScale(AmtrnSize);

	Scn_addObj(pPlr, OBJ_TYPE::PLR); //m_arrObj[STT][PLR].push_back(pObj)

	Scn_registerPLR(pPlr);
	
	//mgr_Cam::GetInst()->setTarget(pPlr);
	/*
	CObj* pOtherPlr = pPlr->clone(); //선언시 CObj로 해줘야 가상함수사용가능
	pOtherPlr->Obj_setPos(Vec2(740.f, 384.f));
	Scn_addObj(pOtherPlr, OBJ_TYPE::PLR);
	*/


	//Monster추가
	Vec2 vResolution = CCore::GetInst()->getResolution();
	//CObj_02MTR* pMtr = FactoryMTR::createMTR(MTR_TYPE::NORMAL,vResolution/2.f-Vec2(0.f,300.f));
	//Scn_addObj(pMtr, OBJ_TYPE::MTR);
	
	//Monster추가(구)
	int iMtrCount = 5;
	float fMtrDist = 150.f;
	float fMtrScale = 50.f;
	float fMtrTerm = (vResolution.x - ((fMtrDist + fMtrScale / 2.f) * 2)) / (float)(iMtrCount-1);
	
	for (int i = 0; i < iMtrCount; ++i)
	{
		//pMtr = new CObj_02MTR;
		CObj_02MTR* pMtr = FactoryMTR::createMTR(MTR_TYPE::NORMAL, Vec2((fMtrDist/2.f + fMtrScale / 2.f) + (float)i * fMtrTerm, 50.f));

		pMtr->Obj_setName(L"MTR"); //충돌검사시 중요
		pMtr->setCenterPos(pMtr->Obj_getPos());
		//pMtr->setMoveDistance(fMtrDist);
		pMtr->Obj_setScale(Vec2(fMtrScale, fMtrScale));

		Scn_addObj(pMtr, OBJ_TYPE::MTR);
	}

	//땅 배치
	CObj* pGround = new CObj_06GRD;
	pGround->Obj_setName(L"Ground");
	pGround->Obj_setPos(Vec2(640.f, 500.f));
	pGround->Obj_setScale(Vec2(200.f,60.f));
	Scn_addObj(pGround, OBJ_TYPE::GRD);

	//충돌 검사대상 설정
	mgr_Clls::GetInst()->checkObj(OBJ_TYPE::PLR, OBJ_TYPE::MTR);
	mgr_Clls::GetInst()->checkObj(OBJ_TYPE::MSL_PLR, OBJ_TYPE::MTR);
	mgr_Clls::GetInst()->checkObj(OBJ_TYPE::PLR, OBJ_TYPE::GRD);

	//카메라 설정
	mgr_Cam::GetInst()->setPsyLookat(vResolution /2.f);//vResolution몬스터쪽에서 기선언

	//카메라 효과지정
	mgr_Cam::GetInst()->fadein(2.f);

	Scn_start(); //Scn
}


void CScn_01STT::update()
{
	if (KEY_HOLD(KEY::LBTN)){
		m_bUseForce = true;
		createForce();
	}
	else {m_bUseForce = false;}

	//CScn::update(); //오버라이딩하긴 했지만 기본은 부모꺼씀 +a 쓸상황
	
	for (UINT i = 0; i < (UINT)OBJ_TYPE::objEND; ++i)
	{
		const vector<CObj*>& vecObj = Scn_getObjGroup((OBJ_TYPE)i);
		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->Obj_isDlt()) //삭제예정은 거르기
			{
				//<CreateForce구현부>
				if (m_bUseForce && vecObj[j]->Obj_getRgdB())
				{
					Vec2 vDiff = vecObj[j]->Obj_getPos() - m_vForcePos;
					float fLen = vDiff.Length();
					if (fLen < m_fForceRange)
					{
						float fRatio = 1.f - (fLen / m_fForceRange);
						float fForce = m_fForce * fRatio;
						vecObj[j]->Obj_getRgdB()->addForce(vDiff.Normalize() * fForce);
					}
				}

				vecObj[j]->update();
			}
		}
	}

	if (KEY_TAP(KEY::ENTER))
	{
		Evt_changeScn(SCN_TYPE::TL);
	}

	/*if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vPsyLookat = mgr_Cam::GetInst()->getRealPos(CURSOR_POS);
		mgr_Cam::GetInst()->setPsyLookat(vPsyLookat);
	}*/

}

void CScn_01STT::render(HDC _dc)
{
	CScn::render(_dc);

	if (!m_bUseForce)
		return;

	CMdl_01SltGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	CMdl_01SltGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fForceRangeCur += m_fForceRange * 3.f * fDT;
	if (m_fForceRangeCur > m_fForceRange)
	{
		m_fForceRangeCur = 0.f;
	}

	Vec2 vRenderPos = mgr_Cam::GetInst()->getRenderPos(m_vForcePos);

	Ellipse(_dc
		, (int)(vRenderPos.x - m_fForceRangeCur)
		, (int)(vRenderPos.y - m_fForceRangeCur)
		, (int)(vRenderPos.x + m_fForceRangeCur)
		, (int)(vRenderPos.y + m_fForceRangeCur));
	
}

void CScn_01STT::Exit()
{
	Scn_clearAll();
	mgr_Clls::GetInst()->reset();
}

void CScn_01STT::createForce() {m_vForcePos = mgr_Cam::GetInst()->getRealPos(CURSOR_POS);}
