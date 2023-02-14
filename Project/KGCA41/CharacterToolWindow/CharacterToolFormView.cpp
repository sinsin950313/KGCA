// CharacterToolFormView.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "CharacterToolFormView.h"


// CharacterToolFormView

IMPLEMENT_DYNCREATE(CharacterToolFormView, CFormView)

CharacterToolFormView::CharacterToolFormView()
	: CFormView(IDD_CharacterToolFormView)
{
	//Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 300), pParent, 0, NULL);
}

CharacterToolFormView::~CharacterToolFormView()
{
}

void CharacterToolFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CharacterToolFormView, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CharacterToolFormView 진단

#ifdef _DEBUG
void CharacterToolFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CharacterToolFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CharacterToolFormView 메시지 처리기


int CharacterToolFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}
