#include <cmath>
#include "CBulletManager.h"
#include "Enum.h"
#include "define.h"
#include "CBullet.h"

CBullet::CBullet()
{
	SetX(0);
	SetY(0);
	SetSpeed(10.0f);
	m_bActive = true;
	m_fAngle = 0;
	m_fUnActiveTime = 0;
}

CBullet::CBullet(float x, float y)
{
	SetX(x);
	SetY(y);
	m_bActive = true;
	m_fAngle = 0;
	m_fUnActiveTime = 0;
}

CBullet::CBullet(float x, float y, int OwnerType)
{
	SetX(x);
	SetY(y);
	m_bActive = true;
	m_fAngle = 0;
	m_nOwnerType = OwnerType;
	m_fUnActiveTime = 0;
}

CBullet::~CBullet()
{
}

void CBullet::Init(float x, float y, float angle, float speed)
{
	SetX(x);
	SetY(y);
	SetSpeed(speed);
	SetAngle(angle);
	
}

void CBullet::UpdateThreeBulletPattern()
{
	if (this->GetPatternType() != (int)SHOOT_PATTERN::THREE_BULLET_PATTERN ||
		!this->IsActive())
	{
		return;
	}
	if (this->GetY() <= 600)
	{
		return;
	}
	// Y가 600이상이면 탄막을 비활성화하고 그 위치에 원형 패턴 시작
	SetPatternType((int)SHOOT_PATTERN::NONE);
	this->SetActive(false);
	PlaySound(TEXT("Three_Bullet_SFX"), NULL, SND_FILENAME | SND_ASYNC);
	CBulletManager::GetInstance()->CirclePattern(this->GetX(), this->GetY());
}

void CBullet::UpdateEnemyBullet()
{
	if (!m_bActive) return;

	// 위치 변경
	float X = GetX();
	float Y = GetY();
	X += cos(RADIAN(m_fAngle)) * GetSpeed();
	Y += sin(RADIAN(m_fAngle)) * GetSpeed();
	SetX(X);
	SetY(Y);
}