#include "pch.h"
#include "framework.h"
#include "CourceWorkApp.h"
#include "Menu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatternApp

BEGIN_MESSAGE_MAP(CCourceWorkApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Ñîçäàíèå CPatternApp

CCourceWorkApp::CCourceWorkApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

}



CCourceWorkApp theApp;

BOOL CCourceWorkApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	CShellManager* pShellManager = new CShellManager;

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("RegKey"));

	CMenuDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// Óäàëèòü äèñïåò÷åð îáîëî÷êè, ñîçäàííûé âûøå.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif


	return FALSE;
}

