#include "CResourceManager.h"
#include "CGameManager.h"
#include "CRenderManager.h"
#include "Enum.h"
#include "define.h"

CResourceManager* CResourceManager::m_sInstance = nullptr;

// 생성자, 소멸자
CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
}

SURFACEINFO CResourceManager::GetCharacterInfo()
{
    // 플레이어의 표면 정보 가져오기
    SURFACEINFO Character;

    switch (CGameManager::GetInstance()->GetCharacterType())
    {
    case (INT)CHARACTERS::LEO:
        Character = GetLeoInfo();
        break;
    case (INT)CHARACTERS::DANTE:
        Character = GetDanteInfo();
        break;
    case (INT)CHARACTERS::EVE:
        Character = GetEveInfo();
        break;
    default:
        MessageBoxA(NULL, "GetCharacterInfo() 캐릭터 표면정보 초기화 오류", "CRenderManager", MB_OKCANCEL | MB_ICONERROR);
        break;
    }
    return Character;
}

BOOL CResourceManager::CreateBackBuffer(HDC dcScreen, int nWidth, int nHeight, SURFACEINFO* pSurfaceInfo)
{
    BOOL ReturnVal;

    // 화면 DC와 호환되는 메모리 DC 생성
    pSurfaceInfo->dcSurface = CreateCompatibleDC(dcScreen); 
    // 원하는 크기의 비트맵 생성
    pSurfaceInfo->hBmp = CreateCompatibleBitmap(dcScreen, nWidth, nHeight);
    // 생성한 비트맵을 메모리 DC에 선택
    pSurfaceInfo->hOldBmp = (HBITMAP)SelectObject(pSurfaceInfo->dcSurface, pSurfaceInfo->hBmp);
    // 비트맵을 PATCOPY로 덮어 초기화
    ReturnVal = PatBlt(pSurfaceInfo->dcSurface, 0, 0, nWidth, nHeight, PATCOPY);
	// 표면 정보에 너비와 높이 설정
    pSurfaceInfo->nWidth = nWidth;
    pSurfaceInfo->nHeight = nHeight;
	// CRenderManager에 백버퍼 정보 설정
    CRenderManager::GetInstance()->SetBackInfo(*pSurfaceInfo);

    return ReturnVal;
}

void CResourceManager::SetImageSurface(SURFACEINFO* pSurfaceInfo)
{
    ::memset(pSurfaceInfo, 0, sizeof(SURFACEINFO));
}

void CResourceManager::LoadSurface(HDC dcScreen, SURFACEINFO* pSurfaceInfo)
{
    BITMAP  Bitmap;

    pSurfaceInfo->dcSurface = CreateCompatibleDC(dcScreen);
    pSurfaceInfo->hOldBmp = (HBITMAP)SelectObject(pSurfaceInfo->dcSurface, pSurfaceInfo->hBmp);

    GetObject(pSurfaceInfo->hBmp, sizeof(BITMAP), &Bitmap);
    pSurfaceInfo->nWidth = Bitmap.bmWidth;
    pSurfaceInfo->nHeight = Bitmap.bmHeight;
}

void CResourceManager::SetSpriteSurface(SURFACEINFO* pSurfaceInfo)
{
    ::memset(pSurfaceInfo, 0, sizeof(SURFACEINFO));
}

