#pragma once
class CCmp_01Cldr
{
friend class CObj;

private:
	static UINT g_iNextID;

	CObj*			m_pOwner; //���ڸ� �����ΰ� ���� Obj�����ڰ� ��Ī����

	Vec2			m_vOffsetPos; //�ݸ����� �������� ���� �ٴ��ʿ� ��
	Vec2			m_vCldrPos; //������Ʈ��ġ + ������
	Vec2			m_vScale;	//�浹üũ��
	
	UINT			m_iID;		//����ID
	int				m_iOnCdlr;	//������ �浹 ��Ȳ��� bool���� int�� ����

	bool			m_bActive;	//�浹ü Ȱ��ȭ����

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void Cldr_setScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 Cldr_getScale() { return m_vScale; }

	UINT Cldr_getID() { return m_iID; }
	Vec2 Cldr_getPos_F() { return m_vCldrPos; }

	CObj* Cldr_getOtherObj() { return m_pOwner; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void Cldr_onClls(CCmp_01Cldr* _pOther); //�浹�� ȣ���Լ�
	void Cldr_onCllsEnter(CCmp_01Cldr* _pOther);
	void Cldr_onCllsExit(CCmp_01Cldr* _pOther);
	void Cldr_nonClls(CCmp_01Cldr* _pOther);
	CCmp_01Cldr& operator = (CCmp_01Cldr& _origin) = delete; //���Կ����� ���ϰ�

public:
	CCmp_01Cldr();
	CCmp_01Cldr(const CCmp_01Cldr& _origin); //��������ڷ� Cldr�� ����Ǵ��� ����ID ������
	~CCmp_01Cldr();

};

