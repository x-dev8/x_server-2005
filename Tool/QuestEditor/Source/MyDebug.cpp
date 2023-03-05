

#include "MyDebug.h"

#include <windows.h>

#include <fstream>
using namespace std;



MyDebugFlags::MyDebugFlags()
{
	m_bActiveDebug = true;
	m_bFileFlag = true;
	m_bFunctionFlag = true;
	m_bLineFlag = true;
	m_bfunctionSignFlag = true;
	m_bTimestampFlag = true;
	m_bWindowFlag = true;
	m_bToFileFlag = true;	
}

MyDebugFlags::~MyDebugFlags()
{
}

MyDebug::MyDebug()
{
	SetDebugFilePath("Debug.log");
}

MyDebug::~MyDebug()
{
}

void MyDebug::SetFilePath(char *rpFilePath)
{
	if(rpFilePath == NULL)
		return;

	strcpy_s(m_sFilePath, sizeof(m_sFilePath), rpFilePath);
}

void MyDebug::SetDebugFilePath(char *rpFilePath)
{
	if(rpFilePath == NULL)
		return;

	strcpy_s(m_sDebugFilePath, sizeof(m_sDebugFilePath), rpFilePath);
}

size_t MyDebug::GetFilePath(char *rpFilePath,size_t rtBufferSize) const
{
	if(rtBufferSize > strlen(m_sFilePath))
	{
		strcpy_s(rpFilePath, sizeof(rpFilePath), m_sFilePath);
	}else{
		rpFilePath[0] = '\0';
	}

	return(strlen(m_sFilePath));
}

void MyDebug::SetFlags(const MyDebugFlags &rgaFlags)
{
	m_gaFlags = rgaFlags;
}

void MyDebug::GetFlags(MyDebugFlags &rgaFlags) const
{
	rgaFlags = m_gaFlags;
	
}


void MyDebug::WriteToFile(const char *rpMsg)
{
	
	ofstream outfile(m_sFilePath,ios_base::app);

	if(!outfile)
	{
		return;
	}
	
	
	outfile << rpMsg;

	outfile.clear();
	outfile.close();
	
}

void MyDebug::ClearDebugFile(const char *rpMsg)
{
	ofstream outfile(m_sDebugFilePath,ios_base::trunc);

	if(!outfile)
	{
		return;
	}

	outfile << rpMsg;

	outfile.clear();
	outfile.close();
}

void MyDebug::WriteToDebugFile(const char *rpMsg)
{
	
	ofstream outfile(m_sDebugFilePath,ios_base::app);

	if(!outfile)
	{		
		return;
	}
	
	
	outfile << rpMsg;

	outfile.clear();
	outfile.close();
	
}

void MyDebug::WriteToWindow(MsgType rmType,char *rpMsg)
{
	HWND hwnd;

	hwnd = GetWindowHandle();
	if(hwnd == NULL)
	{
		return;
	}
	
	
	switch(rmType)
	{
	case Enum_Debug:
		SendData(hwnd,0,rpMsg);
		break;
	case Enum_Info:
		SendData(hwnd,1,rpMsg);
		break;
	case Enum_Error:
		SendData(hwnd,2,rpMsg);
		break;
	}
}

void MyDebug::SendData(HWND rhWnd,int rnChannel,char *rpMsg)
{
	COPYDATASTRUCT cpdata;

	cpdata.dwData = (DWORD)rnChannel;
	cpdata.cbData = (DWORD)strlen(rpMsg) + 1;
	cpdata.lpData = rpMsg;

	::SendMessage(rhWnd,WM_COPYDATA,0,(long)&cpdata);
	
}

HWND MyDebug::GetWindowHandle()
{
	HWND hwnd;

	hwnd = FindWindow(NULL,"Debug messages");

	return(hwnd);
}

