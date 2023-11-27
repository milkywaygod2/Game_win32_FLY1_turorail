#pragma once
class CCmp_03RgdB
{
private:
	CObj*	m_pOwner;

	Vec2	m_vForce; //방향과 힘의 크기
	Vec2	m_vAccel; //가속도
	Vec2	m_vAccel_G; //중력가속도
	Vec2	m_vVelo; //속도 (방향포함)

	//Vec2	m_vVeloMax; //최대속도,공기저항대신
	float	m_fSpeedMax; //최대속력,공기저항대신
	//float	m_fSpeed;	//**속력 (순간)

	float	m_fMass; //질량
	// F = m * a
	// V += a * DT

	float	m_fFric; //정지마찰계수
	float	m_fFricMov; //운동마찰계수



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
	//중력가속도는 상호간에 질량의 제곱에 반비례 하기때문에 F=ma에도 불구, 사실상 같은 힘으로 작용

public:
	void finalupdate();

private:
	void moveRgdB();

public:
	CCmp_03RgdB();
	~CCmp_03RgdB();
	friend class CObj;
};

