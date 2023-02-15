#pragma once


// CharacterEditorDialog 대화 상자

class CharacterEditorDialog : public CFormView
{
	DECLARE_DYNAMIC(CharacterEditorDialog)

public:
	static CharacterEditorDialog* CreateFormView(CWnd* parent);

public:
	CharacterEditorDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CharacterEditorDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	virtual void OnFinalRelease();
	virtual void OnInitialUpdate();
};
