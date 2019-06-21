#include "GasTank.h"
#include "../Transform.h"
#include "../SpriteRenderer.h"
#include "../../GameObject.h"


CGasTank::CGasTank(const CGasTank & component)
{
	m_eComponentType = CT_GASTANK_ANIMATOR;
}

CGasTank::CGasTank()
{
	m_eComponentType = CT_GASTANK_ANIMATOR;
}


CGasTank::~CGasTank()
{
}

void CGasTank::OnAnimationUpdate()
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


	if (fAngle >= 0.0f && fAngle < 360.0f)
	{
		if (pRenderer->GetCurrentClipKey() != "GasTank")
			pRenderer->ChangeCurrentClip("GasTank");
	}
}

void CGasTank::OnAnimationStart()
{
}

void CGasTank::OnAnimationEnd()
{
}

void CGasTank::SaveComponent(FILE * pFile)
{
}

void CGasTank::LoadComponent(FILE * pFile)
{
}

CComponent * CGasTank::clone()
{
	return new CGasTank(*this);
}
