// CRegistrationDlg.cpp : implementation file
//

#include "pch.h"
#include "CourceWorkApp.h"
#include "Registration.h"
#include "afxdialogex.h"
#include <Formatter.h>

#define ALREADY_EXIST L"Аккаунт с таким логином уже существует"
#define PASSWORDS_NOT_SAME L"Пароли должны совпадать"
// CRegistrationDlg dialog

IMPLEMENT_DYNAMIC(CRegistrationDlg, CDialogEx)

CRegistrationDlg::CRegistrationDlg(CWnd* pParent)
	: CDialogEx(IDD_DIALOG_REGISTRATION, pParent)
{
	m_pModule = NULL;
	m_TypeOfUser = TypeOfUser::UNDEFINED;
}

CRegistrationDlg::~CRegistrationDlg()
{
}

void CRegistrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOGIN, m_wndLogin);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_wndPassword);
	DDX_Control(pDX, IDC_EDIT_CONFIRM_PASSWORD, m_wndPassRepeat);
	DDX_Control(pDX, IDC_BUTTON_REGISTRATION, m_wndBtnRegistration);
	DDX_Control(pDX, IDC_STATIC_ALLREADY_EXISTS, m_wndExistst);
}

BOOL CRegistrationDlg::PreTranslateMessage(MSG* pMsg)
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


BEGIN_MESSAGE_MAP(CRegistrationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REGISTRATION, OnBnClickRegistration)
END_MESSAGE_MAP()

BOOL CRegistrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_wndExistst.ShowWindow(SW_HIDE);

	return TRUE;
}

void CRegistrationDlg::OnBnClickRegistration()
{
	UpdateData(TRUE);
	UpdateData(FALSE);

	CString sLogin;
	m_wndLogin.GetWindowText(sLogin);
	CString sPass;
	m_wndPassword.GetWindowText(sPass);
	CString sRepeat;
	m_wndPassRepeat.GetWindowText(sRepeat);

	if (!sPass.Compare(sRepeat))
	{
		string login = WtoA(sLogin);
		string password = WtoA(sPass);
		auto answer = m_pModule->registration(TypeOfUser::CLIENT, login, password);
		switch (answer)
		{
		case AnswerFromServer::SUCCESSFULLY:
		{
			OnOK();
			m_TypeOfUser = TypeOfUser::CLIENT;
			break;
		}
		default:
			m_wndExistst.SetWindowText(ALREADY_EXIST);
			m_wndExistst.ShowWindow(SW_SHOW);
		}
	}
	else
	{
		m_wndExistst.SetWindowText(PASSWORDS_NOT_SAME);
		m_wndExistst.ShowWindow(SW_SHOW);
	}
}

TypeOfUser CRegistrationDlg::DoModal(ClientConnectionModule* pModule)
{
	m_pModule = pModule;

	CDialogEx::DoModal();

	return m_TypeOfUser;
}