#pragma once
#include "Game.h"

//Atlas의 인덱스를 프레임 단위로 삽입한다. 중복으로 삽입 가능하다.
class CSprite
{
private:

	vector<CVector2> m_vecAtlasFrameIndex;
	class CSpriteRenderer* m_pRenderer;
	class CTexture* m_pAtlasTexture;
	unsigned int m_iCurrentFrameIndex;
	float m_iSampleRate;
	float m_fCurrentPlayTime;
	float m_fPlayTime;
	bool m_bDestroyOnEnd;
	bool m_bLoop;
	unsigned int m_iCellWidth;
	unsigned int m_iCellHeight;
	unsigned int m_iHorizontalCellCount;
	unsigned int m_iVerticalCellCount;
	
	bool m_bStart;

	string m_strSpriteKey;

public:
	void SetDestroyOnEnd(bool bStop)
	{
		m_bDestroyOnEnd = bStop;
	}
	bool GetDestroyOnEnd() const
	{
		return m_bDestroyOnEnd;
	}

	string GetSpriteKey() const
	{
		return m_strSpriteKey;
	}
	void SetSpriteKey(const string& strKey)
	{
		m_strSpriteKey = strKey;
	}

	CVector2 GetFrameOffset(unsigned int index)
	{
		return m_vecAtlasFrameIndex[index];
	}
	
	CVector2 GetCurrentFrameLeftTopPosition() const
	{
		float x = m_iCellWidth * m_vecAtlasFrameIndex[m_iCurrentFrameIndex].x;
		float y = m_iCellHeight * m_vecAtlasFrameIndex[m_iCurrentFrameIndex].y;

		return CVector2(x,y);
	}
	CVector2 GetCurrentFrameRightBottomPosition() const
	{
		return GetCurrentFrameLeftTopPosition() + CVector2(m_iCellWidth, m_iCellHeight);
	}

	void AddFrame(int x, int y)
	{
		m_vecAtlasFrameIndex.push_back(CVector2(x,y));
	}
	void AddFrame(CVector2 index)
	{
		m_vecAtlasFrameIndex.push_back(index);
	}
	void SetLoop(bool bLoop)
	{
		m_bLoop = bLoop;
	}
	
	void SetAtlas(class CTexture* pTexture)
	{
		m_pAtlasTexture = pTexture;
	}
	void SetSampleRate(float iSampleRate)
	{
		m_iSampleRate = iSampleRate;
		m_fPlayTime = (float)m_vecAtlasFrameIndex.size() / (float)m_iSampleRate;
	}
	void SetCellSize(unsigned int iWidth, unsigned int iHeight)
	{
		m_iCellWidth = iWidth;
		m_iCellHeight = iHeight;
	}
	void SetCellSize(CVector2 size)
	{
		m_iCellWidth = size.x;
		m_iCellHeight = size.y;	
	}
	void SetCellWidth(unsigned int iWidth)
	{
		m_iCellWidth = iWidth;
	}
	void SetCellHeight(unsigned int iHeight)
	{
		m_iCellHeight = iHeight;
	}
	void SetAtlasGridSize(unsigned int iHorizontalCount, unsigned int iVerticalCount)
	{
		m_iHorizontalCellCount = iHorizontalCount;
		m_iVerticalCellCount = iVerticalCount;
	}
	void SetAtlasGridSize(CVector2 size)
	{
		m_iHorizontalCellCount = size.x;
		m_iVerticalCellCount = size.y;
	}
	void SetHorizontalCellCount(unsigned int iCellCount)
	{
		m_iHorizontalCellCount = iCellCount;
	}
	void SetVerticalCellCount(unsigned int iCellCount)
	{
		m_iVerticalCellCount = iCellCount;
	}

	class CTexture* GetAtlasTexture() const
	{
		return m_pAtlasTexture;
	}
	float GetSampleRate() const
	{
		return m_iSampleRate;
	}
	size_t GetClipLength() const
	{
		return m_vecAtlasFrameIndex.size();
	}
	unsigned int GetCellWidth() const
	{
		return m_iCellWidth;
	}
	unsigned int GetCellHeight() const
	{
		return m_iCellHeight;
	}
	CVector2 GetCellSize() const
	{
		return CVector2((float)m_iCellWidth, (float)m_iCellHeight);
	}
	unsigned int GetHorizontalCellCount() const
	{
		return m_iHorizontalCellCount;
	}
	unsigned int GetVerticalCellCount() const
	{
		return m_iVerticalCellCount;
	}
	CVector2 GetAtlasGridSize() const
	{
		return CVector2((float)m_iHorizontalCellCount, (float)m_iVerticalCellCount);
	}
	bool GetLoop() const
	{
		return m_bLoop;
	}
	

	void InitializeSprite()
	{
		m_bStart = false;
		m_iCurrentFrameIndex = 0;
		m_fCurrentPlayTime = 0;
	}
	
	class CSpriteRenderer* GetRenderer() const
	{
		return m_pRenderer;
	}
	void SetRenderer(class CSpriteRenderer* pRenderer)
	{
		m_pRenderer = pRenderer;
	}
	
	void Update();

public:

	
	void SaveSprite(const string& strFileName);
	
	bool LoadSprite(const string& strKey, const wchar_t* pFileName,
		const string& strPathKey = ANIMATION_CLIP_PATH);
	
	CSprite* clone();


public:
	CSprite(const CSprite& pSprite);
	CSprite();
	~CSprite();
};