MyDebug& MyDebug::WriteToLog(MsgType rmType,char *rpFileName,size_t rtFileLine,char *rpFunction,char *rpFunctionSign)
{
	CTime time;
	char log_msg[500];
	CString temp;
	static bool first_line = true;
	
	

	log_msg[0] = 0;

	

	if(first_line == true)
	{
		first_line = false;
	}else{
		strcpy_s(log_msg, sizeof(log_msg), "\r\n\r\n");
	}

	if(m_gaFlags.m_bFileFlag == true)
	{
		sprintf_s(log_msg + strlen(log_msg), sizeof(log_msg), "%s",rpFileName);
	}

	if(m_gaFlags.m_bLineFlag == true)
	{
		sprintf_s(log_msg + strlen(log_msg), sizeof(log_msg), "(%d)",rtFileLine);
	}

	switch(rmType)
	{
	case Enum_Debug:
		strcpy_s((log_msg + strlen(log_msg)), sizeof(log_msg), "   Debug Msg");
		break;
	case Enum_Info:
		strcpy_s((log_msg + strlen(log_msg)), sizeof(log_msg), "   Info  Msg");
		break;
	case Enum_Error:
		strcpy_s((log_msg + strlen(log_msg)), sizeof(log_msg), "   Error Msg");
		break;
	case Enum_File:
		strcpy_s((log_msg + strlen(log_msg)), sizeof(log_msg), "   File Msg");
		break;
	}

	if(m_gaFlags.m_bTimestampFlag == true)
	{
		time = CTime::GetCurrentTime();
		
		temp = time.Format("%Y/%m/%d-%H:%M:%S");
		sprintf_s(log_msg + strlen(log_msg), sizeof(log_msg), "\r\nTime : %s",(char*)(LPCTSTR)temp);
	}

	

	if(m_gaFlags.m_bfunctionSignFlag == true)
	{
		sprintf_s(log_msg+strlen(log_msg), sizeof(log_msg), "\r\nFuncSign : %s",rpFunctionSign);
	}else if(m_gaFlags.m_bFunctionFlag == true)
	{
		sprintf_s(log_msg + strlen(log_msg), sizeof(log_msg), "\r\nFunc : %s",rpFunction);

	}

	strcat_s(log_msg, sizeof(log_msg), "\r\nExpression :");

	
	if(m_gaFlags.m_bToFileFlag == true)
	{
		WriteToFile(log_msg);
	}

	if(m_gaFlags.m_bWindowFlag == true)
	{
		WriteToWindow(rmType,log_msg);
	}

	return(Instance());
}

MyDebug& MyDebug::WriteToFile(MsgType rmType,char *rpFileName,size_t rtFileLine,char *rpFunction,char *rpFunctionSign)
{
	CTime time;
	char log_msg[1024];
	CString temp;
	static bool first_line = true;
	
	

	log_msg[0] = 0;

	

	if(first_line == true)
	{
		first_line = false;
	}else{
		strcpy_s(log_msg, sizeof(log_msg), "\r\n\r\n");
	}

	if(m_gaFlags.m_bFileFlag == true)
	{
		sprintf_s(log_msg + strlen(log_msg), sizeof(log_msg), "%s",rpFileName);
	}

	if(m_gaFlags.m_bLineFlag == true)
	{
		sprintf_s(log_msg + strlen(log_msg), sizeof(log_msg), "(%d)",rtFileLine);
	}

	strcpy_s((log_msg + strlen(log_msg)), sizeof(log_msg), "   File Msg");

	if(m_gaFlags.m_bTimestampFlag == true)
	{
		time = CTime::GetCurrentTime();
		
		temp = time.Format("%Y/%m/%d-%H:%M:%S");
		sprintf_s(log_msg + strlen(log_msg), sizeof(log_msg), "\r\nTime : %s",(char*)(LPCTSTR)temp);
	}


	if(m_gaFlags.m_bfunctionSignFlag == true)
	{
		sprintf_s(log_msg+strlen(log_msg), sizeof(log_msg), "\r\nFuncSign : %s",rpFunctionSign);
	}
	else if(m_gaFlags.m_bFunctionFlag == true)
	{
		sprintf_s(log_msg + strlen(log_msg), sizeof(log_msg), "\r\nFunc : %s",rpFunction);

	}

	strcat_s(log_msg, sizeof(log_msg), "\r\nExpression :");
	
	if(m_gaFlags.m_bToFileFlag == true)
	{
		WriteToDebugFile(log_msg);
	}

	return(Instance());
}

void MyDebug::Print(MsgType rmType,char *rpFormat,va_list rlist)
{
	char expression[10000] = "";
	
	vsprintf(expression,rpFormat,rlist);

	if(m_gaFlags.m_bToFileFlag == true)
	{
		if(rmType == Enum_File)
		{
			WriteToDebugFile(expression);
		}
		else
		{
			WriteToFile(expression);
		}
	}

	if(m_gaFlags.m_bWindowFlag == true)
	{
		WriteToWindow(rmType,expression);
	}
}

void MyDebug::Printf0(char *rpFormat,...)
{
	va_list valist;
	
	va_start(valist,rpFormat);

	Print(Enum_Debug,rpFormat,valist);
}

void MyDebug::Printf1(char *rpFormat,...)
{
	va_list valist;
	
	va_start(valist,rpFormat);

	Print(Enum_Info,rpFormat,valist);
}

void MyDebug::Printf2(char *rpFormat,...)
{
	va_list valist;
	
	va_start(valist,rpFormat);

	Print(Enum_Error,rpFormat,valist);
}

void MyDebug::Printf3(char *rpFormat,...)
{
	va_list valist;
	
	va_start(valist,rpFormat);

	Print(Enum_File,rpFormat,valist);
}

void MyDebug::DoNothing(char *rpFormat,...)
{

}

MyDebug& MyDebug::Instance()
{
	static MyDebug sdebug;
	
	return(sdebug);
}