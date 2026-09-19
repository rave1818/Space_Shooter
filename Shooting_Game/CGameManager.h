#ifndef _CGAMEMANAGER_H_
#define _CGAMEMANAGER_H_
#include <Windows.h>

class CGameManager
{
public:
	// 생성자, 소멸자
	CGameManager();
	~CGameManager();
	// 싱글톤
	static CGameManager* GetInstance() {
		if (m_sInstance == NULL) {
			m_sInstance = new CGameManager();
		}
		return m_sInstance;
	}
	// Init
	void Init();   // 타이머 초기화
	void InitGame();
	void InitInGame();
	void InitTitleButtonPosition();
	// 
	void LimitFrameRate();
	// Update
	void Update(); // 매 프레임마다 호출되어 Delta Time 계산
	// Set
	inline void SetCurrentScene(int CurrentScene)	{ m_nCurrentScene = CurrentScene; }
	inline void SetCharacterType(int Type)			{ m_nCharacterType = Type; }
	inline void SetCursorX(int x)					{ m_nCursorPosX = x; }
	inline void SetCursorY(int y)					{ m_nCursorPosY = y; }
	inline void SetButtonDown(bool Value)			{ m_bLButtonDown = Value; }
	inline void SetButtonClicked(bool Value)		{ m_bLButtonClicked = Value; }
	inline void SetScore(int Score)					{ m_nScore = Score; }
	// Get
	inline int GetCurrentScene()	{ return m_nCurrentScene; }
	inline int GetCharacterType()	{ return m_nCharacterType; }
	inline int GetCursorX()			{ return m_nCursorPosX; }
	inline int GetCursorY()			{ return m_nCursorPosY; }
	inline bool GetButtonDown()		{ return m_bLButtonDown; }
	inline bool GetButtonClicked()	{ return m_bLButtonClicked; }
	inline int GetScore()			{ return m_nScore; }
	inline int GetTargetFPS()		{ return m_TARGET_FPS; }
	float GetDeltaTime() const		{ return static_cast<float>(m_deltaTime); }
	// Plus
	inline void PlusScore(int Score) { m_nScore += Score; }
private:
	// 싱글톤
	static CGameManager* m_sInstance;
	// 씬
	int m_nCurrentScene;
	// 캐릭터 종류
	int m_nCharacterType;
	// 마우스 커서 위치
	int m_nCursorPosX;
	int m_nCursorPosY;
	// 마우스 눌림 여부
	bool m_bLButtonDown;
	// 마우스 클릭 여부
	bool m_bLButtonClicked;
	// 설정창 열림 여부
	bool m_bSetting;
	// 게임 점수
	int m_nScore;
	// Delta Time
	LARGE_INTEGER m_frequency;   // 초당 카운트 횟수 
	LARGE_INTEGER m_prevTime;    // 이전 프레임의 카운트
	LARGE_INTEGER m_currentTime; // 현재 프레임의 카운트
	double m_deltaTime;          // 계산된 Delta Time
	// fps
	const double m_TARGET_FPS = 60.0;
	const double m_TARGET_FRAME_TIME = 1.0 / m_TARGET_FPS;
};

#endif // !_CGAMEMANAGER_H_
