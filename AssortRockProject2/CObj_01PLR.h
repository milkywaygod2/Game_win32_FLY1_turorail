#pragma once
#include "CObj.h"

enum class PLR_STATE
{
	IDLE,
	FLY,
	ATTACK,
	WALK,
	JUMP,
	DEAD,
};

enum class PLR_STATE_ATTACK
{
	NORMAL_ATT_1,
	NORMAL_ATT_2,
	NORMAL_ATT_3,

	SKILL_ATT_1,
	// ....
};


class CRsc_01TXR; //���漱��!!!!��
//class CCmp_02Amtrn;

class CObj_01PLR :public CObj
{
private:
	//CRsc_01TXR*	m_pTxr; ���� BitBlt�ϴ� �� �ƴ϶� �ִϸ��̼� ��ȯ
	int m_iDir; //�÷��̾� ����
	int m_iDirPrev;
	PLR_STATE m_eCurStatePLR;
	PLR_STATE m_ePrevStatePLR;


public:
	virtual void update();
	virtual void render(HDC _dc);

private:
	void createMSL();
	void updateMovePLR();
	void updateStatePLR();
	void updateAmtrnPLR();
	void updateGravityPLR(); //������ �Ŵ����� �����ϰų�, ������Ʈȭ

	virtual void Obj_onCllsEnter(CCmp_01Cldr* _pCllsCldr);

	CLONE(CObj_01PLR);

public:
	CObj_01PLR();
	CObj_01PLR(const CObj_01PLR& _origin) //���� ���� �ݸ��� �״��(�θ�� ��������)
		: CObj(_origin)
		//, m_pTxr(_origin.m_pTxr)
	{}

	virtual ~CObj_01PLR();
};

