// MonitorMFCView.h : interface of the CMonitorMFCView class
//


#pragma once

class CMonitorMFCSet;

class CMonitorMFCView : public COleDBRecordView
{
protected: // create from serialization only
	CMonitorMFCView();
	DECLARE_DYNCREATE(CMonitorMFCView)

public:
	enum{ IDD = IDD_MONITORMFC_FORM };
	CMonitorMFCSet* m_pSet;

// Attributes
public:
	CMonitorMFCDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual CRowset<>* OnGetRowset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMonitorMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MonitorMFCView.cpp
inline CMonitorMFCDoc* CMonitorMFCView::GetDocument() const
   { return reinterpret_cast<CMonitorMFCDoc*>(m_pDocument); }
#endif

