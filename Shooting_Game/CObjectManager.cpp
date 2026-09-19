#include "CObjectManager.h"
#include "CGameManager.h"
#include "CResourceManager.h"
#include "CBulletManager.h"
#include "CUi.h"
#include "CBackground.h"
#include "CButton.h"
#include "CShield.h"
#include "CBoss.h"
#include "CHeart.h"
#include "Enum.h"

CObjectManager* CObjectManager::m_sInstance = nullptr;

CObjectManager::CObjectManager()
{
	m_Player = nullptr;
}

CObjectManager::~CObjectManager()
{
}

void CObjectManager::CreateLeo()
{
	CLeo* Leo = new CLeo; // 레오 생성
	Leo->SetObjectType((int)OBJECT_TYPE::LEO); // 오브젝트 타입 넣기
	Leo->SetResourceType((int)RESOURCE_TYPE::LEO); // 리소스 타입 넣기
	// 플레이어 오브젝트에 레오 넣기
	SetPlayerObject(Leo);
}

void CObjectManager::CreateBoss()
{
	CBoss* Boss = new CBoss; // 보스 생성
	Boss->SetObjectType((int)OBJECT_TYPE::BOSS); // 오브젝트 타입 
	// 표면 정보 넣기
	Boss->SetAnimationSurfaceInfo(0, CResourceManager::GetInstance()->GetBossIdle0Info());
	Boss->SetAnimationSurfaceInfo(1, CResourceManager::GetInstance()->GetBossIdle1Info());
	Boss->SetAnimationSurfaceInfo(2, CResourceManager::GetInstance()->GetBossIdle2Info());
	Boss->SetAnimationSurfaceInfo(3, CResourceManager::GetInstance()->GetBossIdle3Info());
	// 크기 설정
	Boss->SetAnimationSurfaceSize(0, 4.0f, 4.0f);
	Boss->SetAnimationSurfaceSize(1, 4.0f, 4.0f);
	Boss->SetAnimationSurfaceSize(2, 4.0f, 4.0f);
	Boss->SetAnimationSurfaceSize(3, 4.0f, 4.0f);
	// 벡터에 넣기
	m_vecBoss.push_back(Boss);
}

void CObjectManager::CreateBackground(int type)
{
	CBackground* BackGround = new CBackground; // 배경 생성
	CObject* TitleText; // 타이틀 텍스트 생성
	switch (type)
	{
	case (int)OBJECT_TYPE::SPACE: // 우주 배경 생성
		BackGround->SetObjectType((int)OBJECT_TYPE::SPACE); // 오브젝트 타입 넣기
		BackGround->SetResourceType((int)RESOURCE_TYPE::SPACE); // 리소스 타입 넣기
		// 벡터에 넣기
		m_vecBackGround.push_back(BackGround);
		break;
	case (int)OBJECT_TYPE::TITLE_BACKGROUND: // 타이틀 배경 생성
	{

		BackGround->SetObjectType((int)OBJECT_TYPE::TITLE_BACKGROUND); // 오브젝트 타입 넣기 
		BackGround->SetResourceType((int)RESOURCE_TYPE::TITLE_BACKGROUND); // 리소스 타입 넣기
		BackGround->SetSurfaceInfo(CResourceManager::GetInstance()->GetTitleInfo()); // 표면 정보 넣기
		// 타이틀 텍스트 생성
		TitleText = new CObject;
		TitleText->SetObjectType((int)OBJECT_TYPE::TITLE_TEXT); // 오브젝트 타입 넣기
		TitleText->SetResourceType((int)RESOURCE_TYPE::TITLE_TEXT); // 리소스 타입 넣기
		TitleText->SetSurfaceInfo(CResourceManager::GetInstance()->GetTitleTextInfo()); // 표면 정보 넣기
		// 위치 설정
		TitleText->SetX(390);
		TitleText->SetY(100);
		// 크기 설정
		SURFACEINFO tempSFInfo = TitleText->GetSurfaceInfo();
		tempSFInfo.fSizeX = 0.3;
		tempSFInfo.fSizeY = 0.3;
		TitleText->SetSurfaceInfo(tempSFInfo);

		// 벡터에 넣기
		m_vecBackGround.push_back(BackGround);
		// 오브젝트 넣기
		m_TitleText = TitleText;
		break;
	}
	default:
		// 예외
		MessageBoxA(NULL, "CreateBackground함수 switch문 default", "CObjectManager", MB_OKCANCEL | MB_ICONERROR);
		delete BackGround;
		BackGround = nullptr;
		break;
	}
}

