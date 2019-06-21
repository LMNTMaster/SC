#pragma once
#include "..\Renderer.h"
class CControlButton :
	public CRenderer
{
private:
	friend class CConsoleButtonManager;

private:
	class CConsoleButton* m_pButton;
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
	
	void SetConsoleButton(class CConsoleButton* pButton)
	{
		m_pButton = pButton;
	}
	class CConsoleButton* GetConsoleButton() const
	{
		return m_pButton;
	}


public:
	void Render() override;
	void Update() override;


public:
	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;
public:
	CControlButton(const CControlButton& component);
	CControlButton();
	~CControlButton();
};

