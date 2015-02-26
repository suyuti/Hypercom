// MonitorMFCView.cpp : implementation of the CMonitorMFCView class
//

#include "stdafx.h"
#include "MonitorMFC.h"

#include "MonitorMFCSet.h"
#include "MonitorMFCDoc.h"
#include "MonitorMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMonitorMFCView

IMPLEMENT_DYNCREATE(CMonitorMFCView, COleDBRecordView)

BEGIN_MESSAGE_MAP(CMonitorMFCView, COleDBRecordView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COleDBRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMonitorMFCView construction/destruction

CMonitorMFCView::CMonitorMFCView()
	: COleDBRecordView(CMonitorMFCView::IDD)
{
	m_pSet = NULL;
	// TODO: add construction code here

}

CMonitorMFCView::~CMonitorMFCView()
{
}

void CMonitorMFCView::DoDataExchange(CDataExchange* pDX)
{
	COleDBRecordView::DoDataExchange(pDX);
	// you can insert DDX_* functions, as well as SetDlgItem*/GetDlgItem* API calls to link your database to the view
	// ex. ::SetDlgItemText(m_hWnd, IDC_MYCONTROL, m_pSet->m_MyColumn);
	// See MSDN and OLEDB samples for more information
}

BOOL CMonitorMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COleDBRecordView::PreCreateWindow(cs);
}

void CMonitorMFCView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_MonitorMFCSet;
	{
		CWaitCursor wait;
		HRESULT hr = m_pSet->OpenAll();
		if (FAILED(hr))
		{
			// Failed to open recordset.  If the recordset is a 
			// stored procedure, make sure that you have properly
			// initialized any input parameters before calling
			// the OpenAll() method.

			AfxMessageBox(_T("Record set failed to open."), MB_OK);
			// Disable the Next and Previous record commands,
			// since attempting to change the current record without an
			// open RowSet will cause a crash
			m_bOnFirstRecord = TRUE;
			m_bOnLastRecord = TRUE;
		}
		if( hr == DB_S_ENDOFROWSET )
		{
			// the rowset is empty (does not contain any rows)
			AfxMessageBox(_T("Record set opened but there were no rows to return."), MB_OK);
			// Disable the Next and Previous record commands
			m_bOnFirstRecord = TRUE;
			m_bOnLastRecord = TRUE;
		}
	}
	COleDBRecordView::OnInitialUpdate();

}


// CMonitorMFCView printing

BOOL CMonitorMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMonitorMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMonitorMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMonitorMFCView diagnostics

#ifdef _DEBUG
void CMonitorMFCView::AssertValid() const
{
	COleDBRecordView::AssertValid();
}

void CMonitorMFCView::Dump(CDumpContext& dc) const
{
	COleDBRecordView::Dump(dc);
}

CMonitorMFCDoc* CMonitorMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMonitorMFCDoc)));
	return (CMonitorMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMonitorMFCView database support
CRowset<>* CMonitorMFCView::OnGetRowset()
{
	return m_pSet->GetRowsetBase();
}



// CMonitorMFCView message handlers
