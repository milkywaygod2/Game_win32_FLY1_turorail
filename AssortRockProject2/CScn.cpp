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
			//���� i �׷��� j ��ü ����, �� ���� new�����Ҵ����� ���� �༮��
			delete m_arrObj[i][j];
		}
	}
	//���ʹ� �������ֳ�? �����Ҹ��� ���� ���Ǿ��ϸ� �˾Ƽ� ���õ�, Scn�� �ɹ��̹Ƿ� �ش�Ŭ���� �Ҹ�� ���� ���������� �˾Ƽ� ������
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
	//		if (!m_arrObj[i][j]->Obj_isDlt()) //���������� �Ÿ���
	//		{
	//			m_arrObj[i][j]->update();
	//		}
	//	}
	//}
}

void CScn::finalupdate() //��������
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

		//ȿ������ ������ ����, erase �Լ� ����� ���� iterator ����
		vector<CObj*>::iterator iter = m_arrObj[i].begin(); //[j]�� ���ͷ� �˻�

		for (; iter != m_arrObj[i].end(); )
		{
			if (!((*iter)->Obj_isDlt())) //���������� �Ÿ���
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

	Vec2 vCamLook = mgr_Cam::GetInst()->getCurLookat(); //���ϴ���ǥ
	Vec2 vResolution = CCore::GetInst()->getResolution(); //���ϴ���ǥ
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

	//Ÿ�� ����
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
