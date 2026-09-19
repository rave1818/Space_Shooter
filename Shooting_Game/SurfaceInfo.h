#ifndef _SURFACEINFO_H_
#define _SURFACEINFO_H_

#include <windows.h>

typedef struct SURFACEINFOtag
{
    HDC			dcSurface;		// 비트맵이 적재되있는 표면 DC
    HBITMAP		hBmp;			// 비트맵 핸들
    HBITMAP		hOldBmp;		// 이전 비트맵 핸들
    int			nWidth;         // 비트맵의 가로 픽셀
    int			nHeight;        // 비트맵의 세로 픽셀
    float       fSizeX;         // 비트맵을 출력 시킬 가로 크기
    float       fSizeY;         // 비트맵을 출력 시킬 세로 크기
} SURFACEINFO;


#endif // !_SURFACEINFO_H_
