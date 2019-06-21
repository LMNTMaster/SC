#pragma once
#include "../Game.h"
#include "../Component.h"
class CTestMove :
	public CComponent
{
private:
	bool m_bSelected;

public:
	bool GetSelected() const
	{
		return m_bSelected;
	}
	void SetSelected( bool bSelected)
	{
		m_bSelected = bSelected;
	}
public :
	void Update() override;
	void CollisionEnter() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CTestMove(const CTestMove& component);
	CTestMove();
	~CTestMove();
};

