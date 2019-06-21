
#pragma once
#include "Game.h"

class CVectorFieldManager
{
private:
	static CVectorFieldManager* m_pInstance;
	
public:
	static CVectorFieldManager* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CVectorFieldManager;
		}
		return m_pInstance;
	}
	static void DestoryInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

private:
	unordered_map<int, class CVectorField*> m_mapGroundVectorField;
	unordered_map<int, class CVectorField*> m_mapAirVectorField;

private:
	class CVectorField* CreateVectorField(int iTileIndex);
	class CVectorField* UpdateVectorField(int iTileIndex, class CVectorField* pVectorField);

public:
	class CVectorField* RequestVectorField(int idx);
	class CVectorField* RequestVectorField(CVector2 position);



public:
	void Initialize();
	


private:
	CVectorFieldManager() ;
	~CVectorFieldManager() ;
};

