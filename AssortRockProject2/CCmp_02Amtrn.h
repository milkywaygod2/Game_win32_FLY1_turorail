#pragma once
class CObj;
class CCmp_02Amtr;
class CRsc_01TXR;

struct tAmtrnInfo {
	Vec2	vLTop;
	Vec2	vImageSize;
	float	fDuration;

	Vec2	vOffset; //2D 아이소뷰 구현용
};

class CCmp_02Amtrn
{
private:
	wstring				m_strName;
	CCmp_02Amtr*		m_pAmtr;
	CRsc_01TXR*			m_pTxr;
	vector<tAmtrnInfo>	m_vecFrmInfo;
	int					m_iCurFrm;

	float				m_fAccTime;
	bool				m_bFinish;

private:
	void setName(const wstring& _strName) { m_strName = _strName; }
public:
	const wstring& getName() { return m_strName; }
	bool isFinish() { return m_bFinish; }
	void setFrm(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAmtrnInfo& getFrm(int _iIdx) { 
		//assert(_iIdx >= 0 && _iIdx < m_vecFrmInfo.size()); 
		return m_vecFrmInfo[_iIdx]; } //& 받아간쪽에서 수정의도

	UINT getMaxFrm() { return (UINT)m_vecFrmInfo.size(); }

public:
	void create(CRsc_01TXR* _pTxr, 
		Vec2 _vLTop, Vec2 _vImageSize, Vec2 _vStep, 
		float fDuration, UINT _iFrameCount);
	void update();
	void render(HDC _dc);

public:
	void saveAmtrn(const wstring& _strRltvPath);
	void loadAmtrn(const wstring& _strRltvPath);

public:
	CCmp_02Amtrn();
	~CCmp_02Amtrn();

	friend class CCmp_02Amtr;

};

