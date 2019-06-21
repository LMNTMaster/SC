
#include "Core.h"
#include "Timer.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "FileStream.h"
#include "Option.h"
#include "Tile.h"
#include "Input.h"
#include "VectorFieldManager.h"
#include "ConsoleButtonManager.h"
#include "InfoPanelManager.h"
#include "FogOfWarManager.h"
#include "MinimapManager.h"

CCore* CCore::m_pInstance = NULL;
bool		CCore::m_bLoop = true;


CCore::CCore():
	m_iProgress(0),
	m_iMaxProgress(1000)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(180333);
}


CCore::~CCore()
{	
	if (m_iProgress < m_iMaxProgress)
	{
		m_iProgress = m_iMaxProgress;
		m_pLoadingThread->detach();
	}
	delete m_pLoadingThread;

	CTimer::DestroyInstance();
	CSceneManager::DestroyInstance();
	CResourceManager::DestroyInstance();
	CFileStream::DestroyInstance();
	COption::DestroyInstance();
	CInput::DestroyInstance();
	CVectorFieldManager::DestoryInstance();
	CConsoleButtonManager::DestoryInstance();
	CInfoPanelManager::DestroyInstance();
	CFogOfWarManager::DestroyInstance();
	CMinimapManager::DestroyInstance();
}


