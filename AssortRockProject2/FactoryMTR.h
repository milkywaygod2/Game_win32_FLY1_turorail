#pragma once

enum class MTR_TYPE
{
	NORMAL,
	RANGE,
};


class FactoryMTR
{
private:

public:
	static CObj_02MTR* createMTR(MTR_TYPE _eType, Vec2 _vPos);
		//��ü��� ȣ���Ҽ� �ִ� ���� �ɹ��Լ�

private:
	FactoryMTR() {} //�����Ҹ��� �� ���ѹ�����(��ü�ȸ����)
	~FactoryMTR() {}
};

