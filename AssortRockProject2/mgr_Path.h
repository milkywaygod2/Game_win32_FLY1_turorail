#pragma once
class mgr_Path
{
	SINGLETON(mgr_Path);

private:
	wchar_t		m_szCttPath[256];
	wchar_t		m_szRltvPath[256];

public:
	void init();
	const wchar_t* getCttPath() { return m_szCttPath; }
	wstring getRltvPath(const wchar_t* _filepath);

};

  