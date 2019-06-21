#include "VectorField.h"

CVector2 CVectorField::GetVector(CVector2 worldPosition)
{
	int iX = ((int)worldPosition.x) / 32;
	int iY = ((int)worldPosition.y) / 32;
	int iPositionToIndex = iY * m_iGridWidth + iX;

	return GetVector(iPositionToIndex);
}

CVectorField::CVectorField(CVector2 size)
{
	m_iGridWidth = size.x;
	m_iGridHeight = size.y;

	m_VectorField = new CVector2[size.x * size.y];
}

CVectorField::CVectorField(unsigned int iWidth, unsigned int iHeight)
{
	m_iGridWidth = iWidth;
	m_iGridHeight = iHeight;

	m_VectorField = new CVector2[iWidth * iHeight];
}

CVectorField::~CVectorField()
{
	delete[] m_VectorField;
}
