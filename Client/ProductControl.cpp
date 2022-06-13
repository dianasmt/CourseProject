// CProductCtrlDlg.cpp : implementation file
//

#include "pch.h"
#include "CourceWorkApp.h"
#include "ProductControl.h"
#include "afxdialogex.h"
#include "../SerializableEntities/Object.h"
#include "Formatter.h"
#include <fstream>
#include <iomanip>

#define INDEX_NAME			 0
#define INDEX_TYPE			 1
#define INDEX_COST			 2
#define INDEX_MARK			 3
#define INDEX_DESCRIPTION	 4

// CProductCtrlDlg dialog

IMPLEMENT_DYNAMIC(CProductCtrlDlg, CDialogEx)

CProductCtrlDlg::CProductCtrlDlg(ClientConnectionModule* pModule, TypeOfUser type, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PRODUCT_CONTROL, pParent)
{
	m_pModule = pModule;
	m_TypeOfUser = type;

	nMinFirst = -1;
	nMaxFirst = -1;
	dMinMark = -1.0;
	dMaxMark = -1.0;
}

CProductCtrlDlg::~CProductCtrlDlg()
{
}

BOOL CProductCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_wndReportCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_wndReportCtrl.InsertColumn(INDEX_NAME, L"Название поставщика", 0, 220);
	m_wndReportCtrl.InsertColumn(INDEX_TYPE, L"Тип зерна", 0, 150);
	m_wndReportCtrl.InsertColumn(INDEX_COST, L"Стоимость, руб.", 0, 80);
	m_wndReportCtrl.InsertColumn(INDEX_DESCRIPTION, L"Описание", 0, 150);
	m_wndReportCtrl.InsertColumn(INDEX_MARK, L"Оценка", 0, 56);

	PostMessage(MSG_UPDATE);
	return 0;
}

void CProductCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PRODUCTS, m_wndReportCtrl);

	DDX_Control(pDX, IDC_BUTTON_FILTER_APPLY, m_wndBtnApplyFilter);
	DDX_Control(pDX, IDC_BUTTON_SEARCH_APPLY, m_wndBtnApplySearch);

	DDX_Control(pDX, IDC_BUTTON_ADD, m_wndBtnAdd);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_wndBtnDel);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_wndBtnEdit);
	DDX_Control(pDX, IDC_BUTTON_REPORT, m_wndBtnReport);

	DDX_Control(pDX, IDC_EDIT_F_FIRST_FROM, m_wndEdit1From);
	DDX_Control(pDX, IDC_EDIT_F_FIRST_TO, m_wndEdit1To);
	DDX_Control(pDX, IDC_EDIT_F_MARK_FROM, m_wndEditMarkFrom);
	DDX_Control(pDX, IDC_EDIT_F_MARK_TO, m_wndEditMarkTo);

	DDX_Control(pDX, IDC_EDIT_S_NAME, m_wndEditFilterName);
	DDX_Control(pDX, IDC_EDIT_S_TYPE, m_wndEditFilterType);

	DDX_Control(pDX, IDC_EDIT_A_NAME, m_wndEditNameA);
	DDX_Control(pDX, IDC_EDIT_A_TYPE, m_wndEditTypeA);
	DDX_Control(pDX, IDC_EDIT_A_FIRST, m_wndEditFirstA);
	DDX_Control(pDX, IDC_EDIT_A_DESCRIPTION, m_wndEditDescriptionA);

	DDX_Control(pDX, IDC_EDIT_E_NAME, m_wndEditNameE);
	DDX_Control(pDX, IDC_EDIT_E_TYPE, m_wndEditTypeE);
	DDX_Control(pDX, IDC_EDIT_E_FIRST, m_wndEditFirstE);
	DDX_Control(pDX, IDC_EDIT_E_DESCRIPTION, m_wndEditDescriptionE);

}

BEGIN_MESSAGE_MAP(CProductCtrlDlg, CDialogEx)
	ON_MESSAGE_VOID(MSG_UPDATE, UpdatePage)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnBnClickedEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedDel)
	ON_BN_CLICKED(IDC_BUTTON_FILTER_APPLY, OnBnClickedFilter)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_APPLY, OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnBnClickedReport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PRODUCTS, &CProductCtrlDlg::OnLvnItemchangedListProducts)
	ON_BN_CLICKED(IDC_BUTTON_SORT_NAME, &CProductCtrlDlg::OnBnClickedButtonSortName)
	ON_BN_CLICKED(IDC_BUTTON_SORT_COST, &CProductCtrlDlg::OnBnClickedButtonSortCost)
END_MESSAGE_MAP()

