
#include "FirebatAnimator.h"
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


CFirebatAnimator::CFirebatAnimator(const CFirebatAnimator & component)
{
	m_eComponentType = CT_FIREBAT_ANIMATOR;
}

CFirebatAnimator::CFirebatAnimator()
{
	m_eComponentType = CT_FIREBAT_ANIMATOR;
}


CFirebatAnimator::~CFirebatAnimator()
{
}

void CFirebatAnimator::OnAnimationUpdate()
{
}

void CFirebatAnimator::OnAnimationStart()
{
	CSprite* pCurrentSprite = m_pGameObject->GetComponent<CSpriteRenderer>()->GetCurrentClip();
	string currentSpriteKey = pCurrentSprite->GetSpriteKey();

	if (currentSpriteKey.find("Attack") != string::npos)
	{
		float distance = (m_pTransform->GetPosition() - m_pGameObject->GetScene()->GetCamera()->GameObject()->GetTransform()->GetPosition()).length();
		if (distance <= 1500)
		{
			int i = rand() % 2;
			char sidx[4] = {};
			itoa(i, sidx, 10);
			GET_SINGLE(CResourceManager)->PlaySFX(string("FirebatAttack") + string(sidx));

			CGameObject* pEffect = new CGameObject("VFX");
			GET_SINGLE(CSceneManager)->GetCurrentScene()->FindLayer("GroundVFX")->AddGameObject(pEffect);
			pEffect->GetTransform()->SetPosition(m_pTransform->GetPosition());
			pEffect->GetTransform()->SetPivot(0.5f, 0.5f);
			CSpriteRenderer* pRenderer = pEffect->AddComponent<CSpriteRenderer>();
			pRenderer->SetSize(224, 224);

			pRenderer->AddSprite("FirebatAttack0", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack0"));
			pRenderer->AddSprite("FirebatAttack1", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack1"));
			pRenderer->AddSprite("FirebatAttack2", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack2"));
			pRenderer->AddSprite("FirebatAttack3", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack3"));
			pRenderer->AddSprite("FirebatAttack4", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack4"));
			pRenderer->AddSprite("FirebatAttack5", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack5"));
			pRenderer->AddSprite("FirebatAttack6", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack6"));
			pRenderer->AddSprite("FirebatAttack7", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack7"));
			pRenderer->AddSprite("FirebatAttack8", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack8"));
			pRenderer->AddSprite("FirebatAttack9", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack9"));
			pRenderer->AddSprite("FirebatAttack10", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack10"));
			pRenderer->AddSprite("FirebatAttack11", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack11"));
			pRenderer->AddSprite("FirebatAttack12", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack12"));
			pRenderer->AddSprite("FirebatAttack13", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack13"));
			pRenderer->AddSprite("FirebatAttack14", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack14"));
			pRenderer->AddSprite("FirebatAttack15", GET_SINGLE(CResourceManager)->FindSprite("TerranFirebatAttack15"));
			pRenderer->ChangeCurrentClip("FirebatAttack0");


			if (currentSpriteKey.find("k0") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack0");
			}
			else if (currentSpriteKey.find("k1") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack1");
			}
			else if (currentSpriteKey.find("k2") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack2");
			}
			else if (currentSpriteKey.find("k3") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack3");
			}
			else if (currentSpriteKey.find("k4") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack4");
			}
			else if (currentSpriteKey.find("k5") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack5");
			}
			else if (currentSpriteKey.find("k6") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack6");
			}
			else if (currentSpriteKey.find("k7") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack7");
			}
			else if (currentSpriteKey.find("k8") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack8");
			}
			else if (currentSpriteKey.find("k9") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack9");
			}
			else if (currentSpriteKey.find("k10") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack10");
			}
			else if (currentSpriteKey.find("k11") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack11");
			}
			else if (currentSpriteKey.find("k12") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack12");
			}
			else if (currentSpriteKey.find("k13") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack13");
			}
			else if (currentSpriteKey.find("k14") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack14");
			}
			else if (currentSpriteKey.find("k15") != string::npos)
			{
				pRenderer->ChangeCurrentClip("FirebatAttack15");
			}
		}
	}
}

void CFirebatAnimator::OnAnimationEnd()
{
}

void CFirebatAnimator::SaveComponent(FILE * pFile)
{
}

void CFirebatAnimator::LoadComponent(FILE * pFile)
{
}

CComponent * CFirebatAnimator::clone()
{
	return new CFirebatAnimator(*this);
}
