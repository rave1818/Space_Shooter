#ifndef _CBULLET_H_
#define _CBULLET_H_
#include <Windows.h>
#include "CObject.h"
#include "SurfaceInfo.h"

class CBullet : public CObject
{
public:
    // 생성자, 소멸자
    CBullet();
    CBullet(float x, float y);
    CBullet(float x, float y, int OwnerType);
    ~CBullet();
    // 
    void Init(float x, float y, float angle, float speed);
    // 적 탄막
    void UpdateThreeBulletPattern();
    void UpdateEnemyBullet();
    // Get
    inline float GetAngle() const           { return m_fAngle; }
    inline bool IsActive() const            { return m_bActive; }
    inline int GetOwnerType() const         { return m_nOwnerType; }
    inline int GetPatternType() const       { return m_nPatternType; }
    inline float GetUnActiveTime() const    { return m_fUnActiveTime; }
    // Set
    inline void SetAngle(float angle)       { m_fAngle = angle; }
    inline void SetActive(bool active)      { m_bActive = active; }
    inline void SetOwnerType(int type)      { m_nOwnerType = type; }
    inline void SetPatternType(int type)    { m_nPatternType = type; }
    inline void SetUnActiveTime(float time)   { m_fUnActiveTime = time; }
    // Plus
    inline void PlusUnActiveTime(float time){ m_fUnActiveTime += time; }
private:
    float m_fAngle; // 각도
	bool m_bActive; // 활성화 여부
	int m_nOwnerType; // 소유자 타입 (플레이어, 적)
	int m_nPatternType; // 패턴 타입 (적 탄막 패턴)
	float m_fUnActiveTime; // 비활성화 시간
};

#endif // !_CBULLET_H_