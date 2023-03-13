// SelectonEditorFormView.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "SelectonEditorFormView.h"
#include "Matrix.h"
#include "CharacterToolMainLogic.h"


// SelectonEditorFormView

IMPLEMENT_DYNCREATE(SelectonEditorFormView, CFormView)

SelectonEditorFormView::SelectonEditorFormView()
	: CFormView(IDD_SelectonEditorFormView)
{

}

SelectonEditorFormView::~SelectonEditorFormView()
{
}

void SelectonEditorFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BoneTree, BoneTreeListControl);
	DDX_Control(pDX, IDC_EDIT1, _x);
	DDX_Control(pDX, IDC_EDIT2, _y);
	DDX_Control(pDX, IDC_EDIT3, _z);
	DDX_Control(pDX, IDC_EDIT4, _yaw);
	DDX_Control(pDX, IDC_EDIT5, _pitch);
	DDX_Control(pDX, IDC_EDIT6, _roll);
	DDX_Control(pDX, IDC_EDIT7, _right);
	DDX_Control(pDX, IDC_EDIT8, _up);
	DDX_Control(pDX, IDC_EDIT9, _forward);
	DDX_Control(pDX, IDC_SocketName, _socketName);
}

HTREEITEM SelectonEditorFormView::Find(HTREEITEM hItem, SSB::BoneName name)
{
	HTREEITEM hFindItem = NULL;
	HTREEITEM  hChildItem = NULL;
	HTREEITEM  hSiblingItem = NULL;

	CString selectedBoneStr = BoneTreeListControl.GetItemText(hItem);
	if (std::string(CT2CA(selectedBoneStr)) == name)
	{
		hFindItem = hItem;
	}
	else
	{
		hChildItem = BoneTreeListControl.GetChildItem(hItem);
		if (BoneTreeListControl.ItemHasChildren(hItem))
		{
			if (hFindItem == NULL && hChildItem != NULL)
			{
				hFindItem = Find(hChildItem, name);
			}
		}

		hSiblingItem = BoneTreeListControl.GetNextSiblingItem(hItem);
		if (hFindItem == NULL && hSiblingItem != NULL)
		{
			hFindItem = Find(hSiblingItem, name);
		}
	}

	return hFindItem;
}

void SelectonEditorFormView::UpdateList()
{
	BoneTreeListControl.DeleteAllItems();

	int index = 0;
	std::map<SSB::BoneName, SSB::Bone> boneList = ((CCharacterToolWindowApp*)AfxGetApp())->GetLogic()->GetBones();
	for (auto bone : boneList)
	{
		TVINSERTSTRUCT insertStruct;
		insertStruct.hParent = Find(BoneTreeListControl.GetRootItem(), bone.first);
		BoneTreeListControl.InsertItem(&insertStruct);
	}
}

BEGIN_MESSAGE_MAP(SelectonEditorFormView, CFormView)
	//ON_NOTIFY(TVN_SELCHANGED, IDC_BoneTree, &SelectonEditorFormView::OnTvnSelchangedBonetree)
	ON_BN_CLICKED(IDC_CreateSocketButton, &SelectonEditorFormView::OnBnClickedCreatesocketbutton)
	ON_BN_CLICKED(IDC_AddSocketButton, &SelectonEditorFormView::OnBnClickedAddSocketButton)
END_MESSAGE_MAP()


// SelectonEditorFormView 진단

#ifdef _DEBUG
void SelectonEditorFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SelectonEditorFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SelectonEditorFormView 메시지 처리기


//void SelectonEditorFormView::OnTvnSelchangedBonetree(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	*pResult = 0;
//
//	if (pNMTreeView)
//	{
//		_selectedBoneName = BoneTreeListControl.GetItemText(pNMTreeView->itemNew.hItem);
//		((CCharacterToolWindowApp*)AfxGetApp())->GetLogic()->SetCurrentAnimation(std::string(CT2CA(_selectedBoneName)));
//	}
//}


void SelectonEditorFormView::OnBnClickedCreatesocketbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString xStr = L"0";
	CString yStr = L"0";
	CString zStr = L"0";
	CString yawStr = L"0";
	CString pitchStr = L"0";
	CString rollStr = L"0";
	CString rightStr = L"0";
	CString upStr = L"0";
	CString forwardStr = L"0";

	SSB::CharacterToolMainLogic* logic = ((CCharacterToolWindowApp*)AfxGetApp())->GetLogic();

	CString selectedParentItemStr;
	_parentIndex = logic->GetBoneIndex(std::string(CT2CA(selectedParentItemStr)));
	SSB::HMatrix44 parentMatrix = logic->GetBoneMatrix(_parentIndex);

	HTREEITEM hItem = BoneTreeListControl.GetSelectedItem();
	if (hItem != nullptr)
	{
		selectedParentItemStr = BoneTreeListControl.GetItemText(hItem);
		{
			CString tmp;
			_x.GetWindowTextW(xStr);
		}
		{
			CString tmp;
			_y.GetWindowTextW(yStr);
		}
		{
			CString tmp;
			_z.GetWindowTextW(zStr);
		}
		{
			CString tmp;
			_yaw.GetWindowTextW(yawStr);
		}
		{
			CString tmp;
			_pitch.GetWindowTextW(pitchStr);
		}
		{
			CString tmp;
			_roll.GetWindowTextW(rollStr);
		}
		{
			CString tmp;
			_right.GetWindowTextW(rightStr);
		}
		{
			CString tmp;
			_up.GetWindowTextW(upStr);
		}
		{
			CString tmp;
			_forward.GetWindowTextW(forwardStr);
		}
	}

	SSB::HMatrix44 S = {
		(float)_ttof(rightStr), 0, 0, 0,
		0, (float)_ttof(upStr), 0, 0,
		0, 0, (float)_ttof(forwardStr), 0,
		0, 0, 0, 1
	};

	SSB::HMatrix44 R = SSB::HMatrix44::RotateFromXAxis((float)_ttof(yawStr)) * SSB::HMatrix44::RotateFromYAxis((float)_ttof(pitchStr)) * SSB::HMatrix44::RotateFromZAxis((float)_ttof(rollStr));

	SSB::HMatrix44 T = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		(float)_ttof(xStr), (float)_ttof(yStr), (float)_ttof(zStr), 1
	};

	_socketMatrix = S * R * T;
	_socketMatrix = parentMatrix * _socketMatrix;

	logic->SetSocketViewerObjectMatrix(_socketMatrix);
}


void SelectonEditorFormView::OnBnClickedAddSocketButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString socketName;
	_socketName.GetWindowTextW(socketName);
	((CCharacterToolWindowApp*)AfxGetApp())->GetLogic()->AddSocket(std::string(CT2CA(socketName)), _parentIndex, _socketMatrix);

	UpdateList();
}