void CObjectManager::CreateHeartUI()
{
	// 생성
	CHeart* Heart = new CHeart;
	// 오브젝트 타입
	Heart->SetObjectType((int)OBJECT_TYPE::HEART_UI); // 오브젝트 타입 넣기
	Heart->SetSurfaceInfo(CResourceManager::GetInstance()->GetHeartInfo(0)); // 표면 정보 넣기
	// 위치 설정
	Heart->SetX(INGAMESCREEN_X + 100);
	Heart->SetY(100);
	// 크기 설정
	SURFACEINFO tempSFinfo = Heart->GetSurfaceInfo();
	tempSFinfo.fSizeX = 5.0f;
	tempSFinfo.fSizeY = 5.0f;
	Heart->SetSurfaceInfo(tempSFinfo);
	// 오브젝트 넣기
	m_HeartUI = Heart;
}

void CObjectManager::CreateSkillIconUI()
{
	CUi* SkillIcon = new CUi;
	SkillIcon->SetObjectType((int)OBJECT_TYPE::SKILLICON_UI); // 객체 타입 설정
	SkillIcon->SetSurfaceInfo(CResourceManager::GetInstance()->GetShieldSkillIcon()); // 표면 정보 설정
	// 위치 설정
	SkillIcon->SetX(INGAMESCREEN_X + 100);
	SkillIcon->SetY(200);
	// 크기 설정
	SURFACEINFO tempSFinfo = SkillIcon->GetSurfaceInfo();
	tempSFinfo.fSizeX = 0.3f;
	tempSFinfo.fSizeY = 0.3f;
	SkillIcon->SetSurfaceInfo(tempSFinfo);
	// 등록
	m_SkillIconUI = SkillIcon;
}

void CObjectManager::CreateTableUI()
{
	CUi* Table = new CUi; // 테이블 생성
	Table->SetObjectType((int)OBJECT_TYPE::TABLE); // 오브젝트 타입 넣기
	Table->SetSurfaceInfo(CResourceManager::GetInstance()->GetTable()); // 표면 정보 넣기
	// 위치 설정
	Table->SetX(INGAMESCREEN_X);
	Table->SetY(0);
	// 크기 설정
	SURFACEINFO tempSFinfo = Table->GetSurfaceInfo();
	tempSFinfo.fSizeX = 1.5f;
	tempSFinfo.fSizeY = 1.7f;
	Table->SetSurfaceInfo(tempSFinfo);
	// 오브젝트 넣기
	m_Table = Table;
}

void CObjectManager::CreateGameOverTableUI()
{
	// 게임 오버 UI생성
	CUi* Table = new CUi;
	CObject* Text = new CObject;
	CButton* RetryButton = new CButton;
	CButton* CloseButton = new CButton;
	// 오브젝트 타입 넣기
	Table->SetObjectType((int)OBJECT_TYPE::GAMEOVER_TABLE);
	Text->SetObjectType((int)OBJECT_TYPE::GAMEOVER_TEXT);
	RetryButton->SetObjectType((int)OBJECT_TYPE::RETRY);
	CloseButton->SetObjectType((int)OBJECT_TYPE::CLOSE);
	// 표면 정보 넣기
	Table->SetSurfaceInfo(CResourceManager::GetInstance()->GetGameOverTable());
	Text->SetSurfaceInfo(CResourceManager::GetInstance()->GetGameOverTextInfo());
	RetryButton->SetSurfaceInfo(CResourceManager::GetInstance()->GetRestartButtonInfo());
	RetryButton->SetHoverSuface(CResourceManager::GetInstance()->GetRestartButtonHoverInfo());
	CloseButton->SetSurfaceInfo(CResourceManager::GetInstance()->GetCloseButtonInfo());
	CloseButton->SetHoverSuface(CResourceManager::GetInstance()->GetCloseButtonHoverInfo());
	// 위치 설정
	Table->SetX(200);
	Table->SetY(100);
	Text->SetX(250);
	Text->SetY(250);
	RetryButton->SetX(270);
	RetryButton->SetY(600);
	CloseButton->SetX(480);
	CloseButton->SetY(600);
	// 크기 설정
	SURFACEINFO tempSFinfo = Table->GetSurfaceInfo();
	tempSFinfo.fSizeX = 0.5f;
	tempSFinfo.fSizeY = 0.5f;
	Table->SetSurfaceInfo(tempSFinfo);
	tempSFinfo = Text->GetSurfaceInfo();
	tempSFinfo.fSizeX = 0.2f;
	tempSFinfo.fSizeY = 0.2f;
	Text->SetSurfaceInfo(tempSFinfo);
	tempSFinfo = RetryButton->GetSurfaceInfo();
	tempSFinfo.fSizeX = 0.5f;
	tempSFinfo.fSizeY = 0.5f;
	RetryButton->SetSurfaceInfo(tempSFinfo);
	tempSFinfo = RetryButton->GetHoverSurface();
	tempSFinfo.fSizeX = 0.5f;
	tempSFinfo.fSizeY = 0.5f;
	RetryButton->SetHoverSuface(tempSFinfo);
	tempSFinfo = CloseButton->GetSurfaceInfo();
	tempSFinfo.fSizeX = 0.5f;
	tempSFinfo.fSizeY = 0.5f;
	CloseButton->SetSurfaceInfo(tempSFinfo);
	tempSFinfo = CloseButton->GetHoverSurface();
	tempSFinfo.fSizeX = 0.5f;
	tempSFinfo.fSizeY = 0.5f;
	CloseButton->SetHoverSuface(tempSFinfo);
	// 오브젝트 넣기
	m_GameOverTable = Table;
	m_GameOverText = Text;
	m_Button.push_back(RetryButton);
	m_Button.push_back(CloseButton);
}

