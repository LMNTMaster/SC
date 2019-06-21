#include "ControlButton.h"
#include "Transform.h"
#include "../Component.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../ConsoleButton.h"
#include "../Input.h"
#include "../ConsoleButtonManager.h"
#include "../Scene.h"
#include "../Layer.h"
#include "../GameObject.h"
#include "Cursor.h"
#include "Player.h"
#include "../ButtonComponent.h"


void CControlButton::Render()
{
	if (m_pButton)
	{
		if (m_pButton->GetButtonState() == BS_ENABLE)
		{
			CVector2 renderSize = CVector2(m_Size.x * m_pTransform->GetPivot().x * m_pTransform->GetScale().x,
				m_Size.y * m_pTransform->GetPivot().y * m_pTransform->GetScale().y);

			CVector2 position = m_pTransform->GetPosition() - renderSize;

			CPlayer* pPlayer = m_pGameObject->GetScene()->FindLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

			RACE_TYPE eRaceType = pPlayer->GetRaceType();

			switch (eRaceType)
			{
				case RT_TERRAN:
				{
					CTexture* pBackgroundTexture = GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Background_Terran_Normal");

					TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
						position.x, position.y,
						m_Size.x * m_pTransform->GetScale().x,
						m_Size.y * m_pTransform->GetScale().y,
						pBackgroundTexture->GetDC(), 0, 0,
						pBackgroundTexture->GetTextureInfo().bmWidth,
						pBackgroundTexture->GetTextureInfo().bmHeight,
						RGB(0, 0, 0));
				}
					break;
				case RT_PROTOSS:
				{
					CTexture* pBackgroundTexture = GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Background_Protoss_Normal");

					TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
						position.x, position.y,
						m_Size.x * m_pTransform->GetScale().x,
						m_Size.y * m_pTransform->GetScale().y,
						pBackgroundTexture->GetDC(), 0, 0,
						pBackgroundTexture->GetTextureInfo().bmWidth,
						pBackgroundTexture->GetTextureInfo().bmHeight,
						RGB(0, 0, 0));
				}
					break;
				case RT_ZERG:
				{
					CTexture* pBackgroundTexture = GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Background_Zerg_Normal");

					TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
						position.x, position.y,
						m_Size.x * m_pTransform->GetScale().x,
						m_Size.y * m_pTransform->GetScale().y,
						pBackgroundTexture->GetDC(), 0, 0,
						pBackgroundTexture->GetTextureInfo().bmWidth,
						pBackgroundTexture->GetTextureInfo().bmHeight,
						RGB(0, 0, 0));
				}
					break;
			}

			TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
				position.x, position.y,
				m_Size.x * m_pTransform->GetScale().x,
				m_Size.y * m_pTransform->GetScale().y,
				m_pButton->GetUpIconTexture()->GetDC(), 0, 0,
				m_pButton->GetUpIconTexture()->GetTextureInfo().bmWidth,
				m_pButton->GetUpIconTexture()->GetTextureInfo().bmHeight,
				RGB(0, 0, 0));
		}
		else if (m_pButton->GetButtonState() == BS_DISABLE)
		{
			CVector2 renderSize = CVector2(m_Size.x * m_pTransform->GetPivot().x * m_pTransform->GetScale().x,
				m_Size.y * m_pTransform->GetPivot().y * m_pTransform->GetScale().y);
			CVector2 position = m_pTransform->GetPosition() - renderSize;
			CPlayer* pPlayer = m_pGameObject->GetScene()->FindLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
			RACE_TYPE eRaceType = pPlayer->GetRaceType();

			switch (eRaceType)
			{
			case RT_TERRAN:
			{
				CTexture* pBackgroundTexture = GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Background_Terran_Normal");

				TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
					position.x, position.y,
					m_Size.x * m_pTransform->GetScale().x,
					m_Size.y * m_pTransform->GetScale().y,
					pBackgroundTexture->GetDC(), 0, 0,
					pBackgroundTexture->GetTextureInfo().bmWidth,
					pBackgroundTexture->GetTextureInfo().bmHeight,
					RGB(0, 0, 0));
			}
			break;
			case RT_PROTOSS:
			{
				CTexture* pBackgroundTexture = GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Background_Protoss_Normal");

				TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
					position.x, position.y,
					m_Size.x * m_pTransform->GetScale().x,
					m_Size.y * m_pTransform->GetScale().y,
					pBackgroundTexture->GetDC(), 0, 0,
					pBackgroundTexture->GetTextureInfo().bmWidth,
					pBackgroundTexture->GetTextureInfo().bmHeight,
					RGB(0, 0, 0));
			}
			break;
			case RT_ZERG:
			{
				CTexture* pBackgroundTexture = GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Background_Zerg_Normal");

				TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
					position.x, position.y,
					m_Size.x * m_pTransform->GetScale().x,
					m_Size.y * m_pTransform->GetScale().y,
					pBackgroundTexture->GetDC(), 0, 0,
					pBackgroundTexture->GetTextureInfo().bmWidth,
					pBackgroundTexture->GetTextureInfo().bmHeight,
					RGB(0, 0, 0));
			}
			break;
			}

			TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
				position.x, position.y,
				m_Size.x * m_pTransform->GetScale().x,
				m_Size.y * m_pTransform->GetScale().y,
				m_pButton->GetDownIconTexture()->GetDC(), 0, 0,
				m_pButton->GetDownIconTexture()->GetTextureInfo().bmWidth,
				m_pButton->GetDownIconTexture()->GetTextureInfo().bmHeight,
				RGB(0, 0, 0));
		}
		
	}
}

