#pragma once
#include "../Component.h"
class CCollisionTile :
	public CComponent
{
private:
	unsigned int m_iCellIndex;
	list<class CGameObject*> m_ContainUnitList;

public:
	unsigned int GetCellIndex() const
	{
		return m_iCellIndex;
	}
	void SetCellIndex(int idx)
	{
		m_iCellIndex = idx;
	}
	const list<class CGameObject*>& GetContainUnitList() const
	{
		return m_ContainUnitList;
	}

	void AddUnit(class CGameObject* pGameObject)
	{
		m_ContainUnitList.push_back(pGameObject);
	}

	void ClearList()
	{
		m_ContainUnitList.clear();
	}

	//				||		clear		||		check & add	||		���
	//	�ʱ�ȭ	||			1		||			0				||
	// �߰�		||			1		||			n+1			||	ContainȮ�� ��, ������ �߰�
	// ����		||			0		||			n+1			||	ContainȮ�� ��, ������ ����

	bool Contain(class CGameObject* pGameObject)
	{
		list<class CGameObject*>::iterator iter;
		list<class CGameObject*>::iterator iterEnd = m_ContainUnitList.end();
		for (iter = m_ContainUnitList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == pGameObject)
			{
				return true;
			}
		}
		return false;
	}

	void RemoveUnit(class CGameObject* pGameObject)
	{
		list<class CGameObject*>::iterator iter;
		list<class CGameObject*>::iterator iterEnd = m_ContainUnitList.end();

		for (iter = m_ContainUnitList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == pGameObject)
			{
				m_ContainUnitList.erase(iter);
				break;
			}
		}
	}


public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CCollisionTile(const CCollisionTile& component);
	CCollisionTile();
	~CCollisionTile();
};

