#pragma once
#include "../Game.h"
#include "../Renderer.h"
class CTextureRenderer :
	public CRenderer
{
private:
	class CTexture* m_pTexture;
	CVector2 m_Size;
	COLORREF	m_tColorKey;
	float			m_fAlpha;
	bool			m_bColorKeyEnable;

public :
	void SetSize(float fWidth, float fHeight)
	{
		m_Size = CVector2(fWidth, fHeight);
	}
	void SetSize(CVector2 size)
	{
		m_Size = size;
	}
	void SetColorKey(int r, int g, int b)
	{
		m_tColorKey = RGB(r, g, b);
	}
	void SetColorKeyEnable(bool bEnable)
	{
		m_bColorKeyEnable = bEnable;
	}

	COLORREF GetColorKey() const
	{
		return m_tColorKey;
	}
	bool GetColorKeyEnable() const
	{
		return m_bColorKeyEnable;
	}
	float GetAlpha() const
	{
		return m_fAlpha;
	}
	CVector2 GetSize() const
	{
		return m_Size;
	}
	class CTexture* GetTexture() const
	{
		return m_pTexture;
	}
	void SetTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey);
	void SetTexture(const string& strKey);

public :

	void Render() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CTextureRenderer(const CTextureRenderer& component);
	CTextureRenderer();
	~CTextureRenderer();
};

