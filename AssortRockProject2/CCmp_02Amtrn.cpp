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

		m_vecFrmInfo.push_back(FrmInfo); //������迭��ġ!
	}
}

void CCmp_02Amtrn::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObj* pOwner = m_pAmtr->getObj();
	Vec2 vPos = pOwner->Obj_getPos();
	vPos += m_vecFrmInfo[m_iCurFrm].vOffset; //2D ���̼Һ� ������

	//ī�޶���ġ����(��������ǥ)
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
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb"); //������
	assert(pFile);

	//1.Animation�̸� ���� (����������ȭ)
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end()); //wstring(2����Ʈ����)�� string(1����Ʈ����)�� �ٲ���
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");

	//2.�ؽ���
	fprintf(pFile, "[Texture Key]\n");
	strName = string(m_strName.begin(), m_strName.end()); 
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTxr->getRltvPath().begin(), m_pTxr->getRltvPath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n\n");

	//3.������ ����
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d", (int)m_vecFrmInfo.size());
	fprintf(pFile, "\n\n");

	//4.��� ������ ����
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
	/* ���̳ʸ� �ε����
	//1.Animation�̸� ����
	saveWstring(m_strName, pFile);

	//2.�ؽ���
	saveWstring(m_pTxr->getKey(), pFile);
	saveWstring(m_pTxr->getRltvPath(), pFile);

	//3.������ �� ��
	size_t iFrameCount = m_vecFrmInfo.size();
	fwrite(&iFrameCount, sizeof(size_t), 1, pFile);

	//3.��� ������ ����
	fwrite(m_vecFrmInfo.data(), sizeof(tAmtrnInfo), iFrameCount, pFile);
	*/

	fclose(pFile);
}

void CCmp_02Amtrn::loadAmtrn(const wstring& _strRltvPath)
{
	wstring strFilePath = mgr_Path::GetInst()->getCttPath();
	strFilePath += _strRltvPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb"); //�б���
	assert(pFile);

	//1.Animation�̸� ���� (����������ȭ)
	string str;
	char szBuff[256] = {};

	fscanfSpace(szBuff, pFile);
	fscanfSpace(szBuff, pFile);
	str = szBuff;
	m_strName = wstring(str.begin(), str.end());
	
	//2.�ؽ���
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

	//3.������ ����
	fscanfSpace(szBuff, pFile);
	fscanfSpace(szBuff, pFile);
	int iFramecount = 0;
	fscanf_s(pFile, "%d", &iFramecount);

	//4.��������� ����
	tAmtrnInfo tAmtrn = {};
	for (int i = 0; i < iFramecount; ++i)
	{
		POINT pt = {};
		while (true)
		{
			fscanfSpace(szBuff, pFile);

			if (!strcmp("[Frame Index]",szBuff)) //���Լ� ������ 0��ȯ
			{
				fscanf_s(pFile, "%d", &pt.x);
			}
			else if (!strcmp("[Left Top]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y); //������ �Ѿ�� [,]�� �ȵ�.
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

	/* ���̳ʸ� ������
	//1.Animation�̸� �о����
	loadWstring(m_strName, pFile);

	//2.�ؽ���
	wstring strTxrKey, strTxrRltvPath;
	loadWstring(strTxrKey, pFile);
	loadWstring(strTxrRltvPath, pFile);
	m_pTxr = mgr_Rsc::GetInst()->loadTxr(strTxrKey, strTxrRltvPath);

	//3.������ �� ��
	size_t iFrameCount = 0;
	fread(&iFrameCount, sizeof(size_t), 1, pFile);

	//3.��� ������ ����
	m_vecFrmInfo.resize(iFrameCount); //for�� ���� ȿ�����ϼ�����
	fread(m_vecFrmInfo.data(), sizeof(tAmtrnInfo), iFrameCount, pFile);
	*/

	fclose(pFile);

}

void CCmp_02Amtrn::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT; //�귯�� �ð�

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
		m_fAccTime = m_fAccTime - m_vecFrmInfo[m_iCurFrm].fDuration; //�ð����ռ� ����
	}
}