#ifndef _INIT_H_
#define _INIT_H_
#include "SurfaceInfo.h"

class InitManager
{
public:
	InitManager();
	~InitManager();
	BOOL __CreateBackBuffer(HDC dcScreen, int nWidth, int nHeight, int nBPP, SURFACEINFO* psInfo);
	void __SetImgSurface(SURFACEINFO* psfInfo);
	void __LoadSurface(HDC dcScreen, SURFACEINFO* psInfo);
	void __SetSprSurface(SURFACEINFO* psfInfo, COLORREF crColorKey);
	void __LoadSpriteDDB(HDC dcScreen, SURFACEINFO* psfInfo, int Sprite);
	HBITMAP __MakeDDBFromDIB(HDC hdc, const char* Path);
	void __Init(HDC dcScreen, SURFACEINFO* BackInfo, SURFACEINFO* BGInfo, SURFACEINFO* SpriteInfo);
private:

};


#endif // !_INIT_H_
