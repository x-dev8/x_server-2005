// ItemFactoryDoc.h :  CItemFactoryDoc ��Ľӿ�
//


#pragma once

class CItemFactoryDoc : public CDocument
{
protected: // �������л�����
	CItemFactoryDoc();
	DECLARE_DYNCREATE(CItemFactoryDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CItemFactoryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


