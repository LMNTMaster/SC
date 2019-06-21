#include "EditorManager.h"
#include "../Core.h"
#include "Camera.h"
#include "../Scene.h"
#include "../GameObject.h"
#include "Transform.h"
#include "../Component.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../Tile.h"
#include "../Input.h"
#include "TerrainRenderer.h"
#include "../Layer.h"
#include "../Components/SpriteRenderer.h"
#include "../Components/CircleCollider.h"
#include "../Components/EllipseRenderer.h"

wchar_t CEditorManager::m_strText[LONG_MAX_PATH] = {};

INT_PTR CEditorManager::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			// Edit Box에서 문자열을 얻어온다.
			memset(m_strText, 0, sizeof(wchar_t) * LONG_MAX_PATH);
			GetDlgItemText(hWnd, IDC_EDIT1, m_strText, LONG_MAX_PATH);
		case IDCANCEL:
			EndDialog(hWnd, IDOK);
			return TRUE;
		}
		return FALSE;
	}

	return FALSE;
}

void CEditorManager::AddGameObject(CGameObject * pGameObject)
{
	if (pGameObject->GetComponent<class CStructure>())
	{
		m_ObjectList.push_back(pGameObject);
	}
}

void CEditorManager::SetNextTileSet()
{
	if (m_iTileSetSize - 1 == m_iCurrentTileSetIndex)
	{
		m_iCurrentTileSetIndex = 0;
		while (true)
		{
			if (GET_SINGLE(CResourceManager)->GetTileSet(m_iCurrentTileSetIndex).size() > 0)
			{
				break;
			}
			else
			{
				++m_iCurrentTileSetIndex;
			}
		}
	}
	else
	{
		++m_iCurrentTileSetIndex;
		while (true)
		{
			if (GET_SINGLE(CResourceManager)->GetTileSet(m_iCurrentTileSetIndex).size() > 0)
			{
				break;
			}
			else
			{
				++m_iCurrentTileSetIndex;
			}
		}
		m_iCurrentTileIndex = 0;
	}	
}

void CEditorManager::SetNextTile()
{
	if (m_iCurrentTileIndex == GET_SINGLE(CResourceManager)->GetTileSet(m_iCurrentTileSetIndex).size() - 1)
	{
		m_iCurrentTileIndex = 0;
	}
	else
	{
		++m_iCurrentTileIndex;
	}
}

void CEditorManager::SetNextResource()
{
	if (m_iCurrentResourceIndex == m_vecResources.size() - 1)
	{
		m_iCurrentResourceIndex = 0;
	}
	else
	{
		++m_iCurrentResourceIndex;
	}
}

void CEditorManager::SetPrevTileSet()
{
	if (m_iCurrentTileSetIndex == 0)
	{
		m_iCurrentTileSetIndex = m_iTileSetSize- 1;
		while (true)
		{
			if (GET_SINGLE(CResourceManager)->GetTileSet(m_iCurrentTileSetIndex).size() > 0)
			{
				break;
			}
			else
			{
				--m_iCurrentTileSetIndex;
			}
		}
	}
	else
	{
		--m_iCurrentTileSetIndex;
		m_iCurrentTileIndex = 0;
	}
}

void CEditorManager::SetPrevTile()
{
	if (m_iCurrentTileIndex == 0)
	{
		m_iCurrentTileIndex = GET_SINGLE(CResourceManager)->GetTileSet(m_iCurrentTileSetIndex).size() - 1;
	}
	else
	{
		--m_iCurrentTileIndex;
	}
}

void CEditorManager::SetPrevResource()
{
	if (m_iCurrentResourceIndex == 0)
	{
		m_iCurrentResourceIndex = m_vecResources.size() - 1;
	}
	else
	{
		--m_iCurrentResourceIndex;
	}
}

