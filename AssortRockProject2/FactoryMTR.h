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
		//객체없어도 호출할수 있는 정적 맴버함수

private:
	FactoryMTR() {} //생성소멸자 다 숨켜버리기(객체안만들것)
	~FactoryMTR() {}
};

