#pragma once
#include "..\Renderer.h"

//원의 중심을 기준으로 타원을 그린다.
//타원의 장축은 항상 단축의 2배이다.
class CEllipseRenderer :
	public CRenderer
{
private:
	float m_fMinorAxis;
	float m_fMajorAxisScale;
	COLORREF m_tColor;
	int		m_iThickness;
	CVector2 m_LocalPosition;

public:
	float GetMajorAxisScale() const
	{
		return m_fMajorAxisScale;
	}
	CVector2 GetLocalPosition() const
	{
		return m_LocalPosition;
	}
	float GetMinorAxisLength() const
	{
		return m_fMinorAxis;
	}	
	COLORREF GetColor() const
	{
		return m_tColor;
	}
	int GetThickness() const
	{
		return m_iThickness;
	}

	void SetMajorAxisScale(float fScale)
	{
		m_fMajorAxisScale = fScale;
	}
	void SetLocalPosition(float x, float y)
	{
		m_LocalPosition = CVector2(x, y);
	}
	void SetLocalPosition(CVector2 pos)
	{
		m_LocalPosition = pos;
	}
	void SetMinorAxisLength(float fLength)
	{
		m_fMinorAxis = fLength;
	}
	void SetColor(COLORREF tColor) 
	{
		m_tColor = tColor;
	}
	void SetColor(unsigned char r, unsigned char g, unsigned char b)
	{
		m_tColor = RGB(r,g,b);
	}
	void SetThickness(int iThickness)
	{
		m_iThickness = iThickness;
	}	
	

public :
	void Render() override;

	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CEllipseRenderer(const CEllipseRenderer& component);
	CEllipseRenderer();
	~CEllipseRenderer();
};

