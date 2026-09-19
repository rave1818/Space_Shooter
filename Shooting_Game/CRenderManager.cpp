#include <vector>
#include <string>
#include "CRenderManager.h"
#include "CObjectManager.h"
#include "CBulletManager.h"
#include "CGameManager.h"
#include "CHeart.h"
#include "CUi.h"
#include "CButton.h"
#include "CBackground.h"
#include "SurfaceInfo.h"
#include "CBoss.h"
#include "define.h"
#include "Enum.h"

// static 함수 초기화
CRenderManager* CRenderManager::m_sInstance = nullptr;
int CRenderManager::m_nScrollCount = 0;
int CRenderManager::m_nBossAnimationIndex = 0;

CRenderManager::CRenderManager()
{
}

CRenderManager::~CRenderManager()
{
}

bool CRenderManager::RenderImage(HDC dcDst, int x, int y, SURFACEINFO* pSurfaceInfo)
{
	// StrecthBlt : 가로 세로 길이를 원하는대로 늘리고 줄여서 출력할 수 있게 해줌
	// 다른 dc표면에서 복사해서 붙여넣음
	return StretchBlt(dcDst,
		x, y, INGAMESCREEN_X, INGAMESCREEN_Y,
		pSurfaceInfo->dcSurface, 0, 0,
		pSurfaceInfo->nWidth, pSurfaceInfo->nHeight,
		SRCCOPY);
}

bool CRenderManager::RenderTitleImage(HDC dcDst, int x, int y, SURFACEINFO* pSurfaceInfo)
{
	// 타이틀용 전체화면 출력
	return StretchBlt(dcDst,
		x, y, MAXCLIENT_X, MAXCLIENT_Y,
		pSurfaceInfo->dcSurface, 0, 0,
		pSurfaceInfo->nWidth, pSurfaceInfo->nHeight,
		SRCCOPY);
}

bool CRenderManager::RenderSprite(HDC dcDst, int x, int y, SURFACEINFO* pSurfaceInfo)
{
	// TransparentBlt : 기본적으로 StretchBlt의 기능을 수행할 수 있고 특정색을 지워서 출력할 수 있음
	// 기존 비트맵에 배경이 흰색이라면 지우고 출력하는용도로 사용가능
	return TransparentBlt(dcDst,
		x, y, pSurfaceInfo->nWidth * pSurfaceInfo->fSizeX, pSurfaceInfo->nHeight * pSurfaceInfo->fSizeY,
		pSurfaceInfo->dcSurface,
		0, 0, pSurfaceInfo->nWidth, pSurfaceInfo->nHeight,
		RGB(255, 255, 255));
}

void CRenderManager::DrawLine(HDC hdc, int startX, int startY, int lengthX, int lengthY)
{
	// win API함수로 선을 긋는 함수
	MoveToEx(hdc, startX, startY, nullptr);
	LineTo(hdc, startX + lengthX, startY + lengthY);
}

