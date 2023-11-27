#include "pch.h"
#include "CObj_01PLR.h"
#include "CCmp_03RgdB.h"


CObj_01PLR::CObj_01PLR()
	: m_eCurStatePLR(PLR_STATE::IDLE)
	, m_ePrevStatePLR(PLR_STATE::FLY)
	, m_iDir(1)
	, m_iDirPrev(1)
{
	//Texture�ε�
	//m_pTxr = mgr_Rsc::GetInst()->loadTxr(L"PlrTXR", L"texture\\gp_pilot_167x282.bmp"); //1

	//Collider�ε�
	Obj_createCldr();
	Obj_getCldr()->SetOffsetPos(Vec2(0.f, 15.f));
	Obj_getCldr()->Cldr_setScale(Vec2(15.f, 15.f));
	//Vec2 AmtrnSize = (pAmtrn->getFrm(0).vImageSize) * 0.5f;
	//Obj_getCldr()->Cldr_setScale(AmtrnSize);

	//RigidBody�߰�(��ü) 
	Obj_createRgdB();

	//Texture�ε�
	CRsc_01TXR* pTxrL = mgr_Rsc::GetInst()->loadTxr(L"PlrTXR_L", L"texture\\fly1\\fly1_512x128.bmp"); //2
	CRsc_01TXR* pTxrR = mgr_Rsc::GetInst()->loadTxr(L"PlrTXR_R", L"texture\\fly1\\fly1_512x128.bmp"); //2
		
	Obj_createAmtr();

	//Animation����(.amtrn ���ϻ����� ���ʿ�)
	/*Obj_getAmtr()->createAmtrn(L"FLY1_IDLE_L", pTxrL, Vec2(0.f,0.f), Vec2(32.f,32.f), Vec2(32.f,0.f), 0.05f ,16);
	Obj_getAmtr()->createAmtrn(L"FLY1_IDLE_R", pTxrR, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 16);
	
	Obj_getAmtr()->createAmtrn(L"FLY1_FLY_L", pTxrL, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 16);
	Obj_getAmtr()->createAmtrn(L"FLY1_FLY_R", pTxrR, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 16);

	Obj_getAmtr()->createAmtrn(L"FLY1_JUMP_R", pTxrR, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 16);
	Obj_getAmtr()->createAmtrn(L"FLY1_JUMP_L", pTxrL, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 16);*/

	//Obj_getAmtr()->playAmtrn(L"FLY1_IDLE_R", true);

	//Animation����(.amtrn ���ϻ����� ���ʿ�)
	/*Obj_getAmtr()->findAmtrn(L"FLY1_IDLE_L")->saveAmtrn(L"animation\\player_IDLE_L.amtrn");
	Obj_getAmtr()->findAmtrn(L"FLY1_IDLE_R")->saveAmtrn(L"animation\\player_IDLE_R.amtrn");
	Obj_getAmtr()->findAmtrn(L"FLY1_FLY_L")->saveAmtrn(L"animation\\player_FLY_L.amtrn");
	Obj_getAmtr()->findAmtrn(L"FLY1_FLY_R")->saveAmtrn(L"animation\\player_FLY_R.amtrn");
	Obj_getAmtr()->findAmtrn(L"FLY1_JUMP_R")->saveAmtrn(L"animation\\player_JUMP_L.amtrn");
	Obj_getAmtr()->findAmtrn(L"FLY1_JUMP_L")->saveAmtrn(L"animation\\player_JUMP_R.amtrn");*/

	//.amtrn ���ϻ����� ���
	Obj_getAmtr()->loadAmtr(L"animation\\player_IDLE_L.amtrn");
	Obj_getAmtr()->loadAmtr(L"animation\\player_IDLE_R.amtrn");
	Obj_getAmtr()->loadAmtr(L"animation\\player_FLY_L.amtrn");
	Obj_getAmtr()->loadAmtr(L"animation\\player_FLY_R.amtrn");
	Obj_getAmtr()->loadAmtr(L"animation\\player_JUMP_L.amtrn");
	Obj_getAmtr()->loadAmtr(L"animation\\player_JUMP_R.amtrn");

	//�����Ӻ� ������, ���̼Һ��
	/*CCmp_02Amtrn* pAmtrn = Obj_getAmtr()->findAmtrn(L"FLY1_IDLE_R");
	for (UINT i = 0; i < pAmtrn->getMaxFrm(); ++i) {
		pAmtrn->getFrm(i).vOffset = Vec2(0.f, -20.f);}*/
	
	Obj_createGrbt();
}
CObj_01PLR::~CObj_01PLR(){}

