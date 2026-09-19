#include "CShield.h"
#include "CResourceManager.h"

CShield::CShield()
{
}

CShield::~CShield()
{
}

void CShield::InitSurfaceInfo()
{
	// 쉴드 오프닝 애니메이션 표면 정보 초기화
	for (int i = 0; i < 11; i++)
	{
		m_OpenShieldInfo[i] = CResourceManager::GetInstance()->GetOpenShieldInfo(i);
	}
	// 쉴드 클로징 애니메이션 표면 정보 초기화
	for (int i = 0; i < 8; i++)
	{
		m_CloseShieldInfo[i] = CResourceManager::GetInstance()->GetCloseShieldInfo(i);
	}
	// 완전히 열린 쉴드 표면 정보 초기화
	m_OpnenedShieldInfo = CResourceManager::GetInstance()->GetOpenedShieldInfo();
}