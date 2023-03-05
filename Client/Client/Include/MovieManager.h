/*************************************************************************************
                    动画播放    by zhuomeng.hu		[2/23/2011]
*************************************************************************************/

#pragma once

#include <map>
#include "Me3d/WmvPlay/AsyWmvStreamManager.h"
#include "RapidXml/MeRapidXml.h"

class CMovieManager : public Singleton<CMovieManager>
{
public:
    struct Movie
    {
        Movie();
        Movie& operator = ( const Movie& movie );

        std::string strFileName;                            // 视频文件名
        DWORD       dwBlackTime;                            // 黑屏时间
        DWORD       dwFadeTime;                             // 淡入淡出时间
        bool        bLoop;                                  // 是否循环播放
        bool        bTop;                                   // 是否在最上层
        bool        bDisableInput;                          // 是否屏蔽鼠键输入
        bool        bCanCancel;                             // 是否能用ESC键取消
    };

    enum MovieType
    {
        Type_None               = 0,
        Type_Login              = 1,
    };

public:
    ~CMovieManager();
    bool LoadConfig( MeXmlElement* pRoot );

    void Update();                                          // 更新
    void Render( bool bTop );                               // 播放
    void OnDeviceLost();                                    // 丢失设备需要调用
    void ResetDevice();                                     // 恢复设备需要调用

    bool OpenByType( int nType );                           // 打开文件，如果 nType 为 Type_None，则功能等同于Close
    void Close();                                           // 停止
    bool IsPlaying();                                       // 是否在播放中
    void ProcessESC();                                      // 取消动画播放
    bool DisableInput();                                    // 是否禁用输入

protected:
    bool GetMovieByType( int nType, OUT Movie* pMovieInfo );    // 获取指定动画信息

private:
    friend class Singleton<CMovieManager>;
    CMovieManager();

private:
    std::map< int, Movie >      m_movieMap;                 // 保存视频的一些配置
    int                         m_nCurrentType;             // 保存当前正在播放的动画 ID
    DWORD                       m_dwBlackBeginTime;         // 黑屏的开始时间，大于0说明正处于黑屏时间

};
