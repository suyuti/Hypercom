// MonitorMFCDoc.cpp : implementation of the CMonitorMFCDoc class
//

#include "stdafx.h"
#include "MonitorMFC.h"

#include "MonitorMFCSet.h"
#include "MonitorMFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMonitorMFCDoc

IMPLEMENT_DYNCREATE(CMonitorMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CMonitorMFCDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CMonitorMFCDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CMonitorMFCDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()


// CMonitorMFCDoc construction/destruction

CMonitorMFCDoc::CMonitorMFCDoc()
{
	// TODO: add one-time construction code here

}

CMonitorMFCDoc::~CMonitorMFCDoc()
{
}

BOOL CMonitorMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMonitorMFCDoc serialization

void CMonitorMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMonitorMFCDoc diagnostics

#ifdef _DEBUG
void CMonitorMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMonitorMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMonitorMFCDoc commands
