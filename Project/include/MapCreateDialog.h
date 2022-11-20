#pragma once


// MapCreateDialog 대화 상자

class MapCreateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MapCreateDialog)

public:
	MapCreateDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MapCreateDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
