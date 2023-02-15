#pragma once


// CharacterToolDialog 대화 상자

class CharacterToolDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CharacterToolDialog)

public:
	CharacterToolDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CharacterToolDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CharacterToolDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
