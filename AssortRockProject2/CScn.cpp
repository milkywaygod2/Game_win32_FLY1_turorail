#include "pch.h"
//#include "CScn.h"

CScn::CScn()
	: m_iTileX(0)
	, m_iTileY(0)
	, m_pPlr(nullptr)
{}
CScn::~CScn()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::objEND; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			//백터 i 그룹의 j 물체 삭제, 각 씬의 new동적할당으로 생긴 녀석들
			delete m_arrObj[i][j];
		}
	}
	//벡터는 안지워주나? 생성소멸자 따로 정의안하면 알아서 세팅됨, Scn의 맴버이므로 해당클래스 소멸시 같이 순차적으로 알아서 지워짐
}


void CScn::Scn_start()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::objEND; ++i)
		{
			for (size_t j = 0; j < m_arrObj[i].size(); ++j)
			{
					m_arrObj[i][j]->Obj_start();
			}
		}
}

void CScn::update()
{
	//for (UINT i = 0; i < (UINT)OBJ_TYPE::objEND; ++i)
	//{
	//	for (size_t j = 0; j < m_arrObj[i].size(); ++j)
	//	{
	//		if (!m_arrObj[i][j]->Obj_isDlt()) //삭제예정은 거르기
	//		{
	//			m_arrObj[i][j]->update();
	//		}
	//	}
	//}
}

void CScn::finalupdate() //렌더직전
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::objEND; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScn::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::objEND; ++i)
	{
		if ((UINT)OBJ_TYPE::TL == i)
		{
			renderTL(_dc);
			continue;
		}

		//효과적인 삭제를 위한, erase 함수 사용을 위해 iterator 선언
		vector<CObj*>::iterator iter = m_arrObj[i].begin(); //[j]를 백터로 검사

		for (; iter != m_arrObj[i].end(); )
		{
			if (!((*iter)->Obj_isDlt())) //삭제예정은 거르기
			{
				(*iter)->render(_dc); //m_arrObj[STT][DFT]->render(_dc)
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}
void CScn::renderTL(HDC _dc)
{
	const vector<CObj*>& vecTile = Scn_getObjGroup(OBJ_TYPE::TL);

	Vec2 vCamLook = mgr_Cam::GetInst()->getCurLookat(); //우하단좌표
	Vec2 vResolution = CCore::GetInst()->getResolution(); //우하단좌표
	Vec2 vLeftTop = vCamLook - vResolution / 2.f;

	int iTileSize = TILE_SIZE;
	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;

	int iClientWidth = ((int)vResolution.x / iTileSize) + 1;
	int iClientHeight = ((int)vResolution.y / iTileSize) + 1;

	for (int iCurRow = iLTRow; iCurRow < (iLTRow+iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol+iClientWidth); ++iCurCol)
		{
			if (iCurRow < 0 
			 || m_iTileX <= iCurCol 
			 || iCurCol < 0
			 || m_iTileY <= iCurRow )
			{
				continue;
			}
			int iIdx = (m_iTileX * iCurRow) + iCurCol;
			vecTile[iIdx]->render(_dc);
		}

	}
}

void CScn::Scn_clearAll()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::objEND; ++i)
	{
		Scn_clearObj((OBJ_TYPE)i);
	}
}

void CScn::Scn_createTile(UINT _iXcount, UINT _iYcount)
{
	Scn_clearObj(OBJ_TYPE::TL);

	m_iTileX = _iXcount;
	m_iTileY = _iYcount;
	CRsc_01TXR* pTileTXR = mgr_Rsc::GetInst()->loadTxr(L"TileTXR", L"texture\\tile\\tile256_128x128.bmp");

	//타일 생성
	for (int j = 0; j < _iYcount; ++j)
	{
		for (int i = 0; i < _iXcount; ++i)
		{
			CObj_04TL* pTile = new CObj_04TL();
			pTile->Obj_setPos(Vec2((float)(i * TILE_SIZE), (float)(j * TILE_SIZE)));
			pTile->setTileTXR(pTileTXR);

			Scn_addObj(pTile, OBJ_TYPE::TL);
		}
	}
}

void CScn::loadTile(const wstring& _strRltvPath)
{
	wstring strFilepath = mgr_Path::GetInst()->getCttPath();
	strFilepath += _strRltvPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilepath.c_str(), L"rb");
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	Scn_createTile(xCount, yCount);

	const vector<CObj*>& vecTile = Scn_getObjGroup(OBJ_TYPE::TL);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CObj_04TL*)vecTile[i])->load(pFile);
	}

	fclose(pFile);
}
