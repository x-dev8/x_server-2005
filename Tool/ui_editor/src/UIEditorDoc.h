// UIEditorDoc.h :  CUIEditorDoc 类的接口
//
#pragma once

#include "TgaCore.h"
//#include "Frame.h"
//#include "Control.h"
#include "BaseControl.h"

class CUIEditorDoc : public CDocument
{
protected: // 仅从序列化创建
	CUIEditorDoc();
	DECLARE_DYNCREATE(CUIEditorDoc)

// 属性
public:
	CGraphicsFileData	m_GraphicsData;

// 操作
public:

// 重写
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CUIEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};

CUIEditorDoc* GetDoc();
