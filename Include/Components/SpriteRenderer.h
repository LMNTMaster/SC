#pragma once
#include "../Renderer.h"

//멤버로 가지고 있는 Sprite가 Animator의 이벤트 함수를 호출하기 때문에
//반드시 Animator와 함께 사용 되어야 한다.
//물론 해당 컴포넌트가 없다면 호출하지 않는다.

class CSpriteRenderer :
	public CRenderer
{
private:	
	CVector2 m_LocalPosition;
	unordered_map <string , class CSprite*> m_mapSprite;
	class CSprite* m_pCurrentClip;
	string		m_strCurrentClipKey;
	CVector2	m_Size;

public:
	void SetDefaultClip()
	{		
		ChangeCurrentClip(m_mapSprite.begin()->first);		
	}
	CSprite* GetCurrentClip() const
	{
		return m_pCurrentClip;
	}
	CVector2 GetLocalPosition() const
	{
		return m_LocalPosition;
	}
	void SetLocalPosition(CVector2 pos)
	{
		m_LocalPosition = pos;
	}
	void SetLocalPosition(float x, float y)
	{
		m_LocalPosition = CVector2(x, y);
	}

	//내부에서 힙에 할당 함
	void AddSprite(const string& strKey, class CSprite* pSprite);	

	class CSprite* FindSprite(const string& strKey) const
	{
		if (strKey != "")
		{
			unordered_map<string, class CSprite*>::const_iterator iter = m_mapSprite.find(strKey);
			if ((*iter).second)
			{
				return (*iter).second;
			}
		}
		return NULL;
	}

	string GetCurrentClipKey() const
	{
		return m_strCurrentClipKey;
	}	
	void ChangeCurrentClip(const string& strKey);

	void SetSize(float fWidth, float fHeight)
	{
		m_Size = CVector2(fWidth, fHeight);
	}
	void SetSize(CVector2 size)
	{
		m_Size = size;
	}
	CVector2 GetSize() const
	{
		return m_Size;
	}

	void ChangeSpriteTexture(const string& strKey, class CTexture* pTexture);


public:
	void Start() override;
	void Render() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override; 
	CComponent* clone() override;

public:
	CSpriteRenderer(const CSpriteRenderer& component);
	CSpriteRenderer();
	~CSpriteRenderer();
};

