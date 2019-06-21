#include "ConsoleButton.h"
#include "GameObject.h"
#include "Component.h"
#include "ConsoleButtonManager.h"
#include "ConsoleButton.h"
#include "Components\ControlButton.h"
#include "ButtonComponent.h"

void CConsoleButton::UpdateToNextPage() const
{
	
	GET_SINGLE(CConsoleButtonManager)->ClearControlPanel();
	for (int i = 0; i < 9; ++i)
	{
		CControlButton* pButton = GET_SINGLE(CConsoleButtonManager)->GetControlPanelObject(i)->GetComponent<CControlButton>();
		pButton->SetConsoleButton(m_vecNextButtonPage[i]);
	}
	
}

CConsoleButton::CConsoleButton()
	:m_bRequireCursor(true),
	m_bRequireBuildMode(false),
	m_pButtonComponent(NULL),
	m_eButtonState(BS_ENABLE)
{
		m_vecNextButtonPage.resize(9);
}


CConsoleButton::~CConsoleButton()
{
	for (int i = 0; i < m_vecNextButtonPage.size(); ++i)
	{
		if (m_vecNextButtonPage[i])
		{
			delete m_vecNextButtonPage[i];
		}
	}
	m_vecNextButtonPage.clear();

	//delete m_pButtonComponent->GetConsoleButton();
}
