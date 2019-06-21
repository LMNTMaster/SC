#include "MineralOrb.h"
#include "../Transform.h"
#include "../SpriteRenderer.h"
#include "../../GameObject.h"


CMineralOrb::CMineralOrb(const CMineralOrb & component)
{
	m_eComponentType = CT_MINERALORB_ANIMATOR;
}

CMineralOrb::CMineralOrb()
{
	m_eComponentType = CT_MINERALORB_ANIMATOR;
}

CMineralOrb::~CMineralOrb()
{
}

void CMineralOrb::OnAnimationUpdate()
{
		
	CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
	string unitName = m_pGameObject->GetName();
	float fAngle = m_pTarget->GetTransform()->GetRotation();
	if (fAngle >= 360)
	{
		fAngle -= 360;
	}
	if (fAngle <= 0)
	{
		fAngle += 360;
	}
	m_pTransform->SetRotation(fAngle);

	float fFixedAngle = (int)(fAngle / 22.5f);	
	fFixedAngle = fFixedAngle * 22.5f ;
	if (m_pTarget)
	{
		m_pTransform->SetPosition(m_pTarget->GetTransform()->GetPosition() + CVector2(0,-16) + CVector2::AngleToDirection(fFixedAngle) * -15);
	}

	if ((fAngle >= 0.0f && fAngle < 22.5f) || (fAngle >= 180.0f && fAngle < 202.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "MineralOrb4")
			pRenderer->ChangeCurrentClip("MineralOrb4");
	}
	else if ((fAngle >= 22.5f && fAngle < 45) || (fAngle >= 202.5f && fAngle < 225.0f))
	{
		if (pRenderer->GetCurrentClipKey() != "MineralOrb5")
			pRenderer->ChangeCurrentClip("MineralOrb5");
	}
	else if ((fAngle >= 45.0f && fAngle < 67.5f) || (fAngle >= 225.0f && fAngle < 247.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "MineralOrb6")
			pRenderer->ChangeCurrentClip("MineralOrb6");
	}
	else if ((fAngle >= 67.5f && fAngle < 90.0f) || (fAngle >= 247.5f && fAngle < 270.0f))
	{
		if (pRenderer->GetCurrentClipKey() != "MineralOrb7")
			pRenderer->ChangeCurrentClip("MineralOrb7");
	}
	else if ((fAngle >= 90.0f && fAngle < 112.5f) || (fAngle >= 270.0f && fAngle < 292.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "MineralOrb0")
			pRenderer->ChangeCurrentClip("MineralOrb0");
	}
	else if ((fAngle >= 112.5f && fAngle < 135.0f) || (fAngle >= 292.5f && fAngle < 315.0f))
	{
		if (pRenderer->GetCurrentClipKey() != "MineralOrb1")
			pRenderer->ChangeCurrentClip("MineralOrb1");
	}
	else if ((fAngle >= 135.0f && fAngle < 157.5f) || (fAngle >= 315.0f && fAngle < 337.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "MineralOrb2")
			pRenderer->ChangeCurrentClip("MineralOrb2");
	}
	else if ((fAngle >= 157.5f && fAngle < 180.0f) || (fAngle >= 337.5f && fAngle < 360))
	{
		if (pRenderer->GetCurrentClipKey() != "MineralOrb3")
			pRenderer->ChangeCurrentClip("MineralOrb3");
	}
}

void CMineralOrb::OnAnimationStart()
{
}

void CMineralOrb::OnAnimationEnd()
{
}

void CMineralOrb::SaveComponent(FILE * pFile)
{
}

void CMineralOrb::LoadComponent(FILE * pFile)
{
}

CComponent * CMineralOrb::clone()
{
	return new CMineralOrb(*this);
}
