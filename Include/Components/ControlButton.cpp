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
				//빌드 모드일 떄에는, 버튼의 건설 대상을 받아와 커서에 붙인 뒤, 리퀘스트를 받아 처리해준다.
				//기본적으로 clone을 사용하므로, layer에서 destroy해주는식으로 해제한다.

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
				//커서에 콜백 호출함.
				CCursor* pCursor = m_pGameObject->GetScene()->GetLayer("System")->FindGameObject("Cursor")->GetComponent<CCursor>();
				pCursor->RequestFunction(m_pGameObject, m_pButton, m_pButton->GetFunction());
				//커서에서 이 버튼의 함수를 받아서 파라미터로 들어갈 값을 만들어 줄때까지 들고 있다가 호출함.

				//다음페이지가 존재하는지 확인 후, 존재하면 함수 호출
				if (m_pButton->GetExistNextPage())
				{
					m_pButton->UpdateToNextPage();
				}
			}
			else
			{
				//즉시 사용함.
				m_pButton->GetFunction()(CVector2(), NULL);

				//위의 함수에서 m_pButton이 초기화 될 수 있으므로
				if (m_pButton)
				{
					//다음페이지가 존재하는지 확인 후, 존재하면 함수 호출
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