void CProductCtrlDlg::UpdatePage()
{
	for (auto pWnd : { &m_wndEditNameA ,&m_wndEditTypeA ,&m_wndEditFirstA
						,& m_wndEditDescriptionA ,& m_wndEditNameE ,& m_wndEditTypeE
						,& m_wndEditFirstE ,& m_wndEditDescriptionE })
	{
		pWnd->EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);
	}
	m_wndBtnAdd.EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);
	m_wndBtnEdit.EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);
	m_wndBtnDel.EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);

	m_Objects = m_pModule->getAllObj();
	vector<Food> vec;
	for (auto i : m_Objects)
	{
		vec.push_back(i);
	}

	if (bSortedName)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			for (int j = i; j < vec.size(); j++)
			{
				if (bSortedNameUp && strcmp(vec[i].GetName().c_str(), vec[j].GetName().c_str()) == -1)
				{
					swap(vec[i], vec[j]);
				}
				else if (!bSortedNameUp && strcmp(vec[i].GetName().c_str(), vec[j].GetName().c_str()) == 1)
				{
					swap(vec[i], vec[j]);
				}
			}
		}
	}
	else if (bSortedCost)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			for (int j = i; j < vec.size(); j++)
			{
				if (bSortedCostUp && vec[i].GetCost() < vec[j].GetCost())
				{
					swap(vec[i], vec[j]);
				}
				else if (!bSortedCostUp && vec[i].GetCost() > vec[j].GetCost())
				{
					swap(vec[i], vec[j]);
				}
			}
		}
	}

	m_wndReportCtrl.DeleteAllItems();



	for (auto iter : vec)
	{
		bool bShow = true;
		if (!strNameFilter.IsEmpty())bShow &= AtoW(iter.GetName()).Find(strNameFilter) != -1;
		if (!strTypeFilter.IsEmpty())bShow &= AtoW(iter.GetType()).Find(strTypeFilter) != -1;

		if (nMinFirst != -1) bShow &= iter.GetCost() >= nMinFirst;
		if (nMaxFirst != -1) bShow &= iter.GetCost() <= nMaxFirst;

		if (dMinMark != -1.0) bShow &= iter.GetMark() >= dMinMark;
		if (dMaxMark != -1.0) bShow &= iter.GetMark() <= dMaxMark;

		if (bShow)AddToReport(iter);
	}
}

void CProductCtrlDlg::OnBnClickedAdd()
{
	Food obj;

	CString str;

	m_wndEditNameA.GetWindowText(str);
	if (str.IsEmpty()) { MessageBox(L"Некорректный ввод"); return; }
	obj.SetName(WtoA(str));

	m_wndEditTypeA.GetWindowText(str);
	if (str.IsEmpty()) { MessageBox(L"Некорректный ввод"); return; }
	obj.SetType(WtoA(str));

	m_wndEditFirstA.GetWindowText(str);
	if (str.IsEmpty() || _wtof(str) == 0) { MessageBox(L"Некорректный ввод"); return; }
	obj.SetCost(_wtof(str));

	m_wndEditDescriptionA.GetWindowText(str);
	obj.SetDescription(WtoA(str));

	obj.SetMark(0);

	m_pModule->addOneObj(obj);

	UpdatePage();
}

void CProductCtrlDlg::OnBnClickedEdit()
{
	auto pos = m_wndReportCtrl.GetFirstSelectedItemPosition();

	if (!pos)
		return;

	int index = m_wndReportCtrl.GetNextSelectedItem(pos);

	Food obj;

	obj.SetName(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_NAME)));
	obj.SetType(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_TYPE)));
	obj.SetCost(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_COST)));
	obj.SetDescription(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_DESCRIPTION)));
	obj.SetMark(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_MARK)));

	for (auto iter : m_Objects)
	{
		if (obj == iter)
		{
			obj.SetId(iter.GetId());
			break;
		}
	}

	CString str;

	m_wndEditNameE.GetWindowText(str);
	if (str.IsEmpty()) { MessageBox(L"Некорректный ввод"); return; }
	obj.SetName(WtoA(str));

	m_wndEditTypeE.GetWindowText(str);
	if (str.IsEmpty()) { MessageBox(L"Некорректный ввод"); return; }
	obj.SetType(WtoA(str));

	m_wndEditFirstE.GetWindowText(str);
	if (str.IsEmpty() || _wtof(str) == 0) { MessageBox(L"Некорректный ввод"); return; }
	obj.SetCost(_wtof(str));

	m_wndEditDescriptionE.GetWindowText(str);
	obj.SetDescription(WtoA(str));

	auto answer = m_pModule->editOneObj(obj);
	switch (answer)
	{
	case AnswerFromServer::_ERROR: MessageBox(L"ERROR"); break;
	case AnswerFromServer::UNKNOWN_COMMAND: MessageBox(L"Неизвестная команда"); break;
	}

	UpdatePage();
}

void CProductCtrlDlg::OnBnClickedDel()
{
	auto pos = m_wndReportCtrl.GetFirstSelectedItemPosition();

	if (!pos)
		return;

	int index = m_wndReportCtrl.GetNextSelectedItem(pos);

	Food obj;

	obj.SetName(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_NAME)));
	obj.SetType(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_TYPE)));
	obj.SetCost(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_COST)));
	obj.SetDescription(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_DESCRIPTION)));
	obj.SetMark(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_MARK)));

	for (auto iter : m_Objects)
	{
		if (obj == iter)
		{
			obj = iter;
			break;
		}
	}

	auto answer = m_pModule->delOneObj(obj);
	switch (answer)
	{
	case AnswerFromServer::_ERROR: MessageBox(L"ERROR"); break;
	case AnswerFromServer::UNKNOWN_COMMAND: MessageBox(L"Неизвестная команда"); break;
	}

	UpdatePage();
}

