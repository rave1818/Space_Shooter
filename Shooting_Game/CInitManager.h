#ifndef _INIT_H_
#define _INIT_H_
#include "SurfaceInfo.h"

class CInitManager
{
public:
	// 持失切, 社瑚切
	CInitManager();
	~CInitManager();
	//
	BOOL CreateBackBuffer(HDC dcScreen, int nWidth, int nHeight, SURFACEINFO* psInfo);
	BOOL CreateBackBuffer(HDC dcScreen, int nWidth, int nHeight, int nBPP, SURFACEINFO* psInfo);
	void SetImageSurface(SURFACEINFO* pSurfaceInfo);
	void LoadSurface(HDC dcScreen, SURFACEINFO* pSurfaceInfo);
	void SetSpriteSurface(SURFACEINFO* pSurfaceInfo);
	void LoadSpriteDDB(HDC dcScreen, SURFACEINFO* pSuracefInfo, int Sprite);
	HBITMAP MakeDDBFromDIB(HDC hdc, const char* Path);
	void Init(HDC dcScreen, SURFACEINFO* BackInfo, SURFACEINFO* BackGroundInfo, SURFACEINFO* LeoInfo, SURFACEINFO* DanteInfo, SURFACEINFO* EveInfo);
private:

};


#endif // !_INIT_H_
