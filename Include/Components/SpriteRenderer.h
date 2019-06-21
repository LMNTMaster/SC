#pragma once
#include "../Renderer.h"

//����� ������ �ִ� Sprite�� Animator�� �̺�Ʈ �Լ��� ȣ���ϱ� ������
//�ݵ�� Animator�� �Բ� ��� �Ǿ�� �Ѵ�.
//���� �ش� ������Ʈ�� ���ٸ� ȣ������ �ʴ´�.

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

	//���ο��� ���� �Ҵ� ��
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

