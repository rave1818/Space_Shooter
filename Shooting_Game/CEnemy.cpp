#include "CEnemy.h"

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update(float dt)
{

}

bool CEnemy::IsCollided(CBullet* Bullet) // AABB 충돌 판정
{
	// 플레이어의 좌표 및 크기 정보 가져오기
	int ObjectLeft = GetX() + 10;
	int ObjectTop = GetY();
	SURFACEINFO ObjectInfo = GetSurfaceInfo();
	int ObjectRight = ObjectLeft + ObjectInfo.nWidth;
	int ObjectBottom = ObjectTop + ObjectInfo.nHeight;

	// 총알의 좌표 및 크기 정보 가져오기
	int BulletLeft = Bullet->GetX();
	int BulletTop = Bullet->GetY();
	SURFACEINFO BulletInfo = Bullet->GetSurfaceInfo();
	int BulletRight = BulletLeft + BulletInfo.nWidth;
	int BulletBottom = BulletTop + BulletInfo.nHeight;

	// 충돌 판정
	if (ObjectLeft < BulletRight &&
		ObjectRight > BulletLeft &&
		ObjectTop < BulletBottom &&
		ObjectBottom > BulletTop)
	{
		return true;
	}

	return false;
}