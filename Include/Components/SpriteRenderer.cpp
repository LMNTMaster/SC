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


//���ó..?
//Splash - TextureRenderer or UI Renderer
//���� - atlas
//�ǹ�(�Ǽ��� ����) - atlas(���� ��, �Ǽ� ��, ���.. �� texture�� ����)
//���� - TextureRenderer (�ڿ����� ���, m_pTexture�� ��ü�ϴ¹���� ���� ��)
//����Ʈ - atlas
//�׸��� - TextureRenderer (1�������̹Ƿ�)
//UI - UI Renderer / TextureRenderer (�Ϻ� atlas) ��� UI���� �̺�Ʈ �߻� �� TextureRenderer�� m_pTexture�� ��ü�ϴ¹���� ���Ұ� ����
//Frame���� ���� ��..?

//1. Sprite���� Update �� ���� ���������� �Ѿ�� ���� ����,
//2. Sprite�� �ݵ�� Atlas�̾�� �Ѵ�.
//3. Atlas�� Ư�� �ε���(��(Horizontal) �켱)�� ���Ϳ� �������.
//4. ������ ��ȯ ��, ������ ���� �ε����� ������ ��ġ ã��.
//5. SpriteRenderer���� �ش� ��ġ �׷���.
//6. Flip�� ���� ���� ���� �ʰ�, ���� �̹����� �������� �ϳ� �� ���� ����ϵ��� �Ѵ�.
//7. ���� AnimationClip�� Sprite�� 1���� �ʿ��ϸ�, �� Sprite�� ���� �̹����� �ߺ��Ͽ� ���� �����ϴ�.
//8. ������ Flip�� ���� �ʿ����� �ʴ�.


//strKey�� ����� �߰��� Ű��, ResoueceManager���� ������ Ű�� �����ϰ� �����Ѵ�.
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
	//ī�޶� ������ ���� �̻� ������ ��, �׸��� �ʴ´�. 
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
	
	// �� ũ��
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
		//�о�� ��, �� Ű������ ResoueceManager���� ã�ƿ´�.
	}
}

void CSpriteRenderer::LoadComponent(FILE * pFile)
{
	fread(&m_LocalPosition, sizeof(CVector2), 1, pFile);
	fread(&m_Size, sizeof(CVector2), 1, pFile);

	//���� ũ�� ����
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
