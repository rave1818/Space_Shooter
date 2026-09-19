#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "CUnit.h"

class CPlayer : public CUnit
{
public:
	// 생성자, 소멸자
	CPlayer();
	~CPlayer();
	// 
	void Move(HWND hWnd);
	void Shoot();
	bool IsCollided(CBullet* Bullet);
	virtual void UseSkill();
	// Set
	inline void SetLeftSurfaceInfo(SURFACEINFO sfInfo)	{ m_LeftSurfaceInfo = sfInfo; }
	inline void SetRightSurfaceInfo(SURFACEINFO sfInfo) { m_RightSurfaceInfo = sfInfo; }
	inline void SetCurrentAnimation(int Animation)		{ m_nCurrentAnimation = Animation; }
	inline void SetSkillCollTime(float time)			{ m_fSkillCoolTime = time; }
	inline void SetSkillActive(bool value)				{ m_bIsSkillActive = value; }
	inline void SetSkillTimer(float time)				{ m_fSkillTimer = time; }
	inline void SetSkillState(int state)				{ m_nSkillState = state; }
	// Get
	inline SURFACEINFO GetLeftSurfaceInfo()	{ return m_LeftSurfaceInfo; }
	inline SURFACEINFO GetRightSurfaceInfo(){ return m_RightSurfaceInfo; }
	inline int GetCurrentAnimation()		{ return m_nCurrentAnimation; }
	inline float GetSkillCoolTime()			{ return m_fSkillCoolTime; }
	inline bool GetSkillActive()			{ return m_bIsSkillActive; }
	inline float GetSkillTimer()			{ return m_fSkillTimer; }
	inline int GetSkillState()				{ return m_nSkillState; }
	// Plus
	inline void PlusSkillTimer(float time) { m_fSkillTimer += time; }
private:
	// 플레이어 애니메이션
	SURFACEINFO m_LeftSurfaceInfo;
	SURFACEINFO m_RightSurfaceInfo;
	// 플레이어 현재 애니메이션 인덱스
	int m_nCurrentAnimation;
	// 스킬 쿨타임 
	float m_fSkillCoolTime;
	// 스킬 사용중 
	bool m_bIsSkillActive;
	// 스킬 타이머
	float m_fSkillTimer;
	// 스킬 상태
	int m_nSkillState;
};

#endif // !_CPLAYER_H_
