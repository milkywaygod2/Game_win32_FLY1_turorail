#pragma once
class CRsc
{
private:
	wstring m_rscKey;		//리소스 키
	wstring m_rscRltvPath;		//리소스 상대경로
public:
	void setKey(const wstring& _rscKey) { m_rscKey = _rscKey; }
	void setRltvPath(const wstring& _rscRltvPath) { m_rscRltvPath = _rscRltvPath; }
	const wstring& getKey() { return m_rscKey; }
	const wstring& getRltvPath() { return m_rscRltvPath; }



public:
	CRsc();
	virtual ~CRsc();

};

