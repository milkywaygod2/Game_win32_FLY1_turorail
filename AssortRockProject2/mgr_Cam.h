#pragma once

class Obj;

enum class EFFECT_CAM
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tEffect_Cam
{
	EFFECT_CAM	eEffect;
	float		fDuration;
	float		fCurTime;
};

class mgr_Cam
{
	SINGLETON(mgr_Cam);

private:
	Vec2	m_vPsyLookat;	//카메라 지향	 (조작)
	Vec2	m_vPsy1Lookat;	//카메라 지향1	 (조작)
	Vec2	m_vCurLookat;	//카메라현재 결과 (반영)
	Vec2	m_vPrevLookat;	//카메라이전 결과 (전반영)

	Vec2	m_pPlrPos;
	CObj*	m_pTargetObj;
	Vec2	m_vDiff; //해상도중심과 카메라중심간 차이

	float	m_fTime;	//카메라 반영 시간
	float	m_fSpeed;	//카메라 이동 속도
	float	m_fAccTime;	//이동 누적 시간 

	list<tEffect_Cam>		m_listEffectCam;
	CRsc_01TXR*				m_pVeilTxr;


public:
	void setPsyLookat(Vec2 _vPsyLookat) 
	{ 
		m_vPsyLookat = _vPsyLookat; 

		float fMoveDist = (m_vPsyLookat - m_vPrevLookat).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	/*void setPsy1Lookat(Vec2 _vPsyLookat)
	{
		m_vPsy1Lookat = _vPsyLookat;

		float fMoveDist1 = (m_vPsy1Lookat - m_vPsyLookat).Length();
		m_fSpeed = fMoveDist1 / m_fTime;
		m_fAccTime = 0.f;
	}*/

	Vec2 getCurLookat() { return m_vCurLookat; }

	void setPlrPos(Vec2 _vPlrPos) { m_pPlrPos = _vPlrPos; }
	void setTarget(CObj* _pTargetObj) { m_pTargetObj = _pTargetObj; }
	
	Vec2 getRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; } //카메라를 기준으로 오브젝트 재배치
	Vec2 getRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; } //오브젝트 기준으로 카메라 재배치

	void fadein(float _fDuration) {
		tEffect_Cam ef = {};
		ef.eEffect = EFFECT_CAM::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;
		m_listEffectCam.push_back(ef);
		if (0.f == _fDuration)
			assert(nullptr);
	}
	void fadeout(float _fDuration) {
		tEffect_Cam ef = {};
		ef.eEffect = EFFECT_CAM::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;
		m_listEffectCam.push_back(ef);
		if (0.f == _fDuration)
			assert(nullptr);
	}

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void	calculateDiff();

	
};

