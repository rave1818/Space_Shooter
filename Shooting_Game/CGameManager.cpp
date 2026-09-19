#include "CGameManager.h"
#include "CButton.h"
#include "CObjectManager.h"
#include "Enum.h"
CGameManager* CGameManager::m_sInstance = nullptr;

CGameManager::CGameManager()
{
	m_nCharacterType = (INT)CHARACTERS::LEO;
}

CGameManager::~CGameManager()
{
}

void CGameManager::InitGame()
{
	// 프로그램이 처음 시작했을때 초기화
	m_nCurrentScene = (int)SCENE::TITLE; // 현재 씬 타이틀로 초기화
	InitTitleButtonPosition(); // 타이틀의 버튼들 위치 초기화
	SetButtonDown(false); // 마우스 눌림 여부 초기화
	SetButtonClicked(false); // 마우스 클릭 여부 초기화
	m_nScore = 0; // 게임 점수 초기화
	Init(); // DeltaTime 초기화
}

void CGameManager::InitTitleButtonPosition()
{
	// 타이틀에서 사용할 버튼들의 위치값 초기화
	CButton* PlayButton = dynamic_cast<CButton*>(CObjectManager::GetInstance()->GetButton((int)OBJECT_TYPE::PLAY));
	CButton* ExitButton = dynamic_cast<CButton*>(CObjectManager::GetInstance()->GetButton((int)OBJECT_TYPE::EXIT));
	PlayButton->SetX(350);
	PlayButton->SetY(700);
	ExitButton->SetX(1000);
	ExitButton->SetY(700);
}

void CGameManager::Init()
{
	// 시스템의 고해상도 타이머 주파수와 초기 시간을 구함
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_prevTime);
}

void CGameManager::InitInGame()
{
	// 게임 점수 초기화
	m_nScore = 0;
	// DeltaTime 초기화
	Init();
	// 인게임 오브젝트 생성
	CObjectManager::GetInstance()->CreateInGameObjects();
}

// 목표 프레임(예: 60FPS)을 일정하게 유지하기 위해 남은 시간만큼 대기하는 함수
void CGameManager::LimitFrameRate()
{
	// 현재 시점의 시간 측정
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	// 이번 프레임의 연산 및 렌더링에 실제로 걸린 시간 계산
	double frameWorkTime = static_cast<double>(now.QuadPart - m_prevTime.QuadPart) / m_frequency.QuadPart;

	// 연산이 목표 프레임 시간보다 일찍 끝나 남는 시간이 있는지 확인
	if (frameWorkTime < m_TARGET_FRAME_TIME)
	{
		// 목표 시간에 도달하기까지 남은 대기 시간 계산
		double remainingTime = m_TARGET_FRAME_TIME - frameWorkTime;

		// 남은 초를 밀리초로 변환
		DWORD sleepMs = static_cast<DWORD>(remainingTime * 1000.0);

		// 1ms 이상 남았을 때는 Sleep
		if (sleepMs > 0)
		{
			Sleep(sleepMs);
		}

		// Sleep 이후 남은 아주 미세한 시간은 
		// 목표 시간이 정확히 될 때까지 빈 루프를 돌며 정밀하게 대기
		while (true)
		{
			QueryPerformanceCounter(&now);

			// 프레임 시작점부터 현재까지 흘러간 총 시간 계산
			double totalElapsed = static_cast<double>(now.QuadPart - m_prevTime.QuadPart) / m_frequency.QuadPart;

			// 목표 프레임 시간에 도달하면 대기 종료
			if (totalElapsed >= m_TARGET_FRAME_TIME)
				break;
		}
	}
}

void CGameManager::Update()
{
	QueryPerformanceCounter(&m_currentTime); //  초당 주파수(틱 수)를 구함

	// (현재 카운트 - 이전 카운트) / 주파수 = 경과 시간(초)
	m_deltaTime = static_cast<double>(m_currentTime.QuadPart - m_prevTime.QuadPart) / m_frequency.QuadPart;

	if (m_deltaTime > 0.1) m_deltaTime = 0.1;

	// 다음 프레임 계산을 위해 현재 시간을 이전 시간으로 저장
	m_prevTime = m_currentTime;
}