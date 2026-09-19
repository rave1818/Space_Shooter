#ifndef _CBULLETMANAGER_H_
#define _CBULLETMANAGER_H_
#include <vector>
#include "CBullet.h"
using namespace std;

class CBulletManager
{
public:
	// ½Ì±ÛÅæ
	static CBulletManager* GetInstance() {
		if (m_sInstance == NULL) {
			m_sInstance = new CBulletManager();
		}
		return m_sInstance;
	}
	// »ý¼ºÀÚ, ¼Ò¸êÀÚ
	CBulletManager();
	~CBulletManager();
	// Get
	inline int GetBulletPoolSize() { return m_BulletPool.size(); }
	int GetBulletPoolSize(int OwnerType);
	inline vector<CBullet*> GetBulletPool() { return m_BulletPool; }
	vector<CBullet*> GetBulletPool(int OwnerType);
	int GetPatternBulletSize(int type);
	// Åº¸· »ý¼º,ÆÄ±«
	inline void CreateBullet();
	inline void CreateBullet(int OwnerType);
	inline void DestroyBullet(int index);
	void DestroyAllBullet();
	void DestroyBullet(CBullet* Bullet);
	// Åº¸· °ü¸®
	CBullet* GetUnActivedBullet(int OwnerType);
	CBullet* GetPatternBullet(int type);
	// Åº¸· ÆÐÅÏ
	void FanPattern(int BossX, int BossY);
	void ThreeTimesFanPattern(int BossX, int BossY);
	void ThreeBulletPattern(int BossX, int BossY);
	void SmallerCirclePattern(int BossX, int BossY);
	void RazerPattern(int BossX, int BossY);
	void CirclePattern(int StartX, int StartY);
private:
	// ½Ì±ÛÅæ
	static CBulletManager* m_sInstance;
	// vector¸¦ È°¿ëÇÑ Bullet °ü¸®
	vector<CBullet*> m_BulletPool;
};
	
#endif // !_CBULLETMANAGER_H_