inline void CObj_01PLR::update()
{
	updateMovePLR();
	updateStatePLR();
	updateAmtrnPLR();

	if (KEY_TAP(KEY::SPACE)) { createMSL(); }

	Vec2 vPos = Obj_getPos();
	mgr_Cam::GetInst()->setPlrPos(vPos);

	Obj_getAmtr()->update();
	m_ePrevStatePLR = m_eCurStatePLR;
}

void CObj_01PLR::render(HDC _dc)
{
	/*int iWidth = (int)m_pTxr->Width(); //�̹����� �ȼ����� �����ϼ���������(UINT), BitBlt���� ������ �� �� �������� intȭ
	int iHeight = (int)m_pTxr->Height();
	Vec2 vPos = Obj_getPos();
	*/
	/*BitBlt(_dc
		, int(vPos.x - (float)(iWidth / 2)) //�»��
		, int(vPos.y - (float)(iHeight / 2))//�»��
		, iWidth, iHeight					//ũ��
		, m_pTxr->getDC()					//�����̹��������DC
		, 0, 0								//�����̹���������ġ
		, SRCCOPY);							//�״�κ���
		*/
	/*TransparentBlt(_dc					//������Ʈ�� windows.h�� ���� �����δ� Msimg32.lib���������;���
		, int(vPos.x - (float)(iWidth / 2)) //�»��x
		, int(vPos.y - (float)(iHeight / 2))//�»��y
		, iWidth, iHeight					//ũ��
		, m_pTxr->getDC()					//�����̹��������DC
		, 0, 0, iWidth, iHeight				//�����̹���������ġ+����
		, RGB(255,0,255));					//�����һ���(�״�κ���翬�ؼ�����)
	*/

	//����
	Vec2 vPos = Obj_getPos();
	Vec2 vRenderPos = mgr_Cam::GetInst()->getRenderPos(vPos);

	//���ĺ���+
	/*CRsc_01TXR* pTxr = mgr_Rsc::GetInst()->loadTxr(L"PlrTXR_A", L"texture\\fly1\\fly1AlphaOutline_512x128.bmp");
	float width = (float)pTxr->Width();
	float height = (float)pTxr->Height();
	Vec2 vPosA = mgr_Cam::GetInst()->getRenderPos(vPos);

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127;
	AlphaBlend(_dc
		, int(vPosA.x - width / 2.f)
		, int(vPosA.y - height / 2.f)
		, int(width), int(height)
		, pTxr->getDC()
		, 0, 0
		, int(width), int(height)
		, bf);*/


	//*�÷��̾� ��ġȮ�ο�
	/*Vec2 vScale = Obj_getScale();
	Ellipse(_dc
		, (int)(vRenderPos.x - vScale.x / 4.f)
		, (int)(vRenderPos.y - vScale.y / 4.f)
		, (int)(vRenderPos.x + vScale.x / 4.f)
		, (int)(vRenderPos.y + vScale.y / 4.f));*/

	Obj_renderCmp(_dc);
}

void CObj_01PLR::createMSL()
{
	Vec2 vMslPos = Obj_getPos();
	vMslPos.x += Obj_getScale().x * (1.f / 2.f);
	vMslPos.y += Obj_getScale().y * (2.f / 5.f);

	CObj_03MSL* pMsl = new CObj_03MSL;
	pMsl->Obj_setName(L"MSL_PLR");

	pMsl->Obj_setPos(vMslPos);
	pMsl->Obj_setScale(Vec2(16.f,8.f));

	pMsl->SetDir(Vec2(1.f, 0.f));

	Evt_createObj(pMsl,OBJ_TYPE::MSL_PLR);
}

