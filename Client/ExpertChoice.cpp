// CExpertMethodDlg.cpp : implementation file
//

#include "pch.h"
#include "CourceWorkApp.h"
#include "ExpertChoice.h"
#include "Formatter.h"
#include "afxdialogex.h"

#define INDEX_NAME    0
#define INDEX_MARK    1

// CExpertMethodDlg dialog

IMPLEMENT_DYNAMIC(CExpertMethodDlg, CDialogEx)

CExpertMethodDlg::CExpertMethodDlg(ClientConnectionModule* pModule, std::vector<Food>& lst, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EXPERT_CHOOSE_OBJ, pParent),
	m_Selected(lst)
{
	m_pModule = pModule;
}

CExpertMethodDlg::~CExpertMethodDlg()
{
}

void CExpertMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_wndReportCtrl);
	DDX_Control(pDX, IDC_BUTTON_NEXT2, m_wndBtnCancel);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_wndBtnNext);
}

BOOL CExpertMethodDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;                // Do not process further
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CExpertMethodDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_wndReportCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_wndReportCtrl.InsertColumn(INDEX_NAME, L"Название", 0, 220);
	m_wndReportCtrl.InsertColumn(INDEX_MARK, L"Оценка", 0, 80);

	PostMessage(MSG_UPDATE);
	return 0;
}

void CExpertMethodDlg::UpdatePage()
{
	m_Objects = m_pModule->getAllObj();
	if (m_Objects.size() < 4)
	{
		MessageBox(L"Недостаточно данных");
		OnOK();
	}
	m_wndReportCtrl.DeleteAllItems();

	for (auto iter : m_Objects)
	{
		AddToReport(iter);
	}
}


BEGIN_MESSAGE_MAP(CExpertMethodDlg, CDialogEx)
	ON_MESSAGE_VOID(MSG_UPDATE, UpdatePage)
	ON_BN_CLICKED(IDC_BUTTON_NEXT2, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnBnClickedNext)
END_MESSAGE_MAP()

void CExpertMethodDlg::AddToReport(Food& cloth)
{
	CString strFormat;
	int index = m_wndReportCtrl.InsertItem(INDEX_NAME, AtoW(cloth.GetName()));
	strFormat.Format(L"%0.2lf", cloth.GetMark());
	m_wndReportCtrl.SetItemText(index, INDEX_MARK, strFormat);
}

void CExpertMethodDlg::OnBnClickedNext()
{
	m_Selected.clear();

	if (m_wndReportCtrl.GetSelectedCount() != 4)
	{
		MessageBox(L"Нужно выбрать ровно 4 записи");
		return;
	}

	auto pos = m_wndReportCtrl.GetFirstSelectedItemPosition();

	for (int i = 0; i < 4; i++)
	{
		int index = m_wndReportCtrl.GetNextSelectedItem(pos);
		CString name = m_wndReportCtrl.GetItemText(index, INDEX_NAME);

		for (auto iter : m_Objects)
		{
			if (WtoA(name) == iter.GetName())
			{

				m_Selected.push_back(iter);
				break;
			}
		}
	}
	OnOK();
}

void CExpertMethodDlg::OnBnClickedCancel()
{
	m_Selected.clear();
	OnOK();
}

// CExpertMethodDlg message handlers
