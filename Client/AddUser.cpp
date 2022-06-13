// CAddUserDlg.cpp : implementation file
//

#include "pch.h"
#include "CourceWorkApp.h"
#include "AddUser.h"
#include "Formatter.h"
#include "afxdialogex.h"


// CAddUserDlg dialog

IMPLEMENT_DYNAMIC(CAddUserDlg, CDialogEx)

CAddUserDlg::CAddUserDlg(ClientConnectionModule* pModule, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_USER, pParent)
{
	m_pModule = pModule;
}

CAddUserDlg::~CAddUserDlg()
{
}

void CAddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOGIN, m_wndEditLogin);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_wndEditPassword);
	DDX_Control(pDX, IDC_EDIT_REPEAT_PASSWORD, m_wndEditRepeat);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_wndComboType);
	DDX_Control(pDX, IDC_STATIC_INCORRECT_PASSWORD, m_wndPassIncorrect);
	DDX_Control(pDX, IDC_STATIC_ALREADY_EXIST, m_wndAlreadyExist);
}


BEGIN_MESSAGE_MAP(CAddUserDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CAddUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_wndAlreadyExist.ShowWindow(SW_HIDE);
	m_wndPassIncorrect.ShowWindow(SW_HIDE);
	m_wndComboType.AddString(L"Клиент");
	m_wndComboType.AddString(L"Эксперт");
	m_wndComboType.AddString(L"Админ");
	m_wndComboType.SetCurSel(0);

	return TRUE;
}

// CAddUserDlg message handlers

BOOL CAddUserDlg::PreTranslateMessage(MSG* pMsg)
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


void CAddUserDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
	m_wndPassIncorrect.ShowWindow(SW_HIDE);
	m_wndAlreadyExist.ShowWindow(SW_HIDE);
	CString sLogin;
	m_wndEditLogin.GetWindowText(sLogin);
	CString sPass;
	m_wndEditPassword.GetWindowText(sPass);
	CString sRepeat;
	m_wndEditRepeat.GetWindowText(sRepeat);

	if (!sPass.Compare(sRepeat))
	{
		string login = WtoA(sLogin);
		string password = WtoA(sPass);

		TypeOfUser type = TypeOfUser::CLIENT;
		int index = m_wndComboType.GetCurSel();
		CString str;
		m_wndComboType.GetLBText(index, str);

		AnswerFromServer answer;
		if (str == L"Админ")answer = m_pModule->registerNewAdmin(login, password);
		if (str == L"Эксперт")answer = m_pModule->registerNewExpert(login, password, 1);
		if (str == L"Клиент")answer = m_pModule->registerNewClient(login, password);

		switch (answer)
		{
		case AnswerFromServer::SUCCESSFULLY:
		{
			OnOK();
			break;
		}
		default:
			m_wndAlreadyExist.ShowWindow(SW_SHOW);
		}
	}
	else
	{
		m_wndPassIncorrect.ShowWindow(SW_SHOW);
	}
	CDialogEx::OnOK();
}
