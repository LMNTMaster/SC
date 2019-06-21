#pragma once
#include "../Component.h"
class CResource :
	public CComponent
{
private:
	RESOURCE_TYPE m_eType;
	unsigned int m_iValue;
	queue<class CGameObject*> m_qGatheringUnit;
	float m_fR2BTime;
	float m_fCurrentTime;

public:
	int GetQueueSize() const
	{
		return m_qGatheringUnit.size();
	}
	void SetR2BTime(float fTime)
	{
		m_fR2BTime = fTime;
	}
	float GetR2BTime() const
	{
		return m_fR2BTime;
	}
	void AddUnit(class CGameObject* pGatheringUnit)
	{
		m_qGatheringUnit.push(pGatheringUnit);
	}
	class CGameObject* ReturnUnitFromQueue();


	void SetResourceType(RESOURCE_TYPE eType)
	{
		m_eType = eType;
	}
	RESOURCE_TYPE GetResourceType() const
	{
		return m_eType;
	}

	void SetValue(unsigned int iValue	)
	{
		m_iValue = iValue;
	}
	unsigned int GetValue() const
	{
		return m_iValue;
	}

public:
	void Update() override;

public:
	void LoadComponent(FILE* pFile);
	void SaveComponent(FILE* pFile);
	CComponent* clone();

public:
	CResource(const CResource& component);
	CResource();
	~CResource();
};

