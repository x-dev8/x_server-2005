#include "stdafx.h"
#include "ProcessManager.h"
#include "ApplicationManager.h"
#include "ApplicationManagerDialog.h"

#pragma warning ( push, 0 )
#include "Application_Config.h"
#pragma warning ( pop )

#pragma warning ( push )
#pragma warning ( disable : 4996) 
ProcessManager::ProcessManager()
{
}

int ProcessManager::AddProtectedProcess(const std::string& strProcessName, const std::string& strConfigFileName )
{    
    //bool bFind = false;
    //ProcessListType::iterator it = _processList.begin();
    //for ( ; it != _processList.end(); ++it )
    //{
    //    if ( it->strProcessName == strProcessName )
    //    {
    //        bFind = true;
    //        break;
    //    }
    //}

    //if ( bFind )
    //    return -1;    

    ProcessInfo processInfo;
    processInfo.strProcessName    = strProcessName;
    processInfo.strConfigFilePath = strConfigFileName;
    int ret = StartProcess(processInfo);

    if ( RESULT_FAIL(ret))
        return ret;

   // _processList.push_back( processInfo );
	AddProcessList(&processInfo);
    return 0;
}

void ProcessManager::AddProcessList(ProcessInfo* pInfo)
{
	if (!pInfo)
	{
		return;
	}

	ProcessListType::iterator it = _processList.begin();
	for (; it!=_processList.end(); ++it)
	{
		if (strcmp(it->strConfigFilePath.c_str(),pInfo->strConfigFilePath.c_str())==0)
		{
			it->hProcess = pInfo->hProcess;
			return;
		}
	}
	_processList.push_back(*pInfo);
}

void ProcessManager::WatchProcessList(void)
{
    ProcessListType::iterator it = _processList.begin();
    for (; it!=_processList.end(); ++it)
    {
        HANDLE hHandle = it->hProcess;
        DWORD dwExitCode;   
        
        GetExitCodeProcess(hHandle, &dwExitCode);
////////////////////////////////////////////////////////////////////////// 找到错误窗口,发送关闭消息
        std::string strCurrentDirectory;
        std::string::size_type nPos = it->strProcessName.find_last_of('/');
        if ( nPos != std::string::npos )
        {
            strCurrentDirectory = it->strProcessName.substr(0, nPos);
        }
        nPos = it->strProcessName.find_last_of('\\');
        if ( nPos != std::string::npos )
        {
            strCurrentDirectory =it->strProcessName.substr(0, nPos);
        }
        std::string strErroClassName = it->strProcessName.substr(nPos + 1, it->strProcessName.size());

        HWND errohWnd;
        errohWnd = FindWindow(NULL,strErroClassName.c_str());
        if (errohWnd != NULL)
        {
            //CloseWindow(errohWnd);
            SendMessage(errohWnd,WM_CLOSE,0,0);
            
            dwExitCode = !STILL_ACTIVE;
        }
//////////////////////////////////////////////////////////////////////////
        if( dwExitCode == STILL_ACTIVE )
        {
            
        }
        else
        { // 进程异常
            // 异常log
            SYSTEMTIME SyeTime;
            ::GetSystemTime(&SyeTime);

			CApplicationManagerDialog* pDlg = NULL;
			pDlg = (CApplicationManagerDialog*)theApp.m_pMainWnd;
			if ( pDlg )
				pDlg->SetTreeItemText( it->strConfigFilePath, true );

            /*char strContent[1024] = {0};
            sprintf_s( strContent, "%s %d:%d:%d:%d:%d:%d exception exit\n",it->strProcessName.c_str(),
                SyeTime.wYear, SyeTime.wMonth, SyeTime.wDay,
                SyeTime.wHour, SyeTime.wMinute, SyeTime.wSecond);

            FILE *fp = fopen( (it->strProcessName + ".log").c_str(), "a+");
            if( fp )
            {
                fwrite( strContent, strlen(strContent), 1, fp );
            }*/
			if (_isRestart)
			{
				ProcessInfo processInfo;
				processInfo.strProcessName = it->strProcessName;
				processInfo.strConfigFilePath = it->strConfigFilePath;
				int ret = StartProcess(processInfo);
				if ( RESULT_SUCCESS(ret) )
				{
					it->hProcess = processInfo.hProcess;
				}
				else
				{ // 重启失败log
					/*sprintf_s( strContent, "%s StartProcess fail\n",it->strProcessName.c_str());
					if( fp )
					{
					fwrite( strContent, strlen(strContent), 1, fp );
					}*/
				}

			}

            /*if ( fp )
            {
                fclose ( fp );
            }*/
        }
    }
}


