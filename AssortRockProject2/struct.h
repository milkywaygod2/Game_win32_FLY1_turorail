#pragma once

struct Vec2 //힘방향 좌표구조체
{
	float x;
	float y;

public:
	bool isZero() {
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

	float Length() { return sqrt(x * x + y * y); }
	Vec2& Normalize() //좌표값을 얻었을때, 방향은 유지하면서 단위원으로 정규화해주는 함수
	{
		float fLength = Length();
		//assert(fLength != 0.f);
		if (fLength != 0)
		{
			x /= fLength, //cos의 의미+단위원으로 정규화
			y /= fLength; //sin의 의미+단위원으로 정규화
			
		}
		else
		{
			x = 0.f;
			y = 0.f;
		}
		return *this;
	}
public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}
	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}
	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}


public:
	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}

	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
		return *this;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}
	
	Vec2 operator - (Vec2 _vOther)
	{		return Vec2(x - _vOther.x, y - _vOther.y);	}

	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	void operator -= (float _f)
	{
		x -= _f;
		y -= _f;
	}

	Vec2 operator * (Vec2 _vOther)
	{		return Vec2(x * _vOther.x, y * _vOther.y);	}

	Vec2 operator * (int _i)
	{		return Vec2(x * (float)_i, y * (float)_i);	}

	Vec2 operator * (float _f)
	{		return Vec2(x * _f, y * _f);	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}


	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f));
		return Vec2(x / _f, y / _f);
	}
	Vec2(const POINT _pt) //선언과 동시에대입하는 경우 복사생성자 되는 문제 없애기위해 커스텀생성자 
		:x((float)_pt.x)
		, y((float)_pt.y)
	{
	}
};