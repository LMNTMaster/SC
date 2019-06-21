#include "Transform.h"
#include "../GameObject.h"


void CTransform::SetScale(CVector2 scale)
{
	if (m_pGameObject->GetParent() == NULL)
	{
		m_Scale = scale;
		m_LocalScale = scale;
	}
	else
	{
		m_Scale.x = m_LocalScale.x * m_pGameObject->GetParent()->GetComponent<CTransform>()->GetScale().x;
		m_Scale.y = m_LocalScale.y * m_pGameObject->GetParent()->GetComponent<CTransform>()->GetScale().y;

		list<CGameObject*>::iterator iter = (*m_pGameObject->GetChildren()).begin();
		list<CGameObject*>::iterator iterEnd = (*m_pGameObject->GetChildren()).end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->GetComponent<CTransform>()->SetScale(CVector2(0, 0));
		}
	}
}

void CTransform::SetPosition(CVector2 vec)
{
	if (m_pGameObject->GetParent() == NULL)
	{
		m_WorldPosition = vec;
		m_LocalPosition = vec;
	}
	else
	{
		m_WorldPosition = m_LocalPosition + m_pGameObject->GetParent()->GetComponent<CTransform>()->GetPosition();

		list<CGameObject*>::iterator iter = (*m_pGameObject->GetChildren()).begin();
		list<CGameObject*>::iterator iterEnd = (*m_pGameObject->GetChildren()).end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->GetComponent<CTransform>()->SetPosition(CVector2(0,0));
		}
	}	
}

void CTransform::SetPosition(float x ,float y)
{
	CVector2 vec = CVector2(x, y);
	if (m_pGameObject->GetParent() == NULL)
	{
		m_WorldPosition = vec;
		m_LocalPosition = vec;
	}
	else
	{
		m_WorldPosition = m_LocalPosition + m_pGameObject->GetParent()->GetComponent<CTransform>()->GetPosition();

		list<CGameObject*>::iterator iter = (*m_pGameObject->GetChildren()).begin();
		list<CGameObject*>::iterator iterEnd = (*m_pGameObject->GetChildren()).end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->GetComponent<CTransform>()->SetPosition(CVector2(0, 0));
		}
	}
}


void CTransform::SaveComponent(FILE * pFile)
{
	fwrite(&m_Pivot, sizeof(CVector2), 1, pFile);
	fwrite(&m_LocalPosition, sizeof(CVector2), 1, pFile);
	fwrite(&m_Scale, sizeof(CVector2), 1, pFile);
	fwrite(&m_LocalScale, sizeof(CVector2), 1, pFile);
	fwrite(&m_Rotation, sizeof(float), 1, pFile);
}

void CTransform::LoadComponent(FILE * pFile)
{
	fread(&m_Pivot, sizeof(CVector2), 1, pFile);
	fread(&m_LocalPosition, sizeof(CVector2), 1, pFile);
	fread(&m_Scale, sizeof(CVector2), 1, pFile);
	fread(&m_LocalScale, sizeof(CVector2), 1, pFile);
	fread(&m_Rotation, sizeof(float), 1, pFile);
}

CComponent * CTransform::clone()
{
	return new CTransform(*this);
}

CTransform::CTransform(const CTransform & component)
{
	m_Pivot = component.m_Pivot;
	m_WorldPosition = component.m_WorldPosition;
	m_LocalPosition= component.m_LocalPosition;
	m_Scale= component.m_Scale;
	m_LocalScale= component.m_LocalScale;
	m_Rotation= component.m_Rotation;
	m_eComponentType = CT_TRANSFORM;
}

CTransform::CTransform():
	m_Pivot(0.5f, 0.5f),
	m_LocalPosition(0,0),
	m_Scale(1,1),
	m_LocalScale(1,1),	
	m_Rotation(0)
{
	m_eComponentType = CT_TRANSFORM;
}


CTransform::~CTransform()
{
}
