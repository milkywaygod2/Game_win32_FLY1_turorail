#pragma once
class CRsc
{
private:
	wstring m_rscKey;		//���ҽ� Ű
	wstring m_rscRltvPath;		//���ҽ� �����
public:
	void setKey(const wstring& _rscKey) { m_rscKey = _rscKey; }
	void setRltvPath(const wstring& _rscRltvPath) { m_rscRltvPath = _rscRltvPath; }
	const wstring& getKey() { return m_rscKey; }
	const wstring& getRltvPath() { return m_rscRltvPath; }



public:
	CRsc();
	virtual ~CRsc();

};

