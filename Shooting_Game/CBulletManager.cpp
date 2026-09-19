#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "CGameManager.h"
#include "CBulletManager.h"
#include "CResourceManager.h"
#include "CObjectManager.h"
#include "CPlayer.h"

CBulletManager* CBulletManager::m_sInstance = nullptr;

CBulletManager::CBulletManager()
{
}

CBulletManager::~CBulletManager()
{
}

void CBulletManager::CreateBullet()
{
    // 새 탄막을 생성후 벡터에 넣음
	CBullet* newBullet = new CBullet;
    //newBullet->SetUnActiveTime(0.0);

    m_BulletPool.push_back(newBullet);
}

void CBulletManager::CreateBullet(int OwnerType)
{
    // 새 탄막을 생성후 벡터에 넣음
    CBullet* newBullet = new CBullet;
    // 누구의 총알인지 설정
    newBullet->SetOwnerType(OwnerType);

    m_BulletPool.push_back(newBullet);
}

void CBulletManager::DestroyBullet(int index)
{
    // 벡터의 범위를 벗어나지 않는지 확인
    if (index >= 0 && index < m_BulletPool.size())
    {
        CBullet* target = m_BulletPool[index];
        m_BulletPool.erase(m_BulletPool.begin() + index);
        delete target;
        target = nullptr;
    }
    else { MessageBoxA(NULL, "Void DestroyBullet() 벡터 범위 예외처리", "CBulletManager", MB_OKCANCEL | MB_ICONERROR); }
}

void CBulletManager::DestroyBullet(CBullet* Bullet)
{
    // 알맞는 탄막을 찾아 제거
    for (int i = 0; i < m_BulletPool.size(); i++)
    {
        if (m_BulletPool[i] == Bullet)
        {
            m_BulletPool.erase(m_BulletPool.begin() + i);

            delete Bullet;
            Bullet = nullptr;
            return;
        }
    }
	MessageBoxA(NULL, "Void DestroyBullet() 벡터 범위 예외처리", "CBulletManager", MB_OKCANCEL | MB_ICONERROR);
}

void CBulletManager::DestroyAllBullet()
{
	// 모든 탄막 제거
	for (int i = 0; i < m_BulletPool.size(); i++)
	{
		delete m_BulletPool[i];
		m_BulletPool[i] = nullptr;
	}
	m_BulletPool.clear();
}

int CBulletManager::GetBulletPoolSize(int OwnerType)
{
    // BulletPool에서 알맞은 OwnerType탄막의 개수를 찾아 반환함
    int Size = 0;
    for (const auto& Bullet : m_BulletPool)
    {
        if (Bullet->GetOwnerType() == OwnerType)
        {
            Size++;
        }
    }

    return Size;
}

vector<CBullet*> CBulletManager::GetBulletPool(int OwnerType)
{
    // 알맞은 OwnerType에 있는 탄막들을 vector에 넣어서 반환
    vector<CBullet*> Vec;

    for (const auto& Bullet : m_BulletPool)
    {
        if (Bullet->GetOwnerType() == OwnerType)
        {
            Vec.push_back(Bullet);
        }
    }

    return Vec;
}

int CBulletManager::GetPatternBulletSize(int type)
{
    // 알맞은 type의 패턴을 가지고있는 탄막을 찾아 반환함
    int Size = 0;
    for (const auto& Bullet : m_BulletPool)
    {
        if (Bullet->IsActive() && Bullet->GetPatternType() == type)
        {
            Size++;
        }
    }

    return Size;
}

CBullet* CBulletManager::GetUnActivedBullet(int OwnerType)
{
    // 비활성화된 탄막을 찾아 반환
    for(const auto& Bullet : m_BulletPool)
    {
        if (!Bullet->IsActive() && Bullet->GetOwnerType() == OwnerType)
        {
            Bullet->SetActive(true);
            return Bullet;
        }
    }
    // 비활성화된 탄막이 없다면 새로 생성후 반환
    CreateBullet(OwnerType);
    m_BulletPool.back()->SetActive(true);
    return m_BulletPool.back();
}

CBullet* CBulletManager::GetPatternBullet(int type)
{
    // 패턴에 맞는 탄막을 찾아 반환
    for (const auto& Bullet : m_BulletPool)
    {
        if (Bullet->GetPatternType() == type)
        {
            return Bullet;
        }
    }
    return 0;
}

void CBulletManager::FanPattern(int BossX, int BossY)
{
    CBullet* Bullet[5];
    CPlayer* Player = dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer());
    // 탄막의 각도를 설정함
    for (int i = 0; i < 5; i++)
    {
		Bullet[i] = GetUnActivedBullet((int)OWNER_TYPE::ENEMY); // BulletPool에서 비활성화된 탄막을 가져옴
        if (!Bullet[i]->IsActive()) Bullet[i]->SetActive(true);
        Bullet[i]->SetSurfaceInfo(CResourceManager::GetInstance()->GetEnemyBulletInfo()); // 표면정보를 가져옴
        // 위치 설정
        Bullet[i]->SetX(BossX + 260); 
        Bullet[i]->SetY(BossY + 50);
        // 속도 설정
        Bullet[i]->SetSpeed(1.0f);
        // 패턴 종류 설정
        Bullet[i]->SetPatternType((int)SHOOT_PATTERN::FAN_PATTERN);
        // 탄막의 각도값 구하기
        float dx = Player->GetX() - Bullet[i]->GetX();
        float dy = Player->GetY() - Bullet[i]->GetY();
        double Radian = atan2(dy, dx);
        float TempAngle = (i - 2) * 20.0f;
        // 탄막 각도값 넣기
        Bullet[i]->SetAngle((Radian * 180 / PI) + TempAngle);
    }
}

