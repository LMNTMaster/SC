#pragma once
#include "../Component.h"
#include "../ButtonComponent.h"

class CMove :
	public CButtonComponent
{
private:
	class CVectorField* m_pVectorField;
	CVector2 m_TargetPosition;
	float m_fStopThreshold;
	float m_fMoveSpeed;
	float m_fAngularSpeed;	
	bool m_bPause;
	bool m_bArrived;	
	bool m_bStop;

public:
	void Stop()
	{
		m_pVectorField = NULL;
		m_bStop = true;
	}

	class CVectorField* GetVectorField() const
	{
		return m_pVectorField;
	}

	bool GetArrived() const
	{
		return m_bArrived;
	}

	bool Pause() const
	{
		return m_bPause;
	}
	void Pause(bool bPause)
	{
		m_bPause = bPause;
	}
	void SetAngularSpeed(float fAngularSpeed)
	{
		m_fAngularSpeed = fAngularSpeed;
	}
	float GetAngluarSpeed() const
	{
		return m_fAngularSpeed;
	}
	
	void SetMoveSpeed(float fSpeed)
	{
		m_fMoveSpeed = fSpeed;
	}
	float GetMoveSpeed() const
	{
		return m_fMoveSpeed;
	}
	void SetStopThresholdRadius(float fRadius)
	{
		m_fStopThreshold = fRadius;
	}
	float GetStopThresholdRadius() const
	{
		return m_fStopThreshold;
	}

	void AddUnitToTile();


public:
	void RequestMove(CVector2 worldPosition);
	void RequestMove(CVector2 worldPosition, bool bIsAir);

public:
	void Start() override;
	void Update() override;
	void LateUpdate() override;

	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CMove(const CMove& component);
	CMove();
	~CMove();
};

