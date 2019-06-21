#include "TextureRenderer.h"
#include "../Core.h"
#include "Transform.h"
#include "../ResourceManager.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "../Texture.h"
#include "../Components/Camera.h"



void CTextureRenderer::SetTexture(const string & strKey,	const wchar_t * pFileName, const string & strPathKey)
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = NULL;
	}
	m_pTexture = GET_SINGLE(CResourceManager)->LoadTexture(	strKey, pFileName, strPathKey);
}

void CTextureRenderer::SetTexture(const string & strKey)
{
	//if (m_pTexture)
	//{
	//	delete m_pTexture;
	//	m_pTexture = NULL;
	//}
	m_pTexture = GET_SINGLE(CResourceManager)->FindTexture(strKey);
}

void CTextureRenderer::Render()
{		
	CVector2 renderSize = CVector2(m_Size.x * m_pTransform->GetPivot().x * m_pTransform->GetScale().x,
		m_Size.y * m_pTransform->GetPivot().y * m_pTransform->GetScale().y);

	CVector2 position = m_pTransform->GetPosition() - renderSize;	
	
	position -= m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();
	CVector2 screen = GET_SINGLE(CCore)->GetScreenSize();
	//카메라 밖으로 일정 이상 나갔을 때, 그리지 않는다. 
	if (position.x < -128 || position.x >= screen.x + 128 || position.y < -128 || position.y >= screen.y + 128)
	{
		return;
	}

	TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
		position.x, position.y,
		m_Size.x * m_pTransform->GetScale().x,
		m_Size.y * m_pTransform->GetScale().y,
		m_pTexture->GetDC(), 0, 0,
		m_pTexture->GetTextureInfo().bmWidth,
		m_pTexture->GetTextureInfo().bmHeight,
		m_tColorKey);



	//BLENDFUNCTION blendOption;
	//blendOption.AlphaFormat = AC_SRC_ALPHA;
	//blendOption.BlendFlags = 0;
	//blendOption.BlendOp = AC_SRC_OVER;
	//blendOption.SourceConstantAlpha = 255;
	//
	//AlphaBlend(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
	//	position.x,
	//	position.y,
	//	m_Size.x * m_pTransform->GetScale().x,
	//	m_Size.y * m_pTransform->GetScale().y,
	//	m_pTexture->GetDC(), 0, 0,
	//	m_pTexture->GetTextureInfo().bmWidth,
	//	m_pTexture->GetTextureInfo().bmHeight,
	//	blendOption);



	//BitBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
	//	position.x,
	//	position.y,
	//	m_Size.x * m_pTransform->GetScale().x,
	//	m_Size.y * m_pTransform->GetScale().y,
	//	m_pTexture->GetDC(),
	//	0, 0,
	//	SRCCOPY
	//);

	//HDC stretchDC = CreateCompatibleDC(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC());
	//HDC alphaDC= CreateCompatibleDC(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC());	
	//HBITMAP stretchBit;
	//HBITMAP alphaBit;
	//
	//stretchBit = CreateCompatibleBitmap(
	//	GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
	//	GET_SINGLE(CResourceManager)->GetBackBuffer()->GetTextureInfo().bmWidth,
	//	GET_SINGLE(CResourceManager)->GetBackBuffer()->GetTextureInfo().bmHeight);
	//alphaBit = CreateCompatibleBitmap(
	//	GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
	//	GET_SINGLE(CResourceManager)->GetBackBuffer()->GetTextureInfo().bmWidth,
	//	GET_SINGLE(CResourceManager)->GetBackBuffer()->GetTextureInfo().bmHeight);
	//
	//SelectObject(stretchDC, stretchBit);
	//SelectObject(alphaDC, alphaBit);

	//StretchBlt(stretchDC,
	//	0, 0,
	//	m_Size.x * transform->GetScale().x,
	//	m_Size.y * transform->GetScale().y,
	//	m_pTexture->GetDC(), 0, 0,
	//	m_pTexture->GetTextureInfo().bmWidth,
	//	m_pTexture->GetTextureInfo().bmHeight,
	//	SRCCOPY);

	

	//DeleteObject(alphaBit);
	//DeleteObject(stretchBit);	
	
	//DeleteDC(alphaDC);
	//DeleteDC(stretchDC); 	
}

void CTextureRenderer::SaveComponent(FILE * pFile)
{
}

void CTextureRenderer::LoadComponent(FILE * pFile)
{
}

CComponent * CTextureRenderer::clone()
{
	return new CTextureRenderer(*this);
}

CTextureRenderer::CTextureRenderer(const CTextureRenderer & component)
{
	//Texture는 직접 이미지객체를 변경하지 않기때문에, 그냥 주소를 가져다 쓴다.
	m_pTexture = component.m_pTexture;
	m_Size = component.m_Size;
	m_tColorKey = component.m_tColorKey;
	m_fAlpha = component.m_fAlpha;
	m_bColorKeyEnable = component.m_bColorKeyEnable;

	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_TEXTURE_RENDERER;
}

CTextureRenderer::CTextureRenderer() :
	m_pTexture(NULL),
	m_bColorKeyEnable(false),
	m_tColorKey(RGB(255, 0, 255))
{
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_TEXTURE_RENDERER;
}


CTextureRenderer::~CTextureRenderer()
{
}
