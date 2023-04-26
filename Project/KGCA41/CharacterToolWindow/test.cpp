// test.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "test.h"
#include "afxdialogex.h"


// test 대화 상자

IMPLEMENT_DYNAMIC(test, CDialogEx)

test::test(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

test::~test()
{
}

void test::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(test, CDialogEx)
END_MESSAGE_MAP()


// test 메시지 처리기