void CResourceManager::LoadSpriteDDB(HDC dcScreen, SURFACEINFO* pSurfaceInfo, int Sprite)
{
	switch (Sprite)
	{
	case (INT)RESOURCE_TYPE::PLAYERS:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Players.bmp");
		break;
    case (INT)RESOURCE_TYPE::SPACE:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Sky.bmp");
        break;
    case (INT)RESOURCE_TYPE::LEO:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Leo_Front.bmp");
        break;  
    case (INT)RESOURCE_TYPE::LEO_LEFT:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Leo_Left.bmp");
        break;
    case (INT)RESOURCE_TYPE::LEO_RIGHT:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Leo_Right.bmp");
        break;
    case (INT)RESOURCE_TYPE::DANTE:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Dante_Front.bmp");
        break;
    case (INT)RESOURCE_TYPE::DANTE_LEFT:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Dante_Left.bmp");
        break;
    case (INT)RESOURCE_TYPE::DANTE_RIGHT:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Dante_Right.bmp");
        break;
    case (INT)RESOURCE_TYPE::EVE:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Eve_Front.bmp");
        break;
    case (INT)RESOURCE_TYPE::EVE_LEFT:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Eve_Left.bmp");
        break;
    case (INT)RESOURCE_TYPE::EVE_RIGHT:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Eve_Right.bmp");
        break;
    case (INT)RESOURCE_TYPE::EXIT:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Exit.bmp");
        break;
    case (INT)RESOURCE_TYPE::EXIT_HOVER:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Exit_Hover.bmp");
        break;
    case (INT)RESOURCE_TYPE::HOME:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Home.bmp");
        break;
    case (INT)RESOURCE_TYPE::HOME_HOVER:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Home_Hover.bmp");
        break;
    case (INT)RESOURCE_TYPE::PLAY:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Play.bmp");
        break;
    case (INT)RESOURCE_TYPE::PLAY_HOVER:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Play_Hover.bmp");
        break;
    case (INT)RESOURCE_TYPE::SETTING:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Setting.bmp");
        break;
    case (INT)RESOURCE_TYPE::SETTING_HOVER:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Setting_Hover.bmp");
        break;
    case (INT)RESOURCE_TYPE::SOUND_NONE:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Sound_None.bmp");
        break;
    case (INT)RESOURCE_TYPE::SOUND_NONE_HOVER:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Sound_None_Hover.bmp");
        break;
    case (INT)RESOURCE_TYPE::SOUND_ONE:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Sound_One.bmp");
        break;
    case (INT)RESOURCE_TYPE::SOUND_ONE_HOVER:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Sound_One_Hover.bmp");
        break;
    case (INT)RESOURCE_TYPE::SHIP_SELECT_BOX:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Box.bmp");
        break;
    case (INT)RESOURCE_TYPE::SHIP_SELECT_TABLE:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Table.bmp");
        break;
    case (INT)RESOURCE_TYPE::SHIP_SELECT_LEFT_ARROW:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Left_Arrow.bmp");
        break;
    case (INT)RESOURCE_TYPE::SHIP_SELECT_RIGHT_ARROW:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Right_Arrow.bmp");
        break;
    case (INT)RESOURCE_TYPE::SHIP_SELECT_CHECK:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Check.bmp");
        break;
    case (INT)RESOURCE_TYPE::SHIP_SELECT_DOT1:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Dot1.bmp");
        break;
    case (INT)RESOURCE_TYPE::SHIP_SELECT_DOT2:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Dot2.bmp");
        break;
    case (INT)RESOURCE_TYPE::PLAYER_WHITE_BULLET:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Player_White_Bullet.bmp");
        break;
    case (INT)RESOURCE_TYPE::PLAYER_PURPLE_BULLET:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Player_Purple_Bullet.bmp");
        break;
    case (INT)RESOURCE_TYPE::ENEMY_BULLET:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Enemy_Bullet.bmp");
        break;
    case (INT)RESOURCE_TYPE::BOSS_IDLE0:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Boss1.bmp");
        break;
    case (INT)RESOURCE_TYPE::BOSS_IDLE1:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Boss2.bmp");
        break;
    case (INT)RESOURCE_TYPE::BOSS_IDLE2:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Boss3.bmp");
        break;
    case (INT)RESOURCE_TYPE::BOSS_IDLE3:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Boss4.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD0:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield1.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD1:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield2.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD2:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield3.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD3:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield4.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD4:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield5.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD5:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield6.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD6:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield7.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD7:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield8.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD8:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield9.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD9:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield10.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPEN_SHIELD10:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Open_Shield11.bmp");
        break;
    case (INT)RESOURCE_TYPE::OPENED_SHIELD:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Opened_Shield.bmp");
        break;
    case (INT)RESOURCE_TYPE::CLOSE_SHIELD0:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Shield1.bmp");
        break;
    case (INT)RESOURCE_TYPE::CLOSE_SHIELD1:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Shield2.bmp");
        break;
    case (INT)RESOURCE_TYPE::CLOSE_SHIELD2:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Shield3.bmp");
        break;
    case (INT)RESOURCE_TYPE::CLOSE_SHIELD3:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Shield4.bmp");
        break;
    case (INT)RESOURCE_TYPE::CLOSE_SHIELD4:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Shield5.bmp");
        break;
    case (INT)RESOURCE_TYPE::CLOSE_SHIELD5:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Shield6.bmp");
        break;
    case (INT)RESOURCE_TYPE::CLOSE_SHIELD6:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Shield7.bmp");
        break;
    case (INT)RESOURCE_TYPE::CLOSE_SHIELD7:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Shield8.bmp");
        break;
    case (INT)RESOURCE_TYPE::HEART_UI0:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "HealthUI_01.bmp");
        break;
    case (INT)RESOURCE_TYPE::HEART_UI1:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "HealthUI_02.bmp");
        break;
    case (INT)RESOURCE_TYPE::HEART_UI2:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "HealthUI_03.bmp");
        break;
    case (INT)RESOURCE_TYPE::HEART_UI3:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "HealthUI_04.bmp");
        break;
    case (INT)RESOURCE_TYPE::SHIELD_SKILLICON:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Shield_SkillIcon.bmp");
        break;
    case (INT)RESOURCE_TYPE::TITLE_BACKGROUND:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Title_Background.bmp");
        break;
    case (INT)RESOURCE_TYPE::TITLE_TEXT:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Title_Text.bmp");
        break;
    case (INT)RESOURCE_TYPE::GAMEOVER_TEXT:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "GameOver_Text.bmp");
        break;
    case (INT)RESOURCE_TYPE::KEYBOARD:
        pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Keyboard.bmp");
        break;
	case (INT)RESOURCE_TYPE::RETRY:
		pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Retry_Button.bmp");
		break;
	case (INT)RESOURCE_TYPE::RETRY_HOVER:
		pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Retry_Button_Hover.bmp");
		break;
	case (INT)RESOURCE_TYPE::CLOSE:
		pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Button.bmp");
		break;
	case (INT)RESOURCE_TYPE::CLOSE_HOVER:
		pSurfaceInfo->hBmp = MakeDDBFromDIB(dcScreen, "Close_Button_Hover.bmp");
		break;
	}
    pSurfaceInfo->fSizeX = 1.0f;
    pSurfaceInfo->fSizeY = 1.0f;
}

