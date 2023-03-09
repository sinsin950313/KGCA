#pragma once

#include "CharacterToolFormView.h"

// CharacterToolDockablePane

class CharacterToolDockablePane : public CDockablePane
{
	DECLARE_DYNAMIC(CharacterToolDockablePane)

private:
	CharacterToolAnimationFormView* _view;

public:
	CharacterToolDockablePane();
	virtual ~CharacterToolDockablePane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


