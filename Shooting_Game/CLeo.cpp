#include "CLeo.h"
#include "CShield.h"
#include "CGameManager.h"
#include "CResourceManager.h"
#include "define.h"

#define ANIMATION_DELAY 0.1f
#define SKILL_DURATION 5.0f
// 생성자
CLeo::CLeo()
{
	SetX(370);
	SetY(700);
	SetSpeed(3.0f);
	SetAlive(true);
	SetHp(3);
	SetSkillCollTime(0.0f);

}
// 소멸자
CLeo::~CLeo()
{
}

void CLeo::Update()
{
	// 스킬이 발동 중이 아닐 때는 반환
	if (!GetSkillActive()) return;

	CShield* Shield = GetShield();
	float dt = CGameManager::GetInstance()->GetDeltaTime();
	PlusSkillTimer(dt);
	static bool IsOpeningSoundPlayed = false;
	static bool IsClosingSoundPlayed = false;

	switch (GetSkillState())
	{
	case (int)SKILL_STATE::SKILL_OPENING: // 오프닝 애니메이션
		if (!IsOpeningSoundPlayed)
		{
			PlaySound(TEXT("Shield_On_SFX"), NULL, SND_FILENAME | SND_ASYNC);
			IsOpeningSoundPlayed = true;
		}
		if (GetSkillTimer() >= ANIMATION_DELAY)
		{
			SetSkillTimer(0); // 타이머 초기화
			Shield->PlusAnim(1);

			if (Shield->GetAnimation() >= MAX_OPEN_SHIELD_ANIMATION)
			{
				// 오프닝 애니메이션 끝, 유지 상태로 넘어감
				SetSkillState((int)SKILL_STATE::SKILL_ACTIVE);
				Shield->SetAnimation(0);
				Shield->SetSurfaceInfo(CResourceManager::GetInstance()->GetOpenedShieldInfo());
			}
			else
			{
				// 다음 오프닝 프레임 적용
				Shield->SetSurfaceInfo(CResourceManager::GetInstance()->GetOpenShieldInfo(Shield->GetAnimation()));
			}
		}
		break;

	case (int)SKILL_STATE::SKILL_ACTIVE: // 스킬 유지 상태
		if (GetSkillTimer() >= SKILL_DURATION)
		{
			// 5초 유지 끝, 닫는 상태로 넘어감
			SetSkillState((int)SKILL_STATE::SKILL_CLOSING);
			SetSkillTimer(0.0f);
			Shield->SetAnimation(0);
			Shield->SetSurfaceInfo(CResourceManager::GetInstance()->GetCloseShieldInfo(0));
		}
		break;

	case (int)SKILL_STATE::SKILL_CLOSING: // 클로징 애니메이션
		if (!IsClosingSoundPlayed)
		{
			PlaySound(TEXT("Shield_Off_SFX"), NULL, SND_FILENAME | SND_ASYNC);
			IsClosingSoundPlayed = true;
		}
		if (GetSkillTimer() >= ANIMATION_DELAY)
		{
			SetSkillTimer(0.0f);
			Shield->PlusAnim(1);

			// 닫는 애니메이션까지 모두 끝났을시
			if (Shield->GetAnimation() >= MAX_CLOSE_SHIELD_ANIMATION)
			{
				SetSkillState((int)SKILL_STATE::SKILL_OFF);
				this->SetSkillActive(false);
				SetSkillCollTime(30.0f);

				// 쉴드 객체 해제
				delete Shield;
				Shield = nullptr;
				// 초기화
				IsOpeningSoundPlayed = false;
				IsClosingSoundPlayed = false;
			}
			else
			{
				// 다음 닫는 프레임 적용
				Shield->SetSurfaceInfo(CResourceManager::GetInstance()->GetCloseShieldInfo(Shield->GetAnimation()));
			}
		}
		break;
	}
}

// 전용 스킬 (쉴드)
void CLeo::UseSkill()
{
	if (GetSkillCoolTime() != 0) return; // 스킬 쿨타임이 남아있으면 스킬 사용 불가

	float dt = CGameManager::GetInstance()->GetDeltaTime();
	CShield* Shield = new CShield;
	this->SetSkillActive(true);
	// 애니메이션 정보 초기화
	Shield->SetAnimation(0);
	Shield->InitSurfaceInfo();
	Shield->SetX(GetX() - 20);
	Shield->SetY(GetY() - 20);
	// 스킬 상태를 오프닝으로 설정
	SetSkillState((int)SKILL_STATE::SKILL_OPENING);

	SetShield(Shield);
}