void CProductCtrlDlg::OnBnClickedSearch()
{
	m_wndEditFilterName.GetWindowText(strNameFilter);
	m_wndEditFilterType.GetWindowText(strTypeFilter);

	UpdatePage();
}

BOOL CProductCtrlDlg::PreTranslateMessage(MSG* pMsg)
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

void CProductCtrlDlg::OnBnClickedFilter()
{
	CString str;

	m_wndEdit1From.GetWindowText(str);
	nMinFirst = (str.GetLength() ? _wtoi(str) : -1);

	m_wndEdit1To.GetWindowText(str);
	nMaxFirst = (str.GetLength() ? _wtoi(str) : -1);

	m_wndEditMarkFrom.GetWindowText(str);
	dMinMark = (str.GetLength() ? _wtof(str) : -1.0);

	m_wndEditMarkTo.GetWindowText(str);
	dMaxMark = (str.GetLength() ? _wtof(str) : -1.0);

	UpdatePage();
}

void CProductCtrlDlg::OnBnClickedReport()
{
	int nRated = 0;
	for (auto iter : m_Objects)
	{
		if (iter.GetMark() != 0)nRated++;
	}

	CStdioFile  fl;
	fl.Open(L"Отчет.txt", CFile::modeCreate | CFile::modeWrite);
	CString str = L"Количетво записей: " + IntToStr(m_Objects.size()) + L"\n";
	fl.WriteString(str);
	str = L"Количетво оцененных записей: " + IntToStr(nRated) + L"\n";
	fl.WriteString(str);
	for (auto iter : m_Objects)
	{
		str = L"Название поставщика: " + AtoW(iter.GetName()) + L"\n";
		fl.WriteString(str);
		str = L"Тип зерна: " + AtoW(iter.GetType()) + L"\n";
		fl.WriteString(str);
		str = L"Стоимость: " + IntToStr(iter.GetCost()) + L" руб.\n";
		fl.WriteString(str);
		str = L"Описание: " + AtoW(iter.GetDescription()) + L"\n";
		fl.WriteString(str);
		str = L"Оценка экспертов: " + DoubleToStr(iter.GetMark()) + L"\n";
		fl.WriteString(str);
	}
	MessageBox(L"Отчет сохранен в локальной папке под названием \"Отчет.txt\"");
	//o.close();
}

void CProductCtrlDlg::AddToReport(Food& obj)
{
	CString strFormat;
	int index = m_wndReportCtrl.InsertItem(INDEX_NAME, AtoW(obj.GetName()));
	m_wndReportCtrl.SetItemText(index, INDEX_TYPE, AtoW(obj.GetType()));
	m_wndReportCtrl.SetItemText(index, INDEX_DESCRIPTION, AtoW(obj.GetDescription()));
	strFormat.Format(L"%0.2lf", obj.GetCost());
	m_wndReportCtrl.SetItemText(index, INDEX_COST, strFormat);
	strFormat.Format(L"%0.2lf", obj.GetMark());
	m_wndReportCtrl.SetItemText(index, INDEX_MARK, strFormat);
}

void CProductCtrlDlg::OnLvnItemchangedListProducts(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if ((pNMListView->uChanged & LVIF_STATE)
		&& (pNMListView->uNewState & LVIS_SELECTED))
	{
		if (m_wndEditNameE.IsWindowEnabled())
		{
			auto pos = m_wndReportCtrl.GetFirstSelectedItemPosition();

			if (!pos)
				return;

			int index = m_wndReportCtrl.GetNextSelectedItem(pos);

			m_wndEditNameE.SetWindowText(m_wndReportCtrl.GetItemText(index, INDEX_NAME));
			m_wndEditTypeE.SetWindowText(m_wndReportCtrl.GetItemText(index, INDEX_TYPE));
			m_wndEditDescriptionE.SetWindowText(m_wndReportCtrl.GetItemText(index, INDEX_DESCRIPTION));
			m_wndEditFirstE.SetWindowText(m_wndReportCtrl.GetItemText(index, INDEX_COST));
		}
	}
}

void CProductCtrlDlg::OnBnClickedButtonSortName()
{
	bSortedName = true;
	bSortedNameUp = !bSortedNameUp;
	bSortedCost = false;
	bSortedCostUp = false;

	UpdatePage();
}


void CProductCtrlDlg::OnBnClickedButtonSortCost()
{
	bSortedName = false;
	bSortedNameUp = false;
	bSortedCost = true;
	bSortedCostUp = !bSortedCostUp;

	UpdatePage();
}
