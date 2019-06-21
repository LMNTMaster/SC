#include "InfoPanelButton.h"
#include "../Input.h"
#include "../Scene.h"
#include "../SceneManager.h"
#include "../InfoPanelManager.h"
#include "../Layer.h"
#include "../GameObject.h"
#include "../Component.h"
#include "Cursor.h"
#include "UnitInfo.h"

void CInfoPanelButton::CollisionStay()
{
	if (GETKEYDOWN(VK_LBUTTON))
	{
		CCursor* pCursor = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetLayer("System")->FindGameObject("Cursor")->GetComponent<CCursor>();
		pCursor->UnSelectAllUnit();
		m_pUnit->SetSelected(true);
		pCursor->m_SelectedUnitList.push_back(m_pUnit);
		GET_SINGLE(CInfoPanelManager)->UpdateInfoPanel(m_pUnit->GetComponent<CUnitInfo>());
	}
}

void CInfoPanelButton::SaveComponent(FILE * pFile)
{
	//DO NOTHING
}

void CInfoPanelButton::LoadComponent(FILE * pFile)
{
	//DO NOTHING
}

CComponent * CInfoPanelButton::clone()
{
	return new CInfoPanelButton(*this);
}

CInfoPanelButton::CInfoPanelButton(const CInfoPanelButton & component)
{
	//DO NOTHING
}

CInfoPanelButton::CInfoPanelButton()
{
}


CInfoPanelButton::~CInfoPanelButton()
{
}
