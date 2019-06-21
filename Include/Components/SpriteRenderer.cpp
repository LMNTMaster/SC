#include "SpriteRenderer.h"
#include "../Sprite.h"
#include "../Texture.h"
#include "Transform.h"
#include "../GameObject.h"
#include "../Core.h"
#include "../Scene.h"
#include "Camera.h"
#include "../ResourceManager.h"
#include "../FileStream.h"
#include "Player.h"
#include "../FogOfWarManager.h"
#include "../Layer.h"


//사용처..?
//Splash - TextureRenderer or UI Renderer
//유닛 - atlas
//건물(건설중 포함) - atlas(생산 중, 건설 중, 등등.. 한 texture에 몰빵)
//지형 - TextureRenderer (자원같은 경우, m_pTexture를 교체하는방법이 좋을 듯)
//이펙트 - atlas
//그림자 - TextureRenderer (1프레임이므로)
//UI - UI Renderer / TextureRenderer (일부 atlas) 사실 UI에서 이벤트 발생 시 TextureRenderer의 m_pTexture를 교체하는방법이 편할것 같음
//Frame으로 들어가는 것..?

//1. Sprite에서 Update 시 다음 프레임으로 넘어갈지 여부 결정,
//2. Sprite는 반드시 Atlas이어야 한다.
//3. Atlas의 특정 인덱스(행(Horizontal) 우선)를 벡터에 집어넣음.
//4. 프레임 전환 시, 벡터의 다음 인덱스의 값으로 위치 찾음.
//5. SpriteRenderer에서 해당 위치 그려줌.
//6. Flip은 따로 구현 하지 않고, 원본 이미지를 반전시켜 하나 더 만들어서 사용하도록 한다.
//7. 따라서 AnimationClip당 Sprite는 1개씩 필요하며, 각 Sprite는 같은 이미지를 중복하여 참조 가능하다.
//8. 때문에 Flip이 따로 필요하지 않다.


//strKey는 멤버에 추가할 키와, ResoueceManager에서 가져올 키와 동일하게 동작한다.
void CSpriteRenderer::AddSprite(const string & strKey, CSprite * pSprite)
{
	CSprite* pTempSprite = pSprite->clone();
	unordered_map<string, CSprite*>::const_iterator iter = m_mapSprite.find(strKey);
	pTempSprite->SetRenderer(this);
	pTempSprite->SetSpriteKey(strKey);
	m_mapSprite.insert(make_pair(strKey, pTempSprite));
	
}

void CSpriteRenderer::ChangeCurrentClip(const string & strKey)
{
	m_strCurrentClipKey = strKey;
	m_pCurrentClip = m_mapSprite.find(strKey)->second;
	m_pCurrentClip->InitializeSprite();
}

void CSpriteRenderer::ChangeSpriteTexture(const string & strKey, CTexture * pTexture)
{
	unordered_map<string, CSprite*>::iterator iter = m_mapSprite.find(strKey);
	if (iter == m_mapSprite.end())
	{
		return;
	}
	iter->second->SetAtlas(pTexture);
}

void CSpriteRenderer::Start()
{
	CPlayer* pPlayer = m_pGameObject->GetPilot();

	if (!pPlayer)
		return;
	if (m_pGameObject->GetName().find("Mineral") != string::npos)
		return;
	if (m_pGameObject->GetName().find("Vespene") != string::npos)
		return;

	unordered_map<string, CSprite*>::iterator iter;
	unordered_map<string, CSprite*>::iterator iterEnd = m_mapSprite.end();

	for (iter = m_mapSprite.begin(); iter != iterEnd; ++iter)
	{
		CTexture* pOriginAtlas = (*iter).second->GetAtlasTexture();
		(*iter).second->SetAtlas(GET_SINGLE(CFileStream)->SetTeamColor(pPlayer->GetTeamColor(), pOriginAtlas));
	}
}

