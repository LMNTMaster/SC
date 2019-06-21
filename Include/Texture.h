#pragma once
#include "Game.h"

class CTexture
{
private:

	vector<PIXEL> m_vecPixel;
	BITMAPFILEHEADER m_tFileHeader;
	BITMAPINFOHEADER m_tInfoHeader;

	HDC			m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldBitmap;
	BITMAP		m_tInfo;

	string		m_strTextureKey;
	wchar_t		m_strFileName[LONG_MAX_PATH] = {};
	wchar_t		m_strFileDirectory[LONG_MAX_PATH] = {};
	string		m_strPathKey;


public:
	string GetTextureKey() const
	{
		return m_strTextureKey;
	}
	void SetTextureKey(string strKey)
	{
		m_strTextureKey = strKey;
	}

	char* GetFileDirectory() const
	{
		char cBuffer[LONG_MAX_PATH] = {};
		memset(cBuffer, 0, sizeof(char) * LONG_MAX_PATH);
		WideCharToMultiByte(CP_ACP, 0, m_strFileDirectory, -1, cBuffer, lstrlen(m_strFileDirectory), 0, 0);
		return cBuffer;
	}

	char* GetTextureFileName() const
	{
		char cBuffer[LONG_MAX_PATH] = {};
		memset(cBuffer, 0, sizeof(char) * LONG_MAX_PATH);
		WideCharToMultiByte(CP_ACP, 0, m_strFileName, -1, cBuffer, lstrlen(m_strFileName), 0, 0);
		return cBuffer;
	}

	string GetTexturePathKey() const
	{
		return m_strPathKey;
	}

	BITMAPFILEHEADER GetFileHeader() const
	{
		return m_tFileHeader;
	}
	BITMAPINFOHEADER GetInfoHeader() const
	{
		return m_tInfoHeader;
	}
	vector<PIXEL>* GetPixel() 
	{
		return &m_vecPixel;
	}

	void SetPixel(vector<PIXEL>* pPixel)
	{
		m_vecPixel = *pPixel;
	}
	void SetFileHeader(BITMAPFILEHEADER fh)
	{
		m_tFileHeader = fh;
	}
	void SetInfoHeader(BITMAPINFOHEADER ih)
	{
		m_tInfoHeader = ih;
	}

	COLORREF GetPixel(unsigned int iX, unsigned int iY)
	{
		if (m_vecPixel.size() == 0)
			return NULL;
		
		if (iY * m_tInfoHeader.biWidth + iX < m_vecPixel.size())
		{
			PIXEL tempPixel = m_vecPixel[iY * m_tInfoHeader.biWidth + iX];
			return RGB(tempPixel.r, tempPixel.g, tempPixel.b);
		}
		else
			return NULL;
	}

	HBITMAP GetBitmap() const
	{
		return m_hBitmap;
	}

	BITMAP GetTextureInfo() const
	{
		return m_tInfo;
	}

	

	HDC GetDC()	const
	{
		return m_hMemDC;
	}
	bool LoadTexture(HINSTANCE hInst, HDC hDC,	const string& strKey, const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);


public:
	CTexture(const string& strPathKey, wchar_t* strFileName);
	CTexture();
	~CTexture();
};

