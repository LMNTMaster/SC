#include "Texture.h"
#include "Core.h"
#include "ResourceManager.h"


bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC, const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	m_hMemDC = CreateCompatibleDC(NULL);
	const wchar_t* pPath = GET_SINGLE(CResourceManager)->FindPath(strPathKey);

	if (m_hMemDC == NULL)
	{
		assert(NULL);
		return false;
	}

	wstring	strPath;
	char cFileNameBuffer[LONG_MAX_PATH] = {};

	if (pPath)
	{
		strPath = pPath;		
	}

	char strFullPath[LONG_MAX_PATH] = {};
	string tempFullPath;
	wstring tempFullPathWide;


	wcscpy(m_strFileDirectory, strPath.c_str());	
	strPath += pFileName;	
	wcscpy(m_strFileName, strPath.c_str());	
	m_strPathKey = strPathKey;
	
	tempFullPathWide = m_strFileName;
	tempFullPath.assign(tempFullPathWide.begin(), tempFullPathWide.end());
	
	strcpy(strFullPath, tempFullPath.c_str());

	wcscpy(m_strFileName, pFileName);

	FILE* pFile = NULL;
	char cTempFileName[LONG_MAX_PATH] = {};
	strcpy(cTempFileName, strFullPath);
	fopen_s(&pFile, cTempFileName, "rb");
	
	if (pFile)
	{
		fread(&m_tFileHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
		fread(&m_tInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
		m_vecPixel.clear();
		m_vecPixel.resize(m_tInfoHeader.biWidth * m_tInfoHeader.biHeight);
		fread(&m_vecPixel[0], sizeof(PIXEL), m_tInfoHeader.biWidth * m_tInfoHeader.biHeight, pFile);	

		fclose(pFile);
	}
	else
	{
		return false;
	}

	
	PPIXEL pPixelArr = new PIXEL[m_tInfoHeader.biWidth];

	for (int i = 0; i < m_tInfoHeader.biHeight / 2; ++i)
	{
		memcpy(pPixelArr, &m_vecPixel[i * m_tInfoHeader.biWidth], sizeof(PIXEL) * m_tInfoHeader.biWidth);
		memcpy(&m_vecPixel[i * m_tInfoHeader.biWidth], &m_vecPixel[(m_tInfoHeader.biHeight - i - 1) * m_tInfoHeader.biWidth],
			sizeof(PIXEL) * m_tInfoHeader.biWidth);
		memcpy(&m_vecPixel[(m_tInfoHeader.biHeight - i - 1) * m_tInfoHeader.biWidth], pPixelArr,
			sizeof(PIXEL) * m_tInfoHeader.biWidth);
	}
	delete[] pPixelArr;


	m_hBitmap = (HBITMAP)LoadImage(hInst,  strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC,
		m_hBitmap);


	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}

CTexture::CTexture(const string & strPathKey, wchar_t * strFileName) :
	m_hMemDC(NULL)		
{
	m_strTextureKey = "";
	m_strPathKey = "";
}

CTexture::CTexture() :
	m_hMemDC(NULL)
{
	m_strTextureKey = "";
	m_strPathKey = "";
}


CTexture::~CTexture()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
