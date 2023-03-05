#include "stdafx.h"
#include "DataCenter.h"

DataCenter::DataCenter() : nCounterIndex_(0)
{
}

bool DataCenter::AddApplicationInfo(ApplicationInfo& applicationInfo )
{
    ApplicationInfoListType::const_iterator cit = applicationInfoList_.begin();
    for ( ; cit != applicationInfoList_.end(); ++cit )
    {
        if ( 0 == cit->second.strApplicationName.compare(applicationInfo.strApplicationName))
            return false;
    }

    applicationInfo.id = ++nCounterIndex_;
    applicationInfoList_.insert( ApplicationInfoListType::value_type(applicationInfo.id,applicationInfo));
    return true;
}
 
ApplicationInfo* DataCenter::GetApplicationInfo( unsigned long infoId )
{
    ApplicationInfoListType::iterator it = applicationInfoList_.find(infoId);
    if ( it != applicationInfoList_.end())
    {
        return &(it->second);
    }
    return NULL;
}

void DataCenter::ClearApplicationInfos()
{
    nCounterIndex_ = 0;
    applicationInfoList_.clear();
}
