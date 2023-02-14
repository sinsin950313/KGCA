#pragma once

#include "CharacterToolFormView.h"

// CharacterToolDockablePane

class CharacterToolDockablePane : public CDockablePane
{
private:
	CharacterToolFormView* _view;

	DECLARE_DYNAMIC(CharacterToolDockablePane)

public:
	CharacterToolDockablePane();
	virtual ~CharacterToolDockablePane();

protected:
	DECLARE_MESSAGE_MAP()
};


