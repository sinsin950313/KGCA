// CharacterToolDialog.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "CharacterToolDialog.h"
#include "afxdialogex.h"


// CharacterToolDialog 대화 상자

IMPLEMENT_DYNAMIC(CharacterToolDialog, CDialogEx)

CharacterToolDialog::CharacterToolDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CharacterToolDialog, pParent)
{

}

CharacterToolDialog::~CharacterToolDialog()
{
}

void CharacterToolDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CharacterToolDialog, CDialogEx)
END_MESSAGE_MAP()


// CharacterToolDialog 메시지 처리기
