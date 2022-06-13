#include "pch.h"
#include "framework.h"
#include "CourceWorkApp.h"
#include "Menu.h"
#include "afxdialogex.h"
#include "ProductControl.h"
#include "UserControl.h"
#include "ExpertChoice.h"
#include "ExpertMethod.h"
#include "Authorization.h"
#include "Registration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_START 6666

CMenuDlg::CMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PATTERN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nTypeOfUser = TypeOfUser::UNDEFINED;
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_PRODUCTS_CONTROL, m_wndBtnProduct);
	DDX_Control(pDX, IDC_BUTTON_USER_CONTROL, m_wndBtnUser);
	DDX_Control(pDX, IDC_BUTTON_EXPERT_METHOD, m_wndBtnExpert);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_wndBtnExit);
}

BEGIN_MESSAGE_MAP(CMenuDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PRODUCTS_CONTROL, OnBtnProductClck)
	ON_BN_CLICKED(IDC_BUTTON_USER_CONTROL, OnBtnUserClck)
	ON_BN_CLICKED(IDC_BUTTON_EXPERT_METHOD, OnBtnExpertClck)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnBtnExitClck)
	ON_MESSAGE_VOID(ID_START, OnStart)
END_MESSAGE_MAP()


BOOL CMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	m_pConnectionModule = new ClientConnectionModule();
	//m_pConnectionModule->registration(TypeOfUser::ADMIN, "admin", "admin");

	PostMessage(ID_START);

	return TRUE;
}

void CMenuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

CMenuDlg::~CMenuDlg()
{
	delete m_pConnectionModule;
}

HCURSOR CMenuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMenuDlg::OnBtnProductClck()
{
	CProductCtrlDlg dlg(m_pConnectionModule, m_nTypeOfUser);
	dlg.DoModal();
}

void CMenuDlg::OnBtnUserClck()
{
	CUserControlDlg dlg(m_pConnectionModule);
	dlg.DoModal();
}

void CMenuDlg::OnBtnExpertClck()
{
	std::vector<Food> dishes;
	CExpertMethodDlg dlg(m_pConnectionModule, dishes);
	dlg.DoModal();

	if (dishes.size() == 4)
	{
		CExpDlg dlgExp(dishes);
		dlgExp.DoModal();
		for (auto i : dishes)
		{
			m_pConnectionModule->editOneObj(i);
		}
	}
}

void CMenuDlg::OnBtnExitClck()
{
	PostMessage(WM_CLOSE);
}

void CMenuDlg::OnStart()
{
	CAuthorizationDlg dlg(this);
	m_nTypeOfUser = dlg.DoModal(m_pConnectionModule);

	if (m_nTypeOfUser == TypeOfUser::REGISTRATION)
	{
		CRegistrationDlg regDlg;
		m_nTypeOfUser = regDlg.DoModal(m_pConnectionModule);
	}

	switch (m_nTypeOfUser)
	{
	case TypeOfUser::UNDEFINED:
		PostMessage(WM_CLOSE);
		break;
	case TypeOfUser::ADMIN:
		m_wndBtnExpert.EnableWindow(FALSE);
		break;
	case TypeOfUser::CLIENT:
		m_wndBtnUser.EnableWindow(FALSE);
		m_wndBtnExpert.EnableWindow(FALSE);
		break;
	case TypeOfUser::EXPERT:
		m_wndBtnUser.EnableWindow(FALSE);
		break;
	}
}

BOOL CMenuDlg::PreTranslateMessage(MSG* pMsg)
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


