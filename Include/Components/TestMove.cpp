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
	//unit �� center�� �߽����� lt, rt, lb, rb 4���� Cell�� ���ؼ�
	//�� cellNum�� ����, �ߺ����� �ʵ��� �� cell�� �߰��Ѵ�.
	// �浹 ���� �ÿ��� �Ȱ��� ������� cell�� ���� ��, �� cell���� list�� �޾ƿ� ��, �浹��� �ϵ��� �Ѵ�.

	// iterator �߰� ȸ�� ����.
	// / 4ȸ, * 1ȸ 
	// ������ Ÿ���� ũ�⺸�� Ŭ ���, ������ ������ �˻��� �ʿ� ����, ������ �ִ� ũ��� 32pixl �� �� 4 * 4 (128 * 128) �̰�, 
	// �ǹ��� ���� tile �����Ϳ� ���� �����ϹǷ� ����, ���� ������ �浹 ������, Y�� �������� õõ�� �з������� �ϵ��� �Ѵ�.
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
	// �ߺ� üũ

	int cellNum[4] = {LT,RT,LB,RB};

	//���� LT �߰�
	//RT �߰��ϱ� �� LT�� ������ ��, �ٸ��� �ش� Cell�� �߰�
	//LB �߰��ϱ� �� LT �Ǵ� RT�� ������ ��, �� �� ���� ������ �߰�
	//RB �߰��ϱ� �� LT �Ǵ� RT �Ǵ� LB�� ������ ��, �� �� ���� ������ �߰�
	//�̰� ����for������ ������ ����.
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
