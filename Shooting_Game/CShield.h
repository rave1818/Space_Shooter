#ifndef _CSHIELD_H_
#define _CSHIELD_H_
#include "CSkill.h"


class CShield : public CSkill
{
public:
	// 생성자, 소멸자
	CShield();
	~CShield();
	// 애니메이션 정보 초기화
	void InitSurfaceInfo();
	// Set
	inline void SetOpenShieldInfo(SURFACEINFO sfInfo, int index) { m_OpenShieldInfo[index] = sfInfo; }
	inline void SetCloseShieldInfo(SURFACEINFO sfInfo, int index) { m_CloseShieldInfo[index] = sfInfo; }
	inline void SetAnimation(int value) { m_nCurrentAnimation = value; }
	// Get
	inline SURFACEINFO GetOpenShieldInfo(int index)		{ return m_OpenShieldInfo[index]; }
	inline SURFACEINFO GetCloseShieldInfo(int index)	{ return m_CloseShieldInfo[index]; }
	inline int GetAnimation()							{ return m_nCurrentAnimation; }
	// Plus
	inline void PlusAnim(int value) { m_nCurrentAnimation += value; }
private:
	// SurfaceInfo
	SURFACEINFO m_OpnenedShieldInfo; // 완전히 열린 쉴드 표면 정보
	SURFACEINFO m_OpenShieldInfo[11]; // 쉴드 오프닝 애니메이션 표면 정보
	SURFACEINFO m_CloseShieldInfo[8]; // 쉴드 클로징 애니메이션 표면 정보
	// int
	int m_nCurrentAnimation;
};


#endif // !_CSHIELD_H_
