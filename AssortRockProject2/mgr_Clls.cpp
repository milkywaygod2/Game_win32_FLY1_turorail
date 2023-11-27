#include "pch.h"
#include "mgr_Clls.h"

//�浹�˻�� m_arrCheck ��Ʈ���� �߽����� �����.
mgr_Clls::mgr_Clls()
	: m_arrCheck{}
{}
mgr_Clls::~mgr_Clls(){}

//1.�浹�˻� �����(��Ʈ����) by CScn_01STT.cpp
void mgr_Clls::checkObj(OBJ_TYPE _eLeft, OBJ_TYPE _eRight)
{	UINT iRow = (UINT)_eLeft; UINT iCol = (UINT)_eRight;
	if (iCol < iRow)							//�ຸ�� ���� ũ�� �ݴ�� �����ֱ�
	{		iRow = (UINT)_eRight; iCol = (UINT)_eLeft;	}

	//��Ʈ����(m_arrcheck[]�ప��ü�� ������(�ʱ����00000000 00000000 00000000 00000000))
	if (!(m_arrCheck[iRow] & (1 << iCol)))
	{		m_arrCheck[iRow] |= (1 << iCol);	}//üũ�ڽ� ��������(else) �־��ֱ�(OR)
	else										
	{		m_arrCheck[iRow] &= ~(1 << iCol);	}//üũ�ڽ� �־����� ���ֱ�(AND,~) �������
}
//2.��Ʈ���� ��ȸ �� �ݸ���������Ʈ by CCore.cpp
void mgr_Clls::update()
{	for (UINT iRow = 0; iRow < (UINT)OBJ_TYPE::objEND; ++iRow)	
	{	for (UINT iCol = 0; iCol < (UINT)OBJ_TYPE::objEND; ++iCol)
		{	if (m_arrCheck[iRow] & (1 << iCol)) //��Ʈ���� �˻�
			{	updateCllsObj((OBJ_TYPE)iRow, (OBJ_TYPE)iCol);	}}}}

//3.�ݸ��� ������Ʈ
void mgr_Clls::updateCllsObj(OBJ_TYPE _eLeft, OBJ_TYPE _eRight)
{	CScn* pCurScn = mgr_Scn::GetInst()->getCurScn();

	const vector<CObj*>& vLeftObjs = pCurScn->Scn_getObjGroup(_eLeft); //���� ���� ��ü�� �� ���õ�
	const vector<CObj*>& vRightObjs = pCurScn->Scn_getObjGroup(_eRight); //���� ���� ��ü�� �� ���õ�
	map<ULONGLONG, bool>::iterator iter; //�ݺ��������� ����Ƚ���� ���̱����� �ۿ� ����

	for (size_t i = 0; i < vLeftObjs.size(); ++i)
	{	//i�浹ü�� ���� ���
		if(nullptr == vLeftObjs[i]->Obj_getCldr() )
		{	continue;	} //i��°�� �浹�˻�x (����for�� �ǳʶٱ�)

		for (size_t j = 0; j  < vRightObjs.size(); ++j)
		{		/*Obj�� �����ڴ� void CObj::Obj_createCldr() �Լ��� �����Ͽ� Cldr�� �ڵ�����
				Obj_getCldr���� Obj�� �ּҸ� ���ڷ� ���� Cldr�� �ּҰ� ��������*/

				//��༱�𤻤�, ������Ʈ+�浹ü
				CCmp_01Cldr* pLeftObjsCldr = vLeftObjs[i]->Obj_getCldr();
				CCmp_01Cldr* pRightObjsCldr = vRightObjs[j]->Obj_getCldr();

				//j�浹ü�� ���ų� �ڽŰ� �浹�� ���(i==j)
				if (nullptr == pRightObjsCldr || vLeftObjs[i] == vRightObjs[j])
				{	continue;	}
			
				//5.�浹���� ���̵����
				uCldr_ID ObjCldrID;
				ObjCldrID.iLeftID = pLeftObjsCldr->Cldr_getID();
				ObjCldrID.iRightID = pRightObjsCldr->Cldr_getID();
				iter = m_mapCllsInfo.find(ObjCldrID.iLeftRightID); //������ȸ
			
				//��������, �̵���� ���
				if (m_mapCllsInfo.end()==iter)	
				{
					m_mapCllsInfo.insert(make_pair(ObjCldrID.iLeftRightID, false)); //�ְ�
					iter = m_mapCllsInfo.find(ObjCldrID.iLeftRightID); //�ٽ���ȸ
				}
			
			//6.���� �浹��?
			if (isClls(pLeftObjsCldr, pRightObjsCldr))
			{	
				if (iter->second)//7.�浹����
				{	
					if (vLeftObjs[i]->Obj_isDlt() || vRightObjs[j]->Obj_isDlt()) //8.����ó�� (�������� ��ȿ)
					{	pLeftObjsCldr->Cldr_onCllsExit(pRightObjsCldr); 
						pRightObjsCldr->Cldr_onCllsExit(pLeftObjsCldr);
						iter->second = false;
  					}
					else
					{	pLeftObjsCldr->Cldr_onClls(pRightObjsCldr); //���ڴ� ���� Cldr
						pRightObjsCldr->Cldr_onClls(pLeftObjsCldr);
					}
				}
				else//ù�浹
				{	if (!vLeftObjs[i]->Obj_isDlt() && !vRightObjs[j]->Obj_isDlt()) //8.�Ѵ� alive��츸
					{	pLeftObjsCldr->Cldr_onCllsEnter(pRightObjsCldr);
						pRightObjsCldr->Cldr_onCllsEnter(pLeftObjsCldr);
						iter->second = true;
					}
				}
			}
			else//�浹����
			{	if (iter->second)//�浹����
				{	pLeftObjsCldr->Cldr_onCllsExit(pRightObjsCldr);
					pRightObjsCldr->Cldr_onCllsExit(pLeftObjsCldr);
					iter->second = false;	}
				else//���浹����
				{	pLeftObjsCldr->Cldr_nonClls(pRightObjsCldr);
					pRightObjsCldr->Cldr_nonClls(pLeftObjsCldr);	}
			}
		}
	}
}
//4.�浹���� �Լ�����
bool mgr_Clls::isClls(CCmp_01Cldr* _pLeftObjsCldr, CCmp_01Cldr* _pRightObjsCldr)
{	Vec2 vLeftObjPos_F = _pLeftObjsCldr->Cldr_getPos_F();
	Vec2 vLeftObjsScale = _pLeftObjsCldr->Cldr_getScale();
	Vec2 vRightObjPos_F = _pRightObjsCldr->Cldr_getPos_F();
	Vec2 vRightObjsScale = _pRightObjsCldr->Cldr_getScale();
	if ( abs(vRightObjPos_F.x - vLeftObjPos_F.x) <= (vRightObjsScale.x + vLeftObjsScale.x)/2.f	//����ħ��?, =���� �־��ִ� �� �߿�
		&& abs(vRightObjPos_F.y - vLeftObjPos_F.y) <= (vRightObjsScale.y + vLeftObjsScale.y)/2.f )
	{	return true;	}
	return false;
}