void CEditorManager::SaveMap(const string & strFileName)
{
	FILE* pFile = NULL;

	char strFullPath[LONG_MAX_PATH] = {};
	strcpy(strFullPath, GET_SINGLE(CResourceManager)->FindPathMultiByte(MAP_PATH));
	strcat(strFullPath, strFileName.c_str());
	fopen_s(&pFile, strFullPath, "wb");

	if (pFile)
	{
		//그리드 타일 수 저장
		int iGridWidth = m_pGameObject->GetScene()->GetGridSize().x;
		fwrite(&iGridWidth, 4, 1, pFile);
		int iGridHeight = m_pGameObject->GetScene()->GetGridSize().y;
		fwrite(&iGridHeight, 4, 1, pFile);

		int iLength = iGridWidth * iGridHeight;

		for (int i = 0; i < iLength; ++i)
		{
			CTile* pTile = m_pGameObject->GetComponent<CTerrainRenderer>()->GetTile(i);
			int iTileKey =	pTile->GetTileID();
			CVector2 TilePosition = pTile->GetWorldPosition();
			bool bMovable = pTile->GetMovable();
			int iTileHeight = pTile->GetTerrainHeight();

			//타일 정보 저장
			fwrite(&iTileKey, 4, 1, pFile);
			fwrite(&TilePosition, sizeof(CVector2), 1, pFile);
			fwrite(&bMovable, 1, 1, pFile);
			fwrite(&iTileHeight, 4, 1, pFile);
		}

		iLength = m_ObjectList.size();

		//오브젝트 갯수 저장
		fwrite(&iLength, 4, 1, pFile);

		list<CGameObject*>::iterator iter;
		list<CGameObject*>::iterator iterEnd = m_ObjectList.end();
		for (iter = m_ObjectList.begin(); iter != iterEnd; ++iter)
		{
			char strKey[256] = {};
			strcpy(strKey, (*iter)->GetKey().c_str());			
			iLength = strlen(strKey);

			CVector2 position = (*iter)->GetTransform()->GetPosition();
			CVector2 pivot = (*iter)->GetTransform()->GetPivot();
			vector<CVector2> buildTile = (*iter)->GetComponent<CStructure>()->GetBuildableTile();
			vector<unsigned int> builtTileIndex = (*iter)->GetComponent<CStructure>()->GetBuiltTileIndex();
			int size1 = buildTile.size();
			int size2 = builtTileIndex.size();
			//오브젝트 이름 저장
			fwrite(&iLength, 4, 1, pFile);
			fwrite(&strKey, 1, iLength, pFile);
			//오브젝트의 위치 저장
			fwrite(&position, sizeof(CVector2), 1, pFile);
			fwrite(&pivot, sizeof(CVector2), 1, pFile);
			fwrite(&size1, 4, 1, pFile);
			fwrite(&size2, 4, 1, pFile);
			for (int i = 0; i < size1; ++i)
			{
				CVector2 temp = buildTile[i];
				fwrite(&temp, sizeof(CVector2), 1, pFile);
			}
			for (int i = 0; i < size2; ++i)
			{
				unsigned int temp = builtTileIndex[i];
				fwrite(&temp, 4, 1, pFile);
			}

			//SpriteRenderer의 디폴트 AnimationClip Key 저장
			char strAnimationClipKey[256] = {};			
			strcpy(strAnimationClipKey,	(*iter)->GetComponent<CSpriteRenderer>()->GetCurrentClipKey().c_str());

			int iAnimationClipKeyLength = strlen(strAnimationClipKey);
			fwrite(&iAnimationClipKeyLength, 4, 1, pFile);
			fwrite(&strAnimationClipKey, 1, iAnimationClipKeyLength, pFile);
		}

		fclose(pFile);
	}
}

