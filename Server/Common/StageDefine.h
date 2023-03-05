#ifndef __STAGEDEFINE_H__
#define __STAGEDEFINE_H__

#include "GlobalDef.h"
#include "IOXMLObject.h"
namespace StageDefine
{
    enum EConstDefine
    {
        constMaxAreas         = dr_stageMaxAreas,      // 最大区块数
        constMaxZones         = dr_stageMaxZones,      // 最大触发区块数
        constMaxMapWidth      = dr_stageMaxMapWidth,   // 地图最大宽度
        constMaxMapHeight     = dr_stageMaxMapHeight,  // 地图最大高度
        constAreaSize         = dr_stageAreaSize,      // 区块大小
        constStageAIInterval  = dr_stageAIInterval,    // 地图内怪物的思考频率

        constStoreNameMaxSize = 256,                   // 场所存放名长度最大长度
        constMaxReserveTime   = 60000 * 3,             // 预约时间180秒
        constWaitReleaseTime  = 60000 * 1,             // 等待销毁时间
		constKickOutUserTime  = 10000,				   // 用户不应该在副本里面时等多长时间系统踢

        // 定时器
        ETimerType_1 = 0  , // 一号定时器
        ETimerType_Max, // 定时器的最大个数

        // 区域任务类型
        ECountryType = 0,
        EGuildType   = 1,
    };
}

typedef std::list< GameObjectId >              GameObjectIdContainer;
typedef GameObjectIdContainer::iterator ItrGameObjectIdContainer;

class ReplaceMap
{
public:    
    ReplaceMap(){}

    char m_szName[260];
    INT  m_nBeginX;
    INT  m_nBeginY;

    INT  m_nEndX;
    INT  m_nEndY;

    INT  m_nReplaceX;
    INT  m_nReplaceY;

    INT  m_nReplaceEndX;
    INT  m_nReplaceEndY;
};


class LandStageConfig :public IOXMLObjectInstance
{
public:
    LandStageConfig();
    ~LandStageConfig();
public:
    // IOXMLObjectInstance Interface
    bool loadXMLSettings( const char *szPath  );
    bool loadXMLSettings( XMLElement *pElement );

    bool exportXMLSettings( std::ofstream &xmlFile  );
    bool exportXMLSettings( const char* xmlPath );
    bool ReadReplaceMap( XMLElement *element );
    bool Destory();
    bool IsReplaceMap( INT nX, INT nY, char *szFile, unsigned int szFileLength );

protected:
    typedef std::vector< ReplaceMap > ReplaceMapVector;
    typedef ReplaceMapVector::iterator ReplaceMapVectorIter;

public:
    short m_nWidth;
    short m_nHeight;

    ReplaceMapVector m_vecReplaceMap;
    bool m_bLoaded;
};

#endif