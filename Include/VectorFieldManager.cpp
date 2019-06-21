#include "VectorFieldManager.h"
#include "VectorField.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Component.h"
#include "Components\TerrainRenderer.h"
#include "Tile.h"

CVectorFieldManager* CVectorFieldManager::m_pInstance = NULL;

//���� ������ ���� �ʿ� ����.

CVectorField * CVectorFieldManager::RequestVectorField(int idx)
{
	unordered_map<int, CVectorField*>::iterator iter = m_mapGroundVectorField.find(idx);

	if (iter == m_mapGroundVectorField.end())
	{
		CVectorField* pVectorField = CreateVectorField(idx);
		return pVectorField;
	}
	else
	{
		//UpdateVectorField(iPositionToIndex, iter->second);
		return iter->second;
	}
}

CVectorField * CVectorFieldManager::RequestVectorField(CVector2 position)
{
	CVector2 gridSize = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetGridSize();
	
	int iX = ((int)position.x) / 32;
	int iY = ((int)position.y) / 32;
	int iGridWidth = (int)gridSize.x;
	int iGridHeight = (int)gridSize.y;
	int iPositionToIndex = iY * gridSize.x + iX;

	return RequestVectorField(iPositionToIndex);
}

CVectorField * CVectorFieldManager::CreateVectorField(int iTileIndex)
{
	// ���� �� Ÿ���� �̵� �Ұ����� �����̸�, ������ �κб��� �̵��ؾ� �Ѵ�.
	// ��, �ؽøʿ��� ������ �κ��� �ƴ� ��û�� ��ġ�� �����Ѵ�.
	CVector2 gridSize = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetGridSize();
	CVectorField* pVectorField = new CVectorField(gridSize);
	CTerrainRenderer* pTerrain = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetTerrainRenderer();

	int iGridWidth = (int)gridSize.x;
	int iGridHeight = (int)gridSize.y;

	//Ŭ���� ��ġ�� �̵� �Ұ����� Ÿ���̸�
	if (!pTerrain->GetTile(iTileIndex)->GetMovable())
	{
		//�ش� ��ġ�� �̵� �Ұ����� Ÿ���̸�, �ֺ����� �̵������� ��ġ�� ã�´�.
		int iModifiedIndex = -1;
		bool* pVisit = new bool[gridSize.x * gridSize.y];
		memset(pVisit, 0, gridSize.x * gridSize.y);

		queue<int> queue;
		queue.push(iTileIndex);

		while (!queue.empty())
		{
			//4���� �˻����� �Ѵ�.
			int idx = queue.front();
			queue.pop();

			bool L = false; bool T = false; bool R = false; bool B = false;
			//���� �� : idx �������� ������ ��
			if (idx % iGridWidth == 0)							L = true;
			if (idx / iGridWidth < 1)								T = true;
			if (idx % iGridWidth == iGridWidth - 1)		R = true;
			if (idx >= iGridWidth * (iGridHeight - 1))		B = true;

			if (L && !T && !R && !B)
			{
				//T
				int i = idx - iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//R
				i = idx + 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}					
					queue.push(i);
				}
				//B
				i = idx + iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
			}
			else if (!L && T && !R && !B)
			{
				//L
				int i = idx - 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}					
				//R
				i = idx + 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//B
				i = idx + iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
			}
			else if (!L && !T && R && !B)
			{
				//L
				int i = idx - 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//T
				i = idx - iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}					
				//B
				i = idx + iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
			}
			else if (!L && !T && !R && B)
			{
				//L
				int i = idx - 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//T
				i = idx - iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//R
				i = idx + 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
			}
			else if (L && T && !R && !B)
			{					
				//R
				int i = idx + 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//B
				i = idx + iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
			}
			else if (!L && T && R && !B)
			{
				//L
				int i = idx - 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}				
				//B
				i = idx + iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
			}
			else if (L && !T && !R && B)
			{
				//T
				int i = idx - iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//R
				i = idx + 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//B
				i = idx + iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
			}
			else if (!L && !T && R && B)
			{
				//L
				int i = idx - 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//T
				i = idx - iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
			}
			else
			{
				//L
				int i = idx - 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//T
				i = idx - iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//R
				i = idx + 1;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
				//B
				i = idx + iGridWidth;
				if (!pVisit[i])
				{
					pVisit[i] = true;
					if (pTerrain->GetTile(i)->GetMovable())
					{
						iModifiedIndex = i;
						break;
					}
					queue.push(i);
				}
			}								
		}
		delete[] pVisit;

		if (iModifiedIndex == -1)
		{
			//������ �� �����ʵ� �״�� ��ȯ
			return pVectorField;
		}
		else
		{
			UpdateVectorField(iModifiedIndex, pVectorField);
			m_mapGroundVectorField.insert(make_pair(iTileIndex, pVectorField));
		}
	}
	//Ŭ���� ��ġ�� �̵� ������ Ÿ���̸�
	else
	{
		UpdateVectorField(iTileIndex, pVectorField);
		m_mapGroundVectorField.insert(make_pair(iTileIndex, pVectorField));
	}
	return pVectorField;
	
}


