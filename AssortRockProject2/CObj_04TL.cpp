#include "CObj_04TL.h"

CObj_04TL::CObj_04TL()
	: m_pTileTXR(nullptr)
	, m_iTileIdx(5)
{
	Obj_setScale(Vec2(TILE_SIZE, TILE_SIZE));
}
CObj_04TL::~CObj_04TL(){}

void CObj_04TL::update()
{
}

void CObj_04TL::render(HDC _dc)
{
	Vec2 vRenderPos = mgr_Cam::GetInst()->getRenderPos(Obj_getPos());
	Vec2 vScale = Obj_getScale();

	if (nullptr == m_pTileTXR || -1 == m_iTileIdx)
	{
		Rectangle(_dc
			, int(vRenderPos.x)
			, int(vRenderPos.y)
			, int(vRenderPos.x + vScale.x)
			, int(vRenderPos.y + vScale.y)
		);
	}
	else
	{
		UINT iWidth = m_pTileTXR->Width();
		UINT iHeight = m_pTileTXR->Height();
		UINT iMaxCol = iWidth / TILE_SIZE;  //열
		UINT iMaxRow = iHeight / TILE_SIZE; //행
		UINT iCurCol = (UINT)m_iTileIdx % iMaxCol;
		UINT iCurRow = (UINT)m_iTileIdx / iMaxCol;

		if (iCurRow >= iMaxRow) //나머지값은 몫보다 커질 수 없음.			assert(nullptr);
			assert(nullptr);

		BitBlt(_dc
			, int(vRenderPos.x)
			, int(vRenderPos.y)
			, int(vScale.x)
			, int(vScale.y)
			, m_pTileTXR->getDC()
			, iCurCol * TILE_SIZE
			, iCurRow * TILE_SIZE
			, SRCCOPY);
	}

	
}

void CObj_04TL::save(FILE* _pFile)
{
	fwrite(&m_iTileIdx, sizeof(int), 1, _pFile);
}

void CObj_04TL::load(FILE* _pFile)
{
	fread(&m_iTileIdx, sizeof(int), 1, _pFile);
}
