#pragma once



// CharacterToolFormView 폼 보기

class CharacterToolFormView : public CFormView
{
	DECLARE_DYNCREATE(CharacterToolFormView)

public:
	static CharacterToolFormView* CreateFormView(CWnd* parent);

protected:
	CharacterToolFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CharacterToolFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CharacterToolFormView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

private:
	CEdit _objectFileName;
	CEdit _actionFileName;
	CEdit _scriptFileName;
	CEdit _actionName;
	CEdit _lastFrame;
	CListCtrl _actionListControl;

public:
	afx_msg void OnBnClickedObjectfilenamebutton();
	afx_msg void OnBnClickedActionfilenamebutton();
	afx_msg void OnBnClickedScriptfilenamebutton();
	afx_msg void OnBnClickedFramecutbutton();
	afx_msg void OnBnClickedFramechangebutton();
	afx_msg void OnBnClickedImportbutton();
	afx_msg void OnBnClickedExportbutton();

private:
	void UpdateActionList();
public:
	afx_msg void OnLvnItemchangedActionlistcontrol(NMHDR* pNMHDR, LRESULT* pResult);
};


