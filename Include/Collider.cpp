#include "Collider.h"
#include "GameObject.h"
#include "Components\Transform.h"
#include "Components\CircleCollider.h"
#include "Components\RectCollider.h"
#include "Components\PointCollider.h"
#include "Components\PixelCollider.h"


CVector2 CCollider::GetWorldPosition() const
{
	return m_pTransform->GetPosition() + m_LocalPosition;
	//return  Transform()->GetPosition() + m_LocalPosition;
}

//같은 오브젝트 안에 있으면 충돌 시키지 말것
bool CCollider::CheckCollision(CCollider * pTarget)
{
	COLLIDER_TYPE eType = pTarget->GetColliderType();

	switch (m_eType)
	{
		case COLLIDER_TYPE::RECT:
		{
			CRectCollider* pCurrent = dynamic_cast<CRectCollider*>(this);
			CVector2 currentLT = pCurrent->GetLeftTopPosition();
			CVector2 currentRB = pCurrent->GetRightBottomPosition();
			//LT와 RB의 위치 교정
			if (currentLT.x > currentRB.x)
			{
				float temp = currentLT.x;
				currentLT.x = currentRB.x;
				currentRB.x = temp;
			}
			if (currentLT.y > currentRB.y)
			{
				float temp = currentLT.y;
				currentLT.y = currentRB.y;
				currentRB.y = temp;
			}
			switch (eType)
			{
			case COLLIDER_TYPE::RECT:
			{
				CRectCollider* pRectTarget = dynamic_cast<CRectCollider*>(pTarget);			
				CVector2 targetLT = pRectTarget->GetLeftTopPosition();
				CVector2 targetRB = pRectTarget->GetRightBottomPosition();

				//LT와 RB의 위치 교정
				if (targetLT.x > targetRB.x)
				{
					float temp = targetLT.x;
					targetLT.x = targetRB.x;
					targetRB.x = temp;
				}
				if (targetLT.y > targetRB.y)
				{
					float temp = targetLT.y;
					targetLT.y = targetRB.y;
					targetRB.y = temp;
				}


				if (currentLT.x > targetRB.x)
					return false;
				else if (currentRB.x < targetLT.x)
					return false;
				else if (currentLT.y > targetRB.y)
					return false;
				else if (currentRB.y < targetLT.y)
					return false;
				return true;
			}
			break;
			case COLLIDER_TYPE::CIRCLE:
			{
				CCircleCollider* pTargetCollider = dynamic_cast<CCircleCollider*>(pTarget);
				float targetRadius = pTargetCollider->GetRadius();
				CVector2 targetCenter = pTargetCollider->GetWorldPosition();

				if ((currentLT.x <= targetCenter.x && targetCenter.x <= currentRB.x) ||
					(currentLT.y <= targetCenter.y && targetCenter.y <= currentRB.y))
				{
					CVector2 tempLT = CVector2(currentLT.x - targetRadius, currentLT.y - targetRadius);
					CVector2 tempRB = CVector2(currentRB.x + targetRadius, currentRB.y + targetRadius);

					if (targetCenter.x < tempLT.x)
						return false;

					else if (targetCenter.x > tempRB.x)
						return false;

					else if (targetCenter.y < tempLT.y)
						return false;

					else if (targetCenter.y > tempRB.y)
						return false;

					return true;
				}

				// 사각형의 꼭지점 확인
				CVector2 tPos[4];
				tPos[0] = CVector2(currentLT.x, currentLT.y);
				tPos[1] = CVector2(currentRB.x, currentLT.y);
				tPos[2] = CVector2(currentLT.x, currentRB.y);
				tPos[3] = CVector2(currentRB.x, currentRB.y);

				for (int i = 0; i < 4; ++i)
				{
					float fDistance = CVector2::distance(tPos[i], targetCenter);
					if (fDistance <= targetRadius)
						return true;
				}

				return false;
			}
				break;
			case COLLIDER_TYPE::POINT:
			{
				CPointCollider* pTargetCollider = dynamic_cast<CPointCollider*>(pTarget);
				CVector2 targetPosition = pTargetCollider->GetPosition();

				if (targetPosition.x < currentLT.x)
					return false;

				else if (targetPosition.x > currentRB.x)
					return false;

				else if (targetPosition.y < currentLT.y)
					return false;

				else if (targetPosition.y > currentRB.y)
					return false;

				return true;
			}
				break;
			case COLLIDER_TYPE::PIXEL:
				//충돌 안함
				return false;
				break;
			default:
				break;
			}
		}
		break;
		case COLLIDER_TYPE::CIRCLE:
		{
			CCircleCollider* pCurrent = dynamic_cast<CCircleCollider*>(this);
			CVector2 center = pCurrent->GetWorldPosition();
			float radius = pCurrent->GetRadius();

			switch (eType)
			{
			case COLLIDER_TYPE::RECT:
			{
				CRectCollider* pTargetCollider = dynamic_cast<CRectCollider*>(pTarget);
				CVector2 targetLT = pTargetCollider->GetLeftTopPosition();
				CVector2 targetRB = pTargetCollider->GetRightBottomPosition();

				if (targetLT.x > targetRB.x)
				{
					float temp = targetLT.x;
					targetLT.x = targetRB.x;
					targetRB.x = temp;
				}
				if (targetLT.y > targetRB.y)
				{
					float temp = targetLT.y;
					targetLT.y = targetRB.y;
					targetRB.y = temp;
				}

				if ((targetLT.x <= center.x && center.x <= targetRB.x) ||
					(targetLT.y <= center.y && center.y <= targetRB.y))
				{
					CVector2 tempLT = CVector2(targetLT.x - radius, targetLT.y - radius);
					CVector2 tempRB = CVector2(targetRB.x + radius, targetRB.y + radius);

					if (center.x < tempLT.x)
						return false;

					else if (center.x > tempRB.x)
						return false;

					else if (center.y < tempLT.y)
						return false;

					else if (center.y > tempRB.y)
						return false;

					return true;
				}

				// 사각형의 꼭지점 확인
				CVector2 tPos[4];
				tPos[0] = CVector2(targetLT.x, targetLT.y);
				tPos[1] = CVector2(targetRB.x, targetLT.y);
				tPos[2] = CVector2(targetLT.x, targetRB.y);
				tPos[3] = CVector2(targetRB.x, targetRB.y);

				for (int i = 0; i < 4; ++i)
				{
					float fDistance = CVector2::distance(tPos[i], center);
					if (fDistance <= radius)
						return true;
				}

				return false;
			}
				break;
			case COLLIDER_TYPE::CIRCLE:
			{
				CCircleCollider* pTargetCollider = dynamic_cast<CCircleCollider*>(pTarget);
				CVector2 targetCenter = pTargetCollider->GetWorldPosition();
				float targetRadius = pTargetCollider->GetRadius();
				float	distance = CVector2::distance(center, targetCenter);

				return distance <= radius + targetRadius;
			}
				break;
			case COLLIDER_TYPE::POINT:
			{
				CPointCollider* pTargetCollider = dynamic_cast<CPointCollider*>(pTarget);
				CVector2 targetPosition = pTargetCollider->GetPosition();

				float distance = CVector2::distance(targetPosition, center);

				return distance <= radius;
			}
				break;
			case COLLIDER_TYPE::PIXEL://충돌 안함	
				return false;			
				break;
			default:
				break;
			}
		}
		break;
		case COLLIDER_TYPE::POINT:
		{
			CPointCollider* pCurrent = dynamic_cast<CPointCollider*>(this);
			CVector2 position = pCurrent->GetPosition();

			switch (m_eType)
			{
			case COLLIDER_TYPE::RECT:
			{
				CRectCollider* pTargetCollider = dynamic_cast<CRectCollider*>(pTarget);
				CVector2 targetLT = pTargetCollider->GetLeftTopPosition();
				CVector2 targetRB = pTargetCollider->GetRightBottomPosition();

				if (targetLT.x > targetRB.x)
				{
					float temp = targetLT.x;
					targetLT.x = targetRB.x;
					targetRB.x = temp;
				}
				if (targetLT.y > targetRB.y)
				{
					float temp = targetLT.y;
					targetLT.y = targetRB.y;
					targetRB.y = temp;
				}

				if (targetLT.x > targetRB.x)
				{
					float temp = targetLT.x;
					targetLT.x = targetRB.x;
					targetRB.x = temp;
				}
				if (targetLT.y > targetRB.y)
				{
					float temp = targetLT.y;
					targetLT.y = targetRB.y;
					targetRB.y = temp;
				}

				if (position.x < targetLT.x)
					return false;

				else if (position.x > targetRB.x)
					return false;

				else if (position.y < targetLT.y)
					return false;

				else if (position.y > targetRB.y)
					return false;

				return true;
			}
				break;
			case COLLIDER_TYPE::CIRCLE:
			{
				CCircleCollider* pTargetCollider = dynamic_cast<CCircleCollider*>(this);
				CVector2 center = pTargetCollider->GetWorldPosition();
				float radius = pTargetCollider->GetRadius();

				float distance = CVector2::distance(center, position);

				return distance <= radius;
			}
				break;
			case COLLIDER_TYPE::POINT:
			{
				CPointCollider* pTargetCollider = dynamic_cast<CPointCollider*>(pTarget);
				return position == pTargetCollider->GetPosition();
			}
				break;
			case COLLIDER_TYPE::PIXEL:
			{
				//UI Panel - Cursor 충돌
				//BLACK = 컬링
				//MAGENTA = 충돌			
				CPixelCollider* pTargetCollider = dynamic_cast<CPixelCollider*>(pTarget);
				const vector<PIXEL>& vecPixel = pTargetCollider->GetPixel();

				if (position.x < 0 || position.y < 0 || position.x >= pTargetCollider->GetWidth() || position.y >= pTargetCollider->GetHeight())
				{
					return false;
				}

				int idx = (int)position.y * pTargetCollider->GetWidth() + (int)position.x;
				const PIXEL& pixel = vecPixel[idx];
				if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255)
				{
					m_CollidePosition = position;
					return true;
				}

				return false;
			}
				break;
			default:
				break;
			}
		}
			break;
		case COLLIDER_TYPE::PIXEL:
		{
			CPixelCollider* pCurrent = dynamic_cast<CPixelCollider*>(this);
			const vector<PIXEL>& vecPixel = pCurrent->GetPixel();

			switch (m_eType)
			{
			case COLLIDER_TYPE::RECT:
				//충돌 안함
				return false;
				break;
			case COLLIDER_TYPE::CIRCLE:
				//충돌 안함
				return false;
				break;
			case COLLIDER_TYPE::POINT:
			{
				//UI Panel - Cursor 충돌
				//BLACK = 컬링
				//MAGENTA = 충돌			
				CPointCollider* pTargetCollider = dynamic_cast<CPointCollider*>(pTarget);
				CVector2 position = pTargetCollider->GetPosition();

				if (position.x < 0 || position.y < 0 || position.x >= pCurrent->GetWidth() || position.y >= pCurrent->GetHeight())
				{
					return false;
				}

				int idx = (int)position.y * pCurrent->GetWidth() + (int)position.x;
				const PIXEL& pixel = vecPixel[idx];
				if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255)
				{
					m_CollidePosition = position;
					return true;
				}

				return false;
			}
				break;
			case COLLIDER_TYPE::PIXEL:		
				//충돌 안함
				return false;
				break;
			default:
				break;
			}
		}
			break;
		default:
			return false;
			break;
	}

	return false;
}

CCollider::CCollider():
	m_bCollision(false),
	m_CollidePosition(CVector2()),
	m_pTarget(NULL),
	m_LocalPosition(0,0),
	m_eType(COLLIDER_TYPE::NONE)
{
	m_CollisionList.clear();
}


CCollider::~CCollider()
{
}