void CObj_01PLR::updateMovePLR()
{
	CCmp_03RgdB* pRgdB = Obj_getRgdB();

	float speed = 1400.f;//�ӷ�
	if (KEY_HOLD(KEY::A)) { /*vPos.x -= 400.f * fDT;*/ pRgdB->addForce(Vec2(-speed, 0.f)); }
	if (KEY_HOLD(KEY::D)) {	/*vPos.x += 400.f * fDT;*/ pRgdB->addForce(Vec2(speed, 0.f)); }
	if (KEY_HOLD(KEY::W)) {	/*vPos.y -= 400.f * fDT;*/ pRgdB->addForce(Vec2(0.f, -speed)); }
	if (KEY_HOLD(KEY::S)) {	/*vPos.y += 400.f * fDT;*/ pRgdB->addForce(Vec2(0.f, speed)); }

}

void CObj_01PLR::updateStatePLR()
{
	if (KEY_HOLD(KEY::A)) {
		m_iDir = 1;
		if (PLR_STATE::JUMP != m_eCurStatePLR)
			m_eCurStatePLR = PLR_STATE::FLY;
	}
	if (KEY_HOLD(KEY::D)) {
		m_iDir = -1;
		if (PLR_STATE::JUMP != m_eCurStatePLR)
			m_eCurStatePLR = PLR_STATE::FLY;
	}
	if (0.f == Obj_getRgdB()->getSpeed() && PLR_STATE::JUMP != m_eCurStatePLR){
		m_eCurStatePLR = PLR_STATE::IDLE;
	}
	if (KEY_TAP(KEY::LSHIFT))
	{
		m_eCurStatePLR = PLR_STATE::JUMP;
		if (Obj_getRgdB())
		{
			Obj_getRgdB()->addVelo(Vec2(Obj_getRgdB()->getVelo().x, -3000.f));
		}
	}
	
	/*if (KEY_NONE(KEY::A) && KEY_NONE(KEY::D)) {
		m_eCurStatePLR = PLR_STATE::IDLE;
	}*/ //�̰ɷ� �ϸ� �����̴µ� �ִϸ��̼� ���ߴ� ���
}

void CObj_01PLR::updateAmtrnPLR()
{
	if (m_ePrevStatePLR == m_eCurStatePLR && m_iDirPrev == m_iDir)
		return;

	switch (m_eCurStatePLR)
	{
	case PLR_STATE::IDLE:{
		if(m_iDir == 1)
		Obj_getAmtr()->playAmtrn(L"FLY1_IDLE_R", true);
		else
		Obj_getAmtr()->playAmtrn(L"FLY1_IDLE_L", true);
	}
		break;
	case PLR_STATE::FLY:{
		if (m_iDir == 1)
			Obj_getAmtr()->playAmtrn(L"FLY1_IDLE_R", true);
		else
			Obj_getAmtr()->playAmtrn(L"FLY1_IDLE_L", true);
	}
		break;
	case PLR_STATE::JUMP:
		if (m_iDir == 1)
			Obj_getAmtr()->playAmtrn(L"FLY1_IDLE_R", true);
		else
			Obj_getAmtr()->playAmtrn(L"FLY1_IDLE_L", true);
		break;
	case PLR_STATE::ATTACK:
		break;
	case PLR_STATE::WALK:
		break;
	case PLR_STATE::DEAD:
		break;
	default:

		break;
	}

}

void CObj_01PLR::updateGravityPLR()
{
	Obj_getRgdB()->addForce(Vec2(0.f, 500.f));


}

void CObj_01PLR::Obj_onCllsEnter(CCmp_01Cldr* _pCllsCldr)
{
	CObj* pCllsObj = _pCllsCldr->Cldr_getOtherObj();
	if (L"Ground" == pCllsObj->Obj_getName())
	{
		Vec2 vCllsObjPos = Obj_getPos();
		if (vCllsObjPos.y < pCllsObj->Obj_getPos().y)
		{
			m_eCurStatePLR = PLR_STATE::IDLE;
		}
	}
}