void CControlButton::Update()
{
	static int counter = 0;
	
	if (m_pButton)
	{
		if (GETKEYDOWN(m_pButton->GetShortcutKey()))
		{
			if (m_pButton->GetRequireBuildMode())
			{
				//���� ����� ������, ��ư�� �Ǽ� ����� �޾ƿ� Ŀ���� ���� ��, ������Ʈ�� �޾� ó�����ش�.
				//�⺻������ clone�� ����ϹǷ�, layer���� destroy���ִ½����� �����Ѵ�.

				CPlayer* pPlayer = m_pGameObject->GetScene()->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
				CStructure* pBuildTarget = m_pButton->GetBuildTarget()->GetComponent<CStructure>();
				if (pPlayer->GetMineral() < pBuildTarget->GetRequireMineral())
				{
					GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
				}
				else if (pPlayer->GetVespeneGas() < pBuildTarget->GetRequireGas())
				{
					GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
				}
				else
				{
					CCursor* pCursor = m_pGameObject->GetScene()->GetLayer("System")->FindGameObject("Cursor")->GetComponent<CCursor>();

					pCursor->SetBuildTarget(m_pButton->GetAdvanced(), m_pButton->GetBuildTarget()->clone());
					pCursor->SetBuildMode(true);
					pCursor->RequestFunction(m_pGameObject, m_pButton, m_pButton->GetFunction());
				}
			}
			else if (m_pButton->GetRequireCursor())
			{
				//Ŀ���� �ݹ� ȣ����.
				CCursor* pCursor = m_pGameObject->GetScene()->GetLayer("System")->FindGameObject("Cursor")->GetComponent<CCursor>();
				pCursor->RequestFunction(m_pGameObject, m_pButton, m_pButton->GetFunction());
				//Ŀ������ �� ��ư�� �Լ��� �޾Ƽ� �Ķ���ͷ� �� ���� ����� �ٶ����� ��� �ִٰ� ȣ����.

				//������������ �����ϴ��� Ȯ�� ��, �����ϸ� �Լ� ȣ��
				if (m_pButton->GetExistNextPage())
				{
					m_pButton->UpdateToNextPage();
				}
			}
			else
			{
				//��� �����.
				m_pButton->GetFunction()(CVector2(), NULL);

				//���� �Լ����� m_pButton�� �ʱ�ȭ �� �� �����Ƿ�
				if (m_pButton)
				{
					//������������ �����ϴ��� Ȯ�� ��, �����ϸ� �Լ� ȣ��
					if (m_pButton->GetExistNextPage())
					{
						m_pButton->UpdateToNextPage();
					}
				}
			}
			
		}
	}
}

void CControlButton::LoadComponent(FILE * pFile)
{
}

void CControlButton::SaveComponent(FILE * pFile)
{
}

CComponent * CControlButton::clone()
{
	return nullptr;
}

CControlButton::CControlButton(const CControlButton & component)
{
}

CControlButton::CControlButton():
	m_pButton(NULL)
{
}


CControlButton::~CControlButton()
{
}