CVectorField * CVectorFieldManager::UpdateVectorField(int iTileIndex, CVectorField * pVectorField)
{
	CVector2 gridSize = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetGridSize();
	CTerrainRenderer* pTerrain = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetTerrainRenderer();

	int iGridWidth = (int)gridSize.x;
	int iGridHeight = (int)gridSize.y;

	bool* pMovableTile = new bool[iGridWidth * iGridHeight];
	bool* pVisitTile = new bool[iGridWidth * iGridHeight];
	memset(pVisitTile, 0, sizeof(bool) * iGridWidth * iGridHeight);

	for (int y = 0; y < gridSize.y; ++y)
	{
		for (int x = 0; x < gridSize.x; ++x)
		{
			int idx = y * gridSize.x + x;
			pMovableTile[idx] = pTerrain->GetTile(idx)->GetMovable();
		}
	}

	queue<int> queue;
	queue.push(iTileIndex);
	// �ݵ�� ���� ���� �ٱ��� Ÿ���� �̵��� �� ����.

	while (!queue.empty())
	{
		int idx = queue.front();
		queue.pop();
		bool L = false;
		bool T = false;
		bool R = false;
		bool B = false;
		//���� �� : idx �������� ������ ��
		if (idx % iGridWidth == 0)
			L = true;
		if (idx / iGridWidth < 1)
			T = true;
		if (idx % iGridWidth == iGridWidth - 1)
			R = true;
		if (idx >= iGridWidth * (iGridHeight - 1))
			B = true;

		if (L && !T && !R && !B)
		{
			//Top
			int i = idx - iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, 1)));
					queue.push(i);
				}
			}
			//Right
			i = idx + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-1, 0)));
					queue.push(i);
				}
			}
			//Bottom
			i = idx + iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, -1)));
					queue.push(i);
				}
			}
			//Right Top
			i = idx - iGridWidth + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-0.5f, 0.5f)));
					queue.push(i);
				}
			}
			//Right Bottom
			i = idx + iGridWidth + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-0.5f, -0.5f)));
					queue.push(i);
				}
			}
		}
		else if (!L && T && !R && !B)
		{
			//Left
			int i = idx - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(1, 0)));
					queue.push(i);
				}
			}
			//Right
			i = idx + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-1, 0)));
					queue.push(i);
				}
			}
			//Bottom
			i = idx + iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, -1)));
					queue.push(i);
				}
			}
			//Left Bottom
			i = idx + iGridWidth - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0.5f, -0.5f)));
					queue.push(i);
				}
			}
			//Right Bottom
			i = idx + iGridWidth + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-0.5f, -0.5f)));
					queue.push(i);
				}
			}
		}
		else if (!L && !T && R && !B)
		{
			//Left
			int i = idx - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(1, 0)));
					queue.push(i);
				}
			}
			//Top
			i = idx - iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, 1)));
					queue.push(i);
				}
			}
			//Bottom
			i = idx + iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, -1)));
					queue.push(i);
				}
			}

			//Left Top
			i = idx - iGridWidth - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0.5f, 0.5f)));
					queue.push(i);
				}
			}
			//Left Bottom
			i = idx + iGridWidth - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0.5f, -0.5f)));
					queue.push(i);
				}
			}
		}
		else if (!L && !T && !R && B)
		{
			//Left
			int i = idx - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(1, 0)));
					queue.push(i);
				}
			}
			//Top
			i = idx - iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, 1)));
					queue.push(i);
				}
			}
			//Right
			i = idx + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-1, 0)));
					queue.push(i);
				}
			}
			//Left Top
			i = idx - iGridWidth - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0.5f, 0.5f)));
					queue.push(i);
				}
			}
			//Right Top
			i = idx - iGridWidth + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-0.5f, 0.5f)));
					queue.push(i);
				}
			}
		}
		else if (L && T && !R && !B)
		{
			//Right
			int i = idx + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-1, 0)));
					queue.push(i);
				}
			}
			//Bottom
			i = idx + iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, -1)));
					queue.push(i);
				}
			}
			//Right Bottom
			i = idx + iGridWidth + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-0.5f, -0.5f)));
					queue.push(i);
				}
			}
		}
		else if (!L && T && R && !B)
		{
			//Left
			int i = idx - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(1, 0)));
					queue.push(i);
				}
			}
			//Bottom
			i = idx + iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, -1)));
					queue.push(i);
				}
			}
			//Left Bottom
			i = idx + iGridWidth - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0.5f, -0.5f)));
					queue.push(i);
				}
			}
		}
		else if (L && !T && !R && B)
		{
			//Top
			int i = idx - iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, 1)));
					queue.push(i);
				}
			}
			//Right
			i = idx + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-1, 0)));
					queue.push(i);
				}
			}
			//Right Top
			i = idx - iGridWidth + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(-0.5f, 0.5f)));
					queue.push(i);
				}
			}
		}
		else if (!L && !T && R && B)
		{
			//Left
			int i = idx - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(1, 0)));
					queue.push(i);
				}
			}
			//Top
			i = idx - iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0, 1)));
					queue.push(i);
				}
			}
			//Left Top
			i = idx - iGridWidth - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector(i, ( CVector2(0.5f, 0.5f)));
					queue.push(i);
				}
			}
		}
		else
		{
			//Left
			int i = idx - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector (i,  ( CVector2(1, 0)));
					queue.push(i);
				}
			}
			//Top
			i = idx - iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector (i,  ( CVector2(0, 1)));
					queue.push(i);
				}
			}
			//Right
			i = idx + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector (i,  ( CVector2(-1, 0)));
					queue.push(i);
				}
			}
			//Bottom
			i = idx + iGridWidth;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector (i,  ( CVector2(0, -1)));
					queue.push(i);
				}
			}

			//Left Top
			i = idx - iGridWidth - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector (i,  ( CVector2(0.5f, 0.5f)));
					queue.push(i);
				}
			}
			//Right Top
			i = idx - iGridWidth + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector (i,  ( CVector2(-0.5f, 0.5f)));
					queue.push(i);
				}
			}
			//Left Bottom
			i = idx + iGridWidth - 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector (i,  ( CVector2(0.5f, -0.5f)));
					queue.push(i);
				}
			}
			//Right Bottom
			i = idx + iGridWidth + 1;
			if (!pVisitTile[i])
			{
				pVisitTile[i] = true;
				if (pMovableTile[i])
				{
					pVectorField->SetVector (i, ( CVector2(-0.5f, -0.5f)));
					queue.push(i);
				}
			}
		}
	}

	delete[] pMovableTile;
	delete[] pVisitTile;

	return pVectorField;
}

void CVectorFieldManager::Initialize()
{
}

CVectorFieldManager::CVectorFieldManager()
{
}

CVectorFieldManager::~CVectorFieldManager()
{
	{
		unordered_map<int, CVectorField*>::iterator iter;
		unordered_map<int, CVectorField*>::iterator iterEnd = m_mapAirVectorField.end();
		for (iter = m_mapAirVectorField.begin(); iter != iterEnd; ++iter)
		{
			if (iter->second)
			{
				delete iter->second;
			}
		}
		m_mapAirVectorField.clear();
	}

	{
		unordered_map<int, CVectorField*>::iterator iter;
		unordered_map<int, CVectorField*>::iterator iterEnd = m_mapGroundVectorField.end();
		for (iter = m_mapGroundVectorField.begin(); iter != iterEnd; ++iter)
		{
			if (iter->second)
			{
				delete iter->second;
			}
		}
		m_mapGroundVectorField.clear();
	}
}
