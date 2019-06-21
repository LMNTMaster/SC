#include "ProgressBar.h"
#include "Transform.h"
#include "../Texture.h"
#include "../ResourceManager.h"

void CProgressBar::Render()
{
	CVector2 renderSize = CVector2(m_Size.x * m_pTransform->GetPivot().x * m_pTransform->GetScale().x,
		m_Size.y * m_pTransform->GetPivot().y * m_pTransform->GetScale().y);

	CVector2 position = m_pTransform->GetPosition() - renderSize;
	CTexture* pBackgroundTexture = GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_ProgressBar_Background");
	CTexture* pForegroundTexture = GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_ProgressBar_Foreground");


	BitBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
		position.x, position.y,
		pBackgroundTexture->GetTextureInfo().bmWidth,
		pBackgroundTexture->GetTextureInfo().bmHeight,
		pBackgroundTexture->GetDC(), 0, 0,
		SRCCOPY);

	BitBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
		position.x, position.y,
		pForegroundTexture->GetTextureInfo().bmWidth * m_fProgress,
		pForegroundTexture->GetTextureInfo().bmHeight,
		pForegroundTexture->GetDC(), 0, 0,
		SRCCOPY);
}


void CProgressBar::SaveComponent(FILE * pFile)
{
}

void CProgressBar::LoadComponent(FILE * pFile)
{
}

CComponent * CProgressBar::clone()
{
	return nullptr;
}

CProgressBar::CProgressBar(const CProgressBar & component)
{
}

CProgressBar::CProgressBar()
{
}


CProgressBar::~CProgressBar()
{
}
