#pragma once
#include "Component.h"
class CButtonComponent :
	public CComponent
{
protected:
	class CConsoleButton* m_pButton;

	//건물 지을 때, 
	//Page1 : 건물 선택 페이지
	//Page2 : 선택 후 취소.
	//2페이지 처럼 보이지만, m_pButton에서 선택 후, m_vecButtonPage1이 호출되고,
	//Page의 각 Button은 또다시 NextPage를 가지고 있음.
	//따라서, vecButtonPage는 m_pButton에서 가지고 있어야 함.
public:
	class CConsoleButton* GetConsoleButton() const
	{
		return m_pButton;
	}
	void SetConsoleButton(class CConsoleButton* pButton)
	{
		m_pButton = pButton;
	}

public:
	CButtonComponent();
	virtual ~CButtonComponent();
};

