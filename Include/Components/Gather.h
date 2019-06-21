#pragma once
#include "../ButtonComponent.h"
class CGather :
	public CButtonComponent
{
private:	
	int m_iGatherAmount;	
	class CGameObject* m_pTargetResource;
	list<CGameObject*> m_BaseList;
	GATHER_STATE m_eGatherState;
	bool m_bStop;
	class CGameObject* m_pOrb;
	float m_fAnimationTime;
	float m_fAnimationTimer;

public:
	void SetOrb(class CGameObject* pOrb)
	{
		m_pOrb = pOrb;
	}
	class CGameObject* GetOrb() const
	{
		return m_pOrb;
	}
	void Stop();
	void SetGatherAmount(int iAmount)
	{
		m_iGatherAmount = iAmount;
	}
	int GetGatherAmount() const
	{
		return m_iGatherAmount;
	}
	void SetGatherState(GATHER_STATE eState)
	{
		m_eGatherState = eState;
	}
	GATHER_STATE GetGatherState() const
	{
		return m_eGatherState;
	}

	void AddBaseList(class CGameObject* pBasement)
	{
		m_BaseList.push_back(pBasement);
	}
	class CGameObject* GetNearestBase();

	void SetTargetResource(class CGameObject* pTarget)
	{
		m_pTargetResource = pTarget;
	}
	class CGameObject* GetTargetResource() const
	{
		return m_pTargetResource;
	}
public:
	void RequestMoveToGathering(class CGameObject* pTarget);
	void RequestReturnToBasement();
	class CGameObject* GetNearestMineral();
public:
	void Start() override;
	void Update() override;

	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	class CComponent* clone();

public:
	CGather(const CGather& component);
	CGather();
	~CGather();
};