void CCore::Loading()
{
	GET_SINGLE(CFileStream)->LoadPalette()

	//SFX 파일 읽음

	//Glue
	GET_SINGLE(CResourceManager)->LoadSound("ButtonClick", false, "glue\\mousedown2.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("ButtonOver", false, "glue\\mouseover.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Buzz", false, "glue\\buzz.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("ErrorMineral", false, "terran\\advisor\\taderr00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("ErrorVespeneGas", false, "terran\\advisor\\taderr01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("ErrorSupply", false, "terran\\advisor\\taderr02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("ErrorEnergy", false, "terran\\advisor\\taderr06.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("ErrorLandingInterupted", false, "terran\\advisor\\taderr03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("ErrorLandingPlace", false, "terran\\advisor\\taderr04.wav", SFX_PATH);

	GET_SINGLE(CResourceManager)->LoadSound("UnderAttackBase", false, "terran\\advisor\\tadupd00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("UnderAttackForce", false, "terran\\advisor\\tadupd01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("CompleteResearch", false, "terran\\advisor\\tadupd02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("CompleteAddon", false, "terran\\advisor\\tadupd03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("CompleteUpgrade", false, "terran\\advisor\\tadupd06.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("NukeDetected", false, "terran\\advisor\\tadupd04.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("NukeReady", false, "terran\\advisor\\tadupd07.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BuildStructure", false, "misc\\pbldgplc.wav", SFX_PATH);

	//Unit
	GET_SINGLE(CResourceManager)->LoadSound("SCVAttack0",false,"terran\\scv\\edrrep00.wav",SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVAttack1", false, "terran\\scv\\edrrep01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVAttack2", false, "terran\\scv\\edrrep02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVAttack3", false, "terran\\scv\\edrrep03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVAttack4", false, "terran\\scv\\edrrep04.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVDeath0", false, "terran\\scv\\tscdth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVCannotBuild0", false, "terran\\scv\\tscerr00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVCannotBuild1", false, "terran\\scv\\tscerr01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVReady0", false, "terran\\scv\\tscrdy00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVComplete0", false, "terran\\scv\\tscupd00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVSelect0", false, "terran\\scv\\tscwht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVSelect1", false, "terran\\scv\\tscwht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVSelect2", false, "terran\\scv\\tscwht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVSelect3", false, "terran\\scv\\tscwht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVCommand0", false, "terran\\scv\\tscyes00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVCommand1", false, "terran\\scv\\tscyes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVCommand2", false, "terran\\scv\\tscyes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("SCVCommand3", false, "terran\\scv\\tscyes03.wav", SFX_PATH);	





	GET_SINGLE(CResourceManager)->LoadSound("Stimpack0", false, "terran\\marine\\tmasti00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Stimpack1", false, "terran\\marine\\tmasti01.wav", SFX_PATH);

	GET_SINGLE(CResourceManager)->LoadSound("MarineDeath0", false, "terran\\marine\\tmadth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineDeath1", false, "terran\\marine\\tmadth01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineSelect0", false, "terran\\marine\\tmawht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineSelect1", false, "terran\\marine\\tmawht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineSelect2", false, "terran\\marine\\tmawht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineSelect3", false, "terran\\marine\\tmawht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineCommand0", false, "terran\\marine\\tmayes00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineCommand1", false, "terran\\marine\\tmayes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineCommand2", false, "terran\\marine\\tmayes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineCommand3", false, "terran\\marine\\tmayes03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MarineAttack0", false, "bullet\\tmafir00.wav", SFX_PATH);


	GET_SINGLE(CResourceManager)->LoadSound("FirebatDeath0", false, "terran\\firebat\\tfbdth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatDeath1", false, "terran\\firebat\\tfbdth01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatSelect0", false, "terran\\firebat\\tfbwht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatSelect1", false, "terran\\firebat\\tfbwht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatSelect2", false, "terran\\firebat\\tfbwht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatSelect3", false, "terran\\firebat\\tfbwht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatCommand0", false, "terran\\firebat\\tfbyes00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatCommand1", false, "terran\\firebat\\tfbyes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatCommand2", false, "terran\\firebat\\tfbyes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatCommand3", false, "terran\\firebat\\tfbyes03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatAttack0", false, "terran\\firebat\\tfbfir00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("FirebatAttack1", false, "terran\\firebat\\tfbfir01.wav", SFX_PATH);

	GET_SINGLE(CResourceManager)->LoadSound("MedicDeath0", false, "terran\\medic\\TMdDth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicDeath1", false, "terran\\medic\\tfbdth01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicSelect0", false, "terran\\medic\\TMdWht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicSelect1", false, "terran\\medic\\TMdWht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicSelect2", false, "terran\\medic\\TMdWht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicSelect3", false, "terran\\medic\\TMdWht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicCommand0", false, "terran\\medic\\TMdYes00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicCommand1", false, "terran\\medic\\TMdYes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicCommand2", false, "terran\\medic\\TMdYes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicCommand3", false, "terran\\medic\\TMdYes03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicAttack0", false, "terran\\medic\\tfbfir00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("MedicAttack1", false, "terran\\medic\\tfbfir01.wav", SFX_PATH);


	GET_SINGLE(CResourceManager)->LoadSound("GhostDeath0", false, "terran\\ghost\\tghdth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostDeath1", false, "terran\\ghost\\tghdth01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostSelect0", false, "terran\\ghost\\tghwht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostSelect1", false, "terran\\ghost\\tghwht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostSelect2", false, "terran\\ghost\\tghwht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostSelect3", false, "terran\\ghost\\tghwht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostCommand0", false, "terran\\ghost\\tghyes00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostCommand1", false, "terran\\ghost\\tghyes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostCommand2", false, "terran\\ghost\\tghyes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostCommand3", false, "terran\\ghost\\tghyes03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostAttack0", false, "terran\\ghost\\tghfir00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("GhostAttack1", false, "terran\\ghost\\tghfir00.wav", SFX_PATH);
	
	GET_SINGLE(CResourceManager)->LoadSound("VultureDeath0", false, "terran\\vulture\\tvudth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureDeath1", false, "terran\\vulture\\tvudth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureSelect0", false, "terran\\vulture\\tvuwht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureSelect1", false, "terran\\vulture\\tvuwht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureSelect2", false, "terran\\vulture\\tvuwht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureSelect3", false, "terran\\vulture\\tvuwht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureCommand0", false, "terran\\vulture\\tvuyes00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureCommand1", false, "terran\\vulture\\tvuyes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureCommand2", false, "terran\\vulture\\tvuyes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureCommand3", false, "terran\\vulture\\tvuyes03.wav", SFX_PATH);

	GET_SINGLE(CResourceManager)->LoadSound("VultureAttack0", false, "bullet\\tvufir00.wav", SFX_PATH);
	//Hit
	GET_SINGLE(CResourceManager)->LoadSound("VultureHit0", false, "bullet\\tvuhit00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureHit1", false, "bullet\\tvuhit01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("VultureHit2", false, "bullet\\tvuhit02.wav", SFX_PATH);



	GET_SINGLE(CResourceManager)->LoadSound("WraithDeath0", false, "terran\\wraith\\tphdth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithDeath1", false, "terran\\wraith\\tphdth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithSelect0", false, "terran\\wraith\\tphwht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithSelect1", false, "terran\\wraith\\tphwht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithSelect2", false, "terran\\wraith\\tphwht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithSelect3", false, "terran\\wraith\\tphwht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithCommand0", false, "terran\\wraith\\tphyes00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithCommand1", false, "terran\\wraith\\tphyes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithCommand2", false, "terran\\wraith\\tphyes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithCommand3", false, "terran\\wraith\\tphyes03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithAttack0", false, "bullet\\tphfi100.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("WraithAttack1", false, "bullet\\tphfi100.wav", SFX_PATH);


	GET_SINGLE(CResourceManager)->LoadSound("DropshipDeath0", false, "terran\\dropship\\tdrdth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("DropshipDeath1", false, "terran\\dropship\\tdrdth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("DropshipSelect0", false, "terran\\dropship\\tdrwht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("DropshipSelect1", false, "terran\\dropship\\tdrwht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("DropshipSelect2", false, "terran\\dropship\\tdrwht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("DropshipSelect3", false, "terran\\dropship\\tdrwht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("DropshipCommand0", false, "terran\\dropship\\tdryes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("DropshipCommand1", false, "terran\\dropship\\tdryes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("DropshipCommand2", false, "terran\\dropship\\tdryes03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("DropshipCommand3", false, "terran\\dropship\\tdryes04.wav", SFX_PATH);


	GET_SINGLE(CResourceManager)->LoadSound("Science VesselDeath0", false, "terran\\vessel\\tvedth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Science VesselDeath1", false, "terran\\vessel\\tvedth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Science VesselSelect0", false, "terran\\vessel\\tvewht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Science VesselSelect1", false, "terran\\vessel\\tvewht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Science VesselSelect2", false, "terran\\vessel\\tvewht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Science VesselSelect3", false, "terran\\vessel\\tvewht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Science VesselCommand0", false, "terran\\vessel\\tveyes00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Science VesselCommand1", false, "terran\\vessel\\tveyes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Science VesselCommand2", false, "terran\\vessel\\tveyes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("Science VesselCommand3", false, "terran\\vessel\\tveyes03.wav", SFX_PATH);


	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserDeath0", false, "terran\\battle\\tbadth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserDeath1", false, "terran\\battle\\tbadth00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserSelect0", false, "terran\\battle\\tbawht00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserSelect1", false, "terran\\battle\\tbawht01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserSelect2", false, "terran\\battle\\tbawht02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserSelect3", false, "terran\\battle\\tbawht03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserCommand0", false, "terran\\battle\\tbayes00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserCommand1", false, "terran\\battle\\tbayes01.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserCommand2", false, "terran\\battle\\tbayes02.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserCommand3", false, "terran\\battle\\tbayes03.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserAttack0", false, "bullet\\laserb.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserAttack1", false, "bullet\\lasrhit3.wav", SFX_PATH);

	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserYamatoCharge", false, "terran\\battle\\tbayam01.wav", SFX_PATH);

	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserYamatoShot0", false, "bullet\\tbayam00.wav", SFX_PATH);
	GET_SINGLE(CResourceManager)->LoadSound("BattlecruiserYamatoShot1", false, "terran\\battle\\tbayam02.wav", SFX_PATH);


	//BGM 파일 읽음
	GET_SINGLE(CResourceManager)->LoadSound("Terran1", true, "terran1.wav", BGM_PATH);




	// Texture, AnimationClip, GameObject, Loading
	//텍스쳐 읽음	

	GET_SINGLE(CResourceManager)->LoadTexture("MineralOrb", L"MineralOrb.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("GasTank", L"GasTank.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("GasSac", L"GasSac.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("GasBox", L"GasBox.bmp", UNIT_TEXTURE_PATH);

	GET_SINGLE(CResourceManager)->LoadTexture("Cursor", L"Cursor.bmp", UI_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("CursorRequestPointer", L"CursorRequestPointer.bmp", UI_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Main_EditorBase_Atlas", L"Editor.bmp", UI_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Main_EditorOver_Atlas", L"Editor_over.bmp", UI_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Main_ExitBase_Atlas", L"Exit_base.bmp", UI_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Main_ExitOver_Atlas", L"Exit_over.bmp", UI_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Main_SingleBase_Atlas", L"Single_base.bmp", UI_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Main_SingleOver_Atlas", L"Single_over.bmp", UI_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Terrain_Badland_Atlas", L"Badland.bmp", TILESET_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);	
	GET_SINGLE(CResourceManager)->LoadTexture("Terrain_Badland_Grey_Atlas", L"Badland_GreyScale.bmp", TILESET_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Terrain_Hunter", L"Hunter(8).bmp", TILESET_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Terrain_Hunter_Minimap", L"Hunter(8)_minimap.bmp", TILESET_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("Fog_Minimap", L"Fog.bmp", TILESET_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);


	GET_SINGLE(CResourceManager)->LoadTexture("PositiveCell", L"Positive.bmp", TILESET_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("NegativeCell", L"Negative.bmp", TILESET_TEXTURE_PATH);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("BlackCell", L"Black.bmp", TILESET_TEXTURE_PATH);


	//Top UI
	GET_SINGLE(CResourceManager)->LoadTexture("TopPanel_Icon_Mineral", L"TopPanel\\icons000.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("TopPanel_Icon_Terran_VespeneGas", L"TopPanel\\icons002.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("TopPanel_Icon_Protoss_VespeneGas", L"TopPanel\\icons003.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("TopPanel_Icon_Zerg_VespeneGas", L"TopPanel\\icons001.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("TopPanel_Icon_Terran_Supply", L"TopPanel\\icons005.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("TopPanel_Icon_Terran_Supply", L"TopPanel\\icons006.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("TopPanel_Icon_Zerg_Supply", L"TopPanel\\icons004.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);


	//Bottom UI
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Terran_Background", L"BottomPanel\\Button\\Terran\\tcmdbtns013.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Protoss_Background", L"BottomPanel\\Button\\Protoss\\pcmdbtns013.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Zerg_Background", L"BottomPanel\\Button\\Zerg\\zcmdbtns013.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_ProgressBar_Background", L"BottomPanel\\ConsolePanel\\ProgressBackground.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_ProgressBar_Foreground", L"BottomPanel\\ConsolePanel\\ProgressForeground.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Terran_Queue1", L"BottomPanel\\Button\\Terran\\tcmdbtns006.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Terran_Queue2", L"BottomPanel\\Button\\Terran\\tcmdbtns007.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Terran_Queue3", L"BottomPanel\\Button\\Terran\\tcmdbtns008.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Terran_Queue4", L"BottomPanel\\Button\\Terran\\tcmdbtns009.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Terran_Queue5", L"BottomPanel\\Button\\Terran\\tcmdbtns010.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Protoss_Queue1", L"BottomPanel\\Button\\Protoss\\pcmdbtns006.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Protoss_Queue2", L"BottomPanel\\Button\\Protoss\\pcmdbtns007.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Protoss_Queue3", L"BottomPanel\\Button\\Protoss\\pcmdbtns008.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Protoss_Queue4", L"BottomPanel\\Button\\Protoss\\pcmdbtns009.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Protoss_Queue5", L"BottomPanel\\Button\\Protoss\\pcmdbtns010.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Zerg_Queue1", L"BottomPanel\\Button\\Zerg\\zcmdbtns006.bmp", UI_TEXTURE_PATH);	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Zerg_Queue2", L"BottomPanel\\Button\\Zerg\\zcmdbtns007.bmp", UI_TEXTURE_PATH);	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Zerg_Queue3", L"BottomPanel\\Button\\Zerg\\zcmdbtns008.bmp", UI_TEXTURE_PATH);	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Zerg_Queue4", L"BottomPanel\\Button\\Zerg\\zcmdbtns009.bmp", UI_TEXTURE_PATH);	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Zerg_Queue5", L"BottomPanel\\Button\\Zerg\\zcmdbtns010.bmp", UI_TEXTURE_PATH);	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);


	
	//Terran Info Panel Button
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Terran_SCV", L"BottomPanel\\Button\\UnitButton\\scv.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	// Equipment Info Panel Button
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Terran_EquipmentBackground", L"BottomPanel\\Button\\Terran\\tcmdbtns012.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Protoss_EquipmentBackground", L"BottomPanel\\Button\\Protoss\\pcmdbtns012.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("InfoPanel_Button_Zerg_EquipmentBackground", L"BottomPanel\\Button\\Zerg\\zcmdbtns012.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);



	
	GET_SINGLE(CResourceManager)->LoadTexture("ConsolePanel_Terran", L"BottomPanel\\ConsolePanel\\Terran_mastered.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ConsolePanel_Protoss", L"BottomPanel\\ConsolePanel\\Protoss_mastered.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ConsolePanel_Zerg", L"BottomPanel\\ConsolePanel\\Zerg_mastered.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Background_Terran_Normal", L"BottomPanel\\Button\\Terran\\tcmdbtns000.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Background_Terran_Pressed", L"BottomPanel\\Button\\Terran\\tcmdbtns001.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Background_Protoss_Normal", L"BottomPanel\\Button\\Protoss\\pcmdbtns000.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Background_Protoss_Pressed", L"BottomPanel\\Button\\Protoss\\pcmdbtns001.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Background_Zerg_Normal", L"BottomPanel\\Button\\Zerg\\zcmdbtns000.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Background_Zerg_Pressed", L"BottomPanel\\Button\\Zerg\\zcmdbtns001.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
		
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Move_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons228.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Move_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons228.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Stop_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons229.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Stop_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons229.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Attack_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons230.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Attack_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons230.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Gather_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons231.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Gather_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons231.bmp", UI_TEXTURE_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Repair_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons232.bmp", UI_TEXTURE_PATH); 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Repair_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons232.bmp", UI_TEXTURE_PATH);	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Patrol_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons254.bmp", UI_TEXTURE_PATH);  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Patrol_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons254.bmp", UI_TEXTURE_PATH);	  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Hold_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons255.bmp", UI_TEXTURE_PATH);	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Hold_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons255.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Cancel_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons236.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_Cancel_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons236.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBuild_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons234.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBuild_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons234.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBuildAdvanced_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons235.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBuildAdvanced_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons235.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_ProtossBuild_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons272.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_ProtossBuild_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons272.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_ProtossBuildAdvanced_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons273.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_ProtossBuildAdvanced_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons273.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_ZergBuild_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons257.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_ZergBuild_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons257.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_ZergBuildAdvanced_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons258.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_ZergBuildAdvanced_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons258.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranCommandCenter_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons106.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranCommandCenter_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons106.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranSupplyDepot_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons109.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranSupplyDepot_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons109.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranRefinery_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons110.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranRefinery_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons110.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBarracks_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons111.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBarracks_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons111.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranEngineeringBay_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons122.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranEngineeringBay_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons122.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranMissileTurret_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons124.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranMissileTurret_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons124.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranAcademy_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons112.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranAcademy_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons112.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBunker_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons125.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBunker_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons125.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranFactory_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons113.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranFactory_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons113.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranMachineShop_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons120.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranMachineShop_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons120.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranControlTower_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons115.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranControlTower_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons115.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranStarport_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons114.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranStarport_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons114.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranScienceFacility_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons116.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranScienceFacility_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons116.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranArmory_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons123.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranArmory_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons123.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);


	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranMarine_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons020.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranMarine_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons020.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranFirebat_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons032.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranFirebat_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons032.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranMedic_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons034.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranMedic_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons034.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranGhost_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons001.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranGhost_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons001.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranVulture_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons002.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranVulture_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons002.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranSiegeTank_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons023.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranSiegeTank_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons023.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranSiege_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons025.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranSiege_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons025.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranGoliath_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons003.bmp", UI_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranGoliath_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons003.bmp", UI_TEXTURE_PATH);


	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranWraith_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons008.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranWraith_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons008.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranValkyrie_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons003.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranValkyrie_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons003.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBattlecruiser_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons028.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranBattlecruiser_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons028.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranScienceVessel_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons009.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranScienceVessel_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons009.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranDropship_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons011.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranDropship_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons011.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);




	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranSCV_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons007.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranSCV_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons007.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranStimpack_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons237.bmp", UI_TEXTURE_PATH);  ++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranStimpack_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons237.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranU238_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons238.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranU238_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons238.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranRestoration_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons366.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranRestoration_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons366.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranOpticalFlare_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons373.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranOpticalFlare_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons373.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranCaduceusReactor_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons384.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranCaduceusReactor_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons384.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranInfantryWeapon_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons288.bmp", UI_TEXTURE_PATH);	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranInfantryWeapon_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons288.bmp", UI_TEXTURE_PATH);  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranInfantryArmor_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons292.bmp", UI_TEXTURE_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranInfantryArmor_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons292.bmp", UI_TEXTURE_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranVehicleWeapon_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons289.bmp", UI_TEXTURE_PATH);  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranVehicleWeapon_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons289.bmp", UI_TEXTURE_PATH);   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranVehicleArmor_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons293.bmp", UI_TEXTURE_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranVehicleArmor_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons293.bmp", UI_TEXTURE_PATH);		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranShipWeapon_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons290.bmp", UI_TEXTURE_PATH);			++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranShipWeapon_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons290.bmp", UI_TEXTURE_PATH);			++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranShipArmor_Normal", L"BottomPanel\\Button\\Icon\\YellowScaled\\cmdicons291.bmp", UI_TEXTURE_PATH);		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadTexture("ControlButton_Icon_TerranShipArmor_Pressed", L"BottomPanel\\Button\\Icon\\GreyScaled\\cmdicons291.bmp", UI_TEXTURE_PATH);		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);


		
	GET_SINGLE(CResourceManager)->LoadTexture("SCVLeft", L"Terran\\SCV\\SCVLeft.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("SCVRight", L"Terran\\SCV\\SCVRight.bmp", UNIT_TEXTURE_PATH);

	GET_SINGLE(CResourceManager)->LoadTexture("CommandCenter", L"Terran\\CommandCenter\\CommandCenter.bmp" ,UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("SupplyDepot", L"Terran\\SupplyDepot\\SupplyDepot.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Barracks", L"Terran\\Barracks\\Barracks.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Refinery", L"Terran\\Refinery\\Refinery.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("EngineeringBay", L"Terran\\EngineeringBay\\EngineeringBay.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("MissileTurret", L"Terran\\MissileTurret\\MissileTurret.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("MissileTurretBuild", L"Terran\\MissileTurret\\MissileTurretBuild.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Academy", L"Terran\\Academy\\Academy.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Bunker", L"Terran\\Bunker\\Bunker.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Factory", L"Terran\\Factory\\Factory.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Starport", L"Terran\\Starport\\Starport.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("ScienceFacility", L"Terran\\ScienceFacility\\ScienceFacility.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Armory", L"Terran\\Armory\\Armory.bmp", UNIT_TEXTURE_PATH);
	
	GET_SINGLE(CResourceManager)->LoadTexture("Mineral01", L"Mineral01.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Mineral02", L"Mineral02.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Mineral03", L"Mineral03.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("VespeneGeyser", L"Neutral\\VespeneGeyser.bmp", UNIT_TEXTURE_PATH);	

	GET_SINGLE(CResourceManager)->LoadTexture("Marine", L"Terran\\Marine\\Marine.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Firebat", L"Terran\\Firebat\\Firebat.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Ghost", L"Terran\\Ghost\\Ghost.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Medic", L"Terran\\Medic\\Medic.bmp", UNIT_TEXTURE_PATH);

	GET_SINGLE(CResourceManager)->LoadTexture("Vulture", L"Terran\\Vulture\\Vulture.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("TankHead", L"Terran\\SiegeTank\\TankHead.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("TankBody", L"Terran\\SiegeTank\\TankNormalLowbody.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("TankBodyTransform", L"Terran\\SiegeTank\\TankSeigeMode.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("TankHeadTransform", L"Terran\\SiegeTank\\TankTransformHead.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("GoliathBody", L"Terran\\Goliath\\GoliathLowbody.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("GoliathHead", L"Terran\\Goliath\\GoliathUpbody.bmp", UNIT_TEXTURE_PATH);

	GET_SINGLE(CResourceManager)->LoadTexture("Wraith", L"Terran\\Wraith\\Wraith.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Dropship", L"Terran\\DropShip\\Dropship.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Battlecruiser", L"Terran\\Battlecruiser\\Battlecruiser.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Valkyrie", L"Terran\\Valkyrie\\Valkyrie.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("ScienceVessel", L"Terran\\ScienceVessel\\ScienceVessel.bmp", UNIT_TEXTURE_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("ScienceVesselHead", L"Terran\\ScienceVessel\\ScienceVesselHead.bmp", UNIT_TEXTURE_PATH);
	

	GET_SINGLE(CResourceManager)->LoadTexture("MainMenuBackground", L"MainMenuBackground.bmp", UI_TEXTURE_PATH);
	
	//VFX
	//Terran
	GET_SINGLE(CResourceManager)->LoadTexture("Terran_Explosion_XSmall", L"Terran_XSmall_Explosion.bmp", VFX_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Terran_Explosion_Small", L"Terran_Small_Explosion.bmp", VFX_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Terran_Explosion_Large", L"Terran_Large_Explosion.bmp", VFX_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("Terran_Explosion_XLarge", L"Terran_XLarge_Explosion.bmp", VFX_PATH);

	
	GET_SINGLE(CResourceManager)->LoadTexture("SCVAttack", L"Terran_SCV_Attack.bmp", VFX_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("TerranBulletAttack", L"TerranBulletAttack.bmp", VFX_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("FirebatAttack", L"FirebatAttack.bmp", VFX_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("GeyserSmoke1", L"GeyserSmoke.bmp", VFX_PATH);
	GET_SINGLE(CResourceManager)->LoadTexture("GeyserSmoke2", L"GeyserSmoke2.bmp", VFX_PATH);


	//애니메이션 클립 파일 읽음
	
	GET_SINGLE(CResourceManager)->LoadSprite("CursorNormal", L"CursorNormal.aclp", ANIMATION_CLIP_PATH);
	GET_SINGLE(CResourceManager)->LoadSprite("CursorRequestPointer", L"CursorRequestPointer.aclp", ANIMATION_CLIP_PATH);	  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MineralOrb0", L"MineralOrb0.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MineralOrb1", L"MineralOrb1.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MineralOrb2", L"MineralOrb2.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MineralOrb3", L"MineralOrb3.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MineralOrb4", L"MineralOrb4.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MineralOrb5", L"MineralOrb5.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MineralOrb6", L"MineralOrb6.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MineralOrb7", L"MineralOrb7.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MineralOrb8", L"MineralOrb8.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadSprite("GasBox0", L"GasBox0.aclp", ANIMATION_CLIP_PATH);		   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasBox1", L"GasBox1.aclp", ANIMATION_CLIP_PATH);		   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasBox2", L"GasBox2.aclp", ANIMATION_CLIP_PATH);		   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasBox3", L"GasBox3.aclp", ANIMATION_CLIP_PATH);		   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasBox4", L"GasBox4.aclp", ANIMATION_CLIP_PATH);		   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasBox5", L"GasBox5.aclp", ANIMATION_CLIP_PATH);		   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasBox6", L"GasBox6.aclp", ANIMATION_CLIP_PATH);		   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasBox7", L"GasBox7.aclp", ANIMATION_CLIP_PATH);		   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasBox8", L"GasBox8.aclp", ANIMATION_CLIP_PATH);		   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadSprite("GasSac0", L"GasSac0.aclp", ANIMATION_CLIP_PATH);				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasSac1", L"GasSac1.aclp", ANIMATION_CLIP_PATH);				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasSac2", L"GasSac2.aclp", ANIMATION_CLIP_PATH);				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasSac3", L"GasSac3.aclp", ANIMATION_CLIP_PATH);				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasSac4", L"GasSac4.aclp", ANIMATION_CLIP_PATH);				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasSac5", L"GasSac5.aclp", ANIMATION_CLIP_PATH);				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasSac6", L"GasSac6.aclp", ANIMATION_CLIP_PATH);				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasSac7", L"GasSac7.aclp", ANIMATION_CLIP_PATH);				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GasSac8", L"GasSac8.aclp", ANIMATION_CLIP_PATH);				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadSprite("GasTank", L"GasTank.aclp", ANIMATION_CLIP_PATH);

	//VFX
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack", L"SCVAttack.aclp", ANIMATION_CLIP_PATH);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranBulletAttack", L"TerranBulletAttack.aclp", ANIMATION_CLIP_PATH);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack0", L"FirebatAttackEffect0.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack1", L"FirebatAttackEffect1.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack2", L"FirebatAttackEffect2.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack3", L"FirebatAttackEffect3.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack4", L"FirebatAttackEffect4.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack5", L"FirebatAttackEffect5.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack6", L"FirebatAttackEffect6.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack7", L"FirebatAttackEffect7.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack8", L"FirebatAttackEffect8.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack9", L"FirebatAttackEffect9.aclp", ANIMATION_CLIP_PATH);					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack10", L"FirebatAttackEffect10.aclp", ANIMATION_CLIP_PATH);				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack11", L"FirebatAttackEffect11.aclp", ANIMATION_CLIP_PATH);				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack12", L"FirebatAttackEffect12.aclp", ANIMATION_CLIP_PATH);				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack13", L"FirebatAttackEffect13.aclp", ANIMATION_CLIP_PATH);				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack14", L"FirebatAttackEffect14.aclp", ANIMATION_CLIP_PATH);				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);
	GET_SINGLE(CResourceManager)->LoadSprite("TerranFirebatAttack15", L"FirebatAttackEffect15.aclp", ANIMATION_CLIP_PATH);				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(1);

	GET_SINGLE(CResourceManager)->LoadSprite("CommandCenterNormal", L"CommandCenterNormal.aclp", ANIMATION_CLIP_PATH);				  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("CommandCenterDeath", L"CommandCenterDeath.aclp", ANIMATION_CLIP_PATH);						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("CommandCenterAir", L"CommandCenterAir.aclp", ANIMATION_CLIP_PATH);							 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("CommandCenterBuild", L"CommandCenterBuild.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("CommandCenterLiftUp", L"CommandCenterLiftUp.aclp", ANIMATION_CLIP_PATH);					  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("CommandCenterLiftDown", L"CommandCenterLiftDown.aclp", ANIMATION_CLIP_PATH);			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("CommandCenterWork", L"CommandCenterWork.aclp", ANIMATION_CLIP_PATH);							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

	GET_SINGLE(CResourceManager)->LoadSprite("Supply DepotNormal", L"Supply DepotNormal.aclp", ANIMATION_CLIP_PATH);						  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Supply DepotDeath", L"Supply DepotDeath.aclp", ANIMATION_CLIP_PATH);							   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Supply DepotBuild", L"Supply DepotBuild.aclp", ANIMATION_CLIP_PATH);								  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	
	GET_SINGLE(CResourceManager)->LoadSprite("BarracksNormal", L"BarracksNormal.aclp", ANIMATION_CLIP_PATH);											++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BarracksDeath", L"BarracksDeath.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BarracksWork", L"BarracksWork.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	//GET_SINGLE(CResourceManager)->LoadSprite("BarracksLiftUp", L"BarracksLiftUp.aclp", ANIMATION_CLIP_PATH);										   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	//GET_SINGLE(CResourceManager)->LoadSprite("BarracksLiftDown", L"BarracksLiftDown.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	//GET_SINGLE(CResourceManager)->LoadSprite("BarracksAir", L"BarracksAir.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BarracksBuild", L"BarracksBuild.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);


	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayNormal", L"Engineering BayNormal.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayDeath", L"Engineering BayDeath.aclp", ANIMATION_CLIP_PATH);						 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayWork", L"Engineering BayWork.aclp", ANIMATION_CLIP_PATH);							 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayLiftUp", L"Engineering BayLiftUp.aclp", ANIMATION_CLIP_PATH);						   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayLiftDown", L"Engineering BayLiftDown.aclp", ANIMATION_CLIP_PATH);				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayAir", L"Engineering BayAir.aclp", ANIMATION_CLIP_PATH);								  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayBuild", L"Engineering BayBuild.aclp", ANIMATION_CLIP_PATH);						   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayNormal", L"Engineering BayNormal.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayDeath", L"Engineering BayDeath.aclp", ANIMATION_CLIP_PATH);						 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayWork", L"Engineering BayWork.aclp", ANIMATION_CLIP_PATH);							 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayLiftUp", L"Engineering BayLiftUp.aclp", ANIMATION_CLIP_PATH);						   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayLiftDown", L"Engineering BayLiftDown.aclp", ANIMATION_CLIP_PATH);				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayAir", L"Engineering BayAir.aclp", ANIMATION_CLIP_PATH);								  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Engineering BayBuild", L"Engineering BayBuild.aclp", ANIMATION_CLIP_PATH);						   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Missile TurretNormal", L"Missile TurretNormal.aclp", ANIMATION_CLIP_PATH);							  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Missile TurretDeath", L"Missile TurretDeath.aclp", ANIMATION_CLIP_PATH);								   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Missile TurretBuild", L"Missile TurretBuild.aclp", ANIMATION_CLIP_PATH);									  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("AcademyNormal", L"AcademyNormal.aclp", ANIMATION_CLIP_PATH);										   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("AcademyBuild", L"AcademyBuild.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("AcademyWork", L"AcademyWork.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("AcademyDeath", L"AcademyDeath.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BunkerNormal", L"BunkerNormal.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BunkerBuild", L"BunkerBuild.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BunkerDeath", L"BunkerDeath.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FactoryNormal", L"FactoryNormal.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FactoryBuild", L"FactoryBuild.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FactoryWork", L"FactoryWork.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FactoryDeath", L"FactoryDeath.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FactoryLiftUp", L"FactoryLiftUp.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FactoryAir", L"FactoryAir.aclp", ANIMATION_CLIP_PATH);																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FactoryLiftDown", L"FactoryLiftDown.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("StarportNormal", L"StarportNormal.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("StarportBuild", L"StarportBuild.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("StarportWork", L"StarportWork.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("StarportDeath", L"StarportDeath.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("StarportLiftUp", L"StarportLiftUp.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("StarportAir", L"StarportAir.aclp", ANIMATION_CLIP_PATH);														   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("StarportLiftDown", L"StarportLiftDown.aclp", ANIMATION_CLIP_PATH);									   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science FacilityNormal", L"Science FacilityNormal.aclp", ANIMATION_CLIP_PATH);							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science FacilityBuild", L"Science FacilityBuild.aclp", ANIMATION_CLIP_PATH);								 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science FacilityWork", L"Science FacilityWork.aclp", ANIMATION_CLIP_PATH);							  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science FacilityDeath", L"Science FacilityDeath.aclp", ANIMATION_CLIP_PATH);							  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science FacilityLiftUp", L"Science FacilityLiftUp.aclp", ANIMATION_CLIP_PATH);								++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science FacilityAir", L"Science FacilityAir.aclp", ANIMATION_CLIP_PATH);									   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science FacilityLiftDown", L"Science FacilityLiftDown.aclp", ANIMATION_CLIP_PATH);						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("ArmoryNormal", L"ArmoryNormal.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("ArmoryBuild", L"ArmoryBuild.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("ArmoryWork", L"ArmoryWork.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("ArmoryDeath", L"ArmoryDeath.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral01_100", L"Mineral01_100.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral01_075", L"Mineral01_075.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral01_050", L"Mineral01_050.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral01_025", L"Mineral01_025.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral02_100", L"Mineral02_100.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral02_075", L"Mineral02_075.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral02_050", L"Mineral02_050.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral02_025", L"Mineral02_025.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral03_100", L"Mineral03_100.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral03_075", L"Mineral03_075.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral03_050", L"Mineral03_050.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Mineral03_025", L"Mineral03_025.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VespeneGeyser", L"VespeneGeyser.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GeyserSmoke1", L"GeyserSmoke1.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GeyserSmoke2", L"GeyserSmoke2.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region SCV Animation Clip																																										++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack0", L"SCVAttack0.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack1", L"SCVAttack1.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack2", L"SCVAttack2.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack3", L"SCVAttack3.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack4", L"SCVAttack4.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack5", L"SCVAttack5.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack6", L"SCVAttack6.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack7", L"SCVAttack7.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack8", L"SCVAttack8.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack9", L"SCVAttack9.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack10", L"SCVAttack10.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack11", L"SCVAttack11.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack12", L"SCVAttack12.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack13", L"SCVAttack13.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack14", L"SCVAttack14.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVAttack15", L"SCVAttack15.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand0", L"SCVStand0.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand1", L"SCVStand1.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand2", L"SCVStand2.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand3", L"SCVStand3.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand4", L"SCVStand4.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand5", L"SCVStand5.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand6", L"SCVStand6.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand7", L"SCVStand7.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand8", L"SCVStand8.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand9", L"SCVStand9.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand10", L"SCVStand10.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand11", L"SCVStand11.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand12", L"SCVStand12.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand13", L"SCVStand13.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand14", L"SCVStand14.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVStand15", L"SCVStand15.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove0", L"SCVMove0.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove1", L"SCVMove1.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove2", L"SCVMove2.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove3", L"SCVMove3.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove4", L"SCVMove4.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove5", L"SCVMove5.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove6", L"SCVMove6.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove7", L"SCVMove7.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove8", L"SCVMove8.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove9", L"SCVMove9.aclp", ANIMATION_CLIP_PATH);														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove10", L"SCVMove10.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove11", L"SCVMove11.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove12", L"SCVMove12.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove13", L"SCVMove13.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove14", L"SCVMove14.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVMove15", L"SCVMove15.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("SCVDeath", L"SCVDeath.aclp", ANIMATION_CLIP_PATH);														   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Marine Animation Clip																																							   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack0", L"MarineAttack0.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack1", L"MarineAttack1.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack2", L"MarineAttack2.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack3", L"MarineAttack3.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack4", L"MarineAttack4.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack5", L"MarineAttack5.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack6", L"MarineAttack6.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack7", L"MarineAttack7.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack8", L"MarineAttack8.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack9", L"MarineAttack9.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack10", L"MarineAttack10.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack11", L"MarineAttack11.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack12", L"MarineAttack12.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack13", L"MarineAttack13.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack14", L"MarineAttack14.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineAttack15", L"MarineAttack15.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove0", L"MarineMove0.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove1", L"MarineMove1.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove2", L"MarineMove2.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove3", L"MarineMove3.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove4", L"MarineMove4.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove5", L"MarineMove5.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove6", L"MarineMove6.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove7", L"MarineMove7.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove8", L"MarineMove8.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove9", L"MarineMove9.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove10", L"MarineMove10.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove11", L"MarineMove11.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove12", L"MarineMove12.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove13", L"MarineMove13.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove14", L"MarineMove14.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineMove15", L"MarineMove15.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand0", L"MarineMove0.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand1", L"MarineStand1.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand2", L"MarineStand2.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand3", L"MarineStand3.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand4", L"MarineStand4.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand5", L"MarineStand5.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand6", L"MarineStand6.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand7", L"MarineStand7.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand8", L"MarineStand8.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand9", L"MarineStand9.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand10", L"MarineStand10.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand11", L"MarineStand11.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand12", L"MarineStand12.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand13", L"MarineStand13.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand14", L"MarineStand14.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineStand15", L"MarineStand15.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MarineDeath", L"MarineDeath.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Firebat																																													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand0", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand1", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand2", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand3", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand4", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand5", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand6", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand7", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand8", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand9", L"FirebatStand0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand10", L"FirebatStand10.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand11", L"FirebatStand11.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand12", L"FirebatStand12.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand13", L"FirebatStand13.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand14", L"FirebatStand14.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatStand15", L"FirebatStand15.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack0", L"FirebatAttack0.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack1", L"FirebatAttack1.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack2", L"FirebatAttack2.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack3", L"FirebatAttack3.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack4", L"FirebatAttack4.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack5", L"FirebatAttack5.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack6", L"FirebatAttack6.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack7", L"FirebatAttack7.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack8", L"FirebatAttack8.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack9", L"FirebatAttack9.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack10", L"FirebatAttack10.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack11", L"FirebatAttack11.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack12", L"FirebatAttack12.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack13", L"FirebatAttack13.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack14", L"FirebatAttack14.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatAttack15", L"FirebatAttack15.aclp", ANIMATION_CLIP_PATH);											 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove0", L"FirebatMove0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove1", L"FirebatMove1.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove2", L"FirebatMove2.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove3", L"FirebatMove3.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove4", L"FirebatMove4.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove5", L"FirebatMove5.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove6", L"FirebatMove6.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove7", L"FirebatMove7.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove8", L"FirebatMove8.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove9", L"FirebatMove9.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove10", L"FirebatMove10.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove11", L"FirebatMove11.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove12", L"FirebatMove12.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove13", L"FirebatMove13.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove14", L"FirebatMove14.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatMove15", L"FirebatMove15.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("FirebatDeath", L"FirebatDeath.aclp", ANIMATION_CLIP_PATH);												   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Medic																																													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand0", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand1", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand2", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand3", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand4", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand5", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand6", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand7", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand8", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand9", L"MedicStand0.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand10", L"MedicStand10.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand11", L"MedicStand11.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand12", L"MedicStand12.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand13", L"MedicStand13.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand14", L"MedicStand14.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicStand15", L"MedicStand15.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal0", L"MedicHeal0.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal1", L"MedicHeal1.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal2", L"MedicHeal2.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal3", L"MedicHeal3.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal4", L"MedicHeal4.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal5", L"MedicHeal5.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal6", L"MedicHeal6.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal7", L"MedicHeal7.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal8", L"MedicHeal8.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal9", L"MedicHeal9.aclp", ANIMATION_CLIP_PATH);															++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal10", L"MedicHeal10.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal11", L"MedicHeal11.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal12", L"MedicHeal12.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal13", L"MedicHeal13.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal14", L"MedicHeal14.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicHeal15", L"MedicHeal15.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove0", L"MedicMove0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove1", L"MedicMove1.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove2", L"MedicMove2.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove3", L"MedicMove3.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove4", L"MedicMove4.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove5", L"MedicMove5.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove6", L"MedicMove6.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove7", L"MedicMove7.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove8", L"MedicMove8.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove9", L"MedicMove9.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove10", L"MedicMove10.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove11", L"MedicMove11.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove12", L"MedicMove12.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove13", L"MedicMove13.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove14", L"MedicMove14.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicMove15", L"MedicMove15.aclp", ANIMATION_CLIP_PATH);														++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("MedicDeath", L"MedicDeath.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Ghost																																													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand0", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand1", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand2", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand3", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand4", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand5", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand6", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand7", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand8", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand9", L"GhostStand0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand10", L"GhostStand10.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand11", L"GhostStand11.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand12", L"GhostStand12.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand13", L"GhostStand13.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand14", L"GhostStand14.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostStand15", L"GhostStand15.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack0", L"GhostAttack0.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack1", L"GhostAttack1.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack2", L"GhostAttack2.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack3", L"GhostAttack3.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack4", L"GhostAttack4.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack5", L"GhostAttack5.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack6", L"GhostAttack6.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack7", L"GhostAttack7.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack8", L"GhostAttack8.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack9", L"GhostAttack9.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack10", L"GhostAttack10.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack11", L"GhostAttack11.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack12", L"GhostAttack12.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack13", L"GhostAttack13.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack14", L"GhostAttack14.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostAttack15", L"GhostAttack15.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove0", L"GhostMove0.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove1", L"GhostMove1.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove2", L"GhostMove2.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove3", L"GhostMove3.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove4", L"GhostMove4.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove5", L"GhostMove5.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove6", L"GhostMove6.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove7", L"GhostMove7.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove8", L"GhostMove8.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove9", L"GhostMove9.aclp", ANIMATION_CLIP_PATH);													 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove10", L"GhostMove10.aclp", ANIMATION_CLIP_PATH);												   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove11", L"GhostMove11.aclp", ANIMATION_CLIP_PATH);												   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove12", L"GhostMove12.aclp", ANIMATION_CLIP_PATH);												   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove13", L"GhostMove13.aclp", ANIMATION_CLIP_PATH);												   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove14", L"GhostMove14.aclp", ANIMATION_CLIP_PATH);												   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostMove15", L"GhostMove15.aclp", ANIMATION_CLIP_PATH);												   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("GhostDeath", L"GhostDeath.aclp", ANIMATION_CLIP_PATH);													  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Vulture																																													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand0", L"VultureStand0.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand1", L"VultureStand1.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand2", L"VultureStand2.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand3", L"VultureStand3.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand4", L"VultureStand4.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand5", L"VultureStand5.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand6", L"VultureStand6.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand7", L"VultureStand7.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand8", L"VultureStand8.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand9", L"VultureStand9.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand10", L"VultureStand10.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand11", L"VultureStand11.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand12", L"VultureStand12.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand13", L"VultureStand13.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand14", L"VultureStand14.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureStand15", L"VultureStand15.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove0", L"VultureMove0.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove1", L"VultureMove1.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove2", L"VultureMove2.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove3", L"VultureMove3.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove4", L"VultureMove4.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove5", L"VultureMove5.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove6", L"VultureMove6.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove7", L"VultureMove7.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove8", L"VultureMove8.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove9", L"VultureMove9.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove10", L"VultureMove10.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove11", L"VultureMove11.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove12", L"VultureMove12.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove13", L"VultureMove13.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove14", L"VultureMove14.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureMove15", L"VultureMove15.aclp", ANIMATION_CLIP_PATH);											   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack0", L"VultureAttack0.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack1", L"VultureAttack1.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack2", L"VultureAttack2.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack3", L"VultureAttack3.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack4", L"VultureAttack4.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack5", L"VultureAttack5.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack6", L"VultureAttack6.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack7", L"VultureAttack7.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack8", L"VultureAttack8.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack9", L"VultureAttack9.aclp", ANIMATION_CLIP_PATH);											  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack10", L"VultureAttack10.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack11", L"VultureAttack11.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack12", L"VultureAttack12.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack13", L"VultureAttack13.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack14", L"VultureAttack14.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureAttack15", L"VultureAttack15.aclp", ANIMATION_CLIP_PATH);												++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("VultureDeath", L"VultureDeath.aclp", ANIMATION_CLIP_PATH);												  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Siege Tank																																													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand0", L"Siege TankHeadNormalStand0.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand1", L"Siege TankHeadNormalStand1.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand2", L"Siege TankHeadNormalStand2.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand3", L"Siege TankHeadNormalStand3.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand4", L"Siege TankHeadNormalStand4.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand5", L"Siege TankHeadNormalStand5.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand6", L"Siege TankHeadNormalStand6.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand7", L"Siege TankHeadNormalStand7.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand8", L"Siege TankHeadNormalStand8.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand9", L"Siege TankHeadNormalStand9.aclp", ANIMATION_CLIP_PATH);	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand10", L"Siege TankHeadNormalStand10.aclp", ANIMATION_CLIP_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand11", L"Siege TankHeadNormalStand11.aclp", ANIMATION_CLIP_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand12", L"Siege TankHeadNormalStand12.aclp", ANIMATION_CLIP_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand13", L"Siege TankHeadNormalStand13.aclp", ANIMATION_CLIP_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand14", L"Siege TankHeadNormalStand14.aclp", ANIMATION_CLIP_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadNormalStand15", L"Siege TankHeadNormalStand15.aclp", ANIMATION_CLIP_PATH);		++GET_SINGLE(CCore)->m_iProgress; Sleep(10);

GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand0"	, L"Siege TankHeadTransformedStand0.aclp", ANIMATION_CLIP_PATH);						  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand1"	, L"Siege TankHeadTransformedStand1.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand2"	, L"Siege TankHeadTransformedStand2.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand3"	, L"Siege TankHeadTransformedStand3.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand4"	, L"Siege TankHeadTransformedStand4.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand5"	, L"Siege TankHeadTransformedStand5.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand6"	, L"Siege TankHeadTransformedStand6.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand7"	, L"Siege TankHeadTransformedStand7.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand8"	, L"Siege TankHeadTransformedStand8.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand9"	, L"Siege TankHeadTransformedStand9.aclp", ANIMATION_CLIP_PATH);					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand10", L"Siege TankHeadTransformedStand10.aclp", ANIMATION_CLIP_PATH);					  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand11", L"Siege TankHeadTransformedStand11.aclp", ANIMATION_CLIP_PATH);					  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand12", L"Siege TankHeadTransformedStand12.aclp", ANIMATION_CLIP_PATH);					  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand13", L"Siege TankHeadTransformedStand13.aclp", ANIMATION_CLIP_PATH);					  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand14", L"Siege TankHeadTransformedStand14.aclp", ANIMATION_CLIP_PATH);					  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankHeadTransformedStand15", L"Siege TankHeadTransformedStand15.aclp", ANIMATION_CLIP_PATH);					  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody0"		, L"Siege TankBody0.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody1"		, L"Siege TankBody1.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody2"		, L"Siege TankBody2.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody3"		, L"Siege TankBody3.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody4"		, L"Siege TankBody4.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody5"		, L"Siege TankBody5.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody6"		, L"Siege TankBody6.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody7"		, L"Siege TankBody7.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody8"		, L"Siege TankBody8.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody9"		, L"Siege TankBody9.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody10"	, L"Siege TankBody10.aclp", ANIMATION_CLIP_PATH);																		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody11"	, L"Siege TankBody11.aclp", ANIMATION_CLIP_PATH);																		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody12"	, L"Siege TankBody12.aclp", ANIMATION_CLIP_PATH);																		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody13"	, L"Siege TankBody13.aclp", ANIMATION_CLIP_PATH);																		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody14"	, L"Siege TankBody14.aclp", ANIMATION_CLIP_PATH);																		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankBody15"	, L"Siege TankBody15.aclp", ANIMATION_CLIP_PATH);																		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankTransformBody"	, L"Siege TankTransformBody.aclp", ANIMATION_CLIP_PATH);												 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankTransformedBody", L"Siege TankTransformedBody.aclp", ANIMATION_CLIP_PATH);													++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("Siege TankTransformHead", L"Siege TankTransformHead.aclp", ANIMATION_CLIP_PATH);													   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																							   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Goliath																																																						  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead0"	, L"GoliathHead0.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead1"	, L"GoliathHead1.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead2"	, L"GoliathHead2.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead3"	, L"GoliathHead3.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead4"	, L"GoliathHead4.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead5"	, L"GoliathHead5.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead6"	, L"GoliathHead6.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead7"	, L"GoliathHead7.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead8"	, L"GoliathHead8.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead9"	, L"GoliathHead9.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead10", L"GoliathHead10.aclp", ANIMATION_CLIP_PATH);																					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead11", L"GoliathHead11.aclp", ANIMATION_CLIP_PATH);																					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead12", L"GoliathHead12.aclp", ANIMATION_CLIP_PATH);																					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead13", L"GoliathHead13.aclp", ANIMATION_CLIP_PATH);																					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead14", L"GoliathHead14.aclp", ANIMATION_CLIP_PATH);																					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHead15", L"GoliathHead15.aclp", ANIMATION_CLIP_PATH);																					   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack0"	, L"GoliathHeadAttack0.aclp", ANIMATION_CLIP_PATH);																		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack1", L"GoliathHeadAttack1.aclp", ANIMATION_CLIP_PATH);																	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack2", L"GoliathHeadAttack2.aclp", ANIMATION_CLIP_PATH);																	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack3", L"GoliathHeadAttack3.aclp", ANIMATION_CLIP_PATH);																	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack4", L"GoliathHeadAttack4.aclp", ANIMATION_CLIP_PATH);																	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack5", L"GoliathHeadAttack5.aclp", ANIMATION_CLIP_PATH);																	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack6", L"GoliathHeadAttack6.aclp", ANIMATION_CLIP_PATH);																	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack7", L"GoliathHeadAttack7.aclp", ANIMATION_CLIP_PATH);																	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack8", L"GoliathHeadAttack8.aclp", ANIMATION_CLIP_PATH);																	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack9", L"GoliathHeadAttack9.aclp", ANIMATION_CLIP_PATH);																	   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack10", L"GoliathHeadAttack10.aclp", ANIMATION_CLIP_PATH);																	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack11", L"GoliathHeadAttack11.aclp", ANIMATION_CLIP_PATH);																	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack12", L"GoliathHeadAttack12.aclp", ANIMATION_CLIP_PATH);																	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack13", L"GoliathHeadAttack13.aclp", ANIMATION_CLIP_PATH);																	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack14", L"GoliathHeadAttack14.aclp", ANIMATION_CLIP_PATH);																	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathHeadAttack15", L"GoliathHeadAttack15.aclp", ANIMATION_CLIP_PATH);																	 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody0"	, L"GoliathMoveBody0.aclp", ANIMATION_CLIP_PATH);																		 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody1", L"GoliathMoveBody1.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody2", L"GoliathMoveBody2.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody3", L"GoliathMoveBody3.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody4", L"GoliathMoveBody4.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody5", L"GoliathMoveBody5.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody6", L"GoliathMoveBody6.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody7", L"GoliathMoveBody7.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody8", L"GoliathMoveBody8.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody9", L"GoliathMoveBody9.aclp", ANIMATION_CLIP_PATH);																		  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody10", L"GoliathMoveBody10.aclp", ANIMATION_CLIP_PATH);																			++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody11", L"GoliathMoveBody11.aclp", ANIMATION_CLIP_PATH);																			++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody12", L"GoliathMoveBody12.aclp", ANIMATION_CLIP_PATH);																			++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody13", L"GoliathMoveBody13.aclp", ANIMATION_CLIP_PATH);																			++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody14", L"GoliathMoveBody14.aclp", ANIMATION_CLIP_PATH);																			++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathMoveBody15", L"GoliathMoveBody15.aclp", ANIMATION_CLIP_PATH);																			++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
GET_SINGLE(CResourceManager)->LoadSprite("GoliathDeath", L"GoliathDeath.aclp", ANIMATION_CLIP_PATH);																						  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																							   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Wraith																																																						 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand0"	, L"WraithStand0.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand1"	, L"WraithStand1.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand2"	, L"WraithStand2.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand3"	, L"WraithStand3.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand4"	, L"WraithStand4.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand5"	, L"WraithStand5.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand6"	, L"WraithStand6.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand7"	, L"WraithStand7.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand8"	, L"WraithStand8.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand9"	, L"WraithStand9.aclp", ANIMATION_CLIP_PATH);																						++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand10", L"WraithStand10.aclp", ANIMATION_CLIP_PATH);																				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand11", L"WraithStand11.aclp", ANIMATION_CLIP_PATH);																				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand12", L"WraithStand12.aclp", ANIMATION_CLIP_PATH);																				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand13", L"WraithStand13.aclp", ANIMATION_CLIP_PATH);																				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand14", L"WraithStand14.aclp", ANIMATION_CLIP_PATH);																				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithStand15", L"WraithStand15.aclp", ANIMATION_CLIP_PATH);																				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove0", L"WraithMove0.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove1", L"WraithMove1.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove2", L"WraithMove2.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove3", L"WraithMove3.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove4", L"WraithMove4.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove5", L"WraithMove5.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove6", L"WraithMove6.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove7", L"WraithMove7.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove8", L"WraithMove8.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove9", L"WraithMove9.aclp", ANIMATION_CLIP_PATH);																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove10", L"WraithMove10.aclp", ANIMATION_CLIP_PATH);																				  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove11", L"WraithMove11.aclp", ANIMATION_CLIP_PATH);																				  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove12", L"WraithMove12.aclp", ANIMATION_CLIP_PATH);																				  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove13", L"WraithMove13.aclp", ANIMATION_CLIP_PATH);																				  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove14", L"WraithMove14.aclp", ANIMATION_CLIP_PATH);																				  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove15", L"WraithMove15.aclp", ANIMATION_CLIP_PATH);																				  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack0", L"WraithAttack0.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack1", L"WraithAttack1.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack2", L"WraithAttack2.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack3", L"WraithAttack3.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack4", L"WraithAttack4.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack5", L"WraithAttack5.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack6", L"WraithAttack6.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack7", L"WraithAttack7.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack8", L"WraithAttack8.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack9", L"WraithAttack9.aclp", ANIMATION_CLIP_PATH);																					 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack10", L"WraithAttack10.aclp", ANIMATION_CLIP_PATH);																			   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack11", L"WraithAttack11.aclp", ANIMATION_CLIP_PATH);																			   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack12", L"WraithAttack12.aclp", ANIMATION_CLIP_PATH);																			   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack13", L"WraithAttack13.aclp", ANIMATION_CLIP_PATH);																			   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithAttack14", L"WraithAttack14.aclp", ANIMATION_CLIP_PATH);																			   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithMove15", L"WraithMove15.aclp", ANIMATION_CLIP_PATH);																				  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("WraithDeath", L"WraithDeath.aclp", ANIMATION_CLIP_PATH);																						 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																							   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Science Vessel																																																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand0"	, L"Science VesselStand0.aclp", ANIMATION_CLIP_PATH);																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand1", L"Science VesselStand1.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand2", L"Science VesselStand2.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand3", L"Science VesselStand3.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand4", L"Science VesselStand4.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand5", L"Science VesselStand5.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand6", L"Science VesselStand6.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand7", L"Science VesselStand7.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand8", L"Science VesselStand8.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand9", L"Science VesselStand9.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand10", L"Science VesselStand10.aclp", ANIMATION_CLIP_PATH);																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand11", L"Science VesselStand11.aclp", ANIMATION_CLIP_PATH);																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand12", L"Science VesselStand12.aclp", ANIMATION_CLIP_PATH);																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand13", L"Science VesselStand13.aclp", ANIMATION_CLIP_PATH);																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand14", L"Science VesselStand14.aclp", ANIMATION_CLIP_PATH);																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselStand15", L"Science VesselStand15.aclp", ANIMATION_CLIP_PATH);																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove0"	, L"Science VesselMove0.aclp", ANIMATION_CLIP_PATH);																++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove1", L"Science VesselMove1.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove2", L"Science VesselMove2.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove3", L"Science VesselMove3.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove4", L"Science VesselMove4.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove5", L"Science VesselMove5.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove6", L"Science VesselMove6.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove7", L"Science VesselMove7.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove8", L"Science VesselMove8.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove9", L"Science VesselMove9.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove10", L"Science VesselMove10.aclp", ANIMATION_CLIP_PATH);														   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove11", L"Science VesselMove11.aclp", ANIMATION_CLIP_PATH);														   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove12", L"Science VesselMove12.aclp", ANIMATION_CLIP_PATH);														   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove13", L"Science VesselMove13.aclp", ANIMATION_CLIP_PATH);														   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove14", L"Science VesselMove14.aclp", ANIMATION_CLIP_PATH);														   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselMove15", L"Science VesselMove15.aclp", ANIMATION_CLIP_PATH);														   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("Science VesselDeath", L"Science VesselDeath.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																							   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Dropship																																																							++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand0"	, L"DropshipStand0.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand1"	, L"DropshipStand1.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand2"	, L"DropshipStand2.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand3"	, L"DropshipStand3.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand4"	, L"DropshipStand4.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand5"	, L"DropshipStand5.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand6"	, L"DropshipStand6.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand7"	, L"DropshipStand7.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand8"	, L"DropshipStand8.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand9"	, L"DropshipStand9.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand10", L"DropshipStand10.aclp", ANIMATION_CLIP_PATH);																				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand11", L"DropshipStand11.aclp", ANIMATION_CLIP_PATH);																				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand12", L"DropshipStand12.aclp", ANIMATION_CLIP_PATH);																				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand13", L"DropshipStand13.aclp", ANIMATION_CLIP_PATH);																				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand14", L"DropshipStand14.aclp", ANIMATION_CLIP_PATH);																				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipStand15", L"DropshipStand15.aclp", ANIMATION_CLIP_PATH);																				++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove0"	, L"DropshipMove0.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove1"	, L"DropshipMove1.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove2"	, L"DropshipMove2.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove3"	, L"DropshipMove3.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove4"	, L"DropshipMove4.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove5"	, L"DropshipMove5.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove6"	, L"DropshipMove6.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove7"	, L"DropshipMove7.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove8"	, L"DropshipMove8.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove9"	, L"DropshipMove9.aclp", ANIMATION_CLIP_PATH);																			  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove10"	, L"DropshipMove10.aclp", ANIMATION_CLIP_PATH);																			 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove11"	, L"DropshipMove11.aclp", ANIMATION_CLIP_PATH);																			 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove12"	, L"DropshipMove12.aclp", ANIMATION_CLIP_PATH);																			 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove13"	, L"DropshipMove13.aclp", ANIMATION_CLIP_PATH);																			 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove14"	, L"DropshipMove14.aclp", ANIMATION_CLIP_PATH);																			 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipMove15"	, L"DropshipMove15.aclp", ANIMATION_CLIP_PATH);																			 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("DropshipDeath", L"DropshipDeath.aclp", ANIMATION_CLIP_PATH);																				   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma endregion																																																							   	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
#pragma region Battlecruiser																																																					++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand0"		, L"BattlecruiserStand0.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand1"		, L"BattlecruiserStand1.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand2"		, L"BattlecruiserStand2.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand3"		, L"BattlecruiserStand3.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand4"		, L"BattlecruiserStand4.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand5"		, L"BattlecruiserStand5.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand6"		, L"BattlecruiserStand6.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand7"		, L"BattlecruiserStand7.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand8"		, L"BattlecruiserStand8.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand9"		, L"BattlecruiserStand9.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand10"	, L"BattlecruiserStand10.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand11"	, L"BattlecruiserStand11.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand12"	, L"BattlecruiserStand12.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand13"	, L"BattlecruiserStand13.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand14"	, L"BattlecruiserStand14.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserStand15"	, L"BattlecruiserStand15.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove0"		, L"BattlecruiserMove0.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove1"		, L"BattlecruiserMove1.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove2"		, L"BattlecruiserMove2.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove3"		, L"BattlecruiserMove3.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove4"		, L"BattlecruiserMove4.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove5"		, L"BattlecruiserMove5.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove6"		, L"BattlecruiserMove6.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove7"		, L"BattlecruiserMove7.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove8"		, L"BattlecruiserMove8.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove9"		, L"BattlecruiserMove9.aclp", ANIMATION_CLIP_PATH);																  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove10"	, L"BattlecruiserMove10.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove11"	, L"BattlecruiserMove11.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove12"	, L"BattlecruiserMove12.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove13"	, L"BattlecruiserMove13.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove14"	, L"BattlecruiserMove14.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserMove15"	, L"BattlecruiserMove15.aclp", ANIMATION_CLIP_PATH);															 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack0"	, L"BattlecruiserAttack0.aclp", ANIMATION_CLIP_PATH);															  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack1", L"BattlecruiserAttack1.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack2", L"BattlecruiserAttack2.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack3", L"BattlecruiserAttack3.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack4", L"BattlecruiserAttack4.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack5", L"BattlecruiserAttack5.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack6", L"BattlecruiserAttack6.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack7", L"BattlecruiserAttack7.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack8", L"BattlecruiserAttack8.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack9", L"BattlecruiserAttack9.aclp", ANIMATION_CLIP_PATH);																 	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack10", L"BattlecruiserAttack10.aclp", ANIMATION_CLIP_PATH);																	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack11", L"BattlecruiserAttack11.aclp", ANIMATION_CLIP_PATH);																	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack12", L"BattlecruiserAttack12.aclp", ANIMATION_CLIP_PATH);																	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack13", L"BattlecruiserAttack13.aclp", ANIMATION_CLIP_PATH);																	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack14", L"BattlecruiserAttack14.aclp", ANIMATION_CLIP_PATH);																	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserAttack15", L"BattlecruiserAttack15.aclp", ANIMATION_CLIP_PATH);																	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
																																																														  	++GET_SINGLE(CCore)->m_iProgress; Sleep(10);
	GET_SINGLE(CResourceManager)->LoadSprite("BattlecruiserDeath", L"BattlecruiserDeath.aclp", ANIMATION_CLIP_PATH);

