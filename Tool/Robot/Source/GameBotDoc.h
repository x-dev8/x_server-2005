// GameBotDoc.h : CGameBotDoc ��Ľӿ�
//


#pragma once

class CGameBotDoc : public CDocument
{
protected: // �������л�����
	CGameBotDoc();
	DECLARE_DYNCREATE(CGameBotDoc)

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
	virtual ~CGameBotDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