void CRenderManager::RenderTitle(HWND hWnd)
{
	SURFACEINFO sfBack = GetBackInfo(); // 더블 버퍼링용 뒷 표면
	// 오브젝트들을 가져옴
	CButton* PlayButton = dynamic_cast<CButton*>(CObjectManager::GetInstance()->GetButton((int)OBJECT_TYPE::PLAY));
	CButton* ExitButton = dynamic_cast<CButton*>(CObjectManager::GetInstance()->GetButton((int)OBJECT_TYPE::EXIT));
	CBackground* Title = dynamic_cast<CBackground*>(CObjectManager::GetInstance()->GetBackground((int)OBJECT_TYPE::TITLE_BACKGROUND));
	CObject* TitleText = CObjectManager::GetInstance()->GetTitleText();

	// 타이틀 출력
	RenderTitleImage(sfBack.dcSurface, 0, 0, &Title->GetSurfaceInfo());
	// 타이틀 텍스트 출력
	RenderSprite(sfBack.dcSurface, TitleText->GetX(), TitleText->GetY(), &TitleText->GetSurfaceInfo());
	// 버튼 호버중인지 체크
	SURFACEINFO PlayButtonSFinfo;
	SURFACEINFO ExitButtonSFinfo;
	if (PlayButton->IsHovering()) { PlayButtonSFinfo = PlayButton->GetHoverSurface(); }
	else PlayButtonSFinfo = PlayButton->GetSurfaceInfo();
	if (ExitButton->IsHovering()) { ExitButtonSFinfo = ExitButton->GetHoverSurface(); }
	else ExitButtonSFinfo = ExitButton->GetSurfaceInfo();
	// 버튼 눌렸는지 체크
	if (PlayButton->IsClicked())
	{
		CGameManager::GetInstance()->InitInGame();
		// 인게임 오브젝트 생성
		CObjectManager::GetInstance()->CreateInGameObjects();
		// 기존 오브젝트 삭제
		CObjectManager::GetInstance()->RemoveButtons();
		CObjectManager::GetInstance()->RemoveBackGroundObject((int)OBJECT_TYPE::TITLE_BACKGROUND);
		// 현재 씬 인게임으로 전환후 반환
		CGameManager::GetInstance()->SetCurrentScene((int)SCENE::INGAME);
		return;
	}
	if (ExitButton->IsClicked())
	{
		// 종료 버튼 클릭시 WM_DESTROY 호출
		DestroyWindow(hWnd);
	}
	//// 버튼 출력
	RenderSprite(sfBack.dcSurface, PlayButton->GetX(), PlayButton->GetY(), &PlayButtonSFinfo);
	RenderSprite(sfBack.dcSurface, ExitButton->GetX(), ExitButton->GetY(), &ExitButtonSFinfo);
}

