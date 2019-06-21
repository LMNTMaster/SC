#pragma once
#include "../Renderer.h"
class CMinimapRenderer :
	public CRenderer
{
private:
	CVector2 m_Size;

	class CTexture* m_pBaseTexture;
	class CTexture* m_pFogTexture;


public:
	void SetSize(float fWidth, float fHeight)
	{
		m_Size.x = fWidth;
		m_Size.y = fHeight;
	}
	void SetSize(CVector2 size)
	{
		m_Size = size;
	}

	CVector2 GetSize() const
	{
		return m_Size;
	}

	void SetMinimapPixel(int iTileIndex, COLORREF color);
	void SetMinimapPixel(int iTileIndex, FOW tFogState);
	void SetBasePixel(int iTileIndex, bool bBlended);
	void SetBlackPixel(int iTileIndex);

public:
	void Start() override;
	void Render() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;


public:
	CMinimapRenderer(const CMinimapRenderer& component);
	CMinimapRenderer();
	~CMinimapRenderer();
};