#pragma endregion

	//유닛 파일 읽음
	GET_SINGLE(CFileStream)->LoadUnit("Cursor", "Cursor.unit");
	GET_SINGLE(CFileStream)->LoadUnit("CursorRequestPointer", "CursorRequestPointer.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Mineral01", "Mineral01.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Mineral02", "Mineral02.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Mineral03", "Mineral03.unit");
	GET_SINGLE(CFileStream)->LoadUnit("VespeneGeyser", "VespeneGeyser.unit");
	
	GET_SINGLE(CFileStream)->LoadUnit("MineralOrb", "MineralOrb.unit");
	GET_SINGLE(CFileStream)->LoadUnit("GasBox", "GasBox.unit");
	GET_SINGLE(CFileStream)->LoadUnit("GasSac", "GasSac.unit");
	GET_SINGLE(CFileStream)->LoadUnit("GasTank", "GasTank.unit");
	
	
	GET_SINGLE(CFileStream)->LoadUnit("CommandCenter", "CommandCenter.unit");
	GET_SINGLE(CFileStream)->LoadUnit("SupplyDepot", "SupplyDepot.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Barracks", "Barracks.unit");
	GET_SINGLE(CFileStream)->LoadUnit("MissileTurret", "MissileTurret.unit");
	GET_SINGLE(CFileStream)->LoadUnit("EngineeringBay", "EngineeringBay.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Academy", "Academy.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Bunker", "Bunker.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Factory", "Factory.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Starport", "Starport.unit");
	GET_SINGLE(CFileStream)->LoadUnit("ScienceFacility", "ScienceFacility.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Armory", "Armory.unit");
	GET_SINGLE(CFileStream)->LoadUnit("SCV", "SCV.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Marine", "Marine.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Firebat", "Firebat.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Ghost", "Ghost.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Medic", "Medic.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Vulture", "Vulture.unit");
	GET_SINGLE(CFileStream)->LoadUnit("SiegeTank", "SiegeTank.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Goliath", "Goliath.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Wraith", "Wraith.unit");
	GET_SINGLE(CFileStream)->LoadUnit("ScienceVessel", "ScienceVessel.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Dropship", "Dropship.unit");
	GET_SINGLE(CFileStream)->LoadUnit("Battlecruiser", "Battlecruiser.unit");


	//타일 생성	
	for (int i = 0; i < 128; ++i)
	{
		vector<CTile*> vecTileSet;
		for (int j = 0; j < 128; ++j)
		{
			COLORREF color = GET_SINGLE(CResourceManager)->FindTexture("Terrain_Hunter")->GetPixel(j * 32 + 16, i * 32 + 16);
			COLORREF color2 = GET_SINGLE(CResourceManager)->FindTexture("Terrain_Hunter")->GetPixel(j * 32 + 16, i * 32 + 16);
			//COLORREF color = GET_SINGLE(CResourceManager)->FindTexture("Terrain_Badland_Atlas")->GetPixel(j * 32 + 16, i * 32 + 16);
			//COLORREF color2 = GET_SINGLE(CResourceManager)->FindTexture("Terrain_Badland_Grey_Atlas")->GetPixel(j * 32 + 16, i * 32 + 16);
			if (color == RGB(0, 0, 0))
				continue;


			CTile* pTile = new CTile; // 해제는 ResoueceManager에서 일괄 해제
			pTile->SetBaseTexture(GET_SINGLE(CResourceManager)->FindTexture("Terrain_Hunter"));
			pTile->SetGreyScaleTexture(GET_SINGLE(CResourceManager)->FindTexture("Terrain_Hunter"));
			pTile->SetTileSetID(i);
			pTile->SetTileID(i * 16 + j);
			pTile->SetOffset(j, i);
			GET_SINGLE(CResourceManager)->AddTile(i * 16 + j, pTile);
			pTile->SetTileIndex(vecTileSet.size());
			vecTileSet.push_back(pTile);
		}
		GET_SINGLE(CResourceManager)->AddTileSet(i, vecTileSet);
	}
	



	for (int i = GET_SINGLE(CCore)->m_iProgress; i <= GET_SINGLE(CCore)->m_iMaxProgress; ++i)
	{
		++GET_SINGLE(CCore)->m_iProgress;

		if (GET_SINGLE(CCore)->m_iProgress >= GET_SINGLE(CCore)->m_iMaxProgress )
			break;

		Sleep(10);
	}

	//Sleep(2000);
}

