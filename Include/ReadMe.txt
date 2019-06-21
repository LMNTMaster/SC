========================================================================
    WIN32 응용 프로그램 : SC 프로젝트 개요
========================================================================

2018.02.06
- 팀 컬러 적용
- 유닛 충돌체에 RectCollider 사용하지 않음. 전부 CircleCollider로 사용하고, UI와 Cursor와 충돌만 Rect - Point 로 충돌처리하도록 함.
- '1' 로 유닛 생산 가능. (복사생성 아님. 복사생성은 오브젝트를 파일로 입출력 가능하게 하고 나서 할 예정)
- 화면 끝 근처로 커서 이동 시 카메라 이동. 8방향. 스프라이트는 추후 적용하도록 함. (AnimationClip을 파일로 입출력 가능하게 하고 난 후 함)



2018.02.08
- 충돌 개선
- 충돌 개선에 따른 유닛 선택의 기능 변경
- 옵션 추가
- 커서 가두기


2018.02.09
- FileStream : GameObject, Texture, AnimationClip, Map 읽기 / 쓰기
- Texture : 가장 먼저 읽어야 함.
- AnimationClip : Atlas Texture를 읽고, ClipData를 적용 함. Texture가 
- GameObject : 오브젝트 명, 컴포넌트 갯수, 컴포넌트 추가 및 Value 적용
- Map : 실질적으로 Scene클래스와 동등한 파일이다. 파일을 읽어서 맵 설정, 시작 위치 설정 등을 한다.

- 순서는 다음과 같다.
1. 프로그램 시작 
2. Sound - Texture - AnimationClip - GameObject 로딩 -> unordered_map에 보관
3. 게임 진입 - 종족 설정
4. Map 로딩 - 팀컬러 파일 생성 및, 각 종족 별 팀컬러 적용된 텍스쳐 적용.
5. 유닛 생성 시, unordered_map에서 복사생성해서 사용

- FileStream 완료


2018.02.10 까지
유닛 복사생성 관련
- 유닛 별 파일로 입,출력 하도록 함. (AnimationClip포함)
- 프로그램 로딩 시간에 모든 유닛 파일을 읽은 후, ResourceManater -> unordered_map<string, CGameObject*>에 보관.
- 게임 로딩(Scene Loading) 중에 플레이어와 종족별로 Team Color 적용 된 텍스쳐 만든 후, 캐시폴더에 저장. 캐시 폴더에 해당 텍스쳐가 있으면 만들지 않고 끌어다 쓴다.
- 해시 맵에서 유닛의 포인터 받아 복사생성함.
- 복사한 유닛에 Team Color 적용 되어진 텍스쳐로 SpriteRenderer의 Atlas 변경함.


2018.02.13 까지
지형 관련
- 이동 가능한 지형		
- 건설 가능한 지형		
- 크립							
- 크립의 경우 해당 타일 위에 올라갈 텍스쳐를 선택 할 수 있어야 한다.
- TerrainRenderer에서 모든 타일을 일괄적으로 BitBlt으로 처리하도록 변경 -> *.map 파일을 읽어서 불러올 수 있도록 함.  

마스킹
- 마스킹은 두 개 혹은 3개의 텍스쳐를 병합할 수 있도록 한다.
- 2개 병합일 경우 알파 마스크와 텍스쳐를 받고, 알파 마스크의 픽셀과 
- FileStream에서 MergeTexture를 이용해 합치도록 한다.

전장의 안개
- 유닛의 시야에 따라 볼 수 있는 곳과 볼 수 없는 곳 구분.
- 한 번 지나간 곳은 회색으로 처리한다.
- 한 번도 지나가지 않은 곳은 검정색으로 처리한다.
- 밝혀진 맵과 미니맵의 타일위에 마스크를 씌우는 방식으로 한다. (마스크 타일을 알파블렌딩으로 적용 하도록 한다)

미니맵
- 클릭 중 커서위치의 상대위치로 카메라가 이동한다.
- 우클릭 시 선택되어져 있는 유닛이 있을 경우, 이동 명령을 주도록 한다.
- 이전에 밝혀진 곳은 회색 음영, 현재 밝혀지고 있는 곳은 투명, 밝혀지지 않은 곳은 검정색으로 마스킹 - 맵데이터와 연동 (끌어오는 식..?)