void CRenderManager::RenderInGame() // 인게임 출력
{
	HFONT hFont, hOldFont; // 폰트
	SURFACEINFO sfBack = GetBackInfo(); // 더블 버퍼링용 뒷표면
	// 배경
	CBackground* BackgroundSpace = dynamic_cast<CBackground*>(CObjectManager::GetInstance()->GetBackground((int)OBJECT_TYPE::SPACE));
	// 플레이어
	CPlayer* Player = dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer());
	// 보스
	CBoss* Boss = dynamic_cast<CBoss*>(CObjectManager::GetInstance()->GetBoss((int)OBJECT_TYPE::BOSS));
	SURFACEINFO CurrentBackground = BackgroundSpace->GetSurfaceInfo(); // 현재 배경
	SURFACEINFO BossSurfaceInfo = Boss->GetAnimation(m_nBossAnimationIndex); // 보스 표면 정보
	SURFACEINFO PlayerSurfaceInfo; // 플레이어 표면 정보
	// UI
	CUi* Table = dynamic_cast<CUi*>(CObjectManager::GetInstance()->GetTable());
	CHeart* Heart = dynamic_cast<CHeart*>(CObjectManager::GetInstance()->GetHeartUI());
	CUi* SkillIcon = dynamic_cast<CUi*>(CObjectManager::GetInstance()->GetSkillIconUI());
	CUi* Keyboard = dynamic_cast<CUi*>(CObjectManager::GetInstance()->GetKeyboard());
	switch (Player->GetCurrentAnimation()) // 플레이어의 현재 애니메이션에따라 표면 정보 바꾸기
	{
	case (int)CHARACTER_ANIMATION::FRONT:
		PlayerSurfaceInfo = Player->GetSurfaceInfo();
		break;
	case (int)CHARACTER_ANIMATION::LEFT:
		PlayerSurfaceInfo = Player->GetLeftSurfaceInfo();
		break;
	case (int)CHARACTER_ANIMATION::RIGHT:
		PlayerSurfaceInfo = Player->GetRightSurfaceInfo();
		break;
	default:
		break;
	}
	// 배경 스크롤
	m_nScrollCount += 2;
	if (m_nScrollCount > 0) m_nScrollCount = -900;

	//// 왼쪽 인게임
	// 배경 출력
	RenderImage(sfBack.dcSurface, 0, m_nScrollCount, &CurrentBackground);
	RenderImage(sfBack.dcSurface, 0, m_nScrollCount + 900, &CurrentBackground);
	DrawLine(sfBack.dcSurface, INGAMESCREEN_X, 0, 0, INGAMESCREEN_Y);
	// 캐릭터 출력
	RenderSprite(sfBack.dcSurface, Player->GetX(), Player->GetY(), &PlayerSurfaceInfo);
	// 스킬 출력
	if (Player->GetObjectType() == (int)OBJECT_TYPE::LEO && Player->GetSkillActive())
	{
		CShield* Shield = dynamic_cast<CLeo*>(Player)->GetShield();
		RenderSprite(sfBack.dcSurface, Shield->GetX(), Shield->GetY(), &Shield->GetSurfaceInfo());
	}
	// 총알(탄막) 출력
	RenderPlayerBullet();
	RenderEnemyBullet();
	// 보스 출력
	RenderSprite(sfBack.dcSurface, Boss->GetX(), Boss->GetY(), &BossSurfaceInfo);
	//// 오른쪽 UI
	// 박스 출력
	RenderSprite(sfBack.dcSurface, Table->GetX(), Table->GetY(), &Table->GetSurfaceInfo());
	// 하트 출력
	RenderSprite(sfBack.dcSurface, Heart->GetX(), Heart->GetY(), &Heart->GetSurfaceInfo());
	// 스킬 아이콘 출력
	RenderSprite(sfBack.dcSurface, SkillIcon->GetX(), SkillIcon->GetY(), &SkillIcon->GetSurfaceInfo());
	// 글자 가져오기
	std::string str = std::to_string((int)Player->GetSkillCoolTime());
	if (Player->GetSkillCoolTime() <= 0.0f && !Player->GetSkillActive())	str = "Ready";
	else if (Player->GetSkillActive()) str = "Active";
	else std::string str = std::to_string((int)Player->GetSkillCoolTime());
	// 글자 배경을 불투명하게 변경
	SetBkMode(sfBack.dcSurface, TRANSPARENT);
	// 글자 색 변경
	SetTextColor(sfBack.dcSurface, RGB(0, 0, 0));
	// 글자 출력
	TextOutA(sfBack.dcSurface, SkillIcon->GetX() + 50, SkillIcon->GetY() + 70, str.c_str(), str.length());
	// 키보드 출력
	RenderSprite(sfBack.dcSurface, Keyboard->GetX(), Keyboard->GetY(), &Keyboard->GetSurfaceInfo());
	
	// 폰트 생성
	hFont = CreateFont(
		50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림"
	);

	// 폰트 적용
	hOldFont = (HFONT)SelectObject(sfBack.dcSurface, hFont);
	// 글자 색 변경
	SetTextColor(sfBack.dcSurface, RGB(255, 255, 255));
	// 글자 가져오기
	std::string str1 = "이동";
	std::string str2 = "스킬";
	// 글자 출력
	TextOutA(sfBack.dcSurface, Keyboard->GetX() + 45, Keyboard->GetY() + 155, str1.c_str(), str1.length());
	TextOutA(sfBack.dcSurface, Keyboard->GetX() + 200, Keyboard->GetY() + 155, str2.c_str(), str2.length());
	// 점수 글자 가져오기
	std::string strTemp = "점수 : ";
	std::string strScore = std::to_string(CGameManager::GetInstance()->GetScore());
	strScore = strTemp + strScore;
	// 점수 출력
	TextOutA(sfBack.dcSurface, INGAMESCREEN_X + 100, 20, strScore.c_str(), strScore.length());
	// 게임오버 화면 출력
	if (!Player->GetAlive())
	{
		// 오브젝트 가져오기
		CUi* GameOverTable = dynamic_cast<CUi*>(CObjectManager::GetInstance()->GetGameOverTable());
		CObject* GameOverText = CObjectManager::GetInstance()->GetGameOverText();
		CButton* RetryButton = dynamic_cast<CButton*>(CObjectManager::GetInstance()->GetButton((int)OBJECT_TYPE::RETRY));
		CButton* CloseButton = dynamic_cast<CButton*>(CObjectManager::GetInstance()->GetButton((int)OBJECT_TYPE::CLOSE));
		// 테이블 출력
		RenderSprite(sfBack.dcSurface, GameOverTable->GetX(), GameOverTable->GetY(), &GameOverTable->GetSurfaceInfo());
		// 버튼 출력
		// 호버중일때
		if (RetryButton->IsHovering())
		{
			RenderSprite(sfBack.dcSurface, RetryButton->GetX(), RetryButton->GetY(), &RetryButton->GetHoverSurface());
			if (RetryButton->IsClicked())
			{
				// 기존 오브젝트 삭제 후 게임 재시작
				CObjectManager::GetInstance()->RemoveInGameObjects();
				CBulletManager::GetInstance()->DestroyAllBullet();
				CGameManager::GetInstance()->InitInGame();
			}
		}
		else RenderSprite(sfBack.dcSurface, RetryButton->GetX(), RetryButton->GetY(), &RetryButton->GetSurfaceInfo());
		if (CloseButton->IsHovering())
		{
			RenderSprite(sfBack.dcSurface, CloseButton->GetX(), CloseButton->GetY(), &CloseButton->GetHoverSurface());
			if (CloseButton->IsClicked()) // 타이틀로 돌아가기
			{
				// 모든 인게임 오브젝트 삭제
				CObjectManager::GetInstance()->RemoveInGameObjects();
				CBulletManager::GetInstance()->DestroyAllBullet();
				CObjectManager::GetInstance()->CreateTitleObjects();
				CGameManager::GetInstance()->SetCurrentScene((int)SCENE::TITLE);
			}
		}
		else RenderSprite(sfBack.dcSurface, CloseButton->GetX(), CloseButton->GetY(), &CloseButton->GetSurfaceInfo());
		// 텍스트 출력
		RenderSprite(sfBack.dcSurface, GameOverText->GetX(), GameOverText->GetY(), &GameOverText->GetSurfaceInfo());
		// 점수 글자 가져오기
		std::string strTemp = "최종 점수 : ";
		std::string strScore = std::to_string(CGameManager::GetInstance()->GetScore());
		strScore = strTemp + strScore;
		// 최종 점수 출력
		TextOutA(sfBack.dcSurface, GameOverTable->GetX() + 80, GameOverTable->GetY() + 350, strScore.c_str(), strScore.length());
	}
	// 기존 폰트로 복구 및 만든 폰트 해제
	SelectObject(sfBack.dcSurface, hOldFont);
	DeleteObject(hFont);
}	