ATOM CCore::MyRegisterClass()
{

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_SC));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"SC";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SC));

	return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
	m_hWnd = CreateWindowW(L"SC", L"SC",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}

	RECT	rc = { 0, 0, m_ScreenSize.x , m_ScreenSize.y };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	
	SetWindowPos(m_hWnd, 0, 0, 0, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	GetClientRect(m_hWnd, &rc);


	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);



	return TRUE;
}

void CCore::Logic()
{
	GET_SINGLE(CTimer)->Update();
	GET_SINGLE(CInput)->Update();
	CTexture* pBackBuffer = GET_SINGLE(CResourceManager)->GetBackBuffer();
	//Rectangle(pBackBuffer->GetDC(), 0, 0, 1280, 720);
	GET_SINGLE(CSceneManager)->PlayCurrentScene();
	BitBlt(m_hDC, 0, 0, m_ScreenSize.x, m_ScreenSize.y, pBackBuffer->GetDC(), 0, 0, SRCCOPY);

	float fps = 1 / GET_SINGLE(CTimer)->GetDeltaTime();
	char	strFPS[32] = {};
	sprintf_s(strFPS, "FPS : %.f\n", fps);
	SetWindowTextA(m_hWnd, strFPS);

	
	// 시간 나면 이거 1회만 되도록 고치기

	if (GET_SINGLE(COption)->GetCursorClipped())
	{
		if (GetFocus() == m_hWnd)
		{
			RECT tCursorClip;
			GetClientRect(GET_SINGLE(CCore)->GetWindowHandle(), &tCursorClip);
			ClientToScreen(GET_SINGLE(CCore)->GetWindowHandle(), (LPPOINT) &(tCursorClip));
			ClientToScreen(GET_SINGLE(CCore)->GetWindowHandle(), (LPPOINT) &(tCursorClip.right));
			ClipCursor(&tCursorClip);
		}
		else
		{
			ClipCursor(NULL);
		}		
	}
	else
	{
		ClipCursor(NULL);
	}
	
}


