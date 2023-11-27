#pragma once
class CObj_06GRD : public CObj
{
private:
	virtual void Obj_start();
	virtual void update();

public:
	virtual void Obj_onCllsEnter(CCmp_01Cldr* _pCllsCldr);
	virtual void Obj_onClls(CCmp_01Cldr* _pCllsCldr);
	virtual void Obj_onCllsExit(CCmp_01Cldr* _pCllsCldr);


	CLONE(CObj_06GRD);
public:
	CObj_06GRD();
	~CObj_06GRD();
};

