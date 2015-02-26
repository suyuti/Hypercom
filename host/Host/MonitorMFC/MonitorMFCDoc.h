// MonitorMFCDoc.h : interface of the CMonitorMFCDoc class
//


#pragma once
#include "MonitorMFCSet.h"


class CMonitorMFCDoc : public CDocument
{
protected: // create from serialization only
	CMonitorMFCDoc();
	DECLARE_DYNCREATE(CMonitorMFCDoc)

// Attributes
public:
	CMonitorMFCSet m_MonitorMFCSet;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMonitorMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


