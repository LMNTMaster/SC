#include "Option.h"


COption* COption::m_pInstance = NULL;

void COption::Initialize()
{
	m_fCameraMoveSpeed = 200;
	m_bCursorClipped = false;
}

COption::COption()
{
}


COption::~COption()
{
}