void CBulletManager::ThreeBulletPattern(int BossX, int BossY)
{
    CBullet* FirstBullets[3];

    CPlayer* Player = dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer());
    // 탄막의 각도를 설정함
    for (int i = 0; i < 3; i++)
    {
        FirstBullets[i] = GetUnActivedBullet((int)OWNER_TYPE::ENEMY); // BulletPool에서 비활성화된 탄막을 가져옴
        if (!FirstBullets[i]->IsActive()) FirstBullets[i]->SetActive(true);
        FirstBullets[i]->SetSurfaceInfo(CResourceManager::GetInstance()->GetEnemyBulletInfo()); // 표면 정보를 가져옴
        // 위치 설정
        FirstBullets[i]->SetX(BossX + 260);
        FirstBullets[i]->SetY(BossY + 50);
        // 속도 설정
        FirstBullets[i]->SetSpeed(3.0f);
        // 패턴 종류 설정
        FirstBullets[i]->SetPatternType((int)SHOOT_PATTERN::THREE_BULLET_PATTERN);
        // 탄막의 각도값 구하기
        float dx = Player->GetX() - FirstBullets[i]->GetX();
        float dy = Player->GetY() - FirstBullets[i]->GetY();
        double Radian = atan2(dy, dx);
        float TempAngle = (i - 1) * 30.0f;
        // 탄막 각도값 넣기
        FirstBullets[i]->SetAngle((Radian * 180 / PI) + TempAngle);
    }
}

void CBulletManager::SmallerCirclePattern(int BossX, int BossY)
{
    CBullet* Bullet[8];
    CPlayer* Player = dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer());

    float Radius = 350.0f; // 반지름
    // 각도 및 위치 설정
    for (int i = 0; i < 8; i++)
    {
        Bullet[i] = GetUnActivedBullet((int)OWNER_TYPE::ENEMY); // BulletPool에서 비활성화된 탄막을 가져옴
        if (!Bullet[i]->IsActive()) Bullet[i]->SetActive(true);
        Bullet[i]->SetSurfaceInfo(CResourceManager::GetInstance()->GetEnemyBulletInfo()); // 표면 정보를 가져옴
        // 속도 설정
        Bullet[i]->SetSpeed(3.0f);
        // 패턴 종류 설정
        Bullet[i]->SetPatternType((int)SHOOT_PATTERN::SMALLER_CIRCLE_PATTERN);
        // 플레이어의 위치를 기준으로 8개의 탄막이 원형으로 둘러싸도록 위치 설정
        double Radian = (i * 45) * (PI / 180);
        Bullet[i]->SetX(Player->GetX() + Radius * cos(Radian));
        Bullet[i]->SetY(Player->GetY() + Radius * sin(Radian));
        // 각도는 플레이어를 바라보게 설정
        Bullet[i]->SetAngle((i * 45) + 180);
    }
}

void CBulletManager::CirclePattern(int StartX, int StartY)
{
    // ThreeBulletPattern이후로 y값이 일정 값 아래로 내려가면 CirclePattern이 발동됨
    CBullet* Bullet[16];

    CPlayer* Player = dynamic_cast<CPlayer*>(CObjectManager::GetInstance()->GetPlayer());
	int RandAngle = rand() % 180;
    // 탄막의 각도를 설정함
    for (int i = 0; i < 16; i++)
    {
        Bullet[i] = GetUnActivedBullet((int)OWNER_TYPE::ENEMY); // BulletPool에서 비활성화된 탄막을 가져옴
        if (!Bullet[i]->IsActive()) Bullet[i]->SetActive(true);
        Bullet[i]->SetSurfaceInfo(CResourceManager::GetInstance()->GetEnemyBulletInfo()); // 표면 정보를 가져옴
        // 위치 설정
        Bullet[i]->SetX(StartX);
        Bullet[i]->SetY(StartY);
        // 속도 설정
        Bullet[i]->SetSpeed(2.0f);
        // 패턴 종류 설정
        Bullet[i]->SetPatternType((int)SHOOT_PATTERN::CIRCLE_PATTERN);
        // 탄막의 각도값 구하기
        float dx = Player->GetX() - Bullet[i]->GetX();
        float dy = Player->GetY() - Bullet[i]->GetY();
        double Radian = atan2(dy, dx);
        float TempAngle = (i - 15) * 20.0f;
        // 탄막 각도값 넣기
        Bullet[i]->SetAngle((Radian * 180 / PI) + TempAngle + RandAngle);
    }
}
