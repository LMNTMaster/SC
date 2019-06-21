#include "GasSac.h"
#include "../Transform.h"
#include "../SpriteRenderer.h"
#include "../../GameObject.h"



CGasSac::CGasSac(const CGasSac & component)
{
	m_eComponentType = CT_GASSAC_ANIMATOR;
}

CGasSac::CGasSac()
{
	m_eComponentType = CT_GASSAC_ANIMATOR;
}


CGasSac::~CGasSac()
{
}

void CGasSac::OnAnimationUpdate()
{
	if (m_pTarget)
	{
		m_pTransform->SetPosition(m_pTarget->GetTransform()->GetPosition() + m_pTarget->GetTransform()->forword() * -5);
	}
	CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
	string unitName = m_pGameObject->GetName();
	float fAngle = m_pTransform->GetRotation();

	if (fAngle >= 360)
	{
		fAngle -= 360;
	}
	if (fAngle <= 0)
	{
		fAngle += 360;
	}
	m_pTransform->SetRotation(fAngle);


	if ((fAngle >= 0.0f && fAngle < 22.5f) || (fAngle >= 180.0f && fAngle < 202.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasSac4")
			pRenderer->ChangeCurrentClip("GasSac4");
	}
	else if ((fAngle >= 22.5f && fAngle < 45) || (fAngle >= 202.5f && fAngle < 225.0f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasSac5")
			pRenderer->ChangeCurrentClip("GasSac5");
	}
	else if ((fAngle >= 45.0f && fAngle < 67.5f) || (fAngle >= 225.0f && fAngle < 247.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasSac6")
			pRenderer->ChangeCurrentClip("GasSac6");
	}
	else if ((fAngle >= 67.5f && fAngle < 90.0f) || (fAngle >= 247.5f && fAngle < 270.0f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasSac7")
			pRenderer->ChangeCurrentClip("GasSac7");
	}
	else if ((fAngle >= 90.0f && fAngle < 112.5f) || (fAngle >= 270.0f && fAngle < 292.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasSac0")
			pRenderer->ChangeCurrentClip("GasSac0");
	}
	else if ((fAngle >= 112.5f && fAngle < 135.0f) || (fAngle >= 292.5f && fAngle < 315.0f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasSac1")
			pRenderer->ChangeCurrentClip("GasSac1");
	}
	else if ((fAngle >= 135.0f && fAngle < 157.5f) || (fAngle >= 315.0f && fAngle < 337.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasSac2")
			pRenderer->ChangeCurrentClip("GasSac2");
	}
	else if ((fAngle >= 157.5f && fAngle < 180.0f) || (fAngle >= 337.5f && fAngle < 360))
	{
		if (pRenderer->GetCurrentClipKey() != "GasSac3")
			pRenderer->ChangeCurrentClip("GasSac3");
	}
}

void CGasSac::OnAnimationStart()
{
}

void CGasSac::OnAnimationEnd()
{
}

void CGasSac::SaveComponent(FILE * pFile)
{
}

void CGasSac::LoadComponent(FILE * pFile)
{
}

CComponent * CGasSac::clone()
{
	return new CGasSac(*this);
}
