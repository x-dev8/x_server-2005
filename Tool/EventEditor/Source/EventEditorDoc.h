// EditorDoc.h : interface of the CEditorDoc class
//


#pragma once


class CEditorDoc : public CDocument
{
protected: // create from serialization only
	CEditorDoc();
	DECLARE_DYNCREATE(CEditorDoc)

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
	virtual ~CEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