void CSpriteRenderer::Render()
{
	if (!m_pCurrentClip)
	{
		if (m_mapSprite.size() > 0)
		{
			SetDefaultClip();
		}
		else
		{
			assert(0);
		}
	}

	m_pCurrentClip->Update();

	CTexture* pTexture = m_pCurrentClip->GetAtlasTexture(); 

	if(!pTexture)
	{
		return;
	}
	CVector2 renderSize = CVector2(m_Size.x * m_pTransform->GetPivot().x * m_pTransform->GetScale().x,
		m_Size.y * m_pTransform->GetPivot().y * m_pTransform->GetScale().y);

	CVector2 position = m_pTransform->GetPosition() - renderSize;

	position -= m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();
	CVector2 screen = GET_SINGLE(CCore)->GetScreenSize();
	//카메라 밖으로 일정 이상 나갔을 때, 그리지 않는다. 
	if (position.x < -128 || position.x >= screen.x + 128 || position.y < -128 || position.y >= screen.y + 128)
	{
		return;
	}
	else
	{
		CVector2 atlasTopLeft = m_pCurrentClip->GetCurrentFrameLeftTopPosition();
		CVector2 atlasFrameSize = m_pCurrentClip->GetCellSize();

		if (m_pGameObject->GetScene()->GetName().find("Game") != string::npos)
		{
			CVector2 indexPosition = m_pTransform->GetPosition();
			int iXIndex = (int)indexPosition.x / 32;
			int iYIndex = (int)indexPosition.y / 32;
			int iTileIndex = iYIndex * m_pGameObject->GetScene()->GetGridSize().x + iXIndex;

			
			if (iXIndex < 0 || iXIndex > m_pGameObject->GetScene()->GetGridSize().x || iYIndex < 0 || iYIndex > m_pGameObject->GetScene()->GetGridSize().y)
			{
				return;
			}

			FOW tState = GET_SINGLE(CFogOfWarManager)->GetTileState(iTileIndex);

			if (m_pGameObject->GetLayer()->GetName().find("Terrain") == string::npos ||
				m_pGameObject->GetLayer()->GetName().find("GroundUnit") == string::npos ||
				m_pGameObject->GetLayer()->GetName().find("GroundVFX") == string::npos ||
				m_pGameObject->GetLayer()->GetName().find("AirUnit") == string::npos ||
				m_pGameObject->GetLayer()->GetName().find("AirVFX") == string::npos ||
				m_pGameObject->GetLayer()->GetName().find("FOW") == string::npos)
			{
				TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
					position.x, position.y,
					m_Size.x * m_pTransform->GetScale().x,
					m_Size.y * m_pTransform->GetScale().y,
					pTexture->GetDC(),
					atlasTopLeft.x,
					atlasTopLeft.y,
					atlasFrameSize.x,
					atlasFrameSize.y,
					RGB(0, 0, 0));
			}
			else
			{

				if (tState.m_eState == FS_VISIBLE)
				{
					TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
						position.x, position.y,
						m_Size.x * m_pTransform->GetScale().x,
						m_Size.y * m_pTransform->GetScale().y,
						pTexture->GetDC(),
						atlasTopLeft.x,
						atlasTopLeft.y,
						atlasFrameSize.x,
						atlasFrameSize.y,
						RGB(0, 0, 0));
				}
				else if (tState.m_eState == FS_INVISIBLE &&
					(m_pGameObject->GetName().find("Mineral") != string::npos ||
						m_pGameObject->GetName().find("VespeneGeyser") != string::npos))
				{

					TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
						position.x, position.y,
						m_Size.x * m_pTransform->GetScale().x,
						m_Size.y * m_pTransform->GetScale().y,
						pTexture->GetDC(),
						atlasTopLeft.x,
						atlasTopLeft.y,
						atlasFrameSize.x,
						atlasFrameSize.y,
						RGB(0, 0, 0));
				}
				else
				{
					return;
				}
			}


		}
		else
		{
			TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
				position.x, position.y,
				m_Size.x * m_pTransform->GetScale().x,
				m_Size.y * m_pTransform->GetScale().y,
				pTexture->GetDC(),
				atlasTopLeft.x,
				atlasTopLeft.y,
				atlasFrameSize.x,
				atlasFrameSize.y,
				RGB(0, 0, 0));
		}



