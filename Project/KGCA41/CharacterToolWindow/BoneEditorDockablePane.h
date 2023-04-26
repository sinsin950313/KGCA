#pragma once

#include "SelectonEditorFormView.h"

// BoneEditorDockablePane

class BoneEditorDockablePane : public CDockablePane
{
	DECLARE_DYNAMIC(BoneEditorDockablePane)

private:
	SelectonEditorFormView* _boneEditorView;

public:
	BoneEditorDockablePane();
	virtual ~BoneEditorDockablePane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);

public:
	void CustomUpdateData();
};


