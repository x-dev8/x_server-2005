#ifndef __STAGEDEFINE_H__
#define __STAGEDEFINE_H__

#include "GlobalDef.h"
#include "IOXMLObject.h"
namespace StageDefine
{
    enum EConstDefine
    {
        constMaxAreas         = dr_stageMaxAreas,      // ���������
        constMaxZones         = dr_stageMaxZones,      // ��󴥷�������
        constMaxMapWidth      = dr_stageMaxMapWidth,   // ��ͼ�����
        constMaxMapHeight     = dr_stageMaxMapHeight,  // ��ͼ���߶�
        constAreaSize         = dr_stageAreaSize,      // �����С
        constStageAIInterval  = dr_stageAIInterval,    // ��ͼ�ڹ����˼��Ƶ��

        constStoreNameMaxSize = 256,                   // ���������������󳤶�
        constMaxReserveTime   = 60000 * 3,             // ԤԼʱ��180��
        constWaitReleaseTime  = 60000 * 1,             // �ȴ�����ʱ��
		constKickOutUserTime  = 10000,				   // �û���Ӧ���ڸ�������ʱ�ȶ೤ʱ��ϵͳ��

        // ��ʱ��
        ETimerType_1 = 0  , // һ�Ŷ�ʱ��
        ETimerType_Max, // ��ʱ����������

        // ������������
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