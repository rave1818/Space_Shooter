#include "CBoss.h"
#include "CObjectManager.h"
#include "CBulletManager.h"
#include "Enum.h"
#include "define.h"

CBoss::CBoss()
{
	SetX(270);
	SetY(50);
}

CBoss::~CBoss()
{
}

void CBoss::SetAnimationSurfaceSize(int index, float Xsize, float Ysize)
{
	m_Animation[index].fSizeX = Xsize;
	m_Animation[index].fSizeY = Ysize;
}

bool CBoss::IsCollided(CBullet* Bullet)
{
	// 적 탄막일시 반환
	if (Bullet->GetOwnerType() == (int)OWNER_TYPE::ENEMY) return false;

	// 오브젝트의 좌표 및 크기 정보 가져오기
	int ObjectLeft = GetX();
	int ObjectTop = GetY();
	SURFACEINFO ObjectInfo = dynamic_cast<CBoss*>(CObjectManager::GetInstance()->GetBoss((int)OBJECT_TYPE::BOSS))->GetAnimation(1);
	int ObjectRight = ObjectLeft + (ObjectInfo.nWidth * BOSS_SIZE_X);
	int ObjectBottom = ObjectTop + (ObjectInfo.nHeight * BOSS_SIZE_Y) - 120;

	// 총알의 좌표 및 크기 정보 가져오기
	int bulletLeft = Bullet->GetX();
	int bulletTop = Bullet->GetY();
	SURFACEINFO bulletInfo = Bullet->GetSurfaceInfo();
	int bulletRight = bulletLeft + bulletInfo.nWidth;
	int bulletBottom = bulletTop + bulletInfo.nHeight;

	// 충돌 판정 좌표가 겹치는지 체크
	if (ObjectLeft < bulletRight &&
		ObjectRight > bulletLeft &&
		ObjectTop < bulletBottom &&
		ObjectBottom > bulletTop)
	{
		return true;
	}
	return false;
}

float CBoss::ShootBullet()
{
	SURFACEINFO ObjectInfo = dynamic_cast<CBoss*>(CObjectManager::GetInstance()->GetBoss((int)OBJECT_TYPE::BOSS))->GetAnimation(1);

	m_nCurrentPattern = rand() % 4;

	int ShootPosX = (ObjectInfo.nWidth * (BOSS_SIZE_X / 2));
	int ShootPosY = (ObjectInfo.nHeight * BOSS_SIZE_Y) - 120;
	float PattrenTime = 0;

	switch (m_nCurrentPattern)
	{
	case (int)SHOOT_PATTERN::FAN_PATTERN:
		PattrenTime = 2.0f;
		CBulletManager::GetInstance()->FanPattern(ShootPosX, ShootPosY);
		break;
	case (int)SHOOT_PATTERN::THREE_BULLET_PATTERN:
		PattrenTime = 3.0f;
		CBulletManager::GetInstance()->ThreeBulletPattern(ShootPosX, ShootPosY);
		break;
	case (int)SHOOT_PATTERN::SMALLER_CIRCLE_PATTERN:
		PattrenTime = 2.5f;
		CBulletManager::GetInstance()->SmallerCirclePattern(ShootPosX, ShootPosY);
		break;
	default:
		break;
	}

	return PattrenTime;
}