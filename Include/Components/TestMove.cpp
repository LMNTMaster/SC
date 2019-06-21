#include "TestMove.h"
#include "Transform.h"
#include "../GameObject.h"
#include "../Timer.h"
#include "TextureRenderer.h"
#include "SpriteRenderer.h"
#include "EllipseRenderer.h"
#include "../Scene.h"
#include "../Components/CollisionTile.h"
#include "CircleCollider.h"

void CTestMove::Update()
{
	//unit 의 center를 중심으로 lt, rt, lb, rb 4점의 Cell을 구해서
	//각 cellNum을 구해, 중복되지 않도록 각 cell에 추가한다.
	// 충돌 연산 시에는 똑같은 방법으로 cell을 구한 뒤, 각 cell에서 list를 받아온 뒤, 충돌계산 하도록 한다.

	// iterator 추가 회전 없음.
	// / 4회, * 1회 
	// 유닛이 타일의 크기보다 클 경우, 안쪽의 유닛은 검사할 필요 없고, 유닛의 최대 크기는 32pixl 일 때 4 * 4 (128 * 128) 이고, 
	// 건물은 직접 tile 데이터에 접근 가능하므로 제외, 공중 유닛은 충돌 하지만, Y축 보정으로 천천히 밀려나가게 하도록 한다.
	CVector2 position = m_pTransform->GetPosition();
	CScene* scene = m_pGameObject->GetScene();
	float collisionRadius = m_pGameObject->GetComponent<CCircleCollider>()->GetTileCollisionRadius();
	CVector2 gridSize = scene->GetGridSize();

	int rtX = (position.x + collisionRadius) / TILESIZE.x;
	int rtY = (position.y - collisionRadius) / TILESIZE.y;
	int ltX = (position.x - collisionRadius) / TILESIZE.x;
	int ltY = (position.y - collisionRadius) / TILESIZE.y;
	int lbX = (position.x - collisionRadius) / TILESIZE.x;
	int lbY = (position.y + collisionRadius) / TILESIZE.y;
	int rbX = (position.x + collisionRadius) / TILESIZE.x;
	int rbY = (position.y + collisionRadius) / TILESIZE.y;
	
	int LT = ltY * (int)gridSize.x + ltX;
	int RT = rtY * (int)gridSize.x + rtX;
	int LB = lbY * (int)gridSize.x + lbX;
	int RB = rbY * (int)gridSize.x + rbX;
	// 중복 체크

	int cellNum[4] = {LT,RT,LB,RB};

	//먼저 LT 추가
	//RT 추가하기 전 LT랑 같은지 비교, 다르면 해당 Cell에 추가
	//LB 추가하기 전 LT 또는 RT와 같은지 비교, 둘 다 같지 않으면 추가
	//RB 추가하기 전 LT 또는 RT 또는 LB와 같은지 비교, 셋 다 같지 않으면 추가
	//이게 이중for문보다 빠를것 같다.
	//scene->GetCollisionTile(LT)->AddUnit(this->m_pGameObject);
	//
	//if (LT != RT)
	//{
	//	scene->GetCollisionTile(RT)->AddUnit(this->m_pGameObject);
	//}
	//if (LB != LT && LB != RT)
	//{
	//	scene->GetCollisionTile(LB)->AddUnit(this->m_pGameObject);
	//}
	//if (RB != LT && RB != RT && RB != LB)
	//{
	//	scene->GetCollisionTile(RB)->AddUnit(this->m_pGameObject);
	//}
	//m_pGameObject->GetComponent<CEllipseRenderer>()->SetEnable(m_bSelected);

	//if (m_bSelected)
	{
		if (GetAsyncKeyState('D') & 0x8000)
		{
			CVector2 position = m_pGameObject->GetComponent<CTransform>()->GetPosition();
			position.x += 200 * GET_SINGLE(CTimer)->GetDeltaTime();
			m_pGameObject->GetComponent<CTransform>()->SetPosition(position);
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			CVector2 position = m_pGameObject->GetComponent<CTransform>()->GetPosition();
			position.x -= 200 * GET_SINGLE(CTimer)->GetDeltaTime();
			m_pGameObject->GetComponent<CTransform>()->SetPosition(position);
		}
		if (GetAsyncKeyState('W') & 0x8000)
		{
			CVector2 position = m_pGameObject->GetComponent<CTransform>()->GetPosition();
			position.y -= 200 * GET_SINGLE(CTimer)->GetDeltaTime();
			m_pGameObject->GetComponent<CTransform>()->SetPosition(position);
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			CVector2 position = m_pGameObject->GetComponent<CTransform>()->GetPosition();
			position.y += 200 * GET_SINGLE(CTimer)->GetDeltaTime();
			m_pGameObject->GetComponent<CTransform>()->SetPosition(position);
		}

		if (GetAsyncKeyState('Q') & 0x8000)
		{
			float fAngle = m_pTransform->GetRotation() - 45.0f * GET_SINGLE(CTimer)->GetDeltaTime();

			if (fAngle >= 360)
			{
				fAngle -= 360;
			}
			if (fAngle <= 0)
			{
				fAngle += 360;
			}
			m_pTransform->SetRotation(fAngle);
		}
		if (GetAsyncKeyState('E') & 0x8000)
		{
			float fAngle = m_pTransform->GetRotation() + 45.0f * GET_SINGLE(CTimer)->GetDeltaTime();

			if (fAngle >= 360)
			{
				fAngle -= 360;
			}
			if (fAngle <= 0)
			{
				fAngle += 360;
			}
			m_pTransform->SetRotation(fAngle);
		}

		float fAngle = m_pTransform->GetRotation();
		string unitName = m_pGameObject->GetName();
		CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
		if (fAngle >= 0.0f && fAngle < 22.5f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move0")
				pRenderer->ChangeCurrentClip(unitName + "Move0");
		}
		else if (fAngle >= 22.5f && fAngle < 45)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move1")
				pRenderer->ChangeCurrentClip(unitName + "Move1");
		}
		else if (fAngle >= 45.0f && fAngle < 67.5f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move2")
				pRenderer->ChangeCurrentClip(unitName + "Move2");
		}
		else if (fAngle >= 67.5f && fAngle < 90.0f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move3")
				pRenderer->ChangeCurrentClip(unitName + "Move3");
		}
		else if (fAngle >= 90.0f && fAngle < 112.5f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move4")
				pRenderer->ChangeCurrentClip(unitName + "Move4");
		}
		else if (fAngle >= 112.5f && fAngle < 135.0f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move5")
				pRenderer->ChangeCurrentClip(unitName + "Move5");
		}
		else if (fAngle >= 135.0f && fAngle < 157.5f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move6")
				pRenderer->ChangeCurrentClip(unitName + "Move6");
		}
		else if (fAngle >= 157.5f && fAngle < 180.0f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move7")
				pRenderer->ChangeCurrentClip(unitName + "Move7");
		}
		else if (fAngle >= 180.0f && fAngle < 202.5f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move8")
				pRenderer->ChangeCurrentClip(unitName + "Move8");
		}
		else if (fAngle >= 202.5f && fAngle < 225.0f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move9")
				pRenderer->ChangeCurrentClip(unitName + "Move9");
		}
		else if (fAngle >= 225.0f && fAngle < 247.5f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move10")
				pRenderer->ChangeCurrentClip(unitName + "Move10");
		}
		else if (fAngle >= 247.5f && fAngle < 270.0f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move11")
				pRenderer->ChangeCurrentClip(unitName + "Move11");
		}
		else if (fAngle >= 270.0f && fAngle < 292.5f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move12")
				pRenderer->ChangeCurrentClip(unitName + "Move12");
		}
		else if (fAngle >= 292.5f && fAngle < 315.0f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move13")
				pRenderer->ChangeCurrentClip(unitName + "Move13");
		}
		else if (fAngle >= 315.0f && fAngle < 337.5f)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move14")
				pRenderer->ChangeCurrentClip(unitName + "Move14");
		}
		else if (fAngle >= 337.5f && fAngle < 360)
		{
			if (pRenderer->GetCurrentClipKey() != unitName + "Move15")
				pRenderer->ChangeCurrentClip(unitName + "Move15");
		}


	}

	
}

void CTestMove::CollisionEnter()
{
}

void CTestMove::SaveComponent(FILE * pFile)
{
}

void CTestMove::LoadComponent(FILE * pFile)
{
}

CComponent * CTestMove::clone()
{

	return new CTestMove(*this);
		
}




CTestMove::CTestMove(const CTestMove & component)
{

	m_eComponentType = CT_TEST_MOVE;
}

CTestMove::CTestMove():
	m_bSelected(false)
{
	m_eComponentType = CT_TEST_MOVE;
}


CTestMove::~CTestMove()
{
}
