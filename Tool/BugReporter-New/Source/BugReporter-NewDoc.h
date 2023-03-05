// BugReporter-NewDoc.h : interface of the CBugReporterNewDoc class
//


#pragma once


class CBugReporterNewDoc : public CDocument
{
protected: // create from serialization only
	CBugReporterNewDoc();
	DECLARE_DYNCREATE(CBugReporterNewDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CBugReporterNewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


