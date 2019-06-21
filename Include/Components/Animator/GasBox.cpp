#include "GasBox.h"
#include "../Transform.h"
#include "../SpriteRenderer.h"
#include "../../GameObject.h"


CGasBox::CGasBox(const CGasBox & component)
{
	m_eComponentType = CT_GASBOX_ANIMATOR;
}

CGasBox::CGasBox()
{
	m_eComponentType = CT_GASBOX_ANIMATOR;
}


CGasBox::~CGasBox()
{
}

void CGasBox::OnAnimationUpdate()
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


	if ((fAngle >= 0.0f && fAngle < 22.5f ) || (fAngle >= 180.0f && fAngle < 202.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasBox4")
			pRenderer->ChangeCurrentClip("GasBox4");
	}
	else if ((fAngle >= 22.5f && fAngle < 45) || (fAngle >= 202.5f && fAngle < 225.0f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasBox5")
			pRenderer->ChangeCurrentClip("GasBox5");
	}
	else if ((fAngle >= 45.0f && fAngle < 67.5f) || (fAngle >= 225.0f && fAngle < 247.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasBox6")
			pRenderer->ChangeCurrentClip("GasBox6");
	}
	else if ((fAngle >= 67.5f && fAngle < 90.0f)|| (fAngle >= 247.5f && fAngle < 270.0f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasBox7")
			pRenderer->ChangeCurrentClip("GasBox7");
	}
	else if ((fAngle >= 90.0f && fAngle < 112.5f)|| (fAngle >= 270.0f && fAngle < 292.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasBox0")
			pRenderer->ChangeCurrentClip("GasBox0");
	}
	else if ((fAngle >= 112.5f && fAngle < 135.0f)|| (fAngle >= 292.5f && fAngle < 315.0f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasBox1")
			pRenderer->ChangeCurrentClip("GasBox1");
	}
	else if ((fAngle >= 135.0f && fAngle < 157.5f)|| (fAngle >= 315.0f && fAngle < 337.5f))
	{
		if (pRenderer->GetCurrentClipKey() != "GasBox2")
			pRenderer->ChangeCurrentClip("GasBox2");
	}
	else if ((fAngle >= 157.5f && fAngle < 180.0f)|| (fAngle >= 337.5f && fAngle < 360))
	{
		if (pRenderer->GetCurrentClipKey() != "GasBox3")
			pRenderer->ChangeCurrentClip("GasBox3");
	}
}

void CGasBox::OnAnimationStart()
{
}

void CGasBox::OnAnimationEnd()
{
}

void CGasBox::SaveComponent(FILE * pFile)
{
}

void CGasBox::LoadComponent(FILE * pFile)
{
}

CComponent * CGasBox::clone()
{
	return new CGasBox(*this);
}
