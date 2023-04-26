#pragma once



// SelectonEditorFormView 폼 보기

class SelectonEditorFormView : public CFormView
{
	DECLARE_DYNCREATE(SelectonEditorFormView)

protected:
	SelectonEditorFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~SelectonEditorFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SelectonEditorFormView };
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

private:
	std::map<SSB::BoneName, SSB::BoneIndex> _boneNameToIndexMap;

public:
	static SelectonEditorFormView* CreateFormView(CWnd* parent);

private:
	HTREEITEM Find(HTREEITEM hItem, SSB::BoneName name);
	SSB::HMatrix44 GetSocketLocalMatrix();
	void UpdateList();

private:
	CTreeCtrl BoneTreeListControl;
	CEdit _x;
	CEdit _y;
	CEdit _z;
	CEdit _yaw;
	CEdit _pitch;
	CEdit _roll;
	CEdit _right;
	CEdit _up;
	CEdit _forward;
	CString _selectedBoneName;
	CEdit _socketName;

public:
	afx_msg void OnTvnSelchangedBonetree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedPreviewSocketButton();
	afx_msg void OnBnClickedCreatesocketbutton();

public:
	void CustomUpdateData();
};


