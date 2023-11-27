#include "pch.h"
#include "mgr_Rsc.h"
mgr_Rsc::mgr_Rsc(){}
mgr_Rsc::~mgr_Rsc()
{
	Freq_clearMap(m_mapTxr);
}

CRsc_01TXR* mgr_Rsc::loadTxr(const wstring& _rscKey, const wstring& _rscRltvPath)
{
	CRsc_01TXR* pTxr = findTxr(_rscKey);
	if (nullptr != pTxr)
	{
		return pTxr;
	}

	wstring rscFilePath = mgr_Path::GetInst()->getCttPath();
	rscFilePath += _rscRltvPath;

	pTxr = new CRsc_01TXR;
	pTxr->Load(rscFilePath);

	pTxr->setKey(_rscKey);
	pTxr->setRltvPath(_rscRltvPath);

	m_mapTxr.insert(make_pair(_rscKey, pTxr));
	return pTxr;
	
}

CRsc_01TXR* mgr_Rsc::createTxr(const wstring& _rscKey, UINT _iWidth, UINT _iHeight)
{
	CRsc_01TXR* pTxr = findTxr(_rscKey);
	if (nullptr != pTxr) {return pTxr; }

	pTxr = new CRsc_01TXR;
	pTxr->create(_iWidth, _iHeight);
	pTxr->setKey(_rscKey);

	m_mapTxr.insert(make_pair(_rscKey, pTxr));
	return pTxr;
}

CRsc_01TXR* mgr_Rsc::findTxr(const wstring& _rscKey)
{
	map<wstring, CRsc*>::iterator iter = m_mapTxr.find(_rscKey);
	if (iter == m_mapTxr.end())
	{
		return nullptr;
	}
	return (CRsc_01TXR*)iter->second;
}

CRsc_02SND* mgr_Rsc::loadSnd(const wstring& _rscKey, const wstring& _rscRltvPath)
{
	CRsc_02SND* pSnd = findSnd(_rscKey);
	if (nullptr != pSnd)
	{
		return pSnd;
	}

	wstring rscFilePath = mgr_Path::GetInst()->getCttPath();
	rscFilePath += _rscRltvPath;

	pSnd = new CRsc_02SND;
	pSnd->loadSound(rscFilePath);

	pSnd->setKey(_rscKey);
	pSnd->setRltvPath(_rscRltvPath);

	m_mapSnd.insert(make_pair(_rscKey, pSnd));
	return pSnd;
}

CRsc_02SND* mgr_Rsc::findSnd(const wstring& _rscKey)
{
	map<wstring, CRsc*>::iterator iter = m_mapSnd.find(_rscKey);
	if (iter == m_mapSnd.end())
	{
		return nullptr;
	}
	return (CRsc_02SND*)iter->second;
}
