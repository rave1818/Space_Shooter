#include "CPlayer.h"
#include "CBulletManager.h"
#include "CResourceManager.h"
#include "CObjectManager.h"
#include "CGameManager.h"
#include "CBullet.h"
#include "define.h"
#include "Enum.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

// 이동 로직
void CPlayer::Move(HWND hWnd)
{
	bool IsMoving = false;

	if (GetAsyncKeyState('W') & 0x8000) // 위
	{
		SetY(GetY() - (1 * GetSpeed()));
	}
	if (GetAsyncKeyState('A') & 0x8000) // 왼
	{
		SetX(GetX() - (1 * GetSpeed()));
		m_nCurrentAnimation = (int)CHARACTER_ANIMATION::LEFT;
		IsMoving = true;
	}
	if (GetAsyncKeyState('S') & 0x8000) // 아
	{
		SetY(GetY() + (1 * GetSpeed()));
	}
	if (GetAsyncKeyState('D') & 0x8000) // 오
	{
		SetX(GetX() + (1 * GetSpeed()));
		m_nCurrentAnimation = (int)CHARACTER_ANIMATION::RIGHT;
		if (IsMoving) IsMoving = false;
		else IsMoving = true;
	}
	if (GetAsyncKeyState('E') & 0x8000) // 스킬 사용
	{
		UseSkill();
	}

	if (!IsMoving)
	{
		m_nCurrentAnimation = (int)CHARACTER_ANIMATION::FRONT;
	}

	// 화면 나가기 방지
	if (GetX() < -10)
	{
		SetX(-9);
	}
	if (GetX() > INGAMESCREEN_X - 10)
	{
		SetX(INGAMESCREEN_X - 11);
	}
	if (GetY() > 850)
	{
		SetY(849);
	}
}
// 총알 발사
void CPlayer::Shoot()
{
	CBullet* LeftBullet = CBulletManager::GetInstance()->GetUnActivedBullet((int)OWNER_TYPE::FRIENDLY);
	CBullet* RightBullet = CBulletManager::GetInstance()->GetUnActivedBullet((int)OWNER_TYPE::FRIENDLY);

	float x = GetX();
	float y = GetY();
	SURFACEINFO tempLeftSurface = CResourceManager::GetInstance()->GetWhiteBulletInfo();
	SURFACEINFO tempRightSurface = CResourceManager::GetInstance()->GetWhiteBulletInfo();
	tempLeftSurface.fSizeX = 1.0f;
	tempLeftSurface.fSizeY = 1.0f;
	tempRightSurface.fSizeX = 1.0f;
	tempRightSurface.fSizeY = 1.0f;
	LeftBullet->SetSurfaceInfo(tempLeftSurface);
	RightBullet->SetSurfaceInfo(tempRightSurface);
	
	LeftBullet->SetX(x - 3);
	LeftBullet->SetY(y);
	RightBullet->SetX(x + 3);
	RightBullet->SetY(y);
}

bool CPlayer::IsCollided(CBullet* Bullet)
{
	if (Bullet->GetOwnerType() == (int)OWNER_TYPE::FRIENDLY) return false;
	// 플레이어의 좌표 및 크기 정보 가져오기
	int playerLeft = GetX() + 12;
	int playerTop = GetY() + 12;
	SURFACEINFO playerInfo = GetSurfaceInfo();
	int playerRight = playerLeft + playerInfo.nWidth;
	int playerBottom = playerTop + playerInfo.nHeight;

	// 총알의 좌표 및 크기 정보 가져오기
	int bulletLeft = Bullet->GetX();
	int bulletTop = Bullet->GetY();
	SURFACEINFO bulletInfo = Bullet->GetSurfaceInfo();
	int bulletRight = bulletLeft + bulletInfo.nWidth;
	int bulletBottom = bulletTop + bulletInfo.nHeight;

	// 충돌 판정
	if (playerLeft < bulletRight &&
		playerRight > bulletLeft &&
		playerTop < bulletBottom &&
		playerBottom > bulletTop)
	{
		return true; 
	}

	return false; 
}
// 스킬 사용
void CPlayer::UseSkill()
{

}

