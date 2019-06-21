#include "SCVAnimator.h"
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

void CSCVAnimator::OnAnimationUpdate()
{
}

void CSCVAnimator::OnAnimationStart()
{
	CSprite* pCurrentSprite = m_pGameObject->GetComponent<CSpriteRenderer>()->GetCurrentClip();

	if (pCurrentSprite->GetSpriteKey().find("SCVAttack") != string::npos)
	{
		float distance = (m_pTransform->GetPosition() - m_pGameObject->GetScene()->GetCamera()->GameObject()->GetTransform()->GetPosition()).length();
		if (distance <= 1000)
		{
			char strRandom[4] = {};
			int iRandom = rand() % 5;
			itoa(iRandom, strRandom, 10);
			GET_SINGLE(CResourceManager)->PlaySFX(string("SCVAttack") + string(strRandom));

			CGameObject* pEffect = new CGameObject("VFX");
			GET_SINGLE(CSceneManager)->GetCurrentScene()->FindLayer("GroundVFX")->AddGameObject(pEffect);
			CVector2 effectPosition = m_pTransform->GetPosition() + -m_pTransform->forword() * 10;
			effectPosition = effectPosition; //+ CVector2::RandomDirection() * 32;
			pEffect->GetTransform()->SetPosition(effectPosition);
			pEffect->GetTransform()->SetPivot(1.0f, 1.0f);
			CSpriteRenderer* pRenderer = pEffect->AddComponent<CSpriteRenderer>();
			pRenderer->SetSize(48, 48);
			pRenderer->AddSprite("SCVAttack",GET_SINGLE(CResourceManager)->FindSprite("SCVAttack"));
			pRenderer->ChangeCurrentClip("SCVAttack");
		}
	}
}

void CSCVAnimator::OnAnimationEnd()
{
}

void CSCVAnimator::SaveComponent(FILE * pFile)
{
}

void CSCVAnimator::LoadComponent(FILE * pFile)
{

}

CComponent * CSCVAnimator::clone()
{
	return new CSCVAnimator(*this);
}

CSCVAnimator::CSCVAnimator(const CSCVAnimator & component)
{
	m_eComponentType = CT_SCV_ANIMATOR;
}

CSCVAnimator::CSCVAnimator()
{
	m_eComponentType = CT_SCV_ANIMATOR;
}


CSCVAnimator::~CSCVAnimator()
{
}
