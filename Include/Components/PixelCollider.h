#pragma once
#include "../Collider.h"
class CPixelCollider :
	public CCollider
{
private:
	vector<PIXEL> m_vecPixel;
	int		m_iWidth;
	int		m_iHeight;

public:
	const vector<PIXEL>& GetPixel() const
	{
		return m_vecPixel;
	}
	int GetWidth() const
	{
		return m_iWidth;
	}
	int GetHeight() const
	{
		return m_iHeight;
	}

	void SetPixel(class CTexture* pTexture);


public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;


public:
	CPixelCollider(const CPixelCollider& component);
	CPixelCollider();
	~CPixelCollider();
};

