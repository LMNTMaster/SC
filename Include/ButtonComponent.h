#pragma once
#include "Component.h"
class CButtonComponent :
	public CComponent
{
protected:
	class CConsoleButton* m_pButton;

	//�ǹ� ���� ��, 
	//Page1 : �ǹ� ���� ������
	//Page2 : ���� �� ���.
	//2������ ó�� ��������, m_pButton���� ���� ��, m_vecButtonPage1�� ȣ��ǰ�,
	//Page�� �� Button�� �Ǵٽ� NextPage�� ������ ����.
	//����, vecButtonPage�� m_pButton���� ������ �־�� ��.
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

