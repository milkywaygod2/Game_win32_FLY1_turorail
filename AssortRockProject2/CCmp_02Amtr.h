#pragma once
class CObj;
class CCmp_02Amtrn;


class CCmp_02Amtr
{
private:
	CObj*						m_pOwner;

	map<wstring,CCmp_02Amtrn*>	m_mapAmtrn;
	CCmp_02Amtrn*				m_pCurAmtrn;
	bool						m_bRepeat;

public:
	CObj* getObj() { return m_pOwner; }

public:
	void createAmtrn(const wstring& _strName, CRsc_01TXR* _pTxr, 
		Vec2 _vLTop, Vec2 _vImageSize, Vec2 _vStep, 
		float fDuration, UINT _iFrameCount);
	void loadAmtr(const wstring& _strRltvPath);
	CCmp_02Amtrn* findAmtrn(const wstring& _strName);
	void playAmtrn(const wstring& _strName, bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);

public:
	CCmp_02Amtr();
	~CCmp_02Amtr();

	friend class CObj;
	friend class CScn;
};