void CRenderManager::RenderPlayerBullet() // 플레이어가 발사하는 탄막 출력
{
	SURFACEINFO sfBack = GetBackInfo(); // 더블 버퍼링용 뒷 표면
	CBoss* Boss = dynamic_cast<CBoss*>(CObjectManager::GetInstance()->GetBoss((int)OBJECT_TYPE::BOSS));
	CPlayer* Player = dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer());

	for (int i = 0; i < CBulletManager::GetInstance()->GetBulletPoolSize((int)OWNER_TYPE::FRIENDLY); i++)
	{
		CBullet* Bullet = CBulletManager::GetInstance()->GetBulletPool((int)OWNER_TYPE::FRIENDLY)[i];
		if (Bullet->IsActive())	// 총알이 작동중일때 출력
		{
			if (Bullet->GetOwnerType() == (int)OWNER_TYPE::FRIENDLY && Bullet->GetY() > 0)
			{
				// 총알의 Y값을 줄여서 위로 발사시킴
				Bullet->SetY(Bullet->GetY() - (1 * Bullet->GetSpeed()));
			}
			else
			{
				Bullet->SetActive(false);
			}

			// 충돌시 점수가 증가하고 총알 비활성화
			if (Boss->IsCollided(Bullet) && Player->GetAlive())
			{
				//Boss->SetHp(Boss->GetHp() - 1);
				CGameManager::GetInstance()->PlusScore(5);
				Bullet->SetActive(false);
			}
			else // 충돌하지 않았을시 그냥 출력
				RenderSprite(sfBack.dcSurface, Bullet->GetX(), Bullet->GetY(), &Bullet->GetSurfaceInfo());
		}
	}
}