void CObjectManager::CreateKeyboard()
{
	CUi* Keyboard = new CUi; // 키보드 UI 생성

	Keyboard->SetObjectType((int)OBJECT_TYPE::KEYBOARD); // 오브젝트 타입 넣기
	Keyboard->SetSurfaceInfo(CResourceManager::GetInstance()->GetKeyboardInfo()); // 표면 정보 넣기
	// 위치 설정
	Keyboard->SetX(INGAMESCREEN_X + 80);
	Keyboard->SetY(400);
	// 크기 설정
	SURFACEINFO tempSFinfo = Keyboard->GetSurfaceInfo();
	tempSFinfo.fSizeX = 0.2f;
	tempSFinfo.fSizeY = 0.2f;
	Keyboard->SetSurfaceInfo(tempSFinfo);
	// 오브젝트 넣기
	m_Keyboard = Keyboard;
}

void CObjectManager::CreateTitleObjects()
{
	// 타이틀 화면 오브젝트 생성
	CreateBackground((int)OBJECT_TYPE::TITLE_BACKGROUND); // 배경
	CreateTitleUI(); // UI
	CGameManager::GetInstance()->InitTitleButtonPosition(); // 위치 초기화
	SetButtonResource(); // 버튼 표면 정보 넣기
}

void CObjectManager::CreateInGameObjects()
{
	// 인게임 오브젝트 생성
	CreateLeo(); // 플레이어
	CreateBoss(); // 보스
	CreateTableUI(); // 테이블
	CreateHeartUI(); // 체력
	CreateSkillIconUI(); // 스킬 아이콘
	CreateBackground((int)OBJECT_TYPE::SPACE); // 배경
	CreateKeyboard(); // 키보드 UI
	SetBackgroundResource(); // 배경 표면 정보
	SetPlayerResource(); // 플레이어 표면 정보
}

void CObjectManager::RemovePlayerObject(int type)
{
	// 플레이어 제거
	m_Player = nullptr;
}

void CObjectManager::RemoveBossObject(int type)
{
	// 배열의 특정 오브젝트를 찾아 제거함
	int max = m_vecBoss.size();
	for (int i = 0; i < max; i++)
	{
		if (m_vecBoss[i]->GetObjectType() == type)
		{
			m_vecBoss.erase(m_vecBoss.begin() + i);
			return;
		}
	}
}

void CObjectManager::RemoveButtons()
{
	// 버튼 제거
	int max = m_Button.size();
	for (int i = 0; i < m_Button.size(); i++)
	{
		delete m_Button[i];
		m_Button[i] = nullptr;
	}
	m_Button.clear();
}

void CObjectManager::RemoveBackGroundObject(int type)
{
	// 배열의 특정 오브젝트를 찾아 제거함
	int max = m_vecBackGround.size();
	for (int i = m_vecBackGround.size() - 1; i >= 0; i--)
	{
		if (m_vecBackGround[i]->GetObjectType() == type)
		{
			CObject* tempObject = m_vecBackGround[i];
			m_vecBackGround.erase(m_vecBackGround.begin() + i);

			delete tempObject;
			return;
		}
	}
}

