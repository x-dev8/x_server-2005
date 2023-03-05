#pragma once

#include <string>
#include <vector>
#include <map>

#define RESULT_SUCCESS(x) ((x) == 0)
#define RESULT_FAIL(x)  !RESULT_SUCCESS(x)

struct ProcessInfo 
{
    std::string strProcessName;
    std::string strConfigFilePath;
    HANDLE      hProcess;
};

class ProcessManager;

class ProcessMessageHandle
{
    friend class ProcessManager;
private:
    virtual int HandleMessage( unsigned long ulMessageId, const std::string& strContent ) = 0;
};


class ProcessManager
{
private:
    ProcessManager();
    ProcessManager(const ProcessManager&);
    ProcessManager& operator =(const ProcessManager&);

public:
    int StartProcess(ProcessInfo& outputInfo);

    int AddProtectedProcess(const std::string& strProcessName, const std::string& strConfigFileName);

    void WatchProcessList(void);

    void TerminateProcess(const std::string& strProcessName);

    void TerminateAllProcees();

    void DispatchMessage(unsigned long ulMessageId, const std::string& strContent);

    void RegisterHandle(unsigned long ulMessageId, ProcessMessageHandle* pProcessMessageHandle);
    
    long GetProcessListSize() const { return (long)_processList.size(); }

    static ProcessManager& Instance();

	void SetReStrat(bool isRestart);

	void AddProcessList(ProcessInfo* pInfo);
private:
    typedef std::vector<ProcessInfo> ProcessListType;
    ProcessListType _processList;

    typedef std::multimap<unsigned long, ProcessMessageHandle*> MessageHandleListType;
    typedef std::pair<MessageHandleListType::const_iterator,MessageHandleListType::const_iterator> FindHandleResultType;

    MessageHandleListType _messageHandleList;

	bool _isRestart;
};

inline ProcessManager& ProcessManager::Instance()
{
    static ProcessManager object;

    return object;
}
