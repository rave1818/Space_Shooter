#ifndef _CBOSS_H_
#define _CBOSS_H_
#include "CEnemy.h"

class CBoss : public CEnemy
{
public:
	// 생성자, 소멸자
	CBoss();
	~CBoss();

	// Set
	inline void SetAnimationSurfaceInfo(int index, SURFACEINFO sfInfo)	{ m_Animation[index] = sfInfo; }
	inline void SetCurrentPattern(int value)								{ m_nCurrentPattern = value; }
	void SetAnimationSurfaceSize(int index, float Xsize, float Ysize);
	// Get
	SURFACEINFO GetAnimation(int index) { return m_Animation[index]; }
	inline int GetCurrentPattern()		{ return m_nCurrentPattern; }
	// 충돌 판정
	bool IsCollided(CBullet* Bullet);
	// 탄막 발사
	float ShootBullet();
private:
	// 애니메이션
	SURFACEINFO m_Animation[4];
	// 현재 패턴
	int m_nCurrentPattern;
};


#endif // !_CBOSS_H_
