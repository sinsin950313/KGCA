// SelectonEditorFormView.cpp: 구현 파일
//

#include "pch.h"
#include "CharacterToolWindow.h"
#include "SelectonEditorFormView.h"
#include "Matrix.h"
#include "CharacterToolMainLogic.h"
#include "Common.h"


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

SelectonEditorFormView* SelectonEditorFormView::CreateFormView(CWnd* parent)
{
	SelectonEditorFormView* ret = new SelectonEditorFormView;
	ret->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 300), parent, 0, NULL);
	return ret;
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

SSB::HMatrix44 SelectonEditorFormView::GetSocketLocalMatrix()
{
	float x, y, z, yaw, pitch, roll, right, up, forward;

	{
		CString tmp;
		_x.GetWindowTextW(tmp);

		x = (float)_ttof(tmp);
		if (tmp.IsEmpty())
		{
			x = 0.0f;
		}
	}
	{
		CString tmp;
		_y.GetWindowTextW(tmp);

		y = (float)_ttof(tmp);
		if (tmp.IsEmpty())
		{
			y = 0.0f;
		}
	}
	{
		CString tmp;
		_z.GetWindowTextW(tmp);

		z = (float)_ttof(tmp);
		if (tmp.IsEmpty())
		{
			z = 0.0f;
		}
	}
	{
		CString tmp;
		_yaw.GetWindowTextW(tmp);

		yaw = (float)_ttof(tmp);
		if (tmp.IsEmpty())
		{
			yaw = 0.0f;
		}
	}
	{
		CString tmp;
		_pitch.GetWindowTextW(tmp);

		pitch = (float)_ttof(tmp);
		if (tmp.IsEmpty())
		{
			pitch = 0.0f;
		}
	}
	{
		CString tmp;
		_roll.GetWindowTextW(tmp);

		roll = (float)_ttof(tmp);
		if (tmp.IsEmpty())
		{
			roll = 0.0f;
		}
	}
	{
		CString tmp;
		_right.GetWindowTextW(tmp);

		right = (float)_ttof(tmp);
		if (tmp.IsEmpty())
		{
			right = 1.0f;
		}
	}
	{
		CString tmp;
		_up.GetWindowTextW(tmp);

		up = (float)_ttof(tmp);
		if (tmp.IsEmpty())
		{
			up = 1.0f;
		}
	}
	{
		CString tmp;
		_forward.GetWindowTextW(tmp);

		forward = (float)_ttof(tmp);
		if (tmp.IsEmpty())
		{
			forward = 1.0f;
		}
	}

	SSB::HMatrix44 S = {
		right, 0, 0, 0,
		0, up, 0, 0,
		0, 0, forward, 0,
		0, 0, 0, 1
	};

	SSB::HMatrix44 R = SSB::HMatrix44::RotateFromXAxis(yaw) * SSB::HMatrix44::RotateFromYAxis(pitch) * SSB::HMatrix44::RotateFromZAxis(roll);

	SSB::HMatrix44 T = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	};

	SSB::HMatrix44 socketMatrix = S * R * T;

	return socketMatrix;
}

void SelectonEditorFormView::UpdateList()
{
	BoneTreeListControl.DeleteAllItems();
	_boneNameToIndexMap.clear();

	int index = 0;
	std::map<SSB::BoneIndex, SSB::BoneInfo> boneList = ((CCharacterToolWindowApp*)AfxGetApp())->GetLogic()->GetBones();
	for (auto bone : boneList)
	{
		TVINSERTSTRUCT insertStruct;
		auto parentIter = boneList.find(bone.second.ParentIndex);
		if (parentIter != boneList.end())
		{
			insertStruct.hParent = Find(BoneTreeListControl.GetRootItem(), parentIter->second.Name);
			BoneTreeListControl.InsertItem(SSB::mtw(bone.second.Name).c_str(), insertStruct.hParent, NULL);
		}
		else
		{
			BoneTreeListControl.InsertItem(SSB::mtw(bone.second.Name).c_str(), NULL, NULL);
		}

		_boneNameToIndexMap.insert(std::make_pair(bone.second.Name, bone.first));
	}

	HTREEITEM hItem;
	HTREEITEM hCurrent;

	hItem = BoneTreeListControl.GetFirstVisibleItem();
	while (hItem != NULL)
	{
		BoneTreeListControl.Expand(hItem, TVE_EXPAND);
		hItem = BoneTreeListControl.GetNextItem(hItem, TVGN_NEXTVISIBLE);
	}
}

BEGIN_MESSAGE_MAP(SelectonEditorFormView, CFormView)
	ON_NOTIFY(TVN_SELCHANGED, IDC_BoneTree, &SelectonEditorFormView::OnTvnSelchangedBonetree)
	ON_BN_CLICKED(IDC_CreateSocketButton, &SelectonEditorFormView::OnBnClickedCreatesocketbutton)
	ON_BN_CLICKED(IDC_AddSocketButton, &SelectonEditorFormView::OnBnClickedPreviewSocketButton)
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


void SelectonEditorFormView::OnTvnSelchangedBonetree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (pNMTreeView)
	{
		_selectedBoneName = BoneTreeListControl.GetItemText(pNMTreeView->itemNew.hItem);
	}
}


void SelectonEditorFormView::OnBnClickedCreatesocketbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	SSB::CharacterToolMainLogic* logic = ((CCharacterToolWindowApp*)AfxGetApp())->GetLogic();

	CString socketName;
	_socketName.GetWindowTextW(socketName);

	SSB::BoneName socketBoneName = std::string(CT2CA(socketName));
	SSB::BoneName parentBoneName = std::string(CT2CA(_selectedBoneName));
	SSB::BoneIndex parentBoneIndex = -1;
	if (_boneNameToIndexMap.find(parentBoneName) != _boneNameToIndexMap.end())
	{
		parentBoneIndex = _boneNameToIndexMap.find(parentBoneName)->second;
	}
	logic->AddSocket(socketBoneName, parentBoneIndex, GetSocketLocalMatrix());
	logic->SetCurrentSocket(socketBoneName);

	UpdateList();
}

void SelectonEditorFormView::CustomUpdateData()
{
	UpdateList();
}


void SelectonEditorFormView::OnBnClickedPreviewSocketButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SSB::CharacterToolMainLogic* logic = ((CCharacterToolWindowApp*)AfxGetApp())->GetLogic();

	SSB::HMatrix44 socketWorldMatrix = GetSocketLocalMatrix();

	SSB::BoneName boneName = std::string(CT2CA(_selectedBoneName));
	if (_boneNameToIndexMap.find(boneName) != _boneNameToIndexMap.end())
	{
		SSB::HMatrix44 parentWorldMatrix = logic->GetBoneWorldMatrix(_boneNameToIndexMap.find(boneName)->second);
		socketWorldMatrix = socketWorldMatrix * parentWorldMatrix;
	}
	logic->SetSocketViewerObjectMatrix(socketWorldMatrix);
	logic->SetCurrentSocket(boneName);
}
