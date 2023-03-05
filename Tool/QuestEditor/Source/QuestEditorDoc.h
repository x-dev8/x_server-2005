// EditorDoc.h : interface of the CQuestEditorDoc class
//

#pragma once


class CQuestEditorDoc : public CDocument
{
protected: // create from serialization only
	CQuestEditorDoc();
	DECLARE_DYNCREATE(CQuestEditorDoc)

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
	virtual ~CQuestEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


