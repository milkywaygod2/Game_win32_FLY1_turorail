#include "pch.h"
#include "CCmp_02Amtrn.h"


CCmp_02Amtrn::CCmp_02Amtrn()
	: m_pAmtr(nullptr)
	, m_pTxr(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
{}
CCmp_02Amtrn::~CCmp_02Amtrn(){}

void CCmp_02Amtrn::create(CRsc_01TXR* _pTxr,
	Vec2 _vLTop, Vec2 _vImageSize, Vec2 _vStep, 
	float fDuration, UINT _iFrameCount)
{
	m_pTxr = _pTxr;
	tAmtrnInfo FrmInfo = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		FrmInfo.fDuration = fDuration;
		FrmInfo.vImageSize = _vImageSize;
		FrmInfo.vLTop = _vLTop + _vStep * (float)i;

		m_vecFrmInfo.push_back(FrmInfo); //★저장배열위치!
	}
}

void CCmp_02Amtrn::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObj* pOwner = m_pAmtr->getObj();
	Vec2 vPos = pOwner->Obj_getPos();
	vPos += m_vecFrmInfo[m_iCurFrm].vOffset; //2D 아이소뷰 구현용

	//카메라위치보정(렌더링좌표)
	Vec2 vRenderPos = mgr_Cam::GetInst()->getRenderPos(vPos);

	TransparentBlt(_dc
		,(int)( vRenderPos.x - m_vecFrmInfo[m_iCurFrm].vImageSize.x / 2.f )
		,(int)( vRenderPos.y - m_vecFrmInfo[m_iCurFrm].vImageSize.y / 2.f	)
		,(int)( m_vecFrmInfo[m_iCurFrm].vImageSize.x					)
		,(int)( m_vecFrmInfo[m_iCurFrm].vImageSize.y					)
		, m_pTxr->getDC()										
		,(int)( m_vecFrmInfo[m_iCurFrm].vLTop.x						)
		,(int)( m_vecFrmInfo[m_iCurFrm].vLTop.y						)
		,(int)( m_vecFrmInfo[m_iCurFrm].vImageSize.x					)
		,(int)( m_vecFrmInfo[m_iCurFrm].vImageSize.y					)
		, RGB(255,0,255)
		);
}

void CCmp_02Amtrn::saveAmtrn(const wstring& _strRltvPath)
{
	wstring strFilePath = mgr_Path::GetInst()->getCttPath();
	strFilePath += _strRltvPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb"); //쓰기모드
	assert(pFile);

	//1.Animation이름 저장 (데이터직렬화)
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end()); //wstring(2바이트문자)를 string(1바이트문자)로 바꿔줌
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");

	//2.텍스쳐
	fprintf(pFile, "[Texture Key]\n");
	strName = string(m_strName.begin(), m_strName.end()); 
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTxr->getRltvPath().begin(), m_pTxr->getRltvPath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");

	//3.프레임 개수
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d", (int)m_vecFrmInfo.size());
	fprintf(pFile, "\n\n");

	//4.모든 프레임 정보
	for (size_t i = 0; i < m_vecFrmInfo.size(); ++i)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d", (int)i);
		fprintf(pFile, "\n");

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d %d", (int)m_vecFrmInfo[i].vLTop.x, (int)m_vecFrmInfo[i].vLTop.y);
		fprintf(pFile, "\n");

		fprintf(pFile, "[Image Size]\n");
		fprintf(pFile, "%d %d", (int)m_vecFrmInfo[i].vImageSize.x, (int)m_vecFrmInfo[i].vImageSize.y);
		fprintf(pFile, "\n");

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d", (int)m_vecFrmInfo[i].vOffset.x, (int)m_vecFrmInfo[i].vOffset.y);
		fprintf(pFile, "\n");

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f", (float)m_vecFrmInfo[i].fDuration);
		fprintf(pFile, "\n\n");
	}
	/* 바이너리 로딩방식
	//1.Animation이름 저장
	saveWstring(m_strName, pFile);

	//2.텍스쳐
	saveWstring(m_pTxr->getKey(), pFile);
	saveWstring(m_pTxr->getRltvPath(), pFile);

	//3.프레임 개 수
	size_t iFrameCount = m_vecFrmInfo.size();
	fwrite(&iFrameCount, sizeof(size_t), 1, pFile);

	//3.모든 프레임 정보
	fwrite(m_vecFrmInfo.data(), sizeof(tAmtrnInfo), iFrameCount, pFile);
	*/

	fclose(pFile);
}