void CObjectManager::RemoveInGameObjects()
{
	//// 모든 인게임 오브젝트 제거
	// 플레이어 제거
	if (m_Player != nullptr)
	{
		delete m_Player;
		m_Player = nullptr;
	}
	// 보스 제거
	int max = m_vecBoss.size();
	for (int i = 0; i < max; i++)
	{
		delete m_vecBoss[i];
		m_vecBoss[i] = nullptr;
	}
	m_vecBoss.clear();
	// 배경 제거
	max = m_vecBackGround.size();
	for (int i = 0; i < max; i++)
	{
		delete m_vecBackGround[i];
		m_vecBackGround[i] = nullptr;
	}
	m_vecBackGround.clear();
	// UI 제거
	if (m_HeartUI != nullptr)
	{
		delete m_HeartUI;
		m_HeartUI = nullptr;
	}
	// 스킬 아이콘 제거
	if (m_SkillIconUI != nullptr)
	{
		delete m_SkillIconUI;
		m_SkillIconUI = nullptr;
	}
	// 테이블 제거
	if (m_Table != nullptr)
	{
		delete m_Table;
		m_Table = nullptr;
	}
	// 키보드 UI 제거
	if (m_Keyboard != nullptr)
	{
		delete m_Keyboard;
		m_Keyboard = nullptr;
	}
}

CObject* CObjectManager::GetBackground(int type)
{
	// type에 맞는 배경을 반환
	int size = m_vecBackGround.size();
	for (int i = 0; i < size; i++)
	{
		if (m_vecBackGround[i]->GetObjectType() == type)
		{
			return m_vecBackGround[i];
		}
	}
}

CObject* CObjectManager::GetButton(int type)
{
	// type에 맞는 버튼을 반환
	int size = m_Button.size();
	for (int i = 0; i < size; i++)
	{
		if (dynamic_cast<CButton*>(m_Button[i])->GetObjectType() == type)
		{
			return m_Button[i];
		}
	}
	// 이건 반환되면 안됨
	return 0;
}

CObject* CObjectManager::GetBoss(int type)
{
	// type에 맞는 보스를 반환
	int size = m_vecBoss.size();
	for (int i = 0; i < size; i++)
	{
		if (dynamic_cast<CBoss*>(m_vecBoss[i])->GetObjectType() == type)
		{
			return m_vecBoss[i];
		}
	}
	// 이건 반환되면 안됨
	return 0;
}

void CObjectManager::CreateTitleUI()
{
	// 버튼 생성
	CButton* ExitButton = new CButton;
	CButton* PlayButton = new CButton;
	// 타입 초기화
	ExitButton->SetObjectType((int)OBJECT_TYPE::EXIT);
	PlayButton->SetObjectType((int)OBJECT_TYPE::PLAY);
	ExitButton->SetResourceType((int)RESOURCE_TYPE::EXIT);
	PlayButton->SetResourceType((int)RESOURCE_TYPE::PLAY);
	// 벡터에 넣기
	m_Button.push_back(ExitButton);
	m_Button.push_back(PlayButton);
}

void CObjectManager::DestroyAllObjects()
{
	// 존재하는 모든 오브젝트 제거 (WM_DESTROY)
	// 플레이어 제거
	if (m_Player != nullptr)
	{
		delete m_Player;
		m_Player = nullptr;
	}
	// 보스 제거
	int max = m_vecBoss.size();
	for (int i = 0; i < max; i++)
	{
		delete m_vecBoss[i];
		m_vecBoss[i] = nullptr;
	}
	m_vecBoss.clear();
	// 배경 제거
	max = m_vecBackGround.size();
	for (int i = 0; i < max; i++)
	{
		delete m_vecBackGround[i];
		m_vecBackGround[i] = nullptr;
	}
	m_vecBackGround.clear();
	// 버튼 제거
	max = m_Button.size();
	for (int i = 0; i < max; i++)
	{
		delete m_Button[i];
		m_Button[i] = nullptr;
	}
	m_Button.clear();
	// 타이틀 텍스트 제거
	if (m_TitleText != nullptr)
	{
		delete m_TitleText;
		m_TitleText = nullptr;
	}
	// 체력 UI 제거
	if (m_HeartUI != nullptr)
	{
		delete m_HeartUI;
		m_HeartUI = nullptr;
	}
	// 스킬 아이콘 제거
	if (m_SkillIconUI != nullptr)
	{
		delete m_SkillIconUI;
		m_SkillIconUI = nullptr;
	}
	// 테이블 제거
	if (m_Table != nullptr)
	{
		delete m_Table;
		m_Table = nullptr;
	}
	// 게임오버 테이블 제거
	if (m_GameOverTable != nullptr)
	{
		delete m_GameOverTable;
		m_GameOverTable = nullptr;
	}
	// 게임오버 텍스트 제거
	if (m_GameOverText != nullptr)
	{
		delete m_GameOverText;
		m_GameOverText = nullptr;
	}
	// 키보드 UI 제거
	if (m_Keyboard != nullptr)
	{
		delete m_Keyboard;
		m_Keyboard = nullptr;
	}
	// 모든 탄막 제거
	CBulletManager::GetInstance()->DestroyAllBullet();
}

