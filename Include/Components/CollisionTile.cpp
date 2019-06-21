#include "CollisionTile.h"



void CCollisionTile::SaveComponent(FILE * pFile)
{
}

void CCollisionTile::LoadComponent(FILE * pFile)
{
}

CComponent * CCollisionTile::clone()
{
	return new CCollisionTile(*this);
}

CCollisionTile::CCollisionTile(const CCollisionTile & component)
{
	m_iCellIndex = component.m_iCellIndex;
	m_eComponentType = CT_COLLISION_TILE;
}

CCollisionTile::CCollisionTile()
{
	m_eComponentType = CT_COLLISION_TILE;
}


CCollisionTile::~CCollisionTile()
{
}