void ProcessManager::TerminateProcess(const std::string& strProcessName)
{
    ProcessListType::iterator it = _processList.begin();
    for ( ; it != _processList.end(); ++it )
    {
        if ( it->strProcessName == strProcessName )
        {
            ::TerminateProcess(it->hProcess, 0);
            _processList.erase( it );;
            break;
        }
    }
}

void ProcessManager::TerminateAllProcees()
{
    ProcessListType::iterator it = _processList.begin();
    for ( ; it != _processList.end(); ++it )
    {
        ::TerminateProcess(it->hProcess, 0);
    }
    _processList.clear();
}

void ProcessManager::DispatchMessage(unsigned long ulMessageId, const std::string& strContent)
{
    FindHandleResultType ret = _messageHandleList.equal_range(ulMessageId);
    for ( ; ret.first != ret.second; ++ret.first )
    {
        ProcessMessageHandle* pHandle = ret.first->second;
        if ( !pHandle )
        {
            assert( false );
            continue;
        }
        pHandle->HandleMessage( ulMessageId, strContent );
    }
}

void ProcessManager::RegisterHandle(unsigned long ulMessageId, ProcessMessageHandle* pProcessMessageHandle)
{
    _messageHandleList.insert( MessageHandleListType::value_type(ulMessageId, pProcessMessageHandle) );
}

int ProcessManager::StartProcess( ProcessInfo& processInfo )
{   
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si)); 
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi));
    BOOL bSuccess = FALSE;

    std::string strCurrentDirectory;
    std::string::size_type nPos = processInfo.strProcessName.find_last_of('/');
    if ( nPos != std::string::npos )
    {
        strCurrentDirectory = processInfo.strProcessName.substr(0, nPos);
        
        goto beginCreate;
    }
    nPos = processInfo.strProcessName.find_last_of('\\');
    if ( nPos != std::string::npos )
    {
        strCurrentDirectory = processInfo.strProcessName.substr(0, nPos);
        goto beginCreate;
    }

beginCreate:
#ifdef NEEDKEY
    char version[ MAX_PATH ] = {0};
    sprintf( version, "%u.%u.%u.%u", ApplicationConfig::Instance().GetMajorVersion(),ApplicationConfig::Instance().GetMinorVersion(),
                                        ApplicationConfig::Instance().GetBuildVersion(),ApplicationConfig::Instance().GetRevisionVersion());

    int nLen = (int)strlen(version);
    for ( int i=0; i<nLen; ++i)
    {
        version[i] = char(version[i] ^ ApplicationConfig::START_KEY);
    }
    
    CString strFinalCommand;
    strFinalCommand.Format( "\"%s\" \"%s\"", processInfo.strProcessName.c_str(), version);

    if ( strCurrentDirectory.empty() )
        bSuccess = CreateProcess( NULL, strFinalCommand.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ); 
    else
        bSuccess = CreateProcess( NULL, strFinalCommand.GetBuffer(), NULL, NULL, FALSE, 0, NULL, strCurrentDirectory.c_str(), &si, &pi ); 
    
#else    
    CString strFinalCommand;
    strFinalCommand.Format( "\"%s\" -c \"%s\" -d", processInfo.strProcessName.c_str(), processInfo.strConfigFilePath.c_str() );

    if ( strCurrentDirectory.empty() ) 
    {
        bSuccess = CreateProcess( NULL, strFinalCommand.GetBuffer(),  NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ); 
        //bSuccess = CreateProcess( processInfo.strProcessName.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ); 
    }
    else
    {
        bSuccess = CreateProcess( NULL, strFinalCommand.GetBuffer(), NULL, NULL, FALSE, 0, NULL, strCurrentDirectory.c_str(), &si, &pi ); 
        //bSuccess = CreateProcess( processInfo.strProcessName.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, strCurrentDirectory.c_str(), &si, &pi );
    }
#endif
    
    if ( !bSuccess )
    {
        int nError = GetLastError();
        return nError;
    }
    else
    {
        processInfo.hProcess = pi.hProcess;
    }

	CApplicationManagerDialog* pDlg = NULL;
	pDlg = (CApplicationManagerDialog*)theApp.m_pMainWnd;
	if ( pDlg )
		pDlg->SetTreeItemText( processInfo.strConfigFilePath, false );
    
    return 0;
}

void ProcessManager::SetReStrat(bool isRestart)
{
	_isRestart = isRestart;
}
#pragma warning ( pop )
