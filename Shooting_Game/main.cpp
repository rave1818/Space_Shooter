// 
// 안쓰는 코드나 클래스 enum define이있는지 꼼꼼히 확인하기 
// win api를 썻다는걸 티내기 위해 더블버퍼링요소 ppt에 넣기
#include <Windows.h>
#include <iostream>
#include <mmsystem.h>
#include <tchar.h>
#include <vector>
#include <time.h>
#include "CResourceManager.h"
#include "CPlayer.h"
#include "CLeo.h"
#include "Enum.h"
#include "define.h"
#include "CBackground.h"
#include "CHeart.h"
#include "CBoss.h"
#include "CEnemy.h"
#include "CShield.h"
#include "CRenderManager.h"
#include "CObjectManager.h"
#include "CBulletManager.h"
#include "CGameManager.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
HWND hWndMain;
LPSTR lpszClass = const_cast<LPSTR>("탄막 슈팅게임");
// 버퍼 표면
SURFACEINFO g_sfBack;

// 캐릭터 비트맵 찾아서 적용시키고 이동시키기
// 보스 비트맵 찾아서 적용시키고 출력시키기 << 여기까지 해보기
// 보스를 기준으로 여러가지 탄막 만들어보기
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
    , LPSTR lpszCmdParam, int nCmdShow)
{
    timeBeginPeriod(1);

    HWND hWnd;          // 생성될 창의 핸들을 저장할 변수
    MSG Message;        // 발생한 메시지 정보를 담을 구조체
    WNDCLASS WndClass;  // 생성할 창의 특성(스타일, 아이콘, 커서 등등)을 정의하는 구조체

    // 프로그램의 인스턴스 핸들을 전역 변수(g_hInst)에 저장함 (다른 함수에서 사용하기 위함)
    g_hInst = hInstance;

    // 윈도우 클래스를(WNDCLASS) 설정 
    WndClass.cbClsExtra = 0;    // 클래스 여분 메모리 
    WndClass.cbWndExtra = 0;    // 윈도우 여분 메모리 

    // 배경색을 투명으로 설정 (게임 등에서 직접 화면을 그릴 때 깜빡임을 방지하기 위해 자주 사용)
    WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 기본 화살표 커서 사용
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 기본 애플리케이션 아이콘 사용
    WndClass.hInstance = hInstance; // 현재 프로그램의 인스턴스 핸들 지정

    // 메시지를 처리할 콜백 함수를 지정함
    WndClass.lpfnWndProc = (WNDPROC)WndProc;

    WndClass.lpszClassName = lpszClass; // 등록할 윈도우 클래스의 이름
    WndClass.lpszMenuName = NULL;       // 프로그램 메뉴
    WndClass.style = CS_HREDRAW | CS_VREDRAW; // 창의 가로/세로 크기가 변할 때 화면을 다시 그리도록 설정

    // 설정한 윈도우 클래스를 운영체제에 등록합니다.
    RegisterClass(&WndClass);

    // 윈도우 생성 
    // 등록된 클래스 이름을 바탕으로 실제 메모리상에 윈도우를 생성함
    hWnd = CreateWindow(lpszClass, lpszClass,
        WS_SYSMENU | WS_CAPTION, // 창 스타일
        0, 0, // 창의 시작 X, Y 좌표
        MAXCLIENT_X, MAXCLIENT_Y,     // 창의 가로, 세로 크기
        NULL, (HMENU)NULL, hInstance, NULL);

    // 생성된 윈도우를 화면에 보여줍니다.
    ShowWindow(hWnd, nCmdShow);

    // 생성된 창의 핸들을 전역 변수에 저장함
    hWndMain = hWnd;

	const float SHOOT_DELAY = 0.15f;
    const float BOSS_ANIMATION_DELAY = 0.15f;
    float BossShootDelay = 1.0f;
    float BossAnimationTimer = 0.0f;
	float ShootTimer = 0.0f;
    float BossShootTimer = 0.0f;
    // 메시지 루프
    while (TRUE) // 무한 루프
    {
        // PeekMessage: 메시지 큐에 메시지가 있는지 '확인'만 하고 바로 반환함 (GetMessage와 달리 대기하지 않음)
        // PM_REMOVE: 메시지가 있다면 큐에서 읽어오고 삭제한다
        if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
        {
            // 발생한 메시지가 WM_QUIT면 무한 루프를 탈출함
            if (Message.message == WM_QUIT) break;

            // 그 외의 메시지는 WndProc 함수로 전달하여 처리
            DispatchMessage(&Message);
        }
        else
        {
            // 큐에 처리할 메시지가 없을 때 이 블록이 실행됨   
            CBoss* Boss = dynamic_cast<CBoss*>(CObjectManager::GetInstance()->GetBoss((int)OBJECT_TYPE::BOSS));
            CHeart* Heart = dynamic_cast<CHeart*>(CObjectManager::GetInstance()->GetHeartUI());
            CGameManager::GetInstance()->Update();
            float dt = CGameManager::GetInstance()->GetDeltaTime();
            static int BeforeHP = 3;
            if (dt > 0.1f)
            {
                dt = 0.1f;
            }
            if(CGameManager::GetInstance()->GetCurrentScene() == (int)SCENE::INGAME)
            {
                if (dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer())->GetAlive())
                {
					// 플레이어 이동 로직
					dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer())->Move(hWnd);
					// 플레이어 총알 발사
					ShootTimer += dt;
					if (ShootTimer >= SHOOT_DELAY)
					{
						dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer())->Shoot();
						ShootTimer -= SHOOT_DELAY;
					}
					// 보스 탄막 발사
					BossShootTimer += dt;
					if (BossShootTimer >= BossShootDelay)
					{
						PlaySound(TEXT("Boss_Shoot_SFX"), NULL, SND_FILENAME | SND_ASYNC);
						BossShootDelay = Boss->ShootBullet();
						BossShootTimer -= BossShootDelay;
					}
                }
                // 보스 애니메이션
                BossAnimationTimer += dt;
                if (BossAnimationTimer >= BOSS_ANIMATION_DELAY)
                {
                    CRenderManager::GetInstance()->SetBossAnimationIndex(CRenderManager::GetInstance()->GetBossAnimationIndex() + 1);
                    if (CRenderManager::GetInstance()->GetBossAnimationIndex() == 4) CRenderManager::GetInstance()->SetBossAnimationIndex(0);
                    
                    BossAnimationTimer -= BOSS_ANIMATION_DELAY;
                }
                if ((CObjectManager::GetInstance()->GetPlayer() != nullptr))
                {
                    CLeo* Leo = dynamic_cast<CLeo*>(CObjectManager::GetInstance()->GetPlayer());
                    if (Leo->GetSkillCoolTime() > 0)
                    {
                        // 남은 쿨타임을 감소시키고 음수로 떨어지면 0으로 고정
                        float newCool = Leo->GetSkillCoolTime() - dt;
                        if (newCool < 0.0f) newCool = 0.0f;
                        Leo->SetSkillCollTime(newCool);
                    }

					// 쉴드가 플레이어를 따라감
					if (dynamic_cast<CLeo*>(CObjectManager::GetInstance()->GetPlayer())->GetShield() != nullptr)
					{
						CShield* Shield = Leo->GetShield();
                        // 15, 15의 오프셋
						Shield->SetX(Leo->GetX() - 15);
						Shield->SetY(Leo->GetY() - 15);
					}
                    Leo->Update();
					// UI
					if (Leo->GetHp() != BeforeHP)
					{
                        BeforeHP = Leo->GetHp();
                        Heart->SetSurfaceInfo(CResourceManager::GetInstance()->GetHeartInfo(-(Leo->GetHp() - 3)));
					}
                }
            }

            CRenderManager::GetInstance()->Render(hWnd);

            CGameManager::GetInstance()->LimitFrameRate();
        }
    }
    timeEndPeriod(1);
    // WM_QUIT 메시지의 파라미터를 반환하며 프로그램을 정상 종료
    return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    // HDC
    HDC hdc;
    POINT pt;

    switch (iMessage)
    {
    case WM_CREATE:
        // 난수 초기화
        srand((unsigned)time(NULL));
            
        hdc = GetDC(hWnd);
        // 리소스 가져오기
        CResourceManager::GetInstance()->Init(hdc, &CRenderManager::GetInstance()->GetBackInfo());
        // 타이틀용 버튼 ui 생성
        CObjectManager::GetInstance()->CreateBackground((int)OBJECT_TYPE::TITLE_BACKGROUND);
        CObjectManager::GetInstance()->CreateTitleUI();
        // 오브젝트에 리소스 집어넣기
        CObjectManager::GetInstance()->SetObjectsResource();
        // 게임 초기화
        CGameManager::GetInstance()->InitGame();
    
        return 0;
    case WM_LBUTTONDOWN:
        CGameManager::GetInstance()->SetButtonDown(true);
        return 0;
	case WM_LBUTTONUP:
	{
		CGameManager::GetInstance()->SetButtonDown(false);
		CGameManager::GetInstance()->SetButtonClicked(true);
		return 0;
	}
    case WM_MOUSEMOVE:
        GetCursorPos(&pt); // 화면 좌표 가져오기
        ScreenToClient(hWnd, &pt); // 윈도우 창(Client) 좌표로 변환
        CGameManager::GetInstance()->SetCursorX(pt.x);
        CGameManager::GetInstance()->SetCursorY(pt.y);
        return 0;
    case WM_DESTROY:
		CObjectManager::GetInstance()->DestroyAllObjects();
		PostQuitMessage(0);
        return 0;
    }

    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}