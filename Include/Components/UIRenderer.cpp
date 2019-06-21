#include "UIRenderer.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "Transform.h"
#include "../GameObject.h"
#include "../Input.h"


void CUIRenderer::SetTexture(CTexture * pTexture)
{
	m_pTexture = pTexture;
}

void CUIRenderer::SetTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = NULL;
	}
	m_pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strKey, pFileName, strPathKey);
}


// Transform의 Position 을 Screen좌표계로 사용한다.
void CUIRenderer::Render()
{	


	CVector2 renderSize = CVector2(m_Size.x * m_pTransform->GetPivot().x * m_pTransform->GetScale().x,
		m_Size.y * m_pTransform->GetPivot().y * m_pTransform->GetScale().y);
	
	 CVector2 position = m_pTransform->GetPosition() - renderSize;
	
	//if (m_pGameObject->GetName() == "MineralIcon")
	//{
	//	int Count = position.x;
	//	Count = position.y;
	//	Count = m_Size.x * m_pTransform->GetScale().x;
	//	Count = m_Size.y * m_pTransform->GetScale().y;
	//	m_pTexture->GetTextureInfo().bmWidth;
	//	m_pTexture->GetTextureInfo().bmHeight;
	//	// 레이어가 문제다.
	//	// 
	//}

	
	TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
		position.x, position.y,
		m_Size.x * m_pTransform->GetScale().x,
		m_Size.y * m_pTransform->GetScale().y,
		m_pTexture->GetDC(), 
		0, 0,
		m_pTexture->GetTextureInfo().bmWidth,
		m_pTexture->GetTextureInfo().bmHeight,
		RGB(0, 0, 0));

	
}

void CUIRenderer::SaveComponent(FILE * pFile)
{
}

void CUIRenderer::LoadComponent(FILE * pFile)
{
}

CComponent * CUIRenderer::clone()
{
	return new CUIRenderer(*this);
}

CUIRenderer::CUIRenderer(const CUIRenderer & component)
{
	m_Size = component.m_Size;
	m_pTexture = component.m_pTexture;
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_UI_RENDERER;
}

CUIRenderer::CUIRenderer():
	m_pTexture(NULL)
{
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_UI_RENDERER;
}


CUIRenderer::~CUIRenderer()
{
}
