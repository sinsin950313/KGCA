#pragma once


// MapCreationDialog 대화 상자

class MapCreationDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MapCreationDialog)

public:
	MapCreationDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MapCreationDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MapCreationDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString _componentEditorBox;
	CString _sectionEditorBox;
	CString _sizeEditorBox;
	afx_msg void OnBnClickedOk();
	CComboBox _textureDataComboBox;
};
