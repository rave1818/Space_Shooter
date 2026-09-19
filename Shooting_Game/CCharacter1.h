#ifndef _CCHARACTER1_H_
#define _CCHARACTER1_H_

#include "CPlayer.h"

class CCharacter1 : public CPlayer
{
public:
	// 생성자, 소멸자
	CCharacter1();
	~CCharacter1();
	// 업데이트
	void Update(float dt);
	// 전용 스킬
	void UseSkill();
private:

};


#endif // !_CCHARACTER_H_
