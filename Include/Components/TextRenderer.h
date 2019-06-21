#pragma once
#include "../Renderer.h"
class CTextRenderer :
	public CRenderer
{
private:
	CVector2 m_ScreenPosition;
	COLORREF m_tTextColor;
	int				m_iTextSize;
	wstring		m_strText;
	UINT			m_tAlign;
	HFONT		m_tFont;

public:

	void SetAlign(UINT tMode)
	{
		m_tAlign = tMode;
	}

	void SetTextSize(int iSize)
	{
		m_iTextSize = iSize;
		m_tFont =CreateFont(m_iTextSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_MODERN, TEXT("µ¸¿ò"));

	}
	void SetPosition(CVector2 pos)
	{
		m_ScreenPosition = pos;
	}
	void SetPosition(float x, float y)
	{
		m_ScreenPosition = CVector2(x, y);
	}
	CVector2 GetPosition() const
	{
		return m_ScreenPosition;
	}
	void SetColor(COLORREF tColor)
	{
		m_tTextColor = tColor;
	}
	void SetColor(unsigned char r, unsigned char g, unsigned char b)
	{
		m_tTextColor = RGB(r, g, b);
	}
	COLORREF GetColor() const
	{
		return m_tTextColor;
	}

	void SetText(const wstring& strText)
	{
		m_strText = strText;
	}
	wstring GetText() const
	{
		return m_strText;
	}




public:
	void Render() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CTextRenderer(const CTextRenderer& component);
	CTextRenderer();
	~CTextRenderer();
};

