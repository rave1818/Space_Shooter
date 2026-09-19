#ifndef _INIT_H_
#define _INIT_H_
#include "SurfaceInfo.h"
#include "Enum.h"

class CResourceManager
{
public:
	// 생성자, 소멸자
	CResourceManager();
	~CResourceManager();
	// 싱글톤
	static CResourceManager* GetInstance() {
		if (m_sInstance == NULL) {
			m_sInstance = new CResourceManager();
		}
		return m_sInstance;
	}
	//
	BOOL CreateBackBuffer(HDC dcScreen, int nWidth, int nHeight, SURFACEINFO* psInfo);
	void SetImageSurface(SURFACEINFO* pSurfaceInfo);
	void LoadSurface(HDC dcScreen, SURFACEINFO* pSurfaceInfo);
	void SetSpriteSurface(SURFACEINFO* pSurfaceInfo);
	void LoadSpriteDDB(HDC dcScreen, SURFACEINFO* pSuracefInfo, int Sprite);
	HBITMAP MakeDDBFromDIB(HDC hdc, const char* Path);
	void Init(HDC dcScreen, SURFACEINFO* BackInfo);
	// Set
	inline void SetSkyInfo(SURFACEINFO SurfaceInfo)						{ m_SkyInfo = SurfaceInfo; }
	inline void SetLeoInfo(SURFACEINFO SurfaceInfo)						{ m_LeoInfo[(int)CHARACTER_ANIMATION::FRONT] = SurfaceInfo; }
	inline void SetLeoLeftInfo(SURFACEINFO SurfaceInfo)					{ m_LeoInfo[(int)CHARACTER_ANIMATION::LEFT] = SurfaceInfo; }
	inline void SetLeoRightInfo(SURFACEINFO SurfaceInfo)				{ m_LeoInfo[(int)CHARACTER_ANIMATION::RIGHT] = SurfaceInfo; }
	inline void SetDanteInfo(SURFACEINFO SurfaceInfo)					{ m_DanteInfo[(int)CHARACTER_ANIMATION::FRONT] = SurfaceInfo; }
	inline void SetDanteLeftInfo(SURFACEINFO SurfaceInfo)				{ m_DanteInfo[(int)CHARACTER_ANIMATION::LEFT] = SurfaceInfo; }
	inline void SetDanteRightInfo(SURFACEINFO SurfaceInfo)				{ m_DanteInfo[(int)CHARACTER_ANIMATION::RIGHT] = SurfaceInfo; }
	inline void SetEveInfo(SURFACEINFO SurfaceInfo)						{ m_EveInfo[(int)CHARACTER_ANIMATION::FRONT] = SurfaceInfo; }
	inline void SetEveLeftInfo(SURFACEINFO SurfaceInfo)					{ m_EveInfo[(int)CHARACTER_ANIMATION::LEFT] = SurfaceInfo; }
	inline void SetEveRightInfo(SURFACEINFO SurfaceInfo)				{ m_EveInfo[(int)CHARACTER_ANIMATION::RIGHT] = SurfaceInfo; }
	inline void SetExitButtonInfo(SURFACEINFO SurfaceInfo)				{ m_ExitButton = SurfaceInfo; }
	inline void SetExitButtonHoverInfo(SURFACEINFO SurfaceInfo)			{ m_ExitButtonHover = SurfaceInfo; }
	inline void SetPlayButtonInfo(SURFACEINFO SurfaceInfo)				{ m_PlayButton = SurfaceInfo; }
	inline void SetPlayButtonHoverInfo(SURFACEINFO SurfaceInfo)			{ m_PlayButtonHover = SurfaceInfo; }
	inline void SetSettingButtonInfo(SURFACEINFO SurfaceInfo)			{ m_SettingButton = SurfaceInfo; }
	inline void SetSettingButtonHoverInfo(SURFACEINFO SurfaceInfo)		{ m_SettingButtonHover = SurfaceInfo; }
	inline void SetSoundNoneButtonInfo(SURFACEINFO SurfaceInfo)			{ m_SoundNoneButton = SurfaceInfo; }
	inline void SetSoundNoneButtonHoverInfo(SURFACEINFO SurfaceInfo)	{ m_SoundNoneButtonHover = SurfaceInfo; }
	inline void SetSoundOneButtonInfo(SURFACEINFO SurfaceInfo)			{ m_SouneOneButton = SurfaceInfo; }
	inline void SetSoundOneButtonHoverInfo(SURFACEINFO SurfaceInfo)		{ m_SoundOneButtonHover = SurfaceInfo; }
	inline void SetWhiteBulletInfo(SURFACEINFO SurfaceInfo)				{ m_WhiteBullet = SurfaceInfo; }
	inline void SetPurpleBulletInfo(SURFACEINFO SurfaceInfo)			{ m_PurpleBullet = SurfaceInfo;}
	inline void SetEnemyBulletInfo(SURFACEINFO SurfaceInfo)				{ m_EnemyBullet = SurfaceInfo; }
	inline void SetBossIdle0Info(SURFACEINFO SurfaceInfo)				{ m_Boss[0] = SurfaceInfo; }
	inline void SetBossIdle1Info(SURFACEINFO SurfaceInfo)				{ m_Boss[1] = SurfaceInfo; }
	inline void SetBossIdle2Info(SURFACEINFO SurfaceInfo)				{ m_Boss[2] = SurfaceInfo; }
	inline void SetBossIdle3Info(SURFACEINFO SurfaceInfo)				{ m_Boss[3] = SurfaceInfo; }
	inline void SetOpenShieldInfo(SURFACEINFO SurfaceInfo, int index)	{ m_OpenShield[index] = SurfaceInfo; }
	inline void SetCloseShieldInfo(SURFACEINFO SurfaceInfo, int index)	{ m_CloseShield[index] = SurfaceInfo; }
	inline void SetOpenedShieldInfo(SURFACEINFO SurfaceInfo)			{ m_OpenedShield = SurfaceInfo; }
	inline void SetHeartInfo(SURFACEINFO SurfaceInfo, int index)		{ m_Heart[index] = SurfaceInfo; }
	inline void SetShieldSkillicon(SURFACEINFO SurfaceInfo)				{ m_ShieldSkillIcon = SurfaceInfo; }
	inline void SetTitleInfo(SURFACEINFO SurfaceInfo)					{ m_TitleBackground = SurfaceInfo; }
	inline void SetTitleTextInfo(SURFACEINFO SurfaceInfo)				{ m_TitleText = SurfaceInfo; }
	inline void SetGameOverTextInfo(SURFACEINFO SurfaceInfo)			{ m_GameOverText = SurfaceInfo; }
	inline void SetKeyboardInfo(SURFACEINFO SurfaceInfo)				{ m_Keyboard = SurfaceInfo; }
	inline void SetRestartButtonInfo(SURFACEINFO SurfaceInfo)			{ m_Restart_Button = SurfaceInfo; }
	inline void SetRestartButtonHoverInfo(SURFACEINFO SurfaceInfo)		{ m_Restart_Button_Hover = SurfaceInfo; }
	inline void SetCloseButtonInfo(SURFACEINFO SurfaceInfo)				{ m_Close_Button = SurfaceInfo; }
	inline void SetCloseButtonHoverInfo(SURFACEINFO SurfaceInfo)		{ m_Close_Button_Hover = SurfaceInfo; }
	// Get
	inline SURFACEINFO GetSkyInfo()					{ return m_SkyInfo; }
	inline SURFACEINFO GetLeoInfo()					{ return m_LeoInfo[(int)CHARACTER_ANIMATION::FRONT]; }
	inline SURFACEINFO GetLeoLeftInfo()				{ return m_LeoInfo[(int)CHARACTER_ANIMATION::LEFT]; }
	inline SURFACEINFO GetLeoRightInfo()			{ return m_LeoInfo[(int)CHARACTER_ANIMATION::RIGHT]; }
	inline SURFACEINFO GetDanteInfo()				{ return m_DanteInfo[(int)CHARACTER_ANIMATION::FRONT]; }
	inline SURFACEINFO GetDanteLeftInfo()			{ return m_DanteInfo[(int)CHARACTER_ANIMATION::LEFT]; }
	inline SURFACEINFO GetDanteRightInfo()			{ return m_DanteInfo[(int)CHARACTER_ANIMATION::RIGHT]; }
	inline SURFACEINFO GetEveInfo()					{ return m_EveInfo[(int)CHARACTER_ANIMATION::FRONT]; }
	inline SURFACEINFO GetEveLeftInfo()				{ return m_EveInfo[(int)CHARACTER_ANIMATION::LEFT]; }
	inline SURFACEINFO GetEveRightInfo()			{ return m_EveInfo[(int)CHARACTER_ANIMATION::RIGHT]; }
	inline SURFACEINFO GetExitInfo()				{ return m_ExitButton; }
	inline SURFACEINFO GetExitHoverInfo()			{ return m_ExitButtonHover; }
	inline SURFACEINFO GetPlayInfo()				{ return m_PlayButton; }
	inline SURFACEINFO GetPlayHoverInfo()			{ return m_PlayButtonHover; }
	inline SURFACEINFO GetSettingInfo()				{ return m_SettingButton; }
	inline SURFACEINFO GetSettingHoverInfo()		{ return m_SettingButtonHover; }
	inline SURFACEINFO GetSoundNoneInfo()			{ return m_SoundNoneButton; }
	inline SURFACEINFO GetSoundNoneHoverInfo()		{ return m_SoundNoneButtonHover; }
	inline SURFACEINFO GetSoundOneInfo()			{ return m_SouneOneButton; }
	inline SURFACEINFO GetSoundOneHoverInfo()		{ return m_SoundOneButtonHover; }
	inline SURFACEINFO GetWhiteBulletInfo()			{ return m_WhiteBullet; }
	inline SURFACEINFO GetPurpleBulletInfo()		{ return m_PurpleBullet; }
	inline SURFACEINFO GetEnemyBulletInfo()			{ return m_EnemyBullet; }
	inline SURFACEINFO GetBossIdle0Info()			{ return m_Boss[0]; }
	inline SURFACEINFO GetBossIdle1Info()			{ return m_Boss[1]; }
	inline SURFACEINFO GetBossIdle2Info()			{ return m_Boss[2]; }
	inline SURFACEINFO GetBossIdle3Info()			{ return m_Boss[3]; }
	inline SURFACEINFO GetOpenShieldInfo(int index) { return m_OpenShield[index]; }
	inline SURFACEINFO GetCloseShieldInfo(int index){ return m_CloseShield[index]; }
	inline SURFACEINFO GetOpenedShieldInfo()		{ return m_OpenedShield; }
	inline SURFACEINFO GetHeartInfo(int index)		{ return m_Heart[index]; }
	inline SURFACEINFO GetShieldSkillIcon()			{ return m_ShieldSkillIcon; }
	inline SURFACEINFO GetTable()					{ return m_Table; }
	inline SURFACEINFO GetGameOverTable()			{ return m_Box; }
	inline SURFACEINFO GetTitleInfo()				{ return m_TitleBackground; }
	inline SURFACEINFO GetTitleTextInfo()			{ return m_TitleText; }
	inline SURFACEINFO GetGameOverTextInfo()		{ return m_GameOverText; }
	inline SURFACEINFO GetKeyboardInfo()			{ return m_Keyboard; }
	inline SURFACEINFO GetRestartButtonInfo()		{ return m_Restart_Button; }
	inline SURFACEINFO GetRestartButtonHoverInfo()	{ return m_Restart_Button_Hover; }
	inline SURFACEINFO GetCloseButtonInfo()			{ return m_Close_Button; }
	inline SURFACEINFO GetCloseButtonHoverInfo()	{ return m_Close_Button_Hover; }
	SURFACEINFO GetCharacterInfo();
private:
	// 싱글톤
	static CResourceManager* m_sInstance;
	// 배경
	SURFACEINFO m_SkyInfo;	// 하늘(배경)
	//// 캐릭터
	// 레오
	SURFACEINFO m_LeoInfo[3];
	// 단테
	SURFACEINFO m_DanteInfo[3];
	// 이브
	SURFACEINFO m_EveInfo[3];
	//// 타이틀 버튼
	// 나가기
	SURFACEINFO m_ExitButton;
	SURFACEINFO m_ExitButtonHover;
	// 시작
	SURFACEINFO m_PlayButton;
	SURFACEINFO m_PlayButtonHover;
	// 설정
	SURFACEINFO m_SettingButton;
	SURFACEINFO m_SettingButtonHover;
	// 무음
	SURFACEINFO m_SoundNoneButton;
	SURFACEINFO m_SoundNoneButtonHover;
	// 소리
	SURFACEINFO m_SouneOneButton;
	SURFACEINFO m_SoundOneButtonHover;
	// 캐릭터 선택창 UI
	// 박스
	SURFACEINFO m_Box;
	// 테이블
	SURFACEINFO m_Table;	
	// 화살표 버튼
	SURFACEINFO m_LeftArrow;
	SURFACEINFO m_RightArrow;
	// 확인 버튼
	SURFACEINFO m_Check;
	// 점
	SURFACEINFO m_Dot1;
	SURFACEINFO m_Dot2;
	// 탄막(플레이어)
	SURFACEINFO m_WhiteBullet;
	SURFACEINFO m_PurpleBullet;
	// 탄막(적)
	SURFACEINFO m_EnemyBullet;
	// 보스
	SURFACEINFO m_Boss[4];
	// 쉴드
	SURFACEINFO m_OpenedShield;
	SURFACEINFO m_OpenShield[11];
	SURFACEINFO m_CloseShield[8];
	// 하트 UI
	SURFACEINFO m_Heart[4];
	// 스킬 이이콘 UI
	SURFACEINFO m_ShieldSkillIcon;
	// 타이틀 배경
	SURFACEINFO m_TitleBackground;
	// 타이틀 텍스트
	SURFACEINFO m_TitleText;
	// 게임오버 텍스트
	SURFACEINFO m_GameOverText;
	// 키보드 이미지
	SURFACEINFO m_Keyboard;
	// 재시작 버튼
	SURFACEINFO m_Restart_Button;
	SURFACEINFO m_Restart_Button_Hover;
	// 닫기 버튼
	SURFACEINFO m_Close_Button;
	SURFACEINFO m_Close_Button_Hover;
};


#endif // !_INIT_H_