void CEditorManager::LoadMap(const string & strFileName)
{
	FILE* pFile = NULL;

	char strFullPath[LONG_MAX_PATH] = {};
	strcpy(strFullPath, GET_SINGLE(CResourceManager)->FindPathMultiByte(MAP_PATH));
	strcat(strFullPath, strFileName.c_str());
	fopen_s(&pFile, strFullPath, "rb");

	if (pFile)
	{
		//타일 갯수 읽어옴
		int iGridWidth= 0; 
		fread(&iGridWidth, 4, 1, pFile);
		int iGridHeight = 0;
		fread(&iGridHeight, 4, 1, pFile);

		int iLength = iGridWidth * iGridHeight;

		for (int i = 0; i < iLength; ++i)
		{			
			if (i == 255)
			{
				int a = 151;
			}
			CVector2 TilePosition ;
			bool bMovable = false;
			int iTileHeight = 0;
			int iTileKey = 0;
			//타일 정보 불러오기
			fread(&iTileKey, 4, 1, pFile);
			fread(&TilePosition, sizeof(CVector2), 1, pFile);
			fread(&bMovable, 1, 1, pFile);
			fread(&iTileHeight, 4, 1, pFile);

			CTile * pTile = GET_SINGLE(CResourceManager)->GetTileSet((int)(i / 128))[ i % 128]->clone();
			//pTile->SetCamera(m_pGameObject->GetScene()->GetCamera()); // 아래에 ChangeTile에서 해주니 딱히 안해줘도 됨
			pTile->SetMovable(bMovable);
			pTile->SetWorldPosition(TilePosition);
			pTile->SetTerrainHeight(iTileHeight);
			//불러온 타일은 현재 TerrainRenderer에 옮겨준다.

			m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile(i, pTile);
		}

		iLength = 0;

		//오브젝트 갯수 저장
		fread(&iLength, 4, 1, pFile);

		for (int i = 0; i < iLength; ++i)
		{
			int iKeyLength = 0;
			char strKey[256] = {};

			fread(&iKeyLength, 4, 1, pFile);
			fread(&strKey, 1, iKeyLength, pFile);

			CGameObject* pGameObject = GET_SINGLE(CResourceManager)->FindUnit(string(strKey))->clone();


			CVector2 position;
			CVector2 pivot;
			vector<CVector2> buildTile ;
			vector<unsigned int> builtTileIndex ;
			int buildTileSize = 0;
			int builtTileIndexSize = 0;

			fread(&position, sizeof(CVector2), 1, pFile);
			fread(&pivot, sizeof(CVector2), 1, pFile);
			fread(&buildTileSize, 4, 1, pFile);
			fread(&builtTileIndexSize, 4, 1, pFile);

			pGameObject->GetTransform()->SetPosition(position);
			pGameObject->GetTransform()->SetPivot(pivot);
			pGameObject->GetComponent<CStructure>()->ClearBuildableTile();
			pGameObject->GetComponent<CStructure>()->ClearBuiltTileIndex();
			
			for (int j = 0; j < buildTileSize; ++j)
			{
				CVector2 temp;
				fread(&temp, sizeof(CVector2), 1, pFile);
				pGameObject->GetComponent<CStructure>()->AddBuildableTile(temp.x,temp.y);
			}
			for (int j = 0; j < builtTileIndexSize; ++j)
			{
				unsigned int temp = 0;
				fread(&temp, 4, 1, pFile);
				pGameObject->GetComponent<CStructure>()->AddBuiltTileIndex(temp);
			}

			int iAnimationClipKeyLength = 0;
			char strAnimationClipKey[256] = {};

			fread(&iAnimationClipKeyLength, 4, 1, pFile);
			fread(&strAnimationClipKey, 1, iAnimationClipKeyLength, pFile);

			m_ObjectList.push_back(pGameObject);
			m_pGameObject->GetScene()->FindLayer("UnitLayer")->AddGameObject(pGameObject);

			pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip(string(strAnimationClipKey));
		}
		fclose(pFile);
	}
}

