#include "TextRenderer.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../Core.h"


void CTextRenderer::Render()
{
	HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();

	SelectObject(dc, m_tFont);
	SetTextAlign(dc, m_tAlign);
	SetTextColor(dc, m_tTextColor);
	SetBkMode(dc, TRANSPARENT);
	TextOut(dc, m_ScreenPosition.x, m_ScreenPosition.y, m_strText.c_str(), m_strText.length());
}

void CTextRenderer::SaveComponent(FILE * pFile)
{
}

void CTextRenderer::LoadComponent(FILE * pFile)
{
}

CComponent * CTextRenderer::clone()
{
	return new CTextRenderer(*this);
}

CTextRenderer::CTextRenderer(const CTextRenderer & component) :
	m_iTextSize(25),
	m_tAlign(TA_CENTER)
{

	m_tFont = CreateFont(m_iTextSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_MODERN, TEXT("¸¼Àº °íµñ"));

	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_TEXT_RENDERER;
}

CTextRenderer::CTextRenderer() :
	m_iTextSize(25),
	m_tAlign(TA_CENTER)
{
	m_tFont = CreateFont(m_iTextSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_MODERN, TEXT("¸¼Àº °íµñ"));

	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_TEXT_RENDERER;
}


CTextRenderer::~CTextRenderer()
{
}
