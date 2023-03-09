// CharacterToolDockablePane.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "CharacterToolDockablePane.h"


// CharacterToolDockablePane

IMPLEMENT_DYNAMIC(CharacterToolDockablePane, CDockablePane)

CharacterToolDockablePane::CharacterToolDockablePane()
{
}

CharacterToolDockablePane::~CharacterToolDockablePane()
{
}


BEGIN_MESSAGE_MAP(CharacterToolDockablePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// CharacterToolDockablePane 메시지 처리기




int CharacterToolDockablePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	_view = CharacterToolAnimationFormView::CreateFormView(this);
	_view->ShowWindow(SW_SHOW);

	return 0;
}


void CharacterToolDockablePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (_view)
	{
		_view->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
}


int CharacterToolDockablePane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFrameWnd* parentFrame = GetParentFrame();
	if (parentFrame == pDesktopWnd || pDesktopWnd->IsChild(parentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}

	return MA_NOACTIVATE;
}
