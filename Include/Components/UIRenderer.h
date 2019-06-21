#pragma once
#include "../Renderer.h"
class CUIRenderer :
	public CRenderer
{
private:
	CVector2 m_Size;

	class CTexture* m_pTexture;

public:

	class CTexture* GetTexture() const
	{
		return m_pTexture;
	}	

	CVector2 GetSize() const
	{
		return m_Size;
	}
	void SetTexture(class CTexture* pTexture);
	void SetTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey);
	
	void SetSize(float width, float height)
	{
		m_Size = CVector2(width, height);
	}
	void SetSIze(CVector2 size)
	{
		m_Size = size;	
	}

public:
	void Render() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;



public:
	CUIRenderer(const CUIRenderer& component);
	CUIRenderer();
	~CUIRenderer();
};

