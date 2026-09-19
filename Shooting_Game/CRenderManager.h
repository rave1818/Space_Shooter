#ifndef _RENDERMANAGER_H_
#define _RENDERMANAGER_H_
#include <Windows.h>
#include "SurfaceInfo.h"

class CRenderManager
{
public:
	// 생성자, 소멸자
	CRenderManager();
	~CRenderManager();
	// 싱글톤
	static CRenderManager* GetInstance(){
	if (m_sInstance == NULL) {
		m_sInstance = new CRenderManager();
	}
	return m_sInstance;
}
	// 이미지 출력
	bool RenderImage(HDC dcDst, int x, int y, SURFACEINFO* psInfo);	
	bool RenderTitleImage(HDC dcDst, int x, int y, SURFACEINFO* psInfo);
	// 스프라이트 출력
	bool RenderSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo);
	// 선 출력
	void DrawLine(HDC hdc, int startX, int startY, int lengthX, int lengthY);
	// 씬별 출력
	void RenderTitle(HWND hWnd);
	void RenderInGame();
	void RenderPlayerBullet();
	void RenderEnemyBullet();
	// 최종 출력
	void Render(HWND hWnd);

	// Set
	inline void SetBackInfo(SURFACEINFO SurfaceInfo) { m_BackInfo = SurfaceInfo; }
	inline void SetBossAnimationIndex(int index)	 { m_nBossAnimationIndex = index; }
	// Get
	inline SURFACEINFO GetBackInfo()	{ return m_BackInfo; }
	inline int GetBossAnimationIndex()	{ return m_nBossAnimationIndex; }
private:
	// 싱글톤
	static CRenderManager* m_sInstance;
	// 배경 스크롤
	static int m_nScrollCount;
	// 애니메이션 
	static int m_nBossAnimationIndex;
	// 뒷표면
	SURFACEINFO m_BackInfo;
};

#endif // !_RENDERMANAGER_H_
