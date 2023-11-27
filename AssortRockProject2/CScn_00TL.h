#pragma once
#include "CScn.h"

class CScn_00TL 
	: public CScn
{
private:
	CObj_05UI* m_pUI;

public:
	void setTileIdx();
	 
	void saveTileData();
	void saveTile(const wstring& _strFilePath);
	void loadTileData();

public:
	virtual void Enter();
	virtual void update();
	virtual void Exit();

public:
	CScn_00TL();
	~CScn_00TL();


};