void CEditorManager::LateUpdate()
{

	HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GET_SINGLE(CCore)->GetWindowHandle(), &pos);
	CVector2 cursorPosition = CVector2(pos.x, pos.y);
	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->GameObject()->GetTransform()->GetPosition();
	CVector2 cursorWorldPosition = cursorPosition + cameraPosition;
	int gridX = (int)(cursorWorldPosition.x ) / 32;
	int gridY = (int)(cursorWorldPosition.y ) / 32;
	CVector2 translatePosition = CVector2(gridX * 32, gridY * 32);
	CVector2 worldToScreenPosition = translatePosition - cameraPosition;
	
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0,255,0));
	SelectObject(dc, pen);
	MoveToEx(dc, worldToScreenPosition.x, worldToScreenPosition.y, NULL);
	LineTo(dc, worldToScreenPosition.x  + 32, worldToScreenPosition.y);
	LineTo(dc, worldToScreenPosition.x  + 32, worldToScreenPosition.y + 32);
	LineTo(dc, worldToScreenPosition.x , worldToScreenPosition.y + 32);
	LineTo(dc, worldToScreenPosition.x , worldToScreenPosition.y);
	DeleteObject(pen);


	if (cursorPosition.x < 0 || cursorPosition.x > GET_SINGLE(CCore)->GetScreenSize().x || cursorPosition.y < 0 || cursorPosition.y > GET_SINGLE(CCore)->GetScreenSize().y)
		return;

	if (GETKEYDOWN('S'))
	{
		if (GETKEY(VK_LCONTROL))
		{
			
			DialogBox(GET_SINGLE(CCore)->GetInstanceHandle(), MAKEINTRESOURCE(IDD_DIALOG1),
				GET_SINGLE(CCore)->GetWindowHandle(), CEditorManager::DlgProc);

			char	strFileName[LONG_MAX_PATH] = {};
			WideCharToMultiByte(CP_ACP, 0, m_strText, -1, strFileName,
				lstrlen(m_strText), 0, 0);

			SaveMap(string(strFileName));
		}
	}
	if (GETKEYDOWN('O'))
	{
		if (GETKEY(VK_LCONTROL))
		{
			DialogBox(GET_SINGLE(CCore)->GetInstanceHandle(), MAKEINTRESOURCE(IDD_DIALOG1),
				GET_SINGLE(CCore)->GetWindowHandle(), CEditorManager::DlgProc);

			char	strFileName[LONG_MAX_PATH] = {};
			WideCharToMultiByte(CP_ACP, 0, m_strText, -1, strFileName,
				lstrlen(m_strText), 0, 0);

			LoadMap(string(strFileName));
		}
	}

	//클릭 시 해당 셀 (vector[GridY * GridSize.x + GridY])의 Tile을 교체함.
	if (GETKEYDOWN('Q'))
	{
		switch (m_eState)
		{
		case CEditorManager::ES_TILE:
		{
			SetPrevTile();
		}
			break;
		case CEditorManager::ES_HEIGHT:
			break;
		case CEditorManager::ES_MOVE:
			break;
		case CEditorManager::ES_DOODAD:
			break;
		case CEditorManager::ES_RESOURCE:
		{
			for each (CSpriteRenderer* i in m_vecResources[m_iCurrentResourceIndex]->GetComponents<CSpriteRenderer>())
			{
				i->SetEnable(false);
			}
			SetPrevResource(); 
		}
			break;
		default:
			break;
		}
	}
	if (GETKEYDOWN('E'))
	{
		switch (m_eState)
		{
		case CEditorManager::ES_TILE:
		{
			SetNextTile();
		}
		break;
		case CEditorManager::ES_HEIGHT:
			break;
		case CEditorManager::ES_MOVE:
			break;
		case CEditorManager::ES_DOODAD:
			break;
		case CEditorManager::ES_RESOURCE:
		{
			for each (CSpriteRenderer* i in m_vecResources[m_iCurrentResourceIndex]->GetComponents<CSpriteRenderer>())
			{
				i->SetEnable(false);
			}
			SetNextResource();
		}
			break;
		default:
			break;
		}
	}

	

	if (GETKEYDOWN('1'))
	{
		if (!GETKEY(VK_LSHIFT))
		{
			if (m_eState == ES_TILE)
			{
				SetNextTileSet();
			}
			else
			{
				m_eState = ES_TILE;
			}
		}
		else
		{
			if (m_eState == ES_TILE)
			{
				SetPrevTileSet();
			}
			else
			{
				m_eState = ES_TILE;
			}
		}
	}	
	if (GETKEYDOWN('2'))
	{
		if (m_eState == ES_MOVE)
		{
		}
		else
		{
			m_eState = ES_MOVE;
		}
	}
	if (GETKEYDOWN('3'))
	{
		if (m_eState == ES_HEIGHT)
		{
		}
		else
		{
			m_eState = ES_HEIGHT;
		}
	}
	if (GETKEYDOWN('4'))
	{
		if (m_eState == ES_RESOURCE)
		{
			
		}
		else
		{
			m_eState = ES_RESOURCE;
		}
	}
	if (GETKEYDOWN('5'))
	{
		if (m_eState == ES_DOODAD)
		{
		}
		else
		{
			m_eState = ES_DOODAD;
		}
	}


	switch (m_eState)
	{
	case CEditorManager::ES_TILE:
	{
		m_vecResources[m_iCurrentResourceIndex]->GetComponent<CSpriteRenderer>()->SetEnable(false);

		BLENDFUNCTION tBF;
		tBF.AlphaFormat = NULL;
		tBF.BlendFlags = NULL;
		tBF.BlendOp = AC_SRC_OVER;
		tBF.SourceConstantAlpha = 192;
		CTile* pTile = GET_SINGLE(CResourceManager)->GetTileSet(m_iCurrentTileSetIndex)[m_iCurrentTileIndex];

		AlphaBlend(dc, worldToScreenPosition.x, worldToScreenPosition.y, 32, 32,
			pTile->GetBaseTexture()->GetDC(),
			pTile->GetOffset().x * 32,
			pTile->GetOffset().y * 32,
			32, 32, tBF);

		if (GETKEY(VK_LBUTTON))
		{
			if (pTile->GetTileSetID() == 1)
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 1);
			}
			else if (pTile->GetTileSetID() == 2 || pTile->GetTileSetID() == 3)
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 2, 3);
			}
			else if (pTile->GetTileSetID() == 4 || pTile->GetTileSetID() == 5)
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 4,5);
			}
			else if (pTile->GetTileSetID() == 6 || pTile->GetTileSetID() == 7)
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 6,7);
			}
			else if (pTile->GetTileSetID() == 8 || pTile->GetTileSetID() == 9 || pTile->GetTileSetID() == 10 || pTile->GetTileSetID() == 11)
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 8, 9);
			}
			else if (pTile->GetTileSetID() == 12 || pTile->GetTileSetID() == 13 )
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 12, 13);
			}
			else if (pTile->GetTileSetID() == 14 || pTile->GetTileSetID() == 15 )
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 14, 15);
			}
			else if (pTile->GetTileSetID() == 16 || pTile->GetTileSetID() == 17)
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 16, 17);
			}
			else if (pTile->GetTileSetID() == 18 || pTile->GetTileSetID() == 19)
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 18, 19);
			}
			else if (pTile->GetTileSetID() == 20 || pTile->GetTileSetID() == 21)
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeRandomTileFromTileSet(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, 20, 21);
			}
			else if (pTile->GetTileSetID() == 22 || pTile->GetTileSetID() == 23 || pTile->GetTileSetID() == 24) //Cliff는 3타일이 한번에 찍힌다.
			{				
				//LTI
				unsigned int size = GET_SINGLE(CResourceManager)->GetTileSet(22).size();
				unsigned int idx = rand() % size;

				CTile* pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(22)[idx];
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, pFixedTile->GetTileID());
				pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(23)[idx];
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1) * m_pGameObject->GetScene()->GetGridSize().x + gridX, pFixedTile->GetTileID());
				//LTO
				pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(24)[idx];
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY ) * m_pGameObject->GetScene()->GetGridSize().x + (gridX - 1), pFixedTile->GetTileID());
				pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(25)[idx];
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 1), pFixedTile->GetTileID());
				//RTI
				pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(26)[idx];
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 1), pFixedTile->GetTileID());
				pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(27)[idx];
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 1), pFixedTile->GetTileID());
				//RTO
				pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(28)[idx];
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 2), pFixedTile->GetTileID());
				pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(29)[idx];
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 2), pFixedTile->GetTileID());
				//LBI : 2가지 중 랜덤하게 선택
				int randomLBI = rand() % 2;
				if (!randomLBI)
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(30)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(31)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(32)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 4)* m_pGameObject->GetScene()->GetGridSize().x + (gridX), pFixedTile->GetTileID());
				}
				else
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(33)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(34)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(35)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 4)* m_pGameObject->GetScene()->GetGridSize().x + (gridX), pFixedTile->GetTileID());
				}

				//LBO
				if (!randomLBI)
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(36)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 1), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(37)[idx];																								
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 1), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(38)[idx];																							
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 4)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 1), pFixedTile->GetTileID());
				}
				else
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(39)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 1), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(40)[idx];																							
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 1), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(41)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 4)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 1), pFixedTile->GetTileID());
				}

				//RBI
				if (!randomLBI)
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(42)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 1), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(43)[idx];																										
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 1), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(44)[idx];																										 
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 4)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 1), pFixedTile->GetTileID());
				}
				else
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(45)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 1), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(46)[idx];																										 
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 1), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(47)[idx];																								
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 4)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 1), pFixedTile->GetTileID());
				}

				//RBO
				if (!randomLBI)
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(48)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 2), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(49)[idx];																										
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 2), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(50)[idx];																											
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 4)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 2), pFixedTile->GetTileID());
				}
				else
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(51)[idx];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 2), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(52)[idx];																									 
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 2), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(53)[idx];																							 
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 4)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 2), pFixedTile->GetTileID());
				}

				//L
				int randomL = rand() % 2;
				if (!randomL)
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(54)[0];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 3), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(55)[0];				 																				
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 3), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(56)[0];				 																			
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 3), pFixedTile->GetTileID());

					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(54)[1];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 2), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(55)[1];																									
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 2), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(56)[1];																											
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 2), pFixedTile->GetTileID());
				}																																																				
				else																																																			
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(54)[2];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 3), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(55)[2];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 3), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(56)[2];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 3), pFixedTile->GetTileID());

					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(54)[3];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 2), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(55)[3];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 2), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(56)[3];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX - 2), pFixedTile->GetTileID());
				}

				//R
				int ramdomR = rand() % 2;
				if (!ramdomR)
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(57)[0];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 3), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(58)[0];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 3), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(59)[0];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 3), pFixedTile->GetTileID());

					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(57)[1];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 4), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(58)[1];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 4), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(59)[1];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 4), pFixedTile->GetTileID());
				}
				else
				{
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(57)[2];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 3), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(58)[2];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 3), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(59)[2];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 3), pFixedTile->GetTileID());

					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(57)[3];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 1)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 4), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(58)[3];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 2)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 4), pFixedTile->GetTileID());
					pFixedTile = GET_SINGLE(CResourceManager)->GetTileSet(59)[3];
					m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile((gridY + 3)* m_pGameObject->GetScene()->GetGridSize().x + (gridX + 4), pFixedTile->GetTileID());
				}
			}
			else
			{
				m_pGameObject->GetComponent<CTerrainRenderer>()->ChangeTile(gridY * m_pGameObject->GetScene()->GetGridSize().x + gridX, pTile->GetTileID());
			}
		}
	}
		break;
	case CEditorManager::ES_HEIGHT:

		m_vecResources[m_iCurrentResourceIndex]->GetComponent<CSpriteRenderer>()->SetEnable(false);
		break;
	case CEditorManager::ES_MOVE:
	{

		m_vecResources[m_iCurrentResourceIndex]->GetComponent<CSpriteRenderer>()->SetEnable(false);
		
		int idx = (gridY)* m_pGameObject->GetScene()->GetGridSize().x + gridX;

		BLENDFUNCTION tBF;
		tBF.AlphaFormat = NULL;
		tBF.BlendFlags = NULL;
		tBF.BlendOp = AC_SRC_OVER;
		tBF.SourceConstantAlpha = 64;

		AlphaBlend(dc, worldToScreenPosition.x, worldToScreenPosition.y, 32, 32,
			GET_SINGLE(CResourceManager)->FindTexture("NegativeCell")->GetDC(),
			0,	0,	32, 32, tBF);

		if (GETKEY(VK_LBUTTON))
		{
			if(idx < m_pGameObject->GetScene()->GetGridSize().x * m_pGameObject->GetScene()->GetGridSize().y)
				m_pGameObject->GetComponent<CTerrainRenderer>()->GetTile(idx)->SetMovable(false);
		}
		if (GETKEY(VK_RBUTTON))
		{
			if (idx < m_pGameObject->GetScene()->GetGridSize().x * m_pGameObject->GetScene()->GetGridSize().y)
				m_pGameObject->GetComponent<CTerrainRenderer>()->GetTile(idx)->SetMovable(true);
		}
	}
		break;
	case CEditorManager::ES_DOODAD:
		break;
	case CEditorManager::ES_RESOURCE:
	{
		int idx = (gridY)* m_pGameObject->GetScene()->GetGridSize().x + gridX;

		for each (CSpriteRenderer* i in m_vecResources[m_iCurrentResourceIndex]->GetComponents<CSpriteRenderer>())
		{
			i->SetEnable(true);
		}

		m_vecResources[m_iCurrentResourceIndex]->GetTransform()->SetPosition(worldToScreenPosition + cameraPosition + CVector2(0,32));

		BLENDFUNCTION tBF;
		tBF.AlphaFormat = NULL;
		tBF.BlendFlags = NULL;
		tBF.BlendOp = AC_SRC_OVER;
		tBF.SourceConstantAlpha = 128;
		CVector2 origin = m_vecResources[m_iCurrentResourceIndex]->GetComponent<CSpriteRenderer>()->GetSize();
		origin.x = origin.x * m_vecResources[m_iCurrentResourceIndex]->GetTransform()->GetPivot().x;
		origin.y = origin.y * m_vecResources[m_iCurrentResourceIndex]->GetTransform()->GetPivot().y;
		CVector2 LT = m_vecResources[m_iCurrentResourceIndex]->GetTransform()->GetPosition() - origin;
		LT -= cameraPosition;
		vector<CVector2> buildableTile = m_vecResources[m_iCurrentResourceIndex]->GetComponent<CStructure>()->GetBuildableTile();

		for (int i = 0; i < buildableTile.size(); ++i)
		{
			AlphaBlend(dc, LT.x + buildableTile[i].x * 32, LT.y + buildableTile[i].y * 32, 32, 32,
				GET_SINGLE(CResourceManager)->FindTexture("PositiveCell")->GetDC(),
				0, 0, 32, 32, tBF);
		}

		if (GETKEYDOWN(VK_LBUTTON))
		{
			CLayer* pLayer = m_pGameObject->GetScene()->FindLayer("UnitLayer");
			string clipKey = m_vecResources[m_iCurrentResourceIndex]->GetComponent<CSpriteRenderer>()->GetCurrentClipKey();
			CGameObject* pGameObject = m_vecResources[m_iCurrentResourceIndex]->clone();
			pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip(clipKey);			
			pGameObject->GetTransform()->SetPosition(worldToScreenPosition + cameraPosition + CVector2(0, 32));

			CVector2 worldPosition = worldToScreenPosition + cameraPosition;
			CVector2 worldLT = worldPosition - origin;

			pGameObject->GetComponent<CStructure>()->ClearBuiltTileIndex();
			for (int i = 0; i < buildableTile.size(); ++i)
			{
				CVector2 worldBuiltPosition = CVector2(worldLT.x + buildableTile[i].x * 32 + 16, worldLT.y + 32 + buildableTile[i].y * 32 + 16);
				int idxX = ((int)worldBuiltPosition.x) / 32;
				int idxY = ((int)worldBuiltPosition.y) / 32;
				int idx = idxY * m_pGameObject->GetScene()->GetGridSize().x + idxX;
				pGameObject->GetComponent<CStructure>()->AddBuiltTileIndex(idx);
			}

			m_ObjectList.push_back(pGameObject);
		}
	}
		break;
	default:
		break;
	}

}

