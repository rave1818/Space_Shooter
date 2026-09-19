#ifndef _CBUTTON_H_
#define _CBUTTON_H_
#include "CObject.h"

class CButton : public CObject
{
public:
	// 생성자 소멸자
	CButton();
	~CButton();
	// 호버 및 클릭 여부 확인
	bool IsHovering();
	bool IsClicked();
	// Get
	inline SURFACEINFO GetHoverSurface() { return m_HoverInfo; }
	// Set
	inline void SetHoverSuface(SURFACEINFO sfInfo)	{ m_HoverInfo = sfInfo; }
private:
	SURFACEINFO m_HoverInfo;
};

#endif // !_CBUTTON_H_
