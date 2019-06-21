#include "CameraMove.h"
#include "Transform.h"
#include "../Core.h"
#include "../Timer.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "../Option.h"


#include "../Scenes/DefaultScene.h"


void CCameraMove::Update()
{
	POINT tempPos;
	GetCursorPos(&tempPos);
	ScreenToClient(GET_SINGLE(CCore)->GetWindowHandle(), &tempPos);
	CVector2 cursorPosition = CVector2(tempPos.x , tempPos.y);
	CVector2 screenSize = GET_SINGLE(CCore)->GetScreenSize();
	CVector2 edgeBuffer = CVector2(30, 30);
	CVector2 tileSize = m_pGameObject->GetScene()->GetTileSize();

	CVector2 mapSize = m_pGameObject->GetScene()->GetGridSize();
	CVector2 moveMax;
	moveMax.x = mapSize.x * tileSize.x - screenSize.x;
	moveMax.y = mapSize.y * tileSize.y - screenSize.y;

	
	float speed = GET_SINGLE(COption)->GetCameraSpeed();

	if (m_pGameObject->GetScene()->GetName() == "EditorScene")
		speed = 500;

	if (GetAsyncKeyState(VK_UP) & 0x8000 || (cursorPosition.y < edgeBuffer.y && cursorPosition.y >= 0))
	{
		CVector2 position = m_pTransform->GetPosition();
		position = position + CVector2(0, -1) * speed * GET_SINGLE(CTimer)->GetDeltaTime();
		if (position.y < 0)
			position.y = 0;

		m_pTransform->SetPosition(position);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 || (cursorPosition.y > screenSize.y - edgeBuffer.y && cursorPosition.y <= screenSize.y))
	{
		CVector2 position = m_pTransform->GetPosition();
		position = position + CVector2(0, 1) * speed * GET_SINGLE(CTimer)->GetDeltaTime();

		if (position.y >= moveMax.y)
		{
			position.y = moveMax.y;
		}

		m_pTransform->SetPosition(position);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || (cursorPosition.x < edgeBuffer.x && cursorPosition.x >= 0))
	{
		CVector2 position = m_pTransform->GetPosition();
		position = position + CVector2(-1, 0) * speed * GET_SINGLE(CTimer)->GetDeltaTime();

		if (position.x < 0)
			position.x = 0;

		m_pTransform->SetPosition(position);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || (cursorPosition.x > screenSize.x - edgeBuffer.x && cursorPosition.x <= screenSize.x))
	{
		CVector2 position = m_pTransform->GetPosition();
		position = position + CVector2(1, 0) * speed * GET_SINGLE(CTimer)->GetDeltaTime();

		if (position.x >= moveMax.x)
		{
			position.x = moveMax.x;
		}
		m_pTransform->SetPosition(position);
	}

}

void CCameraMove::SaveComponent(FILE * pFile)
{
}

void CCameraMove::LoadComponent(FILE * pFile)
{
}

CComponent * CCameraMove::clone()
{
	return new CCameraMove(*this);
}

CCameraMove::CCameraMove(const CCameraMove & component)
{
	m_eComponentType = CT_CAMERA_MOVE;
}

CCameraMove::CCameraMove()
{
	m_eComponentType = CT_CAMERA_MOVE;
}


CCameraMove::~CCameraMove()
{
}