#ifdef _DEBUG


		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

		HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();
		CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->GameObject()->GetTransform()->GetPosition();
		SelectObject(dc, pen);

		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x, m_pTransform->GetPosition().y - cameraPosition.y, RGB(0, 255, 0));

		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x + 1, m_pTransform->GetPosition().y - cameraPosition.y - 1, RGB(0, 255, 0));
		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x + 1, m_pTransform->GetPosition().y - cameraPosition.y, RGB(0, 255, 0));
		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x + 1, m_pTransform->GetPosition().y - cameraPosition.y + 1, RGB(0, 255, 0));

		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x, m_pTransform->GetPosition().y - cameraPosition.y - 1, RGB(0, 255, 0));
		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x, m_pTransform->GetPosition().y - cameraPosition.y , RGB(0, 255, 0));
		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x, m_pTransform->GetPosition().y - cameraPosition.y + 1, RGB(0, 255, 0));


		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x - 1, m_pTransform->GetPosition().y - cameraPosition.y - 1, RGB(0, 255, 0));
		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x - 1, m_pTransform->GetPosition().y - cameraPosition.y, RGB(0, 255, 0));
		SetPixel(dc, m_pTransform->GetPosition().x - cameraPosition.x - 1, m_pTransform->GetPosition().y - cameraPosition.y + 1, RGB(0, 255, 0));



		//MoveToEx(dc, position.x - cameraPosition.x, m_StartPosition.y - cameraPosition.y, NULL);
		//LineTo(dc, m_EndPosition.x, m_StartPosition.y - cameraPosition.y);
		//LineTo(dc, m_EndPosition.x, m_EndPosition.y);
		//LineTo(dc, m_StartPosition.x - cameraPosition.x, m_EndPosition.y);
		//LineTo(dc, m_StartPosition.x - cameraPosition.x, m_StartPosition.y - cameraPosition.y);
		DeleteObject(pen);


#endif // DEBUG



	}
}

void CSpriteRenderer::SaveComponent(FILE * pFile)
{
	fwrite(&m_LocalPosition, sizeof(CVector2), 1, pFile);
	fwrite(&m_Size, sizeof(CVector2), 1, pFile);
	
	// 맵 크기
	int iLength = m_mapSprite.size();
	fwrite(&iLength, 4, 1, pFile);
	unordered_map<string, CSprite*>::iterator iter;
	unordered_map<string, CSprite*>::iterator iterEnd = m_mapSprite.end();
	for (iter = m_mapSprite.begin(); iter != iterEnd; ++iter)
	{
		iLength = strlen((*iter).first.c_str());
		char cBuffer[256] = {};
		strcpy(cBuffer, (*iter).first.c_str());

		fwrite(&iLength, 4, 1, pFile);
		fwrite(cBuffer, sizeof(char), iLength, pFile);
		//읽어올 때, 이 키값으로 ResoueceManager에서 찾아온다.
	}
}

void CSpriteRenderer::LoadComponent(FILE * pFile)
{
	fread(&m_LocalPosition, sizeof(CVector2), 1, pFile);
	fread(&m_Size, sizeof(CVector2), 1, pFile);

	//맵의 크기 읽음
	int iLength = 0;
	fread(&iLength, 4, 1, pFile);

	for (int i = 0; i < iLength; ++i)
	{
		int iKeyLength = 0;
		fread(&iKeyLength, 4, 1, pFile);
		char cBuffer[256] = {};
		fread(&cBuffer, sizeof(char), iKeyLength, pFile);
		AddSprite(string(cBuffer), GET_SINGLE(CResourceManager)->FindSprite(string(cBuffer)));
	}

	SetDefaultClip();
}

CComponent * CSpriteRenderer::clone()
{
	return new CSpriteRenderer(*this);
}

CSpriteRenderer::CSpriteRenderer(const CSpriteRenderer & component) :
	m_pCurrentClip(NULL)
{
	m_LocalPosition = component.m_LocalPosition;

	unordered_map<string, CSprite*>::const_iterator iter;
	unordered_map<string, CSprite*>::const_iterator iterEnd = component.m_mapSprite.end();

	for (iter = component.m_mapSprite.begin(); iter != iterEnd; ++iter)
	{
		CSprite* cloneSprite = iter->second->clone();
		cloneSprite->SetRenderer(this);
		m_mapSprite.insert(make_pair(iter->first, cloneSprite));
	}
	
	m_strCurrentClipKey = component.m_strCurrentClipKey;
	m_pCurrentClip = FindSprite(m_strCurrentClipKey);
	m_Size = component.m_Size;

	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_SPRITE_RENDERER;
}

CSpriteRenderer::CSpriteRenderer():
	m_pCurrentClip(NULL)
{
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_SPRITE_RENDERER;
}


CSpriteRenderer::~CSpriteRenderer()
{
	unordered_map<string, CSprite*>::iterator iter;
	unordered_map<string, CSprite*>::iterator iterEnd = m_mapSprite.end();

	for (iter = m_mapSprite.begin(); iter != iterEnd; ++iter)
	{
		delete (*iter).second;
	}

	m_mapSprite.clear();
}
