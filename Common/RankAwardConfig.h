#ifndef __RANKAWARD_CONFIG_H__
#define __RANKAWARD_CONFIG_H__

#pragma once

#define theRankAwardConfig RankAwardConfig::Instance()   //实例接口

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"

class RankAwardConfig
{
public:
    struct RankAward
    {
        uint16  nId;        // ID
        uint16  nRankType;  // 排行类型
        uint16  nBeginPos;  // 开始名次
        uint16  nEndPos;    // 结束名次
        uint16  nTitleId;   // 称号ID

        RankAward() : nId(0),  nRankType(0), nBeginPos(0), nEndPos(0), nTitleId(0)
        { 
        }

        RankAward(const RankAward& xRankAward)
        {
            *this = xRankAward;
        }

        RankAward& operator = (const RankAward& xRankAward)
        {
            if (this != &xRankAward)
            {
                nId         = xRankAward.nId;
                nRankType   = xRankAward.nRankType;
                nBeginPos   = xRankAward.nBeginPos;
                nEndPos     = xRankAward.nEndPos;
                nTitleId    = xRankAward.nTitleId;
            }

            return *this;
        }

        bool operator == (const int Id) { return (this->nId == Id); }

        const uint16 GetID() const { return nId;        }
        const uint16 GetRankType()  const { return nRankType;  }
        const uint16 GetBeginPos () const { return nBeginPos;  }
        const uint16 GetEndPos()    const { return nEndPos;    }
        const uint16 GetTitleId()   const { return nTitleId;   }
    };

protected:
    RankAwardConfig();

public:
    ~RankAwardConfig();

    inline static RankAwardConfig& Instance()
    {
        static RankAwardConfig s_xRankAward;
        return s_xRankAward;
    }

    bool LoadRankAwardConfig(const char* szFile);

    RankAward* GetRankAward(uint16 rankType, uint16 pos )
    {
        for ( RankAwardIter iter = m_vecRankAward.begin(); iter != m_vecRankAward.end(); ++iter )
        {
            if (iter->nRankType != rankType)
            { continue; }

            if (iter->nBeginPos <= pos && iter->nEndPos >= pos)
            { return &(*iter) ; }
        }

        return NULL;
    }

    const std::vector<RankAward>& GetRankAwardList() const{ return m_vecRankAward; }

private:
    std::vector<RankAward> m_vecRankAward;

public:
    typedef std::vector<RankAward>::iterator RankAwardIter;
};

#endif

