#ifndef _CCHARACTER1_H_
#define _CCHARACTER1_H_

#include "CPlayer.h"

class CCharacter3 : public CPlayer
{
public:
	// 생성자, 소멸자
	CCharacter3();
	~CCharacter3();
	// 업데이트
	void Update(float dt);
	// 전용 스킬
	void UseSkill();
private:

};


#endif // !_CCHARACTER_H_
