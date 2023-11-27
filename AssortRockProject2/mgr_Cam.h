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
	Vec2	m_vPsyLookat;	//ī�޶� ����	 (����)
	Vec2	m_vPsy1Lookat;	//ī�޶� ����1	 (����)
	Vec2	m_vCurLookat;	//ī�޶����� ��� (�ݿ�)
	Vec2	m_vPrevLookat;	//ī�޶����� ��� (���ݿ�)

	Vec2	m_pPlrPos;
	CObj*	m_pTargetObj;
	Vec2	m_vDiff; //�ػ��߽ɰ� ī�޶��߽ɰ� ����

	float	m_fTime;	//ī�޶� �ݿ� �ð�
	float	m_fSpeed;	//ī�޶� �̵� �ӵ�
	float	m_fAccTime;	//�̵� ���� �ð� 

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
	
	Vec2 getRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; } //ī�޶� �������� ������Ʈ ���ġ
	Vec2 getRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; } //������Ʈ �������� ī�޶� ���ġ

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

