// CharacterEditorDialog.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "CharacterEditorDialog.h"
#include "afxdialogex.h"


// CharacterEditorDialog 대화 상자

IMPLEMENT_DYNAMIC(CharacterEditorDialog, CFormView)

CharacterEditorDialog* CharacterEditorDialog::CreateFormView(CWnd* parent)
{
	CharacterEditorDialog* ret = new CharacterEditorDialog;
	ret->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 300), parent, 0, NULL);
	return ret;
}

CharacterEditorDialog::CharacterEditorDialog(CWnd* pParent /*=nullptr*/)
	: CFormView(IDD_DIALOG1)
{

}

CharacterEditorDialog::~CharacterEditorDialog()
{
}

void CharacterEditorDialog::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CharacterEditorDialog, CFormView)
END_MESSAGE_MAP()


// CharacterEditorDialog 메시지 처리기


void CharacterEditorDialog::AssertValid() const
{
	CFormView::AssertValid();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CharacterEditorDialog::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CharacterEditorDialog::OnFinalRelease()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CFormView::OnFinalRelease();
}


void CharacterEditorDialog::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
