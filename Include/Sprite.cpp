#include "Sprite.h"
#include "Timer.h"
#include "GameObject.h"
#include "Component.h"
#include "Components\SpriteRenderer.h"
#include "Components\Animator.h"
#include "ResourceManager.h"
#include "Texture.h"


void CSprite::Update()
{
	
	if (!m_pAtlasTexture || m_vecAtlasFrameIndex.size() < 0)
	{
		return;
	}

	if (m_iCurrentFrameIndex == m_vecAtlasFrameIndex.size() - 1 && !m_bDestroyOnEnd && !m_bLoop)
	{
		return;
	}

	if (!m_bStart)
	{
		m_bStart = true;

		if (m_pRenderer->GameObject()->GetComponent<CAnimator>())
		{
			m_pRenderer->GameObject()->GetComponent<CAnimator>()->OnAnimationStart();
		}
	}
	
	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

	m_fCurrentPlayTime += fDeltaTime;
	float fSingleFrameTime = 1.0f / (float)m_iSampleRate;

	if (m_fCurrentPlayTime >= fSingleFrameTime)
	{
		m_fCurrentPlayTime -= fSingleFrameTime;
		
		if (m_bLoop)
		{			
			if (m_iCurrentFrameIndex == m_vecAtlasFrameIndex.size() - 1)
			{
				m_iCurrentFrameIndex = 0;
				InitializeSprite();

				if (m_pRenderer->GameObject()->GetComponent<CAnimator>())
				{
					m_pRenderer->GameObject()->GetComponent<CAnimator>()->OnAnimationEnd();
					m_bStart = false;
					return;
				}
			}
			else
			{
				++m_iCurrentFrameIndex;
			}
		}
		else
		{
			if (m_iCurrentFrameIndex == m_vecAtlasFrameIndex.size() - 1)
			{
				if (m_pRenderer->GameObject()->GetComponent<CAnimator>())
				{
					m_pRenderer->GameObject()->GetComponent<CAnimator>()->OnAnimationEnd();					
					m_bStart = false;
					return;
				}
				if (m_bDestroyOnEnd)
				{
					m_pRenderer->GameObject()->SetDestroy(true);
				}
				return;
			}
			else
			{
				++m_iCurrentFrameIndex;		
			}
		}		
	}	
	if (m_pRenderer->GameObject()->GetComponent<CAnimator>())
	{
		m_pRenderer->GameObject()->GetComponent<CAnimator>()->OnAnimationUpdate();
	}
	

}

void CSprite::SaveSprite(const string & strFileName)
{
	char strFullPath[LONG_MAX_PATH] = {};
	
	strcpy(strFullPath, GET_SINGLE(CResourceManager)->FindPathMultiByte(ANIMATION_CLIP_PATH));

	strcat(strFullPath, strFileName.c_str());

	FILE* pFile = NULL;

	fopen_s(&pFile, strFullPath, "wb");

	if (pFile)
	{
		int frameSize = m_vecAtlasFrameIndex.size();
		fwrite(&frameSize, 4, 1, pFile);

		for (int i = 0; i < frameSize; ++i)
		{
			fwrite(&m_vecAtlasFrameIndex[i], sizeof(CVector2), 1, pFile);
		}

		//Atlas의 Texture Key 저장 
		int iLength = strlen(m_pAtlasTexture->GetTextureKey().c_str());
		fwrite(&iLength, 4, 1, pFile);
		char keyName[256] = {};
		strcpy(keyName, m_pAtlasTexture->GetTextureKey().c_str());
		fwrite(keyName, sizeof(char), iLength, pFile);

		//샘플레이트
		fwrite(&m_iSampleRate, 4, 1, pFile);

		//루프
		fwrite(&m_bLoop, 1, 1, pFile);
		fwrite(&m_bDestroyOnEnd, 1, 1, pFile);

		//한 프레임의 크기
		fwrite(&m_iCellWidth, 4, 1, pFile);
		fwrite(&m_iCellHeight, 4, 1, pFile);

		//프레임 갯수
		fwrite(&m_iHorizontalCellCount, 4, 1, pFile);
		fwrite(&m_iVerticalCellCount, 4, 1, pFile);

		fclose(pFile);
	}

}

bool CSprite::LoadSprite(const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	char pPath[LONG_MAX_PATH] = {};	
	strcpy(pPath, GET_SINGLE(CResourceManager)->FindPathMultiByte(strPathKey));
	string	strPath;
	char cFileNameBuffer[LONG_MAX_PATH] = {};

	if (pPath)
	{
		strPath = pPath;
	}

	WideCharToMultiByte(CP_ACP, 0, pFileName, -1, cFileNameBuffer, lstrlen(pFileName), 0, 0);
	strPath += cFileNameBuffer;

	FILE* pFile = NULL;

	fopen_s(&pFile, strPath.c_str(), "rb");

	if (pFile)
	{
		//벡터의 크기
		int iLength = 0;
		fread(&iLength, 4, 1, pFile);

		for (int i = 0; i < iLength; ++i)
		{
			CVector2 tempVector;
			fread(&tempVector, sizeof(CVector2), 1, pFile);
			m_vecAtlasFrameIndex.push_back(tempVector);
		}

		//Atlas의 Texture Key 로 Texture 불러옴
		iLength = 0;
		fread(&iLength, 4, 1, pFile);
		char keyName[256] = {};
		fread(keyName, sizeof(char), iLength, pFile);

		m_pAtlasTexture = GET_SINGLE(CResourceManager)->FindTexture(string(keyName));

		//샘플레이트
		fread(&m_iSampleRate, 4, 1, pFile);

		//루프
		fread(&m_bLoop, 1, 1, pFile);
		fread(&m_bDestroyOnEnd, 1, 1, pFile);

		//한 프레임의 크기
		fread(&m_iCellWidth, 4, 1, pFile);
		fread(&m_iCellHeight, 4, 1, pFile);

		//프레임 갯수
		fread(&m_iHorizontalCellCount, 4, 1, pFile);
		fread(&m_iVerticalCellCount, 4, 1, pFile);

		fclose(pFile);
	}



	return true;
}

CSprite * CSprite::clone()
{
	return new CSprite(*this);
}

CSprite::CSprite(const CSprite & pSprite):	
	m_iCurrentFrameIndex(0),
	m_fCurrentPlayTime(0),
	m_fPlayTime(0),
	m_pRenderer(NULL),
	m_bStart(false),
	m_bDestroyOnEnd(false)
{
	m_vecAtlasFrameIndex = pSprite.m_vecAtlasFrameIndex;
	m_pAtlasTexture = pSprite.m_pAtlasTexture;
	m_iSampleRate = pSprite.m_iSampleRate;
	m_bLoop = pSprite.m_bLoop;
	m_bDestroyOnEnd = pSprite.m_bDestroyOnEnd;
	m_iCellWidth = pSprite.m_iCellWidth;
	m_iCellHeight = pSprite.m_iCellHeight;
	m_iHorizontalCellCount = pSprite.m_iHorizontalCellCount;
	m_iVerticalCellCount = pSprite.m_iVerticalCellCount;
	
	m_strSpriteKey = pSprite.m_strSpriteKey;
}

CSprite::CSprite() :
	m_pAtlasTexture(NULL),
	m_iCurrentFrameIndex(0),
	m_iSampleRate(0),
	m_fCurrentPlayTime(0),
	m_fPlayTime(0),
	m_bLoop(true),
	m_bStart(false),
	m_bDestroyOnEnd(false)
{
}


CSprite::~CSprite()
{
}
