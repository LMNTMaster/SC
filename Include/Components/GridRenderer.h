#pragma once
#include "../Component.h"
#include "../Renderer.h"
class CGridRenderer :
	public CRenderer
{

private:
	unsigned int m_iWidthCount;
	unsigned int m_iHeightCount;

	unsigned int m_iCellWidth;
	unsigned int m_iCellHeight;

public :
	void SetWidthCount(unsigned int iWidth)
	{
		m_iWidthCount = iWidth;
	}
	void SetHeightCount(unsigned int iHeight)
	{
		m_iHeightCount = iHeight;
	}
	void SetCount(unsigned int iWidth, unsigned int iHeight)
	{
		m_iWidthCount = iWidth;
		m_iHeightCount = iHeight;
	}
	void SetCellWidth(unsigned int iWidth)
	{
		m_iCellWidth = iWidth;
	}
	void SetCellHeight(unsigned int iHeight)
	{
		m_iCellHeight = iHeight;
	}
	void SetCellSize(CVector2 size)
	{
		m_iCellWidth = size.x;
		m_iCellHeight = size.y;
	}
	void SetCellSize(unsigned int iWidth, unsigned int iHeight)
	{
		m_iCellWidth = iWidth;
		m_iCellHeight = iHeight;
	}

	CVector2 GetTotalSize() const
	{
		return CVector2(m_iWidthCount, m_iHeightCount);
	}
	unsigned int GetCellWidth() const
	{
		return m_iCellWidth;
	}
	unsigned int GetCellHeight() const
	{
		return m_iCellHeight;
	}
	CVector2 GetCellSize() const
	{
		return CVector2(m_iCellWidth, m_iCellHeight);
	}
	
public:

	void Render() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CGridRenderer(const CGridRenderer& component);
	CGridRenderer();
	~CGridRenderer();
};

