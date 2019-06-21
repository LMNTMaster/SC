#pragma once
#include "../Renderer.h"
class CProgressBar :
	public CRenderer
{
private:
	float m_fProgress;
	CVector2 m_Size;

public:
	void SetSize(CVector2 size)
	{
		m_Size = size;
	}
	void SetSize(float fWidth, float fHeight)
	{
		m_Size = CVector2(fWidth, fHeight);
	}
	CVector2 GetSize() const
	{
		return m_Size;
	}
	void SetProgress(float fProgress)
	{
		m_fProgress = fProgress;
	}
	float GetProgress()  const
	{
		return m_fProgress;
	}

public:
	void Render() override;


public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CProgressBar(const CProgressBar& component);
	CProgressBar();
	~CProgressBar();
};

