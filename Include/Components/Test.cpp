#include "Test.h"
#include "Transform.h"
#include "../Core.h"


void CTest::Update()
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GET_SINGLE(CCore)->GetWindowHandle(), &pos);
	CVector2 cursorPosition = CVector2(pos.x, pos.y);
	m_pTransform->SetPosition(cursorPosition);
}

void CTest::LoadComponent(FILE * pFile)
{
}

void CTest::SaveComponent(FILE * pFile)
{
}

CComponent * CTest::clone()
{
	return nullptr;
}

CTest::CTest()
{
}


CTest::~CTest()
{
}
