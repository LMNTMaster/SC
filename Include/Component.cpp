#include "Component.h"
#include "GameObject.h"
#include "Components\Transform.h"


void CComponent::SetGameObject(CGameObject * gameObject)
{
	m_pGameObject = gameObject;
	m_pTransform = gameObject->GetComponent<CTransform>();
}

void CComponent::Initialize()
{
}

void CComponent::Start()
{
}

void CComponent::Update()
{
}

void CComponent::LateUpdate()
{
}

void CComponent::CollisionEnter()
{
}

void CComponent::CollisionStay()
{
}

void CComponent::CollisionExit()
{
}

void CComponent::Destroy()
{
}

CComponent::CComponent() :
	m_bStart(false),
	m_bEnable(true),
	m_bDestroy(false),
	m_pGameObject(NULL),
	m_eComponentParentType(PT_NONE)
{

}
CComponent::~CComponent()
{
}
