#ifndef CHEART_H_
#define CHEART_H_
#include "CUi.h"

class CHeart : public CUi
{
public:
	// 생성자, 소멸자
	CHeart();
	~CHeart();
	// Set
	inline void SetAnimation(int value) { m_nCurrentAnimation; }
	// Get
	inline int GetAnimation() { return m_nCurrentAnimation; }
private:
	// 체력 칸별 애니메이션
	int m_nCurrentAnimation;
};

#endif // !CHEART_H_
