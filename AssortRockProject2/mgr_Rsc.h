#pragma once

class CRsc;
class CRsc_01TXR;
class CRsc_02SND;

class mgr_Rsc
{
	SINGLETON(mgr_Rsc);
private:
	map<wstring, CRsc*> m_mapTxr;
	map<wstring, CRsc*> m_mapSnd;




public:
	CRsc_01TXR* loadTxr(const wstring& _rscKey, const wstring& _rscRltvPath);
	CRsc_01TXR* createTxr(const wstring& _rscKey, UINT _iWidth, UINT _iHeight);
	CRsc_01TXR* findTxr(const wstring& _rscKey);

	CRsc_02SND* loadSnd(const wstring& _rscKey, const wstring& _rscRltvPath);
	CRsc_02SND* findSnd(const wstring& _rscKey);
};

