
#include <wchar.h>
#include <windef.h>

#pragma once


#define _DEBUG1
#define _EXCEPTION

#define _FILE_DEBUG


#ifdef _DEBUG1
	#define DebugMsg MyDebug::Instance().WriteToLog(MyDebug::Enum_Debug,__FILE__, __LINE__, __FUNCTION__, __FUNCSIG__).Printf0
	#define InfoMsg  MyDebug::Instance().WriteToLog(MyDebug::Enum_Info,__FILE__, __LINE__, __FUNCTION__, __FUNCSIG__).Printf1
	#define ErrorMsg MyDebug::Instance().WriteToLog(MyDebug::Enum_File,__FILE__, __LINE__, __FUNCTION__, __FUNCSIG__).Printf2
#else
	#define DebugMsg MyDebug::Instance().DoNothing
	#define InfoMsg  MyDebug::Instance().DoNothing
	#define ErrorMsg MyDebug::Instance().DoNothing
#endif

#ifdef _FILE_DEBUG
	#define FileMsg MyDebug::Instance().WriteToFile(MyDebug::Enum_File,__FILE__, __LINE__, __FUNCTION__, __FUNCSIG__).Printf3
	#define ClearFile MyDebug::Instance().ClearDebugFile
#else
	#define FileMsg MyDebug::Instance().DoNothing
	#define ClearFile MyDebug::Instance().DoNothing
#endif

#ifdef _EXCEPTION
	#define ExceptionMsg  MyDebug::Instance().WriteToFile(MyDebug::Enum_File,__FILE__, __LINE__, __FUNCTION__, __FUNCSIG__).Printf3
#else
	#define ExceptionMsg  MyDebug::Instance().DoNothing
#endif

class MyDebugFlags
{
public:
	MyDebugFlags();
	~MyDebugFlags();

	bool m_bActiveDebug;
	bool m_bFileFlag;
	bool m_bLineFlag;
	bool m_bFunctionFlag;
	bool m_bfunctionSignFlag;
	bool m_bTimestampFlag;
	bool m_bWindowFlag;
	bool m_bToFileFlag;
};



class MyDebug
{

public:
	enum MsgType
	{
		Enum_Debug = 1,
		Enum_Info ,
		Enum_Error,
		Enum_File
	};
public:
	~MyDebug();


	void SetFilePath(char *rpFilePath);
	void SetDebugFilePath(char *rpFilePath);
	size_t GetFilePath(char *rpFilePath,size_t rtBufferSize) const;
	void SetFlags(const MyDebugFlags &rgaFlags);
	void GetFlags(MyDebugFlags &rgaFlags) const;
	void WriteToFile(const char *rpMsg);
	void ClearDebugFile(const char *rpMsg);
	void WriteToDebugFile(const char *rpMsg);
	void WriteToWindow(MsgType rmType,char *rpMsg);
	MyDebug& WriteToLog(MsgType rmType,char *rpFileName,size_t rtFileLine,char *rpFunction,char *rpFunctionSign);
	MyDebug& WriteToFile(MsgType rmType,char *rpFileName,size_t rtFileLine,char *rpFunction,char *rpFunctionSign);


	void Print(MsgType rmType,char *rpFormat,va_list rlist);
	void Printf0(char *rpFormat,...);
	void Printf1(char *rpFormat,...);
	void Printf2(char *rpFormat,...);
	void Printf3(char *rpFormat,...);
	void DoNothing(char *rpFormat,...);

	static MyDebug& Instance();



private:
	char m_sFilePath[MAX_PATH];
	char m_sDebugFilePath[MAX_PATH];
	MyDebugFlags m_gaFlags;

	MyDebug();

	void SendData(HWND rhWnd,int rnChannel,char *rpMsg);
	HWND GetWindowHandle();
};
