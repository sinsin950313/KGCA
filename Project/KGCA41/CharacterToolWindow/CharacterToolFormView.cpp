// CharacterToolFormView.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "CharacterToolFormView.h"
#include "Common.h"


// CharacterToolFormView

IMPLEMENT_DYNCREATE(CharacterToolAnimationFormView, CFormView)

CharacterToolAnimationFormView::CharacterToolAnimationFormView()
	: CFormView(IDD_CharacterToolFormView)
{
}

CharacterToolAnimationFormView::~CharacterToolAnimationFormView()
{
}

void CharacterToolAnimationFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ActionNameEditBox, _actionName);
	DDX_Control(pDX, IDC_LastFrameEditBox2, _pivotFrame);
	DDX_Control(pDX, IDC_ActionListControl, _actionListControl);
}

BEGIN_MESSAGE_MAP(CharacterToolAnimationFormView, CFormView)
//	ON_WM_CREATE()
ON_BN_CLICKED(IDC_FrameCutButton, &CharacterToolAnimationFormView::OnBnClickedFramecutbutton)
ON_BN_CLICKED(IDC_FrameChangeButton, &CharacterToolAnimationFormView::OnBnClickedFramechangebutton)
ON_BN_CLICKED(IDC_ImportButton, &CharacterToolAnimationFormView::OnBnClickedImportbutton)
ON_BN_CLICKED(IDC_ExportButton, &CharacterToolAnimationFormView::OnBnClickedExportbutton)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_ActionListControl, &CharacterToolAnimationFormView::OnLvnItemchangedActionlistcontrol)
ON_BN_CLICKED(IDC_ActionAddButton, &CharacterToolAnimationFormView::OnBnClickedActionaddbutton)
ON_BN_CLICKED(IDC_ActionRemoveButton, &CharacterToolAnimationFormView::OnBnClickedActionremovebutton)
ON_BN_CLICKED(IDC_PIEButton, &CharacterToolAnimationFormView::OnBnClickedPiebutton)
END_MESSAGE_MAP()


CharacterToolAnimationFormView* CharacterToolAnimationFormView::CreateFormView(CWnd* parent)
{
	CharacterToolAnimationFormView* ret = new CharacterToolAnimationFormView;
	ret->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 300), parent, 0, NULL);
	return ret;
}

// CharacterToolFormView 진단

#ifdef _DEBUG
void CharacterToolAnimationFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CharacterToolAnimationFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CharacterToolFormView 메시지 처리기

void CharacterToolAnimationFormView::OnInitialUpdate()
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


void CharacterToolAnimationFormView::OnBnClickedFramecutbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	tool->SelectCurrentAction(std::string(CT2CA(_selectedActionName)));

	CString actionName;
	_actionName.GetWindowTextW(actionName);

	CString frame;
	_pivotFrame.GetWindowTextW(frame);

	tool->CutSelectedAnimataion(std::string(CT2CA(actionName)), _ttoi(frame));

	UpdateActionList();
}


void CharacterToolAnimationFormView::OnBnClickedFramechangebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	tool->SelectCurrentAction(std::string(CT2CA(_selectedActionName)));

	CString actionName;
	_actionName.GetWindowTextW(actionName);

	CString frame;
	_pivotFrame.GetWindowTextW(frame);

	tool->ChangeSelectedAnimationData(std::string(CT2CA(actionName)), _ttoi(frame));

	UpdateActionList();
}


void CharacterToolAnimationFormView::OnBnClickedImportbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	{
		CString str;
		_objectFileName.GetWindowTextW(str);
		tool->RegisterObjectFileName(std::string(CT2CA(str)));
	}
	tool->Import();

	UpdateActionList();
}


void CharacterToolAnimationFormView::OnBnClickedExportbutton()
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

void CharacterToolAnimationFormView::UpdateActionList()
{
	_actionListControl.DeleteAllItems();

	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	int index = 0;
	auto actionList = tool->GetActionList();
	for (auto action : actionList)
	{
		auto actionName = SSB::mtw(action.AnimationName);
		_actionListControl.InsertItem(index, actionName.c_str());
		_actionListControl.SetItem(index, 1, LVIF_TEXT, SSB::mtw(std::to_string(action.EndFrame)).c_str(), 0, 0, 0, NULL);
		++index;
	}
}


void CharacterToolAnimationFormView::OnLvnItemchangedActionlistcontrol(NMHDR* pNMHDR, LRESULT* pResult)
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
		((CCharacterToolWindowApp*)AfxGetApp())->GetLogic()->UpdateAnimation();
		((CCharacterToolWindowApp*)AfxGetApp())->GetLogic()->SetCurrentAnimation(std::string(CT2CA(_selectedActionName)));
	}
}


void CharacterToolAnimationFormView::OnBnClickedActionaddbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	CString str;
	CFileDialog dialog(FALSE, L"FBX", NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, L"FBX files(*.FBX)|*.FBX", this);
	if (dialog.DoModal() == IDOK)
	{
		str = dialog.GetFileName();
		tool->AddAction(std::string(CT2CA(str)));
	}

	UpdateActionList();
}


void CharacterToolAnimationFormView::OnBnClickedActionremovebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterTool* tool = ((CCharacterToolWindowApp*)AfxGetApp())->GetTool();

	tool->RemoveAction(std::string(CT2CA(_selectedActionName)));

	UpdateActionList();
}


void CharacterToolAnimationFormView::OnBnClickedPiebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterToolMainLogic* logic = ((CCharacterToolWindowApp*)AfxGetApp())->GetLogic();

	//logic->ChangePIEState();
}
