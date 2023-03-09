#pragma once



// CharacterToolFormView 폼 보기

class CharacterToolAnimationFormView : public CFormView
{
	DECLARE_DYNCREATE(CharacterToolAnimationFormView)

public:
	static CharacterToolAnimationFormView* CreateFormView(CWnd* parent);

protected:
	CharacterToolAnimationFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CharacterToolAnimationFormView();

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
	CEdit _scriptFileName;
	CEdit _actionName;
	CEdit _pivotFrame;
	CListCtrl _actionListControl;
	CString _selectedActionName;

private:
	void UpdateActionList();

public:
	afx_msg void OnBnClickedFramecutbutton();
	afx_msg void OnBnClickedFramechangebutton();
	afx_msg void OnLvnItemchangedActionlistcontrol(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedActionaddbutton();
	afx_msg void OnBnClickedActionremovebutton();
	afx_msg void OnBnClickedPiebutton();
};


