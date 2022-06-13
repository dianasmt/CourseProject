// CAuthorizationDlg.cpp : implementation file
//

#include "pch.h"
#include "CourceWorkApp.h"
#include "Formatter.h"
#include "Authorization.h"
#include "Registration.h"
#include "afxdialogex.h"

// CAuthorizationDlg dialog

IMPLEMENT_DYNAMIC(CAuthorizationDlg, CDialogEx)

CAuthorizationDlg::CAuthorizationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AUTHORIZATION, pParent)
{
	m_pModule = NULL;
	m_TypeOfUser = TypeOfUser::UNDEFINED;
}

CAuthorizationDlg::~CAuthorizationDlg()
{
}

void CAuthorizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_INCORRECT_CREDENTIALS, m_wndIncorect);
	DDX_Control(pDX, IDC_EDIT_LOGIN, m_wndLogin);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_wndPassword);
	DDX_Control(pDX, IDC_BUTTON_ENTER, m_wndBtnAuthorization);
	DDX_Control(pDX, IDC_MFCLINK_REGISTRATION, m_wndLnkRegistration);
}

BEGIN_MESSAGE_MAP(CAuthorizationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ENTER, OnBnClickAuthorization)
	ON_BN_CLICKED(IDC_MFCLINK_REGISTRATION, OnBnClickRegistration)
END_MESSAGE_MAP()

BOOL CAuthorizationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_wndIncorect.ShowWindow(SW_HIDE);

	return TRUE;
}

// CAuthorizationDlg message handlers

BOOL CAuthorizationDlg::PreTranslateMessage(MSG* pMsg)
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

void CAuthorizationDlg::OnBnClickAuthorization()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
	CString sLogin;
	m_wndLogin.GetWindowText(sLogin);
	CString sPass;
	m_wndPassword.GetWindowText(sPass);

	m_TypeOfUser = m_pModule->authorization(WtoA(sLogin), WtoA(sPass));

	switch (m_TypeOfUser)
	{
	case TypeOfUser::ADMIN:
	case TypeOfUser::CLIENT:
	case TypeOfUser::EXPERT:
	{
		OnOK();
		break;
	}
	case TypeOfUser::UNDEFINED:
	{
		m_wndIncorect.ShowWindow(SW_SHOW);
		break;
	}
	}
}

TypeOfUser CAuthorizationDlg::DoModal(ClientConnectionModule* pModule)
{
	m_pModule = pModule;

	CDialogEx::DoModal();

	return m_TypeOfUser;
}

void CAuthorizationDlg::OnBnClickRegistration()
{
	m_TypeOfUser = TypeOfUser::REGISTRATION;
	OnOK();
}