void CCmp_02Amtrn::loadAmtrn(const wstring& _strRltvPath)
{
	wstring strFilePath = mgr_Path::GetInst()->getCttPath();
	strFilePath += _strRltvPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb"); //읽기모드
	assert(pFile);

	//1.Animation이름 저장 (데이터직렬화)
	string str;
	char szBuff[256] = {};

	fscanfSpace(szBuff, pFile);
	fscanfSpace(szBuff, pFile);
	str = szBuff;
	m_strName = wstring(str.begin(), str.end());
	
	//2.텍스쳐
	fscanfSpace(szBuff, pFile);
	fscanfSpace(szBuff, pFile);
	fscanfSpace(szBuff, pFile);
	str = szBuff;
	wstring strTxrKey = wstring(str.begin(), str.end());

	fscanfSpace(szBuff, pFile);
	fscanfSpace(szBuff, pFile);
	fscanfSpace(szBuff, pFile);
	str = szBuff;
	wstring strTxrPath = wstring(str.begin(), str.end());

	m_pTxr = mgr_Rsc::GetInst()->loadTxr(strTxrKey, strTxrPath);

	//3.프레임 개수
	fscanfSpace(szBuff, pFile);
	fscanfSpace(szBuff, pFile);
	int iFramecount = 0;
	fscanf_s(pFile, "%d", &iFramecount);

	//4.모든프레임 정보
	tAmtrnInfo tAmtrn = {};
	for (int i = 0; i < iFramecount; ++i)
	{
		POINT pt = {};
		while (true)
		{
			fscanfSpace(szBuff, pFile);

			if (!strcmp("[Frame Index]",szBuff)) //비교함수 같으면 0반환
			{
				fscanf_s(pFile, "%d", &pt.x);
			}
			else if (!strcmp("[Left Top]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y); //공백은 넘어가줌 [,]는 안됨.
				tAmtrn.vLTop = pt;
			}
			else if (!strcmp("[Image Size]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				tAmtrn.vImageSize = pt;
			}
			else if (!strcmp("[Offset]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				tAmtrn.vOffset = pt;
			}
			else if (!strcmp("[Duration]", szBuff))
			{
				fscanf_s(pFile, "%f", &tAmtrn.fDuration);
				break;
			}
		}
		m_vecFrmInfo.push_back(tAmtrn);
	}

	/* 바이너리 저장방식
	//1.Animation이름 읽어오기
	loadWstring(m_strName, pFile);

	//2.텍스쳐
	wstring strTxrKey, strTxrRltvPath;
	loadWstring(strTxrKey, pFile);
	loadWstring(strTxrRltvPath, pFile);
	m_pTxr = mgr_Rsc::GetInst()->loadTxr(strTxrKey, strTxrRltvPath);

	//3.프레임 개 수
	size_t iFrameCount = 0;
	fread(&iFrameCount, sizeof(size_t), 1, pFile);

	//3.모든 프레임 정보
	m_vecFrmInfo.resize(iFrameCount); //for문 보다 효율적일수있음
	fread(m_vecFrmInfo.data(), sizeof(tAmtrnInfo), iFrameCount, pFile);
	*/

	fclose(pFile);

}

void CCmp_02Amtrn::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT; //흘러간 시간

	if (m_fAccTime > m_vecFrmInfo[m_iCurFrm].fDuration)
	{
		++m_iCurFrm; 
		if (m_iCurFrm >= m_vecFrmInfo.size())
		{
			m_iCurFrm = -1; 
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}
		m_fAccTime = m_fAccTime - m_vecFrmInfo[m_iCurFrm].fDuration; //시간정합성 관리
	}
}