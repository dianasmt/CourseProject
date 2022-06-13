// CUserControlDlg.cpp : implementation file
//

#include "pch.h"
#include "CourceWorkApp.h"
#include "UserControl.h"
#include "Formatter.h"
#include "AddUser.h"
#include "afxdialogex.h"

#define INDEX_NAME 0
#define INDEX_TYPE 1

// CUserControlDlg dialog

IMPLEMENT_DYNAMIC(CUserControlDlg, CDialogEx)

CUserControlDlg::CUserControlDlg(ClientConnectionModule* pModule, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_USER_CONTROL, pParent)
{
	m_pModule = pModule;
}

CUserControlDlg::~CUserControlDlg()
{
}

BOOL CUserControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_wndReport.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_wndReport.InsertColumn(INDEX_NAME, L"Логин", 0, 120);
	m_wndReport.InsertColumn(INDEX_TYPE, L"Тип", 0, 70);

	PostMessage(MSG_UPDATE);
	return 0;
}

void CUserControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USERS, m_wndReport);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_wndBtnAdd);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_wndBtnDel);
}

BEGIN_MESSAGE_MAP(CUserControlDlg, CDialogEx)
	ON_MESSAGE_VOID(MSG_UPDATE, UpdatePage)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedDel)
END_MESSAGE_MAP()

BOOL CUserControlDlg::PreTranslateMessage(MSG* pMsg)
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

void CUserControlDlg::UpdatePage()
{
	m_Clients = m_pModule->getAllClient();
	m_Admins = m_pModule->getAllAdmin();
	m_Experts = m_pModule->getAllExpert();

	m_wndReport.DeleteAllItems();

	for (auto iter : m_Clients)
		AddToReport(AtoW(iter.getLogin()), L"Клиент");
	for (auto iter : m_Admins)
		AddToReport(AtoW(iter.getLogin()), L"Админ");
	for (auto iter : m_Experts)
		AddToReport(AtoW(iter.getLogin()), L"Эксперт");
}

void CUserControlDlg::AddToReport(CString login, CString type)
{
	CString strFormat;
	int index = m_wndReport.InsertItem(INDEX_NAME, login);
	m_wndReport.SetItemText(index, INDEX_TYPE, type);
}

void CUserControlDlg::OnBnClickedAdd()
{
	CAddUserDlg dlg(m_pModule);
	dlg.DoModal();
	UpdatePage();
}

void CUserControlDlg::OnBnClickedDel()
{
	auto pos = m_wndReport.GetFirstSelectedItemPosition();

	if (!pos)
		return;

	int index = m_wndReport.GetNextSelectedItem(pos);

	CString strLogin = m_wndReport.GetItemText(index, INDEX_NAME);
	CString strType = m_wndReport.GetItemText(index, INDEX_TYPE);

	if (strType == L"Клиент")
	{
		for (auto i : m_Clients)
		{
			if (i.getLogin() == WtoA(strLogin))
			{
				if (m_pModule->deleteClientWith(i.getLogin()) == AnswerFromServer::_ERROR)
				{
					MessageBox(L"Произошла ошибка");
				}
			}
		}
	}
	else if (strType == L"Эксперт")
	{
		for (auto i : m_Experts)
		{
			if (i.getLogin() == WtoA(strLogin))
			{
				if (m_pModule->deleteExpertWith(i.getLogin()) == AnswerFromServer::_ERROR)
				{
					MessageBox(L"Произошла ошибка");
				}
			}
		}
	}
	else
	{
		MessageBox(L"Вы не имеете прав удалять администраторов");
	}

	UpdatePage();
}


// CUserControlDlg message handlers
