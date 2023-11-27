#pragma once
class CCmp_04Grbt
{
private:
	CObj*	m_pOwner;

	bool	m_bGround; //¶¥¿¡ ´ê¾Ò´ÂÁö ¿©ºÎ

public:
	void setGRD(bool _b) { 
		m_bGround = _b; 
		if (m_bGround)
		{
			Vec2 vVelo = m_pOwner->Obj_getRgdB()->getVelo();
			m_pOwner->Obj_getRgdB()->setVelo(Vec2(vVelo.x, 0.f));
		}
	}
	bool getGRD() { return m_bGround; }

public:
	void finalupdate();

public:
	CCmp_04Grbt();
	~CCmp_04Grbt();
	friend class CObj;
};