void CEditorManager::Initialize()
{
	{
		CGameObject* pResource = GET_SINGLE(CResourceManager)->FindUnit("Mineral01")->clone();
		CLayer* pLayer = m_pGameObject->GetScene()->FindLayer("UnitLayer");
		pLayer->AddGameObject(pResource);
		pResource->GetTransform()->SetPivot(0.5f, 0.6666665f);
		m_vecResources.push_back(pResource);
		pResource->GetComponent<CCircleCollider>()->SetEnable(false);
		pResource->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("Mineral01_100");
		pResource->GetComponent<CSpriteRenderer>()->SetEnable(false);
		pResource->GetComponent<CEllipseRenderer>()->SetEnable(false);
	}
	{
		CGameObject* pResource = GET_SINGLE(CResourceManager)->FindUnit("Mineral02")->clone();
		CLayer* pLayer = m_pGameObject->GetScene()->FindLayer("UnitLayer");
		pLayer->AddGameObject(pResource);
		pResource->GetTransform()->SetPivot(0.5f, 0.6666665f);
		m_vecResources.push_back(pResource);
		pResource->GetComponent<CCircleCollider>()->SetEnable(false);
		pResource->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("Mineral02_100");
		pResource->GetComponent<CSpriteRenderer>()->SetEnable(false);
		pResource->GetComponent<CEllipseRenderer>()->SetEnable(false);
			
	}
	{
		CGameObject* pResource = GET_SINGLE(CResourceManager)->FindUnit("Mineral03")->clone();
		CLayer* pLayer = m_pGameObject->GetScene()->FindLayer("UnitLayer");
		pLayer->AddGameObject(pResource);
		pResource->GetTransform()->SetPivot(0.5f, 0.6666665f);
		m_vecResources.push_back(pResource);
		pResource->GetComponent<CCircleCollider>()->SetEnable(false);
		pResource->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("Mineral03_100");
		pResource->GetComponent<CSpriteRenderer>()->SetEnable(false);
		pResource->GetComponent<CEllipseRenderer>()->SetEnable(false);
	}
	{

		CGameObject* pResource = GET_SINGLE(CResourceManager)->FindUnit("VespeneGeyser")->clone();
		CLayer* pLayer = m_pGameObject->GetScene()->FindLayer("UnitLayer");
		pLayer->AddGameObject(pResource);
		m_vecResources.push_back(pResource);
		pResource->GetComponent<CCircleCollider>()->SetEnable(false);
		pResource->GetComponent<CEllipseRenderer>()->SetEnable(false);

		for each (CSpriteRenderer* i in pResource->GetComponents<CSpriteRenderer>())
		{
			i->SetEnable(false);
			i->SetDefaultClip();
		}
	}
}

void CEditorManager::SaveComponent(FILE * pFile)
{
}

void CEditorManager::LoadComponent(FILE * pFile)
{
}

CComponent * CEditorManager::clone()
{
	return nullptr;
}

CEditorManager::CEditorManager(const CEditorManager & component)
{
}

CEditorManager::CEditorManager()
{
	m_eState = ES_TILE;
	m_iCurrentTileIndex = 0;
	m_iCurrentTileSetIndex = 0;
	m_iCurrentResourceIndex = 0;
	m_iTileSetSize = GET_SINGLE(CResourceManager)->GetTileSetMap().size();
	
	if (GET_SINGLE(CResourceManager)->GetTileSet(m_iCurrentTileSetIndex).size() == 0)
	{
		while (true)
		{
			if (GET_SINGLE(CResourceManager)->GetTileSet(m_iCurrentTileSetIndex).size() > 0)
			{
				break;
			}
			else
			{
				++m_iCurrentTileSetIndex;
			}
		}
	}	
}


CEditorManager::~CEditorManager()
{
	//벡터는 Layer에서 해제해줌
}