유닛 행동
-이동 : 유닛을 해당 위치로 이동시킨다. 유닛은 항상 정면으로만 이동한다. 
-정지 : 유닛의 현재 진행중인 모든 행동을 정지시킨다.
-순찰 : 현재 유닛의 위치와 선택된 위치를 왕복하도록 한다.
-공격 : 대상이 유닛일 경우 현재 유닛의 사정 거리 내에 존재하면 공격, 사정거리 밖이면 이동 후 공격하고, 대상이 지형이면 해당 위치로 이동하면서 이동 중 적 유닛을 발견하면 공격하도록 한다. 
-위치 고정 : 유닛이 이동중일 때, 현재위치에서 멈추고, 사정거리 내에 적 유닛이 들어오면 공격하도록 한다. 쫒아가지 않는다.
-수리 : 해당 유닛을 수리한다.
-건설A - A' : A를 선택 시 버튼UI 세트 변경 A' 선택 시 해당 유닛 건설
-건설B - B' : B를 선택 시 버튼UI 세트 변경 B' 선택 시 해당 유닛 건설
-스킬 : 해당 스킬에 따라 사용함.
-...

유닛 상태
- SightRange / RequireResources 
- Shield / HP / MP / Gen
- SpawnRequireTime
- Wireframe
- Portrait
- Move(Speed, CollisionRadius)
- Attack(Name, AttackType,Damage, AttackSpeed , Upgrade, Range)
- Deffence(Name, DamageReduction, DeffendType, Upgrade)
- Shield(Name, DamageReduction, DeffendType, Upgrade)


건물 상태
- SightRange, RequireResources , Suppliment
- Name
- BuildRequireCondition (선행 요구조건)
- BuildBlockRange (width, height) 타일기준
- BuildRequireTime (요구시간)
- BuildElapseTime (현재 경과 시간)
- Shield / HP / MP / Gen
- Spawnable Unit List
- SpawnProgress
- SpawnQueue
- Wireframe
- Portrait
- Move(테란 건물 일부..)
- Attack(Name, AttackType,Damage, AttackSpeed , Upgrade, Range) (타워 형 건물들)
- Deffence(Name, DamageReduction, DeffendType, Upgrade)
- Shield(Name, DamageReduction, DeffendType, Upgrade)

플레이어 상태
- TeamColor
- GameResoueces
- SelectedUnit
- Game Condition
- APM

/////////////////////////////////////////////////////////////////////////////




맵툴 

- Tile크기에 맞게 초기 설정을 해준다.
- 배경 타일을 랜덤하게 깔아준다.
- 사용 할 타일셋은 따로 창을 띄운다.
- 타일 셋에서 선택한 타일로 바닥을 깔아준다.
- 해당 타일의 이동, 이동불가 옵션도 설정 해준다.
- 맵 파일로 저장한다.





Sprite 저장시 사용 방법
-	예시
	CSprite* pSprite = new CSprite;	
	pSprite->AddFrame(CVector2(5,6));
	pSprite->AddFrame(CVector2(6,6));
	pSprite->AddFrame(CVector2(7,6));

	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("TextureKey"));
	pSprite->SetCellSize(160, 140);
	pSprite->SetAtlasGridSize(10, 10);
	pSprite->SetSampleRate(5);
	pSprite->SetLoop(true);
	pSprite->SaveSprite("Dir.aclp");

Tile Render 방법
- 임시로 사용 할 CTile 생성
- 임시로 만든 CTile에 Base Atlas 에서의 타일 크기, 타일셋ID, 타일ID 설정
- 같은 종류의 타일은 vector로 묶음. 1개라도 vector로 묶음
- ResoueceManager에 AddTileSet으로 unordered_map<int, vec<Tile*>>에 저장
- ResoueceManager에 AddTile로 unordered_map<int, Tile*>로 1개 타일 저장 int는 id가 된다.

- 여기까지가 로딩중 할 일
- TerrainRenderer를 TerrainLayer에 빈 오브젝트 생성 후, AddComponent함.
- TerrainRenderer Component에 Tile을 저장하도록 한다. 저장 할 때에 Camera와 WorldPosition은 자동으로 설정된다. (Horizontal Major)
- TerrainRenderer에 읽어온 맵  파일 보관하도록 함. 읽을 때에는 1개 타일을 기준으로만 읽도록 한다.



