#include "PixelCollider.h"
#include "../Texture.h"


void CPixelCollider::SetPixel(CTexture * pTexture)
{
	m_vecPixel.clear();
	m_vecPixel = *pTexture->GetPixel();

	m_iWidth = pTexture->GetTextureInfo().bmWidth;
	m_iHeight = pTexture->GetTextureInfo().bmHeight;

	PPIXEL pPixelArr = new PIXEL[m_iWidth];

	for (int i = 0; i < m_iHeight / 2; ++i)
	{
		memcpy(pPixelArr, &m_vecPixel[i * m_iWidth], sizeof(PIXEL) * m_iWidth);
		memcpy(&m_vecPixel[i * m_iWidth], &m_vecPixel[(m_iHeight - i - 1) * m_iWidth],
			sizeof(PIXEL) * m_iWidth);
		memcpy(&m_vecPixel[(m_iHeight - i - 1) * m_iWidth], pPixelArr,
			sizeof(PIXEL) * m_iWidth);
	}
	delete[] pPixelArr;

	//벡터에 원본 받아서 상하 반전시켜서 보관
}

void CPixelCollider::SaveComponent(FILE * pFile)
{
}

void CPixelCollider::LoadComponent(FILE * pFile)
{
}

CComponent * CPixelCollider::clone()
{
	return new CPixelCollider(*this);
}

CPixelCollider::CPixelCollider(const CPixelCollider & component)
{
	m_iWidth = component.m_iWidth;
	m_iHeight = component.m_iHeight;
	//고비용
	m_vecPixel = component.m_vecPixel;

	m_eType = COLLIDER_TYPE::PIXEL;
	m_eComponentType = CT_PIXEL_COLLIDER;
	m_eComponentParentType = PT_COLLIDER;
}

CPixelCollider::CPixelCollider()
{
	m_eType = COLLIDER_TYPE::PIXEL;
	m_eComponentType = CT_PIXEL_COLLIDER;
	m_eComponentParentType = PT_COLLIDER;
}


CPixelCollider::~CPixelCollider()
{
}
