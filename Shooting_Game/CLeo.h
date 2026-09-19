#ifndef _CCHARACTER1_H_
#define _CCHARACTER1_H_

#include "CPlayer.h"
#include "CShield.h"

class CLeo : public CPlayer
{
public:
	// 생성자, 소멸자
	CLeo();
	~CLeo();
	// Set
	void SetShield(CShield* Shield) { m_Shield = Shield; }
	// Get
	CShield* GetShield() { return m_Shield; }
	// 업데이트
	void Update();
	// 전용 스킬 (쉴드)
	void UseSkill();
private:
	// 스킬
	CShield* m_Shield;
};


#endif // !_CCHARACTER_H_
