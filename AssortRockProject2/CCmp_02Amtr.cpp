#include "pch.h"
#include "CCmp_02Amtr.h"


CCmp_02Amtr::CCmp_02Amtr()
	: m_pOwner(nullptr)
	, m_pCurAmtrn(nullptr)
	, m_bRepeat(false) 
{}
CCmp_02Amtr::~CCmp_02Amtr()
{
	Freq_clearMap(m_mapAmtrn);
}




void CCmp_02Amtr::createAmtrn(
	const wstring& _strName, CRsc_01TXR* _pTxr, 
	Vec2 _vLTop, Vec2 _vImageSize, Vec2 _vStep, 
	float fDuration, UINT _iFrameCount)
{
	CCmp_02Amtrn* pAmtrn = findAmtrn(_strName);
	assert(nullptr == pAmtrn);
		
	pAmtrn = new CCmp_02Amtrn;
	pAmtrn->setName(_strName);
	pAmtrn->m_pAmtr = this;
	pAmtrn->create(_pTxr, 
		_vLTop, _vImageSize, _vStep, 
		fDuration, _iFrameCount);

	m_mapAmtrn.insert(make_pair(_strName, pAmtrn));
}

void CCmp_02Amtr::loadAmtr(const wstring& _strRltvPath)
{
	CCmp_02Amtrn* pAmtrn = new CCmp_02Amtrn;
	pAmtrn->loadAmtrn(_strRltvPath);
	pAmtrn->m_pAmtr = this; //연결만 해주고 나머지는 애니메이션 정보
	m_mapAmtrn.insert(make_pair(pAmtrn->getName(), pAmtrn));
}

CCmp_02Amtrn* CCmp_02Amtr::findAmtrn(const wstring& _strName)
{
	map<wstring, CCmp_02Amtrn*>::iterator iter = m_mapAmtrn.find(_strName);
	if (iter == m_mapAmtrn.end())
		return nullptr;
	return iter->second;
}

void CCmp_02Amtr::playAmtrn(const wstring& _strName, bool _bRepeat)
{
	m_pCurAmtrn = findAmtrn(_strName);
	m_bRepeat = _bRepeat;
}
void CCmp_02Amtr::update()
{
	
}

void CCmp_02Amtr::finalupdate()
{
	if (nullptr != m_pCurAmtrn)
	{
		m_pCurAmtrn->update();

		if (m_bRepeat && m_pCurAmtrn->isFinish())
		{
			m_pCurAmtrn->setFrm(0);
		}
	}
}

void CCmp_02Amtr::render(HDC _dc)
{
	if (nullptr != m_pCurAmtrn)
		m_pCurAmtrn->render(_dc);
}