Tool 
- 1,2,3,4,5,6 WHEEL_UP, WHEEL_DOWN, LBUTTON_DOWN 의 키로 조작 함.
- 1: 맵의 타일셋을 WHEEL_UP, WHEEL_DOWN 으로 조절함. 타일은 특정 조건 내에 랜덤한 타일을 선택 하도록 한다. 타일셋은 같은 조건의 타일들을 묶어 놓은 벡터이다.
- 2: 이동가능 여부를 LBUTTON_DOWN, RBUTTON_DOWN으로 설정 함.
- 3: 타일의 높이를 WHEEL_UP, WHEEL_DOWN으로  설정함.
- 4: 자원을 배치할 수 있도록 함.
- 5: Doodad을 WHEEL_UP, WHEEL_DOWN으로 선택하여 배치할 수 있도록 함.
- 6: Starting Point를 배치할 수 있도록 함.
- Ctrl + S : 맵 저장
- Ctrl + O : 맵 불러오기

※ Doodad은 타일과 동일하게 처리하도록 하고, Resources는 건물과 동일하게 처리함.
따라서 맵 파일에 Unit을 설치할 수 있도록 해야 하는데, Unit은 3종류로 구분한다.
1. 건물
2. 지상 유닛
3. 공중 유닛

건물의 위치는 Tile에 의존적이다. 따라서, Tile에 의해 위치가 선정되어야 한다.
지상유닛은 이동 가능한 Tile에 의존적이다. 배치 시, Tile에 의해 이동 가능한 지역인지의 여부를 파악해야 한다.
공중 유닛은 어떠한 타일에도 의존적이지 않다. 배치는 자유로우나, 맵의 크기를 벗어나서는 안된다.


Tile
-TileSet 0 : NULL
-TileSet 1 [0 ~ 12] : Creep
-TileSet 2 ~ 3 [0 ~ 8 , 10 ~ 14] : Soil
-TileSet 4 ~ 5 [0 ~ 8 , 10 ~ 14] : Dirt
-TileSet 6 ~ 7 [0 ~ 5] : Water
-TileSet 8 ~ 11 [0 ~ 6 , 8 ~ 10] : Grass
-TileSet 12 ~ 13 [0 ~ 11] : Stone


-TileSet 188 ~ 203 [0 ~ 4] : Back : Soil, Fore : Grass
-TileSet 204 ~ 211 [0 ~ 2] : Back : Soil, Fore : Grass
-TileSet 212 ~ 235 [0 ~ 4] : Back : Soil, Fore : Grass
-TileSet 212 ~ 235 [0 ~ 4] : Back : Soil, Fore : Grass
-TileSet 236 ~ 251 [0 ~ 4] : Back : Dirt, Fore : Grass
-TileSet 252 ~ 259 [0 ~ 2] : Back : Dirt, Fore : Grass
-TileSet 260 ~ 283 [0 ~ 4] : Back : Dirt, Fore : Grass


전장의 안개
- 유닛의 최내곽부터 1타일 씩 밖으로 돌면서 비출 수 있는지, 없는 지 확인 후, 비출 수 있으면 해당 타일의 FOW(구조체).bVisit = true, FOW.bVisible = true로 함.
- 타일 기반으로 설정 하도록 하며, 외곽의 블렌딩 처리는 크립과 동일하도록 한다.
- bVisit == false && bVisible == false  : Black
- bVisit == true && bVisible == false  : Black + Alpha 200
- bVisit == false && bVisible == true : 불가능. bVisit = true로 변경해준다.
- bVisit == true && bVisible == true : Alpha == 0 


18.2.19
맵 세이브, 로드, Unit배치, Doodad배치 (미니맵 포함), 맵 제작

18.2.20
fmod 추가 및 리소스 로드 편하게 구현, 이동 구현

18.2.21
인게임 - 건설, 생산, 공격, 정지, 고정, 채취, 수리, 패트롤 구현 및 이펙트 밑작업 
버튼, 툴팁

18.2.22 ~ 23
미니맵, 하단UI패널

18.2.24
인게임 - 크립 구현, 전장의 안개 구현 

18.2.25 ~ 27
인게임 - 모든 종족 구현

18.2.28 ~ 3.1
인게임 - 모든 유닛 스킬 구현

3.1
옵션 UI 구현

3.2 ~ 3.3 
AI  



//기술 소개서 용 내용
- Move 컴포넌트 내에 LateUpdate() 에서 방향 벡터 표기할지 안할지 여부



애니메이션 클립 명명 규칙 

1. UnitName + ClipName + Num
ex)
Marine Attack 10
Probe Move 5
Cursor Normal 4
Cursor Select 0
Cursor Over 3
etc...