#pragma once

#include "../Game.h"
#include "fmod.hpp"

using namespace FMOD;

#pragma comment(lib, "fmod_vc")

enum SOUND_TYPE
{
	ST_BGM,
	ST_EFFECT,
	ST_END
};

typedef struct _tagSoundInfo
{
	Sound*	pSound;
	bool	bLoop;
}SOUNDINFO, *PSOUNDINFO;

class CSoundManager
{
private:
	System*		m_pSystem;
	Channel*	m_pChannel[ST_END];
	unordered_map<string, PSOUNDINFO>	m_mapSound;

public:
	bool Init();
	bool LoadSound(const string& strKey, bool bLoop, const char* pFileName,
		const string& strPathKey = SOUND_PATH);
	bool Play(const string& strKey);
	void Stop(SOUND_TYPE eType);
	void Volume(SOUND_TYPE eType, float fVolume);

private:
	PSOUNDINFO FindSound(const string& strKey);

	DECLARE_SINGLE(CSoundManager)
};

