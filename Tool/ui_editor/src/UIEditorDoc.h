// UIEditorDoc.h :  CUIEditorDoc ��Ľӿ�
//
#pragma once

#include "TgaCore.h"
//#include "Frame.h"
//#include "Control.h"
#include "BaseControl.h"

class CUIEditorDoc : public CDocument
{
protected: // �������л�����
	CUIEditorDoc();
	DECLARE_DYNCREATE(CUIEditorDoc)

// ����
public:
	CGraphicsFileData	m_GraphicsData;

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CUIEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};

CUIEditorDoc* GetDoc();
