#ifndef _COBJECT_H_
#define _COBJECT_H_

#include <Windows.h>
#include "SurfaceInfo.h"

class CObject
{
public:
	// 생성자, 소멸자
	CObject();
	virtual ~CObject();

	// Set
	inline void SetX(float Value)						{ m_fX = Value; }
	inline void SetY(float Value)						{ m_fY = Value; }
	inline void SetSpeed(float Value)				{ m_fSpeed = Value; }
	inline void SetSurfaceInfo(SURFACEINFO sfInfo)	{ m_SurfaceInfo = sfInfo; }
	inline void SetObjectType(int type)				{ m_nObjectType = type;}
	inline void SetResourceType(int type)			{ m_nResourceType = type; }
	// Get
	inline float GetX()					{ return m_fX; }
	inline float GetY()					{ return m_fY; }
	inline int GetObjectType()			{ return m_nObjectType; }
	inline int GetResourceType()		{ return m_nResourceType; }
	inline float GetSpeed()				{ return m_fSpeed; }
	SURFACEINFO GetSurfaceInfo()		{ return m_SurfaceInfo; }
private:
	// 속도
	float m_fSpeed;
	// 위치
	float m_fX, m_fY;
	// 종류
	int m_nObjectType;
	int m_nResourceType;
	// 표면정보
	SURFACEINFO m_SurfaceInfo;
};



#endif // !_COBJECT_H_
