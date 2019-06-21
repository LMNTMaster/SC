#pragma once
#include "../Renderer.h"
class CRectangleRenderer :
	public CRenderer
{

private:
	CVector2 m_StartPosition;
	CVector2 m_EndPosition;
	COLORREF m_tColor;
	int			m_iThickness;

public:
	void SetThickness(int iThickness)
	{
		m_iThickness = iThickness;
	}
	void SetColor(COLORREF color)
	{
		m_tColor = color;
	}
	void SetStartPosition(CVector2 pos)
	{
		m_StartPosition = pos;
	}
	void SetEndPosition(CVector2 pos)
	{
		m_EndPosition = pos;
	}

	int GetThickness() const
	{
		return m_iThickness;
	}

	COLORREF GetColor()  const
	{
		return m_tColor;
	}

	CVector2 GetStartPosition() const
	{
		return m_StartPosition;
	}
	CVector2 GetEndPosition() const
	{
		return m_EndPosition;
	}

public:
	void Render() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CRectangleRenderer(const CRectangleRenderer& component);
	CRectangleRenderer();
	~CRectangleRenderer();
};

