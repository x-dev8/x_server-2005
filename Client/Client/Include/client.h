//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef AFX_DRAGOONAPP_H__8436D781_CD57_450E_B5B3_A553410C6A39__INCLUDED_
#define AFX_DRAGOONAPP_H__8436D781_CD57_450E_B5B3_A553410C6A39__INCLUDED_

#include "D3dApp.h"


//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
// TODO: change "DirectX AppWizard Apps" to your name or the company name
#define DXAPP_KEY        TEXT("Software\\DirectX AppWizard Apps\\DragoonApp")


// Struct to store the current input state
struct UserInput
{
    // TODO: change as needed
    BOOL bRotateUp;
    BOOL bRotateDown;
    BOOL bRotateLeft;
    BOOL bRotateRight;
};




//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CMyD3DApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
    BOOL                    m_bLoadingApp;          // TRUE, if the app is loading
    

    UserInput               m_UserInput;            // Struct for storing user input 

	

protected:
    virtual HRESULT OneTimeSceneInit();
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT InvalidateDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual HRESULT Render();
    virtual HRESULT FrameMove();
    virtual HRESULT FinalCleanup();
    virtual HRESULT ConfirmDevice( D3DCAPS9*, DWORD, D3DFORMAT );

    void    UpdateInput( UserInput* pUserInput );

public:
    LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

	CMyD3DApplication();
	virtual ~CMyD3DApplication(){}
};

#endif // !defined(AFX_DRAGOONAPP_H__8436D781_CD57_450E_B5B3_A553410C6A39__INCLUDED_)
