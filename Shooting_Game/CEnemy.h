#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CUnit.h"

class CEnemy : public CUnit
{
public:
	// 생성자, 소멸자
	CEnemy();
	~CEnemy();
	// 충돌 판정
	virtual bool IsCollided(CBullet* Bullet);
	// 업데이트
	virtual void Update(float dt);
private:

};

#endif // !_CENEMY_H_
