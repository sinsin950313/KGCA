// MapCreationDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ToolBase.h"
#include "MapCreationDialog.h"
#include "afxdialogex.h"


// MapCreationDialog 대화 상자

IMPLEMENT_DYNAMIC(MapCreationDialog, CDialogEx)

MapCreationDialog::MapCreationDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MapCreationDialog, pParent)
	, _componentEditorBox(_T(""))
	, _sectionEditorBox(_T(""))
	, _sizeEditorBox(_T(""))
{

}

MapCreationDialog::~MapCreationDialog()
{
}

void MapCreationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MapCreationComponentEditorBox, _componentEditorBox);
	DDX_Text(pDX, IDC_MapCreationSectionEditorBox, _sectionEditorBox);
	DDX_Text(pDX, IDC_MapCreationSizeEditorBox, _sizeEditorBox);
	DDX_Control(pDX, IDC_TextureDataComboBox, _textureDataComboBox);
}


BEGIN_MESSAGE_MAP(MapCreationDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &MapCreationDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// MapCreationDialog 메시지 처리기


BOOL MapCreationDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	_componentEditorBox = L"10";
	_sectionEditorBox = L"20";
	_sizeEditorBox = L"30";
	_textureDataComboBox.AddString(L"1");
	_textureDataComboBox.AddString(L"2");
	_textureDataComboBox.AddString(L"4");
	_textureDataComboBox.AddString(L"8");
	_textureDataComboBox.AddString(L"16");
	_textureDataComboBox.SetCurSel(3);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MapCreationDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();

	CToolBaseApp* app = (CToolBaseApp*)AfxGetApp();
	app->ComponentSize = _componentEditorBox;
	app->Section = _sectionEditorBox;
	app->SectionSize = _sizeEditorBox;
	app->TextureData = _textureDataComboBox.GetCurSel();
	UpdateData(TRUE);
}
