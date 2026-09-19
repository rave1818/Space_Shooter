#include "CButton.h"
#include "CGameManager.h"

CButton::CButton()
{
}

CButton::~CButton()
{
}

bool CButton::IsHovering()
{
	// 마우스 커서의 위치와 버튼의 가로, 세로길이를 얻음
	int CursorX = CGameManager::GetInstance()->GetCursorX(); 
	int CursorY = CGameManager::GetInstance()->GetCursorY();
	int Width = GetSurfaceInfo().nWidth * GetSurfaceInfo().fSizeX;
	int Height = GetSurfaceInfo().nHeight * GetSurfaceInfo().fSizeY;
	// 마우스 커서가 버튼 박스 내에 있는지 확인
	if (GetX() <= CursorX && CursorX <= (GetX() + Width) &&
		GetY() <= CursorY && CursorY <= (GetY() + Height))
	{
		//MessageBoxA(NULL, "Hovering", "CButton", MB_OKCANCEL | MB_ICONERROR);
		return true;
	}
	else
	{
		return false;
	}
}

bool CButton::IsClicked()
{
	// 호버링 중에 마우스가 클릭됐는지 확인
	if (IsHovering() && CGameManager::GetInstance()->GetButtonDown()) 
	{
		CGameManager::GetInstance()->SetButtonClicked(false);
		return true;
	}
	return false;
}