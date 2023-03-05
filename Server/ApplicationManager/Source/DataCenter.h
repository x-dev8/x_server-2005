/********************************************************************
	Filename: 	DataCenter.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

struct ApplicationInfo 
{
    long          id;
    std::string   strApplicationName;
    std::string   strApplicationPath;
    std::string   strConfigFilePath;
    unsigned long nDetectInterval;
    int           nIsLog;
};

typedef std::map<unsigned long, ApplicationInfo> ApplicationInfoListType;
typedef ApplicationInfoListType::iterator ItrApplicationInfoListType;

class DataCenter
{
public:
    static DataCenter& Instance();
    
    bool AddApplicationInfo(ApplicationInfo& applicationInfo );

    ApplicationInfo* GetApplicationInfo( unsigned long infoId );

    void ClearApplicationInfos();

    ApplicationInfoListType& GetApplicationInfos() { return applicationInfoList_; }

protected:
    DataCenter();

    DataCenter(const DataCenter&);

    DataCenter& operator =(const DataCenter&);

private:
    ApplicationInfoListType applicationInfoList_;
    unsigned long nCounterIndex_;
};

inline DataCenter& DataCenter::Instance()
{
    static DataCenter object;

    return object;
}
