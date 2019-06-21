#include "PointCollider.h"



void CPointCollider::SaveComponent(FILE * pFile)
{
	fwrite(&m_Position, sizeof(CVector2), 1, pFile);
}

void CPointCollider::LoadComponent(FILE * pFile)
{
	fread(&m_Position, sizeof(CVector2), 1, pFile);
}

CComponent * CPointCollider::clone()
{
	return new CPointCollider(*this);
}

CPointCollider::CPointCollider(const CPointCollider & component)
{
	m_Position = component.m_Position;
	m_eType = COLLIDER_TYPE::POINT;
	m_eComponentType = CT_POINT_COLLIDER;
	m_eComponentParentType = PT_COLLIDER;
}

CPointCollider::CPointCollider()
{
	m_eType = COLLIDER_TYPE::POINT;
	m_eComponentType = CT_POINT_COLLIDER;
	m_eComponentParentType = PT_COLLIDER;
}


CPointCollider::~CPointCollider()
{
}
