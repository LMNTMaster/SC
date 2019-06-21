#include "CursorMove.h"
#include "Transform.h"
#include "../Core.h"
#include "../Scene.h"
#include "../SceneManager.h"
#include "../GameObject.h"
#include "../Components/Camera.h"
#include "../Components/SpriteRenderer.h"
#include "../Option.h"
#include "../Timer.h"

void CCursorMove::Update()
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GET_SINGLE(CCore)->GetWindowHandle(), &pos);
	CVector2 cursorPosition = CVector2(pos.x, pos.y) + m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();
	m_pTransform->SetPosition(cursorPosition);

	int screenHeight = GET_SINGLE(CCore)->GetScreenSize().y;
	int screenWidth = GET_SINGLE(CCore)->GetScreenSize().x;
	CVector2 padding(30, 30);
	CVector2 mapSize =m_pGameObject->GetScene()->GetGridSize();
	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();
	CVector2 moveMax;
	moveMax.x = mapSize.x * 32 - GET_SINGLE(CCore)->GetScreenSize().x;
	moveMax.y = mapSize.y * 32 - GET_SINGLE(CCore)->GetScreenSize().y;

	//클립 만들어 줘야함
	//if (pos.x > 0 && pos.x < padding.x && pos.y > padding.y && pos.y < screenHeight - padding.y)
	//{
	//	m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("LeftEdge");
	//	CVector2 direction = CVector2(-1, 0);
	//	cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
	//
	//	if (cameraPosition.x < 0)
	//		cameraPosition.x = 0;
	//
	//	m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	//}
	////Top
	//else if (pos.x > padding.x && pos.x < screenWidth - padding.x && pos.y < padding.y && pos.y > 0)
	//{
	//	m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("TopEdge");
	//	CVector2 direction = CVector2(0, -1);
	//	cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
	//
	//	if (cameraPosition.y < 0)
	//		cameraPosition.y = 0;
	//
	//	m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	//}
	////Right
	//else if (pos.x < screenWidth && pos.x > screenWidth - padding.x && pos.y > padding.y && pos.y < screenHeight - padding.y)
	//{
	//	m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("RightEdge");
	//	CVector2 direction = CVector2(1, 0);
	//	cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
	//
	//	if (cameraPosition.x > moveMax.x)
	//		cameraPosition.x = moveMax.x;
	//
	//	m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	//}
	////Bottom
	//else if (pos.x > padding.x && pos.x < screenWidth - padding.x && pos.y > screenHeight - padding.y && pos.y < screenHeight)
	//{
	//	m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("BottomEdge");
	//	CVector2 direction = CVector2(0, 1);
	//	cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
	//
	//	if (cameraPosition.y > moveMax.y)
	//		cameraPosition.y = moveMax.y;
	//
	//	m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	//}
	////TopLeft
	//else if (pos.x > 0 && pos.x < padding.x && pos.y > 0 && pos.y < padding.y)
	//{
	//	m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("LeftTopEdge");
	//	CVector2 direction = CVector2(-1, -1).normalize();
	//	cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
	//
	//	if (cameraPosition.x < 0)
	//		cameraPosition.x = 0;
	//
	//	if (cameraPosition.y < 0)
	//		cameraPosition.y = 0;
	//
	//	m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	//}
	////TopRight
	//else if (pos.x < screenWidth && pos.x > screenWidth - padding.x && pos.y > 0 && pos.y < padding.y)
	//{
	//	m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("RightTopEdge");
	//	CVector2 direction = CVector2(1, -1).normalize();
	//	cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
	//
	//	if (cameraPosition.y < 0)
	//		cameraPosition.y = 0;
	//
	//	if (cameraPosition.x > moveMax.x)
	//		cameraPosition.x = moveMax.x;
	//
	//	m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	//}
	////LeftBottom
	//else if (pos.x > 0 && pos.x < padding.x && pos.y < screenHeight && pos.y > screenHeight - padding.y)
	//{
	//	m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("LeftBottomEdge");
	//	CVector2 direction = CVector2(-1, 1).normalize();
	//	cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
	//
	//	if (cameraPosition.x < 0)
	//		cameraPosition.x = 0;
	//
	//	if (cameraPosition.y > moveMax.y)
	//		cameraPosition.y = moveMax.y;
	//
	//	m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	//}
	//else if (pos.x < screenWidth && pos.x > screenWidth - padding.x && pos.y < screenHeight && pos.y > screenHeight - padding.y)
	//{
	//	m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("RightBottomEdge");
	//	CVector2 direction = CVector2(1, 1).normalize();
	//	cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
	//	m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	//}
	//else
	//{		
	//	m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("CursorNormal");		
	//}


}

void CCursorMove::LoadComponent(FILE * pFile)
{
}

void CCursorMove::SaveComponent(FILE * pFile)
{
}

CComponent * CCursorMove::clone()
{
	return nullptr;
}

CCursorMove::CCursorMove()
{
}


CCursorMove::~CCursorMove()
{
}
