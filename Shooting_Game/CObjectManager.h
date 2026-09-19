#ifndef _COBJECTMANAGER_H_
#define _COBJECTMANAGER_H_ 
#include <vector>
#include "CObject.h"
#include "CPlayer.h"
#include "CLeo.h"
#include "CEnemy.h"
#include "CBackground.h"
#include "define.h"
using namespace std;

class CObjectManager
{
public:
	// 생성자, 소멸자
	CObjectManager();
	~CObjectManager();
	// 싱글톤
	static CObjectManager* GetInstance() {
		if (m_sInstance == NULL) {
			m_sInstance = new CObjectManager();
		}
		return m_sInstance;
	}
	// Create
	void CreateLeo();
	void CreateBoss();
	void CreateShowingPlayer();
	void CreateTitleUI();
	void CreateCharacterSelectUI();
	void CreateBackground(int type);
	void CreateHeartUI();
	void CreateSkillIconUI();
	void CreateTableUI();
	void CreateGameOverTableUI();
	void CreateKeyboard();
	void CreateTitleObjects();
	void CreateInGameObjects();
	// Get
	CObject* GetBackground(int type);
	CObject* GetButton(int type);
	CObject* GetBoss(int type);
	CObject* GetPlayer()		{ return m_Player; }
	CObject* GetHeartUI()		{ return m_HeartUI; }
	CObject* GetSkillIconUI()	{ return m_SkillIconUI; }
	CObject* GetTable()			{ return m_Table; }
	CObject* GetGameOverTable() { return m_GameOverTable; }
	CObject* GetTitleText()		{ return m_TitleText; }
	CObject* GetGameOverText()	{ return m_GameOverText; }
	CObject* GetKeyboard()		{ return m_Keyboard; }
	// SetObject
	void SetPlayerObject(CPlayer* obj) { m_Player = obj; }
	// Add
	void AddBossObject(CEnemy* obj) { m_vecBoss.push_back(obj); }
	void AddBackGroundObject(CBackground* obj) { m_vecBackGround.push_back(obj); }
	// Remove
	void RemovePlayerObject(int type);
	void RemoveBossObject(int type);
	void RemoveBackGroundObject(int type);
	void RemoveShowingPlayer();
	void RemoveButtons();
	void RemoveInGameObjects();
	// Destroy
	void DestroyAllObjects();
	// SetResource
	void SetPlayerResource();
	void SetShowingPlayerResource();
	void SetButtonResource();
	void SetBackgroundResource();
	void SetObjectsResource();
private:
	// 싱글톤
	static CObjectManager* m_sInstance;
	// 캐릭터(플레이어)
	CObject* m_Player;
	// 보스들
	vector <CObject*> m_vecBoss;
	// 배경들
	vector <CObject*> m_vecBackGround;
	CObject* m_TitleText;
	// UI
	CObject* m_HeartUI;
	CObject* m_SkillIconUI;
	CObject* m_Table;
	CObject* m_GameOverTable;
	CObject* m_GameOverText;
	CObject* m_Keyboard;
	// 버튼들
	vector <CObject*> m_Button;
};

#endif // !_COBJECTMANAGER_H_
