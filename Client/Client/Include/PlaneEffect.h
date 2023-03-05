/********************************************************************
	         Created by Zhuomeng.Hu  [11/15/2010]
	            平面序列帧特效，如用于UI控件
                美术资源要求:等大连续，矩阵排列

                Example:    1  2  3  4  5  6
                            7  8  9 10 11 12
                           13 14 15
               
               nRowCount   =  3
               nColCount   =  6
               nCount      = 15
               bOrderByRow = true
*********************************************************************/

#pragma once
#include <string>
#include <vector>
#include <windows.h>

class CPlaneEffect
{
public:
    struct SrcRect
    {
        SrcRect()
        {
            pNext = NULL;
            rcSrc.left = 0;
            rcSrc.top = 0;
            rcSrc.right = 0;
            rcSrc.bottom = 0;
        }
        SrcRect*    pNext;
        RECT        rcSrc;
    };

public:
    CPlaneEffect();
    ~CPlaneEffect();

    bool Initialize( const std::string& strPicPath,             // 图片路径 \Data\Ui\之后，如"Common\xxx.tga"
                                    int nRowCount,              // 序列帧有几排
                                    int nColCount,              // 序列帧有几列
                                    int nCount,                 // 总共有几个
                            const RECT& rcFirst,                // 第一张序列帧的资源坐标
                                  DWORD dwTotalTime,            // 播放完一个循环所需时间 (毫秒)
                                   bool bOrderByRow = true,     // 美术提供的序列帧是否为横向排列
                                   bool bReverse = false );     // 播放时是否倒序

    void Display( const RECT& rcDest );                       // 每帧需要调用
	void Restart();

protected:
    const RECT& GetNextSrcRect();

private:
    // 外部设置参数
    std::string             m_strPicPath;               // 图片路径
    DWORD                   m_dwTimePerFrame;           // 播放完一个循环所需时间

    // 内部逻辑
    bool                    m_bInited;                  // 是否已经初始化
    std::vector<SrcRect>    m_rectVec;                  // 资源图片坐标队列
    SrcRect*                m_pCurRect;                 // 当前资源坐标
    DWORD                   m_dwLastPicTime;            // 上幅图的播放时间
};
