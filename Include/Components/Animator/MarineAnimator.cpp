#include "MarineAnimator.h"
#include "../../Sprite.h"
#include "../../GameObject.h"
#include "../../Component.h"
#include "../../SceneManager.h"
#include "../../ResourceManager.h"
#include "../SpriteRenderer.h"
#include "../Camera.h"
#include "../Transform.h"
#include "../../Scene.h"
#include "../../Layer.h"
#include "../Attack.h"


CMarineAnimator::CMarineAnimator(const CMarineAnimator & component)
{
	m_eComponentType = CT_MARINE_ANIMATOR;
}

CMarineAnimator::CMarineAnimator()
{
	m_eComponentType = CT_MARINE_ANIMATOR;
}


CMarineAnimator::~CMarineAnimator()
{
	
}

void CMarineAnimator::OnAnimationUpdate()
{
}

void CMarineAnimator::OnAnimationStart()
{
	CSprite* pCurrentSprite = m_pGameObject->GetComponent<CSpriteRenderer>()->GetCurrentClip();

	if (pCurrentSprite->GetSpriteKey().find("Attack") != string::npos)
	{
		float distance = (m_pTransform->GetPosition() - m_pGameObject->GetScene()->GetCamera()->GameObject()->GetTransform()->GetPosition()).length();
		if (distance <= 1500)
		{
			GET_SINGLE(CResourceManager)->PlaySFX(string("MarineAttack0"));

			CGameObject* pEffect = new CGameObject("VFX");
			GET_SINGLE(CSceneManager)->GetCurrentScene()->FindLayer("GroundVFX")->AddGameObject(pEffect);
			pEffect->GetTransform()->SetPosition(m_pTransform->GetPosition() + -m_pTransform->forword() * 10);
			pEffect->GetTransform()->SetPivot(0.5f, 0.5f);
			CSpriteRenderer* pRenderer = pEffect->AddComponent<CSpriteRenderer>();
			pRenderer->SetSize(40, 40);
			pRenderer->AddSprite("TerranBulletAttack", GET_SINGLE(CResourceManager)->FindSprite("TerranBulletAttack"));
			pRenderer->ChangeCurrentClip("TerranBulletAttack");

			CVector2 targetPosition = m_pGameObject->GetComponent<CAttack>()->GetAttackTarget()->GetTransform()->GetPosition();

			targetPosition = targetPosition + CVector2::RandomDirection() * 16;
			pEffect->GetTransform()->SetPosition(targetPosition);
		}
	}
}

void CMarineAnimator::OnAnimationEnd()
{
}

void CMarineAnimator::SaveComponent(FILE * pFile)
{
}

void CMarineAnimator::LoadComponent(FILE * pFile)
{
}

CComponent * CMarineAnimator::clone()
{
	return new CMarineAnimator(*this);
}
