#include "Bunker.h"

#include "../../GameObject.h"
#include "../Transform.h"
#include "../SpriteRenderer.h"
#include "../ControlButton.h"
#include "../../ConsoleButton.h"
#include "../../Components/Player.h"
#include "../../ConsoleButtonManager.h"
#include "../../SceneManager.h"
#include "../../ResourceManager.h"
#include "../../Scene.h"
#include "../../SceneManager.h"
#include "../../Layer.h"
#include "../Player.h"
#include "../../Component.h"
#include "../Move.h"
#include "../GameResource.h"
#include "../Stop.h"
#include "../UnitStatus.h"
#include "../../Timer.h"
#include "../Attack.h"
#include "../UnitInfo.h"


void CBunker::Start()
{
	
}

void CBunker::Update()
{
}

void CBunker::LoadComponent(FILE * pFile)
{
}

void CBunker::SaveComponent(FILE * pFile)
{
}

CComponent * CBunker::clone()
{
	return new CBunker(*this);
}

CBunker::CBunker(const CBunker & component)
{
	m_eComponentType = CT_BUNKER;
}

CBunker::CBunker()
{
	m_eComponentType = CT_BUNKER;
}


CBunker::~CBunker()
{
}