void CRenderManager::RenderEnemyBullet() // 보스가 소환하는 탄막 출력
{
	SURFACEINFO sfBack = GetBackInfo();
	CPlayer* Player = dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer());

	// 적 총알 풀의 전체 크기를 가져옴
	int poolSize = CBulletManager::GetInstance()->GetBulletPoolSize((int)OWNER_TYPE::ENEMY);
	// 제거 대상 모음 (루프중에 제거시 예외가 나는 현상 방지)
	vector<CBullet*> removeList;

	for (int i = 0; i < poolSize; i++)
	{
		CBullet* Bullet = CBulletManager::GetInstance()->GetBulletPool((int)OWNER_TYPE::ENEMY)[i];

		// 총알이 활성화 상태일 때만 로직 수행
		if (Bullet->IsActive())
		{
			// 총알 위치 업데이트 (패턴 로직에 따라 이동)
			Bullet->UpdateThreeBulletPattern();
			Bullet->UpdateEnemyBullet();

			// 충돌 판정 및 비활성화 처리
			if (Player->IsCollided(Bullet))
			{
				// 스킬 사용중일시 피해를 안받음
				if (!Player->GetSkillActive()) Player->SetHp(Player->GetHp() - 1);
				Bullet->SetPatternType((int)SHOOT_PATTERN::NONE);
				Bullet->SetActive(false);
				if (Player->GetHp() <= 0)
				{
					Player->SetAlive(false);
					Player->SetHp(0);
					CObjectManager::GetInstance()->CreateGameOverTableUI();
				}
			}
			// 화면 밖에 나갔을시 비활성화
			else if (Bullet->GetX() < -10 ||
				Bullet->GetX() > INGAMESCREEN_X - 13||
				Bullet->GetY() < 0 ||
				Bullet->GetY() > INGAMESCREEN_Y + 10)
			{
				Bullet->SetActive(false);
			}
			else
			{
				// 렌더링
				RenderSprite(
					sfBack.dcSurface,
					(int)Bullet->GetX(),
					(int)Bullet->GetY(),
					&(Bullet->GetSurfaceInfo())
				);
			}
		}
		else
		{
			// 창이 멈췄을때 방지
			float dt = CGameManager::GetInstance()->GetDeltaTime();
			if (dt > 0.1f)
			{
				dt = 0.1f;
			}
			Bullet->PlusUnActiveTime(dt);

			if (Bullet->GetUnActiveTime() > 5.0f)
			{
				// 즉시 삭제하지 않고 목록에 추가
				removeList.push_back(Bullet);
			}
		}
	}

	// 루프 종료 후에 제거할 리스트에서 삭제 
	for (auto b : removeList)
	{
		CBulletManager::GetInstance()->DestroyBullet(b);
	}
}

void CRenderManager::Render(HWND hWnd) // 최종 출력
{
	// DC핸들
	HDC hdc;
	// Rect
	RECT rect;
	GetClientRect(hWnd, &rect);
	// 표면정보 가져오기
	SURFACEINFO sfBack = GetBackInfo();

	hdc = GetDC(hWnd);
	{
		// 화면 초기화
		FillRect(sfBack.dcSurface, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		// 씬에따라 Render하기
		switch (CGameManager::GetInstance()->GetCurrentScene())
		{
		case (int)SCENE::TITLE:
		{
			RenderTitle(hWnd);
			break;
		}
		case (int)SCENE::INGAME:
		{
			RenderInGame();
			break;
		}
		default:
			break;
		}
	}
	// 뒷표면을 앞으로 복사
	BitBlt(hdc, 0, 0, MAXCLIENT_X, MAXCLIENT_Y, m_BackInfo.dcSurface, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
}