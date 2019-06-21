#include "Structure.h"
#include "../Component.h"
#include "../Components/Transform.h"
#include "../GameObject.h"
#include "SpriteRenderer.h"
#include "../Tile.h"
#include "../Layer.h"
#include "Player.h"

void CStructure::SetPosition(unsigned int iX, unsigned int iY)
{
	m_iPositionX = iX;
	m_iPositionY = iY;	
}
void CStructure::Start()
{
	CScene* pScene = m_pGameObject->GetScene();
	m_vecBuiltTileIndex.resize(m_vecBuildableTile.size());
	pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>()->AddMaxPopulation(m_fSupply);
	//������ ������ ����
	CVector2 gridSize = m_pGameObject->GetScene()->GetGridSize();
	CVector2 size = m_pGameObject->GetComponent<CSpriteRenderer>()->GetSize();
	CVector2 origin;
	origin.x = m_pTransform->GetPosition().x - m_pTransform->GetPivot().x * size.x;
	origin.y = m_pTransform->GetPosition().y - m_pTransform->GetPivot().y * size.y;
	origin += CVector2(16, 16);
	int iOriginX = (int)origin.x / 32;
	int iOriginY = (int)origin.y / 32;
	//�̵� �Ұ����� Ÿ���� �ε����� ����, m_vecBuildableTile�� ũ�⸸ŭ�� �ε����� �ʿ���.
	for (int i = 0; i < m_vecBuildableTile.size(); ++i)
	{
		int iIndexX = m_vecBuildableTile[i].x;
		int iIndexY = m_vecBuildableTile[i].y;

		//ù ��° Ÿ���� ��ȣ�� ���ϰ�, �����ġ�� ������ �� �ε��� �����
		int iX = iOriginX + iIndexX;
		int iY = iOriginY + iIndexY;
		int iIndex = iY * (int)gridSize.x + iX;

		//�ǹ��� ���ŵǾ��� ��츦 ���� ����
		m_vecBuiltTileIndex[i] = iIndex;

		//Ÿ�� ó��
		pScene->GetTileByIndex(iIndex)->SetBuildable(false);
		pScene->GetTileByIndex(iIndex)->SetMovable(false);	

		if (m_bVespeneGeyser)
			pScene->GetTileByIndex(iIndex)->SetResourceType(RT_VESPENE_GAS);
		else
			pScene->GetTileByIndex(iIndex)->SetResourceType(RT_NONE);
	}	
}
void CStructure::Update()
{
	CScene* pScene = m_pGameObject->GetScene();

	for (int i = 0; i < m_vecBuiltTileIndex.size(); ++i)
	{
		pScene->GetTileByIndex(m_vecBuiltTileIndex[i])->AddUnit(m_pGameObject);
	}
}
void CStructure::SaveComponent(FILE * pFile)
{
	fwrite(&m_fRequireMineral, 4, 1, pFile);
	fwrite(&m_fRequireGas, 4, 1, pFile);
	fwrite(&m_fSupply, 4, 1, pFile);
	fwrite(&m_fBuildTime, 4, 1, pFile);
	fwrite(&m_iTextureTileWidth, 4, 1, pFile);
	fwrite(&m_iTextureTileHeight, 4, 1, pFile);
	int iLength = m_vecBuildableTile.size();
	fwrite(&iLength, 4, 1, pFile);

	for (int i = 0; i < iLength; ++i)
	{
		fwrite(&m_vecBuildableTile[i], sizeof(CVector2), 1, pFile);
	}

}

void CStructure::LoadComponent(FILE * pFile)
{
	fread(&m_fRequireMineral, 4, 1, pFile);
	fread(&m_fRequireGas, 4, 1, pFile);
	fread(&m_fSupply, 4, 1, pFile);
	fread(&m_fBuildTime, 4, 1, pFile);

	fread(&m_iTextureTileWidth, 4, 1, pFile);
	fread(&m_iTextureTileHeight, 4, 1, pFile);


	int iLength = 0;
	fread(&iLength, 4, 1, pFile);

	for (int i = 0; i < iLength; ++i)
	{
		CVector2 temp;
		fread(&temp, sizeof(CVector2), 1, pFile);
		m_vecBuildableTile.push_back(temp);
	}
}

CComponent * CStructure::clone()
{
	return new CStructure(*this);
}

CStructure::CStructure(const CStructure & component) :
	m_fSupply(0),
	m_fRequireMineral(0),
	m_fRequireGas(0),
	m_fBuildTime(10),
	m_bVespeneGeyser(false)
{

	m_fRequireMineral = component.m_fRequireMineral;
	m_fRequireGas = component.m_fRequireGas;

	m_fSupply = component.m_fSupply;
	m_fBuildTime = component.m_fBuildTime;
	m_fBuildElipse = 0;

	m_iTextureTileWidth = component.m_iTextureTileWidth;
	m_iTextureTileHeight = component.m_iTextureTileHeight;
	m_iPositionX = component.m_iPositionX;
	m_iPositionY = component.m_iPositionY;

	m_vecBuildableTile = component.m_vecBuildableTile;
	
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_STRUCTURE;

}

CStructure::CStructure() :
	m_fSupply(0),
	m_fRequireMineral(0),
	m_fRequireGas(0),
	m_fBuildTime(10),
	m_bVespeneGeyser(false)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_STRUCTURE;
}


CStructure::~CStructure()
{
}
