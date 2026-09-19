#ifndef _CSKILL_H_
#define _CSKILL_H_
#include "CObject.h"

class CSkill : public CObject
{
public:
	// 생성자, 소멸자
	CSkill();
	~CSkill();
	// 애니메이션 정보 초기화
	virtual void InitSurfaceInfo();
private:
};



#endif // !_CSKILL_H_
