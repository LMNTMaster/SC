#pragma once
#include "Game.h"

class CConsoleButton
{
private:
	friend class CConsoleButtonManager;
	
private:
	BUTTON_STATE m_eButtonState;
	class CButtonComponent* m_pButtonComponent;
	bool m_bRequireCursor;
	bool m_bRequireBuildMode;
	class CGameObject* m_pBuildTarget;
	bool m_bAdvancedBuild;

	string m_strButtonName;
	class CTexture* m_pUpBackgroundTexture;
	class CTexture* m_pDownBackgroundTexture;
	class CTexture* m_pUpIconTexture;
	class CTexture* m_pDownIconTexture;

	function<void(CVector2, class CGameObject*)> m_Function;
	int m_iShortcutKey;
	unsigned int m_iControlPanelIndex;


	bool m_bExistNextPage;
	vector<class CConsoleButton*> m_vecNextButtonPage;
	
public:
	void SetAdvanced(bool bAdvancedBuild)
	{
		m_bAdvancedBuild = bAdvancedBuild;
	}
	bool GetAdvanced()
	{
		return m_bAdvancedBuild;
	}
	class CGameObject* GetBuildTarget() const
	{
		return m_pBuildTarget;
	}
	void SetBuildTarget(class CGameObject* pTarget)
	{
		m_pBuildTarget = pTarget;
	}
	void SetRequireBuildMode(bool bBuildMode)
	{
		m_bRequireBuildMode = bBuildMode;
	}
	bool GetRequireBuildMode() const
	{
		return m_bRequireBuildMode;
	}
	void SetButtonState(BUTTON_STATE eState)
	{
		m_eButtonState = eState;
	}
	BUTTON_STATE GetButtonState() const
	{
		return m_eButtonState;
	}
	void SetNextPage(vector<class CConsoleButton*>& vecNextButtonPage)
	{
		m_vecNextButtonPage = vecNextButtonPage;
	}
	class CConsoleButton* GetNextPage(int idx)
	{
		return m_vecNextButtonPage[idx];
	}
	vector<class CConsoleButton*> GetNextPage()
	{
		return m_vecNextButtonPage;
	}
	bool GetExistNextPage() const
	{
		return m_bExistNextPage;
	}

	void SetExistNextPage(bool bExist)
	{
		m_bExistNextPage = bExist;
	}
	void UpdateToNextPage() const;

	void SetButtonComponent(class CButtonComponent* pComponent)
	{
		m_pButtonComponent = pComponent;
	}
	class CButtonComponent* GetButtonComponent() const
	{
		return m_pButtonComponent;
	}
	void SetRequireCursor(bool bState)
	{
		m_bRequireCursor = bState;
	}
	bool GetRequireCursor() const
	{
		return m_bRequireCursor;
	}
	unsigned int GetPanelIndex() const
	{
		return m_iControlPanelIndex;
	}
	void SetPanelIndex(unsigned int idx)
	{
		m_iControlPanelIndex = idx;
	}
	void SetFunction(function<void(CVector2, class CGameObject*)> func)
	{
		m_Function = func;
	}
	function<void(CVector2, class CGameObject*)> GetFunction()
	{
		return m_Function;
	}
	void RequestFunction(CVector2 position, class CGameObject* pTarget)
	{
		m_Function(position, pTarget);
	}
	void SetButtonName(const string& strName)
	{
		m_strButtonName = strName;
	}
	string GetButtonName() const
	{
		return m_strButtonName;
	}
	void SetShortcutKey(int iKey)
	{
		m_iShortcutKey = iKey;
	}
	int GetShortcutKey() const
	{
		return m_iShortcutKey;
	}

	void SetUpBackgroundTexture(class CTexture* pTexture)
	{
		m_pUpBackgroundTexture = pTexture;
	}
	void SetDownBackgroundTexture(class CTexture* pTexture)
	{
		m_pDownBackgroundTexture = pTexture;
	}
	void SetUpIconTexture(class CTexture* pTexture)
	{
		m_pUpIconTexture = pTexture;
	}
	void SetDownIconTexture(class CTexture* pTexture)
	{
		m_pDownIconTexture = pTexture;
	}
	
	class CTexture* GetUpBackgroundTexture() const
	{
		return m_pUpBackgroundTexture;
	}
	class CTexture* GetDownBackgroundTexture() const
	{
		return m_pDownBackgroundTexture;
	}
	class CTexture* GetUpIconTexture() const
	{
		return m_pUpIconTexture;
	}
	class CTexture* GetDownIconTexture() const
	{
		return m_pDownIconTexture;
	}

public:
	CConsoleButton();
	~CConsoleButton();
};

