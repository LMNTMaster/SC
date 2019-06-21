#pragma once
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define PI		  3.14159265358979f
#define D2R	  0.01745329251994f
#define R2D	57.29577951308231f

class CVector2
{
public:
	float x, y;

public:
	void operator = (const CVector2& vec)
	{
		x = vec.x;
		y = vec.y;
	}
	CVector2 operator + (const CVector2& vec) const
	{
		return CVector2(this->x + vec.x, this->y + vec.y);
	}
	CVector2 operator - (const CVector2& vec) const
	{
		return CVector2(this->x - vec.x, this->y - vec.y);
	}
	CVector2 operator * (float fValue) const
	{
		return CVector2(this->x * fValue, this->y * fValue);
	}
	CVector2 operator / (float fValue) const
	{
		return CVector2(this->x / fValue, this->y / fValue);
	}
	CVector2 operator -() const
	{
		return CVector2(this->x  * -1 , this->y * -1);
	}

	void operator += (const CVector2& vec)
	{
		x += vec.x;
		y += vec.y;
	}
	void operator -= (const CVector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}
	bool operator == (const CVector2& vec) const
	{
		return x == vec.x && y == vec.y;
	}
	bool operator != (const CVector2& vec) const
	{
		return x != vec.x || y != vec.y;
	}


public:
	static CVector2 RandomDirection()
	{
		srand(time(0));
		int i = rand() % 36001; //0 ~ 36000
		float r = i * 0.01f;
		return AngleToDirection(r);		
	}
	static float DirectionToAngle(CVector2 vec)
	{
		if (vec.y >= 0)
			return R2D * acosf(vec.x);
		else
			return -(R2D * acosf(vec.x));
	}
	static CVector2 AngleToDirection(float fAngle)
	{
		fAngle *= D2R;
		return CVector2(cosf(fAngle), sinf(fAngle));
	}
	//둘 중 하나가 영벡터여도 단위벡터 반환함
	static CVector2 NormalDirectionEverage(CVector2 vec1, CVector2 vec2)
	{
		return CVector2((vec1.x + vec2.x) / 2, (vec1.y + vec2.y) / 2).normalize();
	}
	static CVector2 zero()
	{		
		return CVector2(0,0);
	}
	float length() const
	{
		return sqrtf(x*x + y*y);
	}
	CVector2 normalize() const
	{
		if (*this == zero())
			return zero();

		CVector2 temp;
		float len = 1.f / length();
		temp.x = x * len;
		temp.y = y * len;

		return temp;
	}
	float dot(CVector2 vec)
	{
		return x * vec.x + y * vec.y;
	}
	CVector2 dotVector(CVector2 vec)
	{
		CVector2 result;
		result = vec * dot(vec) / dot(*this);
		return result;
	}

public:
	static float distance(CVector2 vec1, CVector2 vec2)
	{
		return (vec1 - vec2).length();
	}


public:
	CVector2(float x, float y);
	CVector2();
	~CVector2();
};


typedef struct _tagColor
{
	float r, g, b;

	_tagColor(float _r, float _g, float _b) :r(_r), g(_g), b(_b)
	{}
	_tagColor() :r(0.0f), g(0.0f), b(0.0f)
	{}

}Color;