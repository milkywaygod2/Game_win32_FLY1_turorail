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


class CRsc_01TXR; //전방선언!!!!★
//class CCmp_02Amtrn;

class CObj_01PLR :public CObj
{
private:
	//CRsc_01TXR*	m_pTxr; 직접 BitBlt하는 게 아니라 애니메이션 소환
	int m_iDir; //플레이어 방향
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
	void updateGravityPLR(); //정석은 매니저로 관리하거나, 컴포넌트화

	virtual void Obj_onCllsEnter(CCmp_01Cldr* _pCllsCldr);

	CLONE(CObj_01PLR);

public:
	CObj_01PLR();
	CObj_01PLR(const CObj_01PLR& _origin) //얕은 복사 콜리전 그대로(부모는 깊은복사)
		: CObj(_origin)
		//, m_pTxr(_origin.m_pTxr)
	{}

	virtual ~CObj_01PLR();
};

