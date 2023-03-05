#pragma once

#include "../Resource/Resource.h"
#include <string>
#include "ProcessManager.h"

class CApplicationInfoPage : public CDialog, public ProcessMessageHandle
{
	DECLARE_DYNAMIC(CApplicationInfoPage)

public:
	CApplicationInfoPage(CWnd* pParent = NULL);

	virtual ~CApplicationInfoPage();

	enum { IDD = IDD_PROPPAGE_PROCESS_INFO };

    virtual int HandleMessage( unsigned long ulMessageId, const std::string& strContent );

    afx_msg void OnBnClickedButtonStart();

    void SetApplicationPath( const std::string& strPath );
    void SetConfigPath( const std::string& strConfigPath ){ _strConfigPath = strConfigPath; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

    virtual BOOL OnInitDialog();

    virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

protected:    
    CButton*  _buttonStart;

    CListBox* _listCtrl;

    bool      _bRunning;

    std::string _strApplicationPath;
    std::string _strConfigPath;
};