HBITMAP CResourceManager::MakeDDBFromDIB(HDC hdc, const char* Path)
{
    // DDB(Device Dependent Bitmap) : 장치(출력장치, 모니터)에 종속적인 비트맵 이미지
    // DIB(Device Independent Bitmap) : DIB는 장치에 종속되지 않는 독립적인 비트맵
    // 이미지를 파일로 저장된 상태가 DIB이다 이를 WIN32 api로 출력하기 위해서는
    // DDB로 변환시키는 과정이 필요함 + 프로그램 내부에서의 관리는 DDB가 효율적임
    HANDLE              hFile;
    DWORD               FileSize, dwRead;
    HBITMAP             hBitmap;
    BITMAPFILEHEADER*   BitmapFileHeader;
    BITMAPINFO*         Bitmapinfo;
    BITMAPINFOHEADER*   BitmapinfoHeader;
    LPBYTE			    LpMemBlock;

    //// 파일을 연다
    hFile = CreateFile(Path, GENERIC_READ, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    FileSize = GetFileSize(hFile, NULL);

    LpMemBlock = (LPBYTE)malloc(FileSize);
    BitmapFileHeader = (BITMAPFILEHEADER*)LpMemBlock;
    ReadFile(hFile, LpMemBlock, FileSize, &dwRead, NULL);
    CloseHandle(hFile);

    Bitmapinfo = (BITMAPINFO*)(LpMemBlock + sizeof(BITMAPFILEHEADER));
    BitmapinfoHeader = (BITMAPINFOHEADER*)(LpMemBlock + sizeof(BITMAPFILEHEADER));

    //// DDB로 변환한다.
    hBitmap = CreateDIBitmap(hdc,						// hdc
        BitmapinfoHeader,					// BITMAPINFOHEADER 헤더
        CBM_INIT,					// 0 또는 CBM_INIT ( 초기화 )
        LpMemBlock + BitmapFileHeader->bfOffBits,	// 래스터 어드래스
        Bitmapinfo,							// BITMAPINFO 헤더
        DIB_RGB_COLORS);

    free(LpMemBlock);

    return hBitmap;
}

void CResourceManager::Init(HDC dcScreen, SURFACEINFO* BackInfo)
{
    ////
    CreateBackBuffer(dcScreen, MAXCLIENT_X, MAXCLIENT_Y, BackInfo);
    // 배경
    SetImageSurface(&m_SkyInfo);
    LoadSpriteDDB(dcScreen, &m_SkyInfo, (INT)RESOURCE_TYPE::SPACE);
    LoadSurface(dcScreen, &m_SkyInfo);
    //// 레오(1번째 캐릭터)
    // 기본
    SetSpriteSurface(&m_LeoInfo[(int)CHARACTER_ANIMATION::FRONT]);
    LoadSpriteDDB(dcScreen, &m_LeoInfo[(int)CHARACTER_ANIMATION::FRONT], (INT)RESOURCE_TYPE::LEO);
    LoadSurface(dcScreen, &m_LeoInfo[(int)CHARACTER_ANIMATION::FRONT]);
    // 왼쪽
    SetSpriteSurface(&m_LeoInfo[(int)CHARACTER_ANIMATION::LEFT]);
    LoadSpriteDDB(dcScreen, &m_LeoInfo[(int)CHARACTER_ANIMATION::LEFT], (INT)RESOURCE_TYPE::LEO_LEFT);
    LoadSurface(dcScreen, &m_LeoInfo[(int)CHARACTER_ANIMATION::LEFT]);
    // 오른쪽
    SetSpriteSurface(&m_LeoInfo[(int)CHARACTER_ANIMATION::RIGHT]);
    LoadSpriteDDB(dcScreen, &m_LeoInfo[(int)CHARACTER_ANIMATION::RIGHT], (INT)RESOURCE_TYPE::LEO_RIGHT);
    LoadSurface(dcScreen, &m_LeoInfo[(int)CHARACTER_ANIMATION::RIGHT]);
    //// 단테(2번째 캐릭터)
    // 기본
    SetSpriteSurface(&m_DanteInfo[(int)CHARACTER_ANIMATION::FRONT]);
    LoadSpriteDDB(dcScreen, &m_DanteInfo[(int)CHARACTER_ANIMATION::FRONT], (INT)RESOURCE_TYPE::DANTE);
    LoadSurface(dcScreen, &m_DanteInfo[(int)CHARACTER_ANIMATION::FRONT]);
    // 왼쪽
    SetSpriteSurface(&m_DanteInfo[(int)CHARACTER_ANIMATION::LEFT]);
    LoadSpriteDDB(dcScreen, &m_DanteInfo[(int)CHARACTER_ANIMATION::LEFT], (INT)RESOURCE_TYPE::DANTE_LEFT);
    LoadSurface(dcScreen, &m_DanteInfo[(int)CHARACTER_ANIMATION::LEFT]);
    // 오른쪽
    SetSpriteSurface(&m_DanteInfo[(int)CHARACTER_ANIMATION::RIGHT]);
    LoadSpriteDDB(dcScreen, &m_DanteInfo[(int)CHARACTER_ANIMATION::RIGHT], (INT)RESOURCE_TYPE::DANTE_RIGHT);
    LoadSurface(dcScreen, &m_DanteInfo[(int)CHARACTER_ANIMATION::RIGHT]);
    //// 이브(3번째 캐릭터)
    // 기본
    SetSpriteSurface(&m_EveInfo[(int)CHARACTER_ANIMATION::FRONT]);
    LoadSpriteDDB(dcScreen, &m_EveInfo[(int)CHARACTER_ANIMATION::FRONT], (INT)RESOURCE_TYPE::EVE);
    LoadSurface(dcScreen, &m_EveInfo[(int)CHARACTER_ANIMATION::FRONT]);
    // 왼쪽
    SetSpriteSurface(&m_EveInfo[(int)CHARACTER_ANIMATION::LEFT]);
    LoadSpriteDDB(dcScreen, &m_EveInfo[(int)CHARACTER_ANIMATION::LEFT], (INT)RESOURCE_TYPE::EVE_LEFT);
    LoadSurface(dcScreen, &m_EveInfo[(int)CHARACTER_ANIMATION::LEFT]);
    // 오른쪽
    SetSpriteSurface(&m_EveInfo[(int)CHARACTER_ANIMATION::RIGHT]);
    LoadSpriteDDB(dcScreen, &m_EveInfo[(int)CHARACTER_ANIMATION::RIGHT], (INT)RESOURCE_TYPE::EVE_RIGHT);
    LoadSurface(dcScreen, &m_EveInfo[(int)CHARACTER_ANIMATION::RIGHT]);
    // 나가기 버튼
    SetSpriteSurface(&m_ExitButton);
    LoadSpriteDDB(dcScreen, &m_ExitButton, (INT)RESOURCE_TYPE::EXIT);
    LoadSurface(dcScreen, &m_ExitButton);
    // 나가기 버튼 (호버)
    SetSpriteSurface(&m_ExitButtonHover);
    LoadSpriteDDB(dcScreen, &m_ExitButtonHover, (INT)RESOURCE_TYPE::EXIT_HOVER);
    LoadSurface(dcScreen, &m_ExitButtonHover);
    // 시작 버튼
    SetSpriteSurface(&m_PlayButton);
    LoadSpriteDDB(dcScreen, &m_PlayButton, (INT)RESOURCE_TYPE::PLAY);
    LoadSurface(dcScreen, &m_PlayButton);
    // 시작 버튼 (호버)
    SetSpriteSurface(&m_PlayButtonHover);
    LoadSpriteDDB(dcScreen, &m_PlayButtonHover, (INT)RESOURCE_TYPE::PLAY_HOVER);
    LoadSurface(dcScreen, &m_PlayButtonHover);
    // 설정 버튼
    SetSpriteSurface(&m_SettingButton);
    LoadSpriteDDB(dcScreen, &m_SettingButton, (INT)RESOURCE_TYPE::SETTING);
    LoadSurface(dcScreen, &m_SettingButton);
    // 설정 버튼 (호버)
    SetSpriteSurface(&m_SettingButtonHover);
    LoadSpriteDDB(dcScreen, &m_SettingButtonHover, (INT)RESOURCE_TYPE::SETTING_HOVER);
    LoadSurface(dcScreen, &m_SettingButtonHover);
    // 무음 버튼
    SetSpriteSurface(&m_SoundNoneButton);
    LoadSpriteDDB(dcScreen, &m_SoundNoneButton, (INT)RESOURCE_TYPE::SOUND_NONE);
    LoadSurface(dcScreen, &m_SoundNoneButton);
    // 무음 버튼 (호버)
    SetSpriteSurface(&m_SoundNoneButtonHover);
    LoadSpriteDDB(dcScreen, &m_SoundNoneButtonHover, (INT)RESOURCE_TYPE::SOUND_NONE_HOVER);
    LoadSurface(dcScreen, &m_SoundNoneButtonHover);
    // 소리 버튼 
    SetSpriteSurface(&m_SouneOneButton);
    LoadSpriteDDB(dcScreen, &m_SouneOneButton, (INT)RESOURCE_TYPE::SOUND_ONE);
    LoadSurface(dcScreen, &m_SouneOneButton);
    // 소리 버튼 (호버)
    SetSpriteSurface(&m_SoundOneButtonHover);
    LoadSpriteDDB(dcScreen, &m_SoundOneButtonHover, (INT)RESOURCE_TYPE::SOUND_ONE_HOVER);
    LoadSurface(dcScreen, &m_SoundOneButtonHover);
    // 캐릭터 선택창
    // 박스
    SetSpriteSurface(&m_Box);
    LoadSpriteDDB(dcScreen, &m_Box, (INT)RESOURCE_TYPE::SHIP_SELECT_BOX);
    LoadSurface(dcScreen, &m_Box);
    // 테이블
    SetSpriteSurface(&m_Table);
    LoadSpriteDDB(dcScreen, &m_Table, (INT)RESOURCE_TYPE::SHIP_SELECT_TABLE);
    LoadSurface(dcScreen, &m_Table);
    // 왼쪽 화살표
    SetSpriteSurface(&m_LeftArrow);
    LoadSpriteDDB(dcScreen, &m_LeftArrow, (INT)RESOURCE_TYPE::SHIP_SELECT_LEFT_ARROW);
    LoadSurface(dcScreen, &m_LeftArrow);
    // 오른쪽 화살표
    SetSpriteSurface(&m_RightArrow);
    LoadSpriteDDB(dcScreen, &m_RightArrow, (INT)RESOURCE_TYPE::SHIP_SELECT_RIGHT_ARROW);
    LoadSurface(dcScreen, &m_RightArrow);
    // 확인 버튼
    SetSpriteSurface(&m_Check);
    LoadSpriteDDB(dcScreen, &m_Check, (INT)RESOURCE_TYPE::SHIP_SELECT_CHECK);
    LoadSurface(dcScreen, &m_Check);
    // 점1
    SetSpriteSurface(&m_Dot1);
    LoadSpriteDDB(dcScreen, &m_Dot1, (INT)RESOURCE_TYPE::SHIP_SELECT_DOT1);
    LoadSurface(dcScreen, &m_Dot1);
    // 점2 (선택)
    SetSpriteSurface(&m_Dot2);
    LoadSpriteDDB(dcScreen, &m_Dot2, (INT)RESOURCE_TYPE::SHIP_SELECT_DOT2);
    LoadSurface(dcScreen, &m_Dot2);
    // 플레이어 탄막 (흰색)
    SetSpriteSurface(&m_WhiteBullet);
    LoadSpriteDDB(dcScreen, &m_WhiteBullet, (INT)RESOURCE_TYPE::PLAYER_WHITE_BULLET);
    LoadSurface(dcScreen, &m_WhiteBullet);
    // 플레이어 탄막 (보라색)
    SetSpriteSurface(&m_PurpleBullet);
    LoadSpriteDDB(dcScreen, &m_PurpleBullet, (INT)RESOURCE_TYPE::PLAYER_PURPLE_BULLET);
    LoadSurface(dcScreen, &m_PurpleBullet);
    // 상대 탄막
    SetSpriteSurface(&m_EnemyBullet);
    LoadSpriteDDB(dcScreen, &m_EnemyBullet, (INT)RESOURCE_TYPE::ENEMY_BULLET);
    LoadSurface(dcScreen, &m_EnemyBullet);
    // 보스 애니메이션 0 
    SetSpriteSurface(&m_Boss[0]);
    LoadSpriteDDB(dcScreen, &m_Boss[0], (INT)RESOURCE_TYPE::BOSS_IDLE0);
    LoadSurface(dcScreen, &m_Boss[0]);
    // 보스 애니메이션 1
    SetSpriteSurface(&m_Boss[1]);
    LoadSpriteDDB(dcScreen, &m_Boss[1], (INT)RESOURCE_TYPE::BOSS_IDLE1);
    LoadSurface(dcScreen, &m_Boss[1]);
    // 보스 애니메이션 2 
    SetSpriteSurface(&m_Boss[2]);
    LoadSpriteDDB(dcScreen, &m_Boss[2], (INT)RESOURCE_TYPE::BOSS_IDLE2);
    LoadSurface(dcScreen, &m_Boss[2]);
    // 보스 애니메이션 3 
    SetSpriteSurface(&m_Boss[3]);
    LoadSpriteDDB(dcScreen, &m_Boss[3], (INT)RESOURCE_TYPE::BOSS_IDLE3);
    LoadSurface(dcScreen, &m_Boss[3]);
    // 펼쳐진 쉴드  
    SetSpriteSurface(&m_OpenedShield);
    LoadSpriteDDB(dcScreen, &m_OpenedShield, (INT)RESOURCE_TYPE::OPENED_SHIELD);
    LoadSurface(dcScreen, &m_OpenedShield);
    // 펼쳐지는 쉴드 애니메이션 0
    SetSpriteSurface(&m_OpenShield[0]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[0], (INT)RESOURCE_TYPE::OPEN_SHIELD0);
    LoadSurface(dcScreen, &m_OpenShield[0]);
    // 펼쳐지는 쉴드 애니메이션 1
    SetSpriteSurface(&m_OpenShield[1]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[1], (INT)RESOURCE_TYPE::OPEN_SHIELD1);
    LoadSurface(dcScreen, &m_OpenShield[1]);
    // 펼쳐지는 쉴드 애니메이션 2
    SetSpriteSurface(&m_OpenShield[2]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[2], (INT)RESOURCE_TYPE::OPEN_SHIELD2);
    LoadSurface(dcScreen, &m_OpenShield[2]);
    // 펼쳐지는 쉴드 애니메이션 3
    SetSpriteSurface(&m_OpenShield[3]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[3], (INT)RESOURCE_TYPE::OPEN_SHIELD3);
    LoadSurface(dcScreen, &m_OpenShield[3]);
    // 펼쳐지는 쉴드 애니메이션 4
    SetSpriteSurface(&m_OpenShield[4]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[4], (INT)RESOURCE_TYPE::OPEN_SHIELD4);
    LoadSurface(dcScreen, &m_OpenShield[4]);
    // 펼쳐지는 쉴드 애니메이션 5
    SetSpriteSurface(&m_OpenShield[5]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[5], (INT)RESOURCE_TYPE::OPEN_SHIELD5);
    LoadSurface(dcScreen, &m_OpenShield[5]);
    // 펼쳐지는 쉴드 애니메이션 6
    SetSpriteSurface(&m_OpenShield[6]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[6], (INT)RESOURCE_TYPE::OPEN_SHIELD6);
    LoadSurface(dcScreen, &m_OpenShield[6]);
    // 펼쳐지는 쉴드 애니메이션 7
    SetSpriteSurface(&m_OpenShield[7]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[7], (INT)RESOURCE_TYPE::OPEN_SHIELD7);
    LoadSurface(dcScreen, &m_OpenShield[7]);
    // 펼쳐지는 쉴드 애니메이션 8
    SetSpriteSurface(&m_OpenShield[8]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[8], (INT)RESOURCE_TYPE::OPEN_SHIELD8);
    LoadSurface(dcScreen, &m_OpenShield[8]);
    // 펼쳐지는 쉴드 애니메이션 9
    SetSpriteSurface(&m_OpenShield[9]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[9], (INT)RESOURCE_TYPE::OPEN_SHIELD9);
    LoadSurface(dcScreen, &m_OpenShield[9]);
    // 펼쳐지는 쉴드 애니메이션 10
    SetSpriteSurface(&m_OpenShield[10]);
    LoadSpriteDDB(dcScreen, &m_OpenShield[10], (INT)RESOURCE_TYPE::OPEN_SHIELD10);
    LoadSurface(dcScreen, &m_OpenShield[10]);
    // 닫히는 쉴드 애니메이션 0
    SetSpriteSurface(&m_CloseShield[0]);
    LoadSpriteDDB(dcScreen, &m_CloseShield[0], (INT)RESOURCE_TYPE::CLOSE_SHIELD0);
    LoadSurface(dcScreen, &m_CloseShield[0]);
    // 닫히는 쉴드 애니메이션 1
    SetSpriteSurface(&m_CloseShield[1]);
    LoadSpriteDDB(dcScreen, &m_CloseShield[1], (INT)RESOURCE_TYPE::CLOSE_SHIELD1);
    LoadSurface(dcScreen, &m_CloseShield[1]);
    // 닫히는 쉴드 애니메이션 2
    SetSpriteSurface(&m_CloseShield[2]);
    LoadSpriteDDB(dcScreen, &m_CloseShield[2], (INT)RESOURCE_TYPE::CLOSE_SHIELD2);
    LoadSurface(dcScreen, &m_CloseShield[2]);
    // 닫히는 쉴드 애니메이션 3
    SetSpriteSurface(&m_CloseShield[3]);
    LoadSpriteDDB(dcScreen, &m_CloseShield[3], (INT)RESOURCE_TYPE::CLOSE_SHIELD3);
    LoadSurface(dcScreen, &m_CloseShield[3]);
    // 닫히는 쉴드 애니메이션 4
    SetSpriteSurface(&m_CloseShield[4]);
    LoadSpriteDDB(dcScreen, &m_CloseShield[4], (INT)RESOURCE_TYPE::CLOSE_SHIELD4);
    LoadSurface(dcScreen, &m_CloseShield[4]);
    // 닫히는 쉴드 애니메이션 5
    SetSpriteSurface(&m_CloseShield[5]);
    LoadSpriteDDB(dcScreen, &m_CloseShield[5], (INT)RESOURCE_TYPE::CLOSE_SHIELD5);
    LoadSurface(dcScreen, &m_CloseShield[5]);
    // 닫히는 쉴드 애니메이션 6
    SetSpriteSurface(&m_CloseShield[6]);
    LoadSpriteDDB(dcScreen, &m_CloseShield[6], (INT)RESOURCE_TYPE::CLOSE_SHIELD6);
    LoadSurface(dcScreen, &m_CloseShield[6]);
    // 닫히는 쉴드 애니메이션 7
    SetSpriteSurface(&m_CloseShield[7]);
    LoadSpriteDDB(dcScreen, &m_CloseShield[7], (INT)RESOURCE_TYPE::CLOSE_SHIELD7);
    LoadSurface(dcScreen, &m_CloseShield[7]);
    for (int i = 0; i < MAX_OPEN_SHIELD_ANIMATION; i++)
    {
        m_OpenShield[i].fSizeX = 0.1f;
        m_OpenShield[i].fSizeY = 0.1f;
    }
    for (int i = 0; i < MAX_CLOSE_SHIELD_ANIMATION; i++)
    {
        m_CloseShield[i].fSizeX = 0.1f;
        m_CloseShield[i].fSizeY = 0.1f;
    }
    m_OpenedShield.fSizeX = 0.1f;
    m_OpenedShield.fSizeY = 0.1f;
    // 하트 UI 0
    SetSpriteSurface(&m_Heart[0]);
    LoadSpriteDDB(dcScreen, &m_Heart[0], (INT)RESOURCE_TYPE::HEART_UI0);
    LoadSurface(dcScreen, &m_Heart[0]);
    m_Heart[0].fSizeX = 5.0f;
    m_Heart[0].fSizeY = 5.0f;
    // 하트 UI 1
    SetSpriteSurface(&m_Heart[1]);
    LoadSpriteDDB(dcScreen, &m_Heart[1], (INT)RESOURCE_TYPE::HEART_UI1);
    LoadSurface(dcScreen, &m_Heart[1]);
    m_Heart[1].fSizeX = 5.0f;
    m_Heart[1].fSizeY = 5.0f;
    // 하트 UI 2
    SetSpriteSurface(&m_Heart[2]);
    LoadSpriteDDB(dcScreen, &m_Heart[2], (INT)RESOURCE_TYPE::HEART_UI2);
    LoadSurface(dcScreen, &m_Heart[2]);
    m_Heart[2].fSizeX = 5.0f;
    m_Heart[2].fSizeY = 5.0f;
    // 하트 UI 3
    SetSpriteSurface(&m_Heart[3]);
    LoadSpriteDDB(dcScreen, &m_Heart[3], (INT)RESOURCE_TYPE::HEART_UI3);
    LoadSurface(dcScreen, &m_Heart[3]);
    m_Heart[3].fSizeX = 5.0f;
    m_Heart[3].fSizeY = 5.0f;
    // 쉴드 스킬 아이콘
    SetSpriteSurface(&m_ShieldSkillIcon);
    LoadSpriteDDB(dcScreen, &m_ShieldSkillIcon, (INT)RESOURCE_TYPE::SHIELD_SKILLICON);
    LoadSurface(dcScreen, &m_ShieldSkillIcon);
    // 타이틀 배경
    SetSpriteSurface(&m_TitleBackground);
    LoadSpriteDDB(dcScreen, &m_TitleBackground, (INT)RESOURCE_TYPE::TITLE_BACKGROUND);
    LoadSurface(dcScreen, &m_TitleBackground);
    // 타이틀 텍스트
    SetSpriteSurface(&m_TitleText);
    LoadSpriteDDB(dcScreen, &m_TitleText, (INT)RESOURCE_TYPE::TITLE_TEXT);
    LoadSurface(dcScreen, &m_TitleText);
    // 게임오버 텍스트 
    SetSpriteSurface(&m_GameOverText);
    LoadSpriteDDB(dcScreen, &m_GameOverText, (INT)RESOURCE_TYPE::GAMEOVER_TEXT);
    LoadSurface(dcScreen, &m_GameOverText);
    // 키보드 
    SetSpriteSurface(&m_Keyboard);
    LoadSpriteDDB(dcScreen, &m_Keyboard, (INT)RESOURCE_TYPE::KEYBOARD);
    LoadSurface(dcScreen, &m_Keyboard);
	// 재시작 버튼
	SetSpriteSurface(&m_Restart_Button);
	LoadSpriteDDB(dcScreen, &m_Restart_Button, (INT)RESOURCE_TYPE::RETRY);
	LoadSurface(dcScreen, &m_Restart_Button);
	// 재시작 버튼 (호버)
	SetSpriteSurface(&m_Restart_Button_Hover);
	LoadSpriteDDB(dcScreen, &m_Restart_Button_Hover, (INT)RESOURCE_TYPE::RETRY_HOVER);
	LoadSurface(dcScreen, &m_Restart_Button_Hover);
	// 닫기 버튼
	SetSpriteSurface(&m_Close_Button);
	LoadSpriteDDB(dcScreen, &m_Close_Button, (INT)RESOURCE_TYPE::CLOSE);
	LoadSurface(dcScreen, &m_Close_Button);
	// 닫기 버튼 (호버)
	SetSpriteSurface(&m_Close_Button_Hover);
	LoadSpriteDDB(dcScreen, &m_Close_Button_Hover, (INT)RESOURCE_TYPE::CLOSE_HOVER);
	LoadSurface(dcScreen, &m_Close_Button_Hover);
}

