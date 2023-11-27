#include "pch.h"
#include "CObj_06GRD.h"


CObj_06GRD::CObj_06GRD()
{
	Obj_createCldr();
}

CObj_06GRD::~CObj_06GRD()
{
}

void CObj_06GRD::Obj_start()
{
	Obj_getCldr()->Cldr_setScale(Vec2(Obj_getScale()));
}

void CObj_06GRD::update()
{
}

void CObj_06GRD::Obj_onCllsEnter(CCmp_01Cldr* _pCllsCldr)
{
	CObj* pCllsObj = _pCllsCldr->Cldr_getOtherObj();
	if (pCllsObj->Obj_getName() == L"PLR")
	{
		pCllsObj->Obj_getGrbt()->setGRD(true);

		Vec2 vCldrPos = _pCllsCldr->Cldr_getPos_F();
		Vec2 vCldrScale = _pCllsCldr->Cldr_getScale();

		Vec2 vGroundPos = Obj_getCldr()->Cldr_getPos_F();
		Vec2 vGroundScale = Obj_getCldr()->Cldr_getScale();
		
		float fCtoCLen = abs(vCldrPos.y - vGroundPos.y);
		float fDiffLen = (vCldrScale.y / 2.f + vGroundScale.y / 2.f) - fCtoCLen; //��ģ�κб��ϱ�

		vCldrPos = pCllsObj->Obj_getPos(); //Obj��ġ���� Cldr��ġ�� ������Ʈ
		vCldrPos.y -= fDiffLen;
		pCllsObj->Obj_setPos(vCldrPos);
	} 
}

void CObj_06GRD::Obj_onClls(CCmp_01Cldr* _pCllsCldr)
{
	CObj* pCllsObj = _pCllsCldr->Cldr_getOtherObj();
	if (pCllsObj->Obj_getName() == L"PLR")
	{
		pCllsObj->Obj_getGrbt()->setGRD(true);

		Vec2 vCldrPos = _pCllsCldr->Cldr_getPos_F();
		Vec2 vCldrScale = _pCllsCldr->Cldr_getScale();

		Vec2 vGroundPos = Obj_getCldr()->Cldr_getPos_F();
		Vec2 vGroundScale = Obj_getCldr()->Cldr_getScale();

		float fCtoCLen = abs(vCldrPos.y - vGroundPos.y);
		float fDiffLen = (vCldrScale.y / 2.f + vGroundScale.y / 2.f) - fCtoCLen; //��ģ�κб��ϱ�

		vCldrPos = pCllsObj->Obj_getPos(); //Obj��ġ���� Cldr��ġ�� ������Ʈ
		vCldrPos.y -= fDiffLen;
		pCllsObj->Obj_setPos(vCldrPos);
	/*	if (pCllsObj->Obj_getGrbt()->getGRD())
		{
			pCllsObj->Obj_getRgdB()->setVelo(Vec2(0.f, 0.f));
		}*/
	}
}

void CObj_06GRD::Obj_onCllsExit(CCmp_01Cldr* _pCllsCldr)
{
	CObj* pCllsObj = _pCllsCldr->Cldr_getOtherObj();
	if (pCllsObj->Obj_getName() == L"PLR")
	{
		pCllsObj->Obj_getGrbt()->setGRD(false);
	}
}
