#include "Camera.h"



void CCamera::SaveComponent(FILE * pFile)
{
}

void CCamera::LoadComponent(FILE * pFile)
{
}

CComponent * CCamera::clone()
{
	return new CCamera(*this);
}

CCamera::CCamera(const CCamera & component)
{

	m_eComponentType = CT_CAMERA;
}

CCamera::CCamera()
{
	m_eComponentType = CT_CAMERA;
}


CCamera::~CCamera()
{
}
