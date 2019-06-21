#pragma once

#include "Game.h"
class CVectorField 
{
public:
	explicit CVectorField(CVector2 size);
	explicit CVectorField(unsigned int iWidth, unsigned int iHeight);
	~CVectorField();

public:
	uint32_t	m_iGridWidth;
	uint32_t	m_iGridHeight;
	CVector2*	m_VectorField;
	
public:
	
	CVector2 operator [] (const int idx)
	{
		return m_VectorField[idx];
	}

public:
	void SetVector(int idx, CVector2 dir)
	{
		m_VectorField[idx] = dir;
	}
	CVector2 GetVector(int idx)
	{
		return m_VectorField[idx];
	}
	CVector2 GetVector(CVector2 worldPosition);
	


};