bool CCore::Init(HINSTANCE hInst)
{
	this->m_hInst = hInst;

	MyRegisterClass();

	// 해상도 설정
	m_ScreenSize.x = 1280;
	m_ScreenSize.y = 720;

	Create();

	// 화면 DC를 만들어준다.
	m_hDC = GetDC(m_hWnd);	
	
	//TODO:  Initialize Managers
	GET_SINGLE(CTimer)->Initialize();
	GET_SINGLE(CFileStream)->Initialize();
	GET_SINGLE(CInput)->Initialize();
	GET_SINGLE(CConsoleButtonManager)->Initialize();
	GET_SINGLE(CInfoPanelManager)->Initialize();
	GET_SINGLE(CFogOfWarManager)->Initialize();
	GET_SINGLE(CMinimapManager)->Initialize();
	
	//아 레이스 컨디션
	if (GET_SINGLE(CResourceManager)->Initialize())
	{
		GET_SINGLE(CSceneManager)->Initialize();
		m_pLoadingThread = new thread(Loading);	
	}
	else
	{
		return false;
	}
	
	GET_SINGLE(COption)->Initialize();	
	GET_SINGLE(CVectorFieldManager)->Initialize();
	return true;
}

int CCore::Run()
{
	MSG msg;

	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Logic();
		}
	}
	return (int)msg.wParam;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	//case WM_GETMINMAXINFO:
	//{
	//	//((MINMAXINFO*)lParam)->ptMaxTrackSize.x = GET_SINGLE(CCore)->GetScreenSize().x + 16;
	//	//((MINMAXINFO*)lParam)->ptMaxTrackSize.y = GET_SINGLE(CCore)->GetScreenSize().y + 39;
	//	//((MINMAXINFO*)lParam)->ptMinTrackSize.x = GET_SINGLE(CCore)->GetScreenSize().x + 16;
	//	//((MINMAXINFO*)lParam)->ptMinTrackSize.y = GET_SINGLE(CCore)->GetScreenSize().y + 39;
	//
	//}
	//break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_F4:
		{
			m_bLoop = false;
		}
		default:
			break;
		}
	}break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