void CObjectManager::SetPlayerResource()
{
	// 플레이어의 표면 정보를 넣는 함수
	SURFACEINFO tempSurface, tempLeftSurface, tempRightSurface;
	if (m_Player != nullptr)
	{
		CPlayer* Player = dynamic_cast<CPlayer*>(m_Player);
		// 플레이어의 종류에 따라 알맞은 표면 정보를 넣음(현재는 LEO만 구현)
		switch (Player->GetObjectType())
		{
		case (int)OBJECT_TYPE::LEO:
			tempSurface = CResourceManager::GetInstance()->GetLeoInfo();
			tempLeftSurface = CResourceManager::GetInstance()->GetLeoLeftInfo();
			tempRightSurface = CResourceManager::GetInstance()->GetLeoRightInfo();
			break;
		case (int)OBJECT_TYPE::DANTE:
			tempSurface = CResourceManager::GetInstance()->GetDanteInfo();
			tempLeftSurface = CResourceManager::GetInstance()->GetDanteLeftInfo();
			tempRightSurface = CResourceManager::GetInstance()->GetDanteRightInfo();
			break;
		case (int)OBJECT_TYPE::EVE:
			tempSurface = CResourceManager::GetInstance()->GetEveInfo();
			tempLeftSurface = CResourceManager::GetInstance()->GetEveLeftInfo();
			tempRightSurface = CResourceManager::GetInstance()->GetEveRightInfo();
			break;
		default:
			break;
		}
		// 크기 설정
		tempSurface.fSizeX = 3.0f;
		tempSurface.fSizeY = 3.0f;
		tempLeftSurface.fSizeX = 3.0f;
		tempLeftSurface.fSizeY = 3.0f;
		tempRightSurface.fSizeX = 3.0f;
		tempRightSurface.fSizeY = 3.0f;
		Player->SetSurfaceInfo(tempSurface);
		Player->SetLeftSurfaceInfo(tempLeftSurface);
		Player->SetRightSurfaceInfo(tempRightSurface);
	}
}

void CObjectManager::SetButtonResource()
{
	// 버튼의 표면 정보를 넣는 함수
	SURFACEINFO tempSurface, tempHoverSFinfo;
	int size;
	// 버튼 리소스
	size = m_Button.size();
	for (int i = 0; i < size; i++)
	{
		if (m_Button[i]->GetSurfaceInfo().dcSurface != nullptr)
		{
			// 리소스 타입에 맞게 표면 정보를 넣음
			switch (m_Button[i]->GetResourceType())
			{
			case (int)RESOURCE_TYPE::EXIT:
				tempSurface = CResourceManager::GetInstance()->GetExitInfo();
				tempHoverSFinfo = CResourceManager::GetInstance()->GetExitHoverInfo();
				break;
			case (int)RESOURCE_TYPE::PLAY:
				tempSurface = CResourceManager::GetInstance()->GetPlayInfo();
				tempHoverSFinfo = CResourceManager::GetInstance()->GetPlayHoverInfo();
				break;
			default:
				break;
			}
			// 크기 설정
			tempSurface.fSizeX = 1.0f;
			tempHoverSFinfo.fSizeX = 1.0f;
			tempSurface.fSizeY = 1.0f;
			tempHoverSFinfo.fSizeY = 1.0f;
			m_Button[i]->SetSurfaceInfo(tempSurface);
			dynamic_cast<CButton*>(m_Button[i])->SetHoverSuface(tempHoverSFinfo);
		}
	}
}

void CObjectManager::SetBackgroundResource()
{
	// 배경의 리소스 타입에 맞게 표면 정보를 넣는 함수
	SURFACEINFO tempSurface;
	int size;
	size = m_vecBackGround.size();
	for (int i = 0; i < size; i++)
	{
		switch (m_vecBackGround[i]->GetResourceType())
		{
		case (int)RESOURCE_TYPE::SPACE:
			tempSurface = CResourceManager::GetInstance()->GetSkyInfo();
			break;
		case (int)RESOURCE_TYPE::TITLE_BACKGROUND:
			tempSurface = CResourceManager::GetInstance()->GetTitleInfo();
		default:
			break;
		}
		m_vecBackGround[i]->SetSurfaceInfo(tempSurface);
	}
}

void CObjectManager::SetObjectsResource()
{
	// 오브젝트들의 리소스를 넣는 함수
	SetButtonResource();		// 버튼 리소스
	SetBackgroundResource();	// 배경 리소스
}