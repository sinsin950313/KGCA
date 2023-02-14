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

}

CharacterToolFormView::~CharacterToolFormView()
{
}

void CharacterToolFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CharacterToolFormView, CFormView)
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
