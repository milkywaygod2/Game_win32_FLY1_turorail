#include "pch.h"
#include "mgr_Clls.h"

//충돌검사는 m_arrCheck 매트릭스 중심으로 진행됨.
mgr_Clls::mgr_Clls()
	: m_arrCheck{}
{}
mgr_Clls::~mgr_Clls(){}

//1.충돌검사 대상설정(매트릭스) by CScn_01STT.cpp
void mgr_Clls::checkObj(OBJ_TYPE _eLeft, OBJ_TYPE _eRight)
{	UINT iRow = (UINT)_eLeft; UINT iCol = (UINT)_eRight;
	if (iCol < iRow)							//행보다 열이 크면 반대로 돌려주기
	{		iRow = (UINT)_eRight; iCol = (UINT)_eLeft;	}

	//비트연산(m_arrcheck[]행값자체가 연산대상(초기상태00000000 00000000 00000000 00000000))
	if (!(m_arrCheck[iRow] & (1 << iCol)))
	{		m_arrCheck[iRow] |= (1 << iCol);	}//체크박스 없었으면(else) 넣어주기(OR)
	else										
	{		m_arrCheck[iRow] &= ~(1 << iCol);	}//체크박스 있었으면 빼주기(AND,~) 해제기능
}
//2.매트릭스 조회 → 콜리전업데이트 by CCore.cpp
void mgr_Clls::update()
{	for (UINT iRow = 0; iRow < (UINT)OBJ_TYPE::objEND; ++iRow)	
	{	for (UINT iCol = 0; iCol < (UINT)OBJ_TYPE::objEND; ++iCol)
		{	if (m_arrCheck[iRow] & (1 << iCol)) //매트릭스 검사
			{	updateCllsObj((OBJ_TYPE)iRow, (OBJ_TYPE)iCol);	}}}}

//3.콜리전 업데이트
void mgr_Clls::updateCllsObj(OBJ_TYPE _eLeft, OBJ_TYPE _eRight)
{	CScn* pCurScn = mgr_Scn::GetInst()->getCurScn();

	const vector<CObj*>& vLeftObjs = pCurScn->Scn_getObjGroup(_eLeft); //같은 유형 객체는 다 선택됨
	const vector<CObj*>& vRightObjs = pCurScn->Scn_getObjGroup(_eRight); //같은 유형 객체는 다 선택됨
	map<ULONGLONG, bool>::iterator iter; //반복문내에서 수행횟수를 줄이기위해 밖에 선언

	for (size_t i = 0; i < vLeftObjs.size(); ++i)
	{	//i충돌체가 없는 경우
		if(nullptr == vLeftObjs[i]->Obj_getCldr() )
		{	continue;	} //i번째는 충돌검사x (다음for문 건너뛰기)

		for (size_t j = 0; j  < vRightObjs.size(); ++j)
		{		/*Obj는 생성자는 void CObj::Obj_createCldr() 함수를 포함하여 Cldr를 자동생성
				Obj_getCldr에는 Obj의 주소를 인자로 가진 Cldr의 주소가 남겨있음*/

				//축약선언ㅋㅋ, 오브젝트+충돌체
				CCmp_01Cldr* pLeftObjsCldr = vLeftObjs[i]->Obj_getCldr();
				CCmp_01Cldr* pRightObjsCldr = vRightObjs[j]->Obj_getCldr();

				//j충돌체가 없거나 자신과 충돌인 경우(i==j)
				if (nullptr == pRightObjsCldr || vLeftObjs[i] == vRightObjs[j])
				{	continue;	}
			
				//5.충돌조합 아이디생성
				uCldr_ID ObjCldrID;
				ObjCldrID.iLeftID = pLeftObjsCldr->Cldr_getID();
				ObjCldrID.iRightID = pRightObjsCldr->Cldr_getID();
				iter = m_mapCllsInfo.find(ObjCldrID.iLeftRightID); //최초조회
			
				//최초조합, 미등록인 경우
				if (m_mapCllsInfo.end()==iter)	
				{
					m_mapCllsInfo.insert(make_pair(ObjCldrID.iLeftRightID, false)); //넣고
					iter = m_mapCllsInfo.find(ObjCldrID.iLeftRightID); //다시조회
				}
			
			//6.현재 충돌중?
			if (isClls(pLeftObjsCldr, pRightObjsCldr))
			{	
				if (iter->second)//7.충돌지속
				{	
					if (vLeftObjs[i]->Obj_isDlt() || vRightObjs[j]->Obj_isDlt()) //8.예외처리 (삭제대상시 무효)
					{	pLeftObjsCldr->Cldr_onCllsExit(pRightObjsCldr); 
						pRightObjsCldr->Cldr_onCllsExit(pLeftObjsCldr);
						iter->second = false;
  					}
					else
					{	pLeftObjsCldr->Cldr_onClls(pRightObjsCldr); //인자는 상대방 Cldr
						pRightObjsCldr->Cldr_onClls(pLeftObjsCldr);
					}
				}
				else//첫충돌
				{	if (!vLeftObjs[i]->Obj_isDlt() && !vRightObjs[j]->Obj_isDlt()) //8.둘다 alive경우만
					{	pLeftObjsCldr->Cldr_onCllsEnter(pRightObjsCldr);
						pRightObjsCldr->Cldr_onCllsEnter(pLeftObjsCldr);
						iter->second = true;
					}
				}
			}
			else//충돌없음
			{	if (iter->second)//충돌해제
				{	pLeftObjsCldr->Cldr_onCllsExit(pRightObjsCldr);
					pRightObjsCldr->Cldr_onCllsExit(pLeftObjsCldr);
					iter->second = false;	}
				else//미충돌지속
				{	pLeftObjsCldr->Cldr_nonClls(pRightObjsCldr);
					pRightObjsCldr->Cldr_nonClls(pLeftObjsCldr);	}
			}
		}
	}
}
//4.충돌여부 함수구현
bool mgr_Clls::isClls(CCmp_01Cldr* _pLeftObjsCldr, CCmp_01Cldr* _pRightObjsCldr)
{	Vec2 vLeftObjPos_F = _pLeftObjsCldr->Cldr_getPos_F();
	Vec2 vLeftObjsScale = _pLeftObjsCldr->Cldr_getScale();
	Vec2 vRightObjPos_F = _pRightObjsCldr->Cldr_getPos_F();
	Vec2 vRightObjsScale = _pRightObjsCldr->Cldr_getScale();
	if ( abs(vRightObjPos_F.x - vLeftObjPos_F.x) <= (vRightObjsScale.x + vLeftObjsScale.x)/2.f	//영역침범?, =까지 넣어주는 거 중요
		&& abs(vRightObjPos_F.y - vLeftObjPos_F.y) <= (vRightObjsScale.y + vLeftObjsScale.y)/2.f )
	{	return true;	}
	return false;
}

