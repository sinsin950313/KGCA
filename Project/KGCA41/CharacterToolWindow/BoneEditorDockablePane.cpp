// BoneEditorDockablePane.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "BoneEditorDockablePane.h"


// BoneEditorDockablePane

IMPLEMENT_DYNAMIC(BoneEditorDockablePane, CDockablePane)

BoneEditorDockablePane::BoneEditorDockablePane()
{

}

BoneEditorDockablePane::~BoneEditorDockablePane()
{
}


BEGIN_MESSAGE_MAP(BoneEditorDockablePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// BoneEditorDockablePane 메시지 처리기




int BoneEditorDockablePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	_boneEditorView = SelectonEditorFormView::CreateFormView(this);
	_boneEditorView->ShowWindow(SW_SHOW);

	return 0;
}


void BoneEditorDockablePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (_boneEditorView)
	{
		_boneEditorView->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
}


int BoneEditorDockablePane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFrameWnd* parentFrame = GetParentFrame();
	if (parentFrame == pDesktopWnd || pDesktopWnd->IsChild(parentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}

	return MA_NOACTIVATE;
}

void BoneEditorDockablePane::CustomUpdateData()
{
	_boneEditorView->CustomUpdateData();
}
