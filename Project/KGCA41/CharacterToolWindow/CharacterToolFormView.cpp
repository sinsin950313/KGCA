// CharacterToolFormView.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "CharacterToolFormView.h"
#include "Common.h"


// CharacterToolFormView

IMPLEMENT_DYNCREATE(CharacterToolFormView, CFormView)

CharacterToolFormView::CharacterToolFormView()
	: CFormView(IDD_CharacterToolFormView)
{
}

CharacterToolFormView::~CharacterToolFormView()
{
}

void CharacterToolFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ObjectFileNameEditBox, _objectFileName);
	DDX_Control(pDX, IDC_ActionFileNameEditBox, _actionFileName);
	DDX_Control(pDX, IDC_ScriptFileNameEditBox, _scriptFileName);
	DDX_Control(pDX, IDC_ActionNameEditBox, _actionName);
	DDX_Control(pDX, IDC_LastFrameEditBox2, _lastFrame);
	DDX_Control(pDX, IDC_ActionListControl, _actionListControl);
}

BEGIN_MESSAGE_MAP(CharacterToolFormView, CFormView)
//	ON_WM_CREATE()
ON_BN_CLICKED(IDC_ObjectFileNameButton, &CharacterToolFormView::OnBnClickedObjectfilenamebutton)
ON_BN_CLICKED(IDC_ActionFileNameButton, &CharacterToolFormView::OnBnClickedActionfilenamebutton)
ON_BN_CLICKED(IDC_ScriptFileNameButton, &CharacterToolFormView::OnBnClickedScriptfilenamebutton)
ON_BN_CLICKED(IDC_FrameCutButton, &CharacterToolFormView::OnBnClickedFramecutbutton)
ON_BN_CLICKED(IDC_FrameChangeButton, &CharacterToolFormView::OnBnClickedFramechangebutton)
ON_BN_CLICKED(IDC_ImportButton, &CharacterToolFormView::OnBnClickedImportbutton)
ON_BN_CLICKED(IDC_ExportButton, &CharacterToolFormView::OnBnClickedExportbutton)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_ActionListControl, &CharacterToolFormView::OnLvnItemchangedActionlistcontrol)
ON_BN_CLICKED(IDC_ActionAddButton, &CharacterToolFormView::OnBnClickedActionaddbutton)
ON_BN_CLICKED(IDC_ActionRemoveButton, &CharacterToolFormView::OnBnClickedActionremovebutton)
END_MESSAGE_MAP()


CharacterToolFormView* CharacterToolFormView::CreateFormView(CWnd* parent)
{
	CharacterToolFormView* ret = new CharacterToolFormView;
	ret->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 300), parent, 0, NULL);
	return ret;
}

// CharacterToolFormView 진단

#ifdef _DEBUG
void CharacterToolFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CharacterToolFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CharacterToolFormView 메시지 처리기

void CharacterToolFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CRect rcClient;
	GetClientRect(&rcClient);
	GetParentFrame()->RecalcLayout();
	SetScaleToFitSize(rcClient.Size());

	_actionListControl.InsertColumn(0, L"Action Name", LVCFMT_CENTER, 100, -1);
	_actionListControl.InsertColumn(1, L"Total Frame", LVCFMT_CENTER, 100, -1);
}


void CharacterToolFormView::OnBnClickedObjectfilenamebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dialog(FALSE, L"FBX", NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, L"FBX files(*.FBX)|*.FBX", this);
	if (dialog.DoModal() == IDOK)
	{
		_objectFileName.SetWindowTextW(dialog.GetFileName());
	}
}


void CharacterToolFormView::OnBnClickedActionfilenamebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dialog(FALSE, L"FBX", NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, L"FBX files(*.FBX)|*.FBX", this);
	if (dialog.DoModal() == IDOK)
	{
		_actionFileName.SetWindowTextW(dialog.GetFileName());
	}
}


void CharacterToolFormView::OnBnClickedScriptfilenamebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dialog(FALSE, L"FBXScript", NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, L"FBXScript files(*.FBXScript)|*.FBXScript", this);
	if (dialog.DoModal() == IDOK)
	{
		_scriptFileName.SetWindowTextW(dialog.GetFileName());
	}
}


void CharacterToolFormView::OnBnClickedFramecutbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	tool->SelectCurrentAction(std::string(CT2CA(_selectedActionName)));

	CString actionName;
	_actionName.GetWindowTextW(actionName);

	CString frame;
	_lastFrame.GetWindowTextW(frame);

	tool->CutAnimataion(std::string(CT2CA(actionName)), _ttoi(frame));

	UpdateActionList();
}


void CharacterToolFormView::OnBnClickedFramechangebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	tool->SelectCurrentAction(std::string(CT2CA(_selectedActionName)));

	CString actionName;
	_actionName.GetWindowTextW(actionName);

	CString frame;
	_lastFrame.GetWindowTextW(frame);

	tool->ChangeSelectedActionData(std::string(CT2CA(actionName)), _ttoi(frame));

	UpdateActionList();
}


void CharacterToolFormView::OnBnClickedImportbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	{
		CString str;
		_objectFileName.GetWindowTextW(str);
		tool->RegisterObjectFileName(std::string(CT2CA(str)));
	}
	{
		CString str;
		_actionFileName.GetWindowTextW(str);
		tool->RegisterActionFileName(std::string(CT2CA(str)));
	}
	{
		CString str;
		_scriptFileName.GetWindowTextW(str);
		tool->RegisterScriptFileName(std::string(CT2CA(str)));
	}
	tool->Import();

	UpdateActionList();
}


void CharacterToolFormView::OnBnClickedExportbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	{
		CString str;
		_scriptFileName.GetWindowTextW(str);
		tool->RegisterScriptFileName(std::string(CT2CA(str)));
	}
	tool->Export();
}

void CharacterToolFormView::UpdateActionList()
{
	_actionListControl.DeleteAllItems();

	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	int index = 0;
	auto actionList = tool->GetActionList();
	for (auto action : actionList)
	{
		auto actionName = SSB::mtw(action.ActionName);
		_actionListControl.InsertItem(index, actionName.c_str());
		_actionListControl.SetItem(index, 1, LVIF_TEXT, SSB::mtw(std::to_string(action.EndFrame)).c_str(), 0, 0, 0, NULL);
		++index;
	}
}


void CharacterToolFormView::OnLvnItemchangedActionlistcontrol(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (pNMLV && (pNMLV->uNewState == (UINT)(LVIS_FOCUSED | LVIS_SELECTED)))
	{
		int index = pNMLV->iItem;
		_selectedActionName = _actionListControl.GetItemText(index, 0);
		SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();
		tool->SelectCurrentAction(std::string(CT2CA(_selectedActionName)));
	}
}


void CharacterToolFormView::OnBnClickedActionaddbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	CString str;
	_actionFileName.GetWindowTextW(str);
	tool->AddAction(std::string(CT2CA(str)));

	UpdateActionList();
}


void CharacterToolFormView::OnBnClickedActionremovebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	tool->RemoveAction(std::string(CT2CA(_selectedActionName)));

	UpdateActionList();
}
