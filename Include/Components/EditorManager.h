#pragma once
#include "../Component.h"
class CEditorManager :
	public CComponent
{
private:
	enum EDIT_STATE
	{
		ES_TILE,
		ES_HEIGHT,
		ES_MOVE,
		ES_DOODAD,
		ES_RESOURCE
	};

private:
	EDIT_STATE m_eState;

	list<class CGameObject*> m_ObjectList;

	vector<class CGameObject*> m_vecResources;
	int m_iCurrentResourceIndex;
	int m_iCurrentTileIndex;
	int m_iCurrentTileSetIndex;
	int m_iTileSetSize;

public:
	static wchar_t m_strText[LONG_MAX_PATH];
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:

	EDIT_STATE GetEditState()  const
	{
		return m_eState;
	}


	void AddGameObject(class CGameObject* pGameObject);

	void SetNextTileSet();
	void SetNextTile();
	void SetNextResource();
	void SetPrevTileSet();
	void SetPrevTile();
	void SetPrevResource();

	void SaveMap(const string& strFileName);
	void LoadMap(const string& strFileName);

	void LateUpdate() override;
	void Initialize();

	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;
public:
	CEditorManager(const CEditorManager& component);
	CEditorManager();
	~CEditorManager();
};

