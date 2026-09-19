#ifndef _CUNIT_H_
#define _CUNIT_H_
#include "CObject.h"
#include "CBullet.h"

class CUnit : public CObject
{
public:
	// 생성자, 소멸자
	CUnit();
	~CUnit();
	// Set
	inline void SetHp(int Value)		{ m_nHp = Value; }
	inline void SetAlive(bool Value)	{ m_bisAlive = Value; }
	// Get
	inline int GetHp()			{ return m_nHp; }
	inline bool GetAlive()		{ return m_bisAlive; }
	// 충돌시
	virtual bool IsCollided(CBullet* Bullet);
private:
	// 체력
	int m_nHp;
	bool m_bisAlive;
};

#endif // !_CUNIT_H_
