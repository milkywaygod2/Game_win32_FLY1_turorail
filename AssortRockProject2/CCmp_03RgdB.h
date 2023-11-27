#pragma once
class CCmp_03RgdB
{
private:
	CObj*	m_pOwner;

	Vec2	m_vForce; //����� ���� ũ��
	Vec2	m_vAccel; //���ӵ�
	Vec2	m_vAccel_G; //�߷°��ӵ�
	Vec2	m_vVelo; //�ӵ� (��������)

	//Vec2	m_vVeloMax; //�ִ�ӵ�,�������״��
	float	m_fSpeedMax; //�ִ�ӷ�,�������״��
	//float	m_fSpeed;	//**�ӷ� (����)

	float	m_fMass; //����
	// F = m * a
	// V += a * DT

	float	m_fFric; //�����������
	float	m_fFricMov; //��������



public:
	void addForce(Vec2 _vF) { m_vForce += _vF; }

	void setMass(float _fMass) { m_fMass = _fMass; }
	float getMass() { return m_fMass; }

	void setVelo(Vec2 _v) { m_vVelo = _v; }
	Vec2 getVelo() { return m_vVelo; }
	void addVelo(Vec2 _v) { m_vVelo += _v; }

	void setSpeedMax(float _s) { m_fSpeedMax = _s; }
	float getSpeed() { return m_vVelo.Length(); }

	void setAccel_G(Vec2 _vAccel_G) { m_vAccel_G = _vAccel_G; } 
	//�߷°��ӵ��� ��ȣ���� ������ ������ �ݺ�� �ϱ⶧���� F=ma���� �ұ�, ��ǻ� ���� ������ �ۿ�

public:
	void finalupdate();

private:
	void moveRgdB();

public:
	CCmp_03RgdB();
	~CCmp_03RgdB();
	friend class CObj;
};

