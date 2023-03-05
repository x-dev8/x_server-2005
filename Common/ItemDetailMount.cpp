#include "ItemDetail.h"
#include "SlkReader.h"
#include "Helper.h"
#include "Official.h"
#include "SystemConfig.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "ProcessCharInfo.h"
#include "NewWithDebug.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "core/Name.h"
#include "application_config.h"
#include "TitleConfig.h"
//#include "Cipher/cipher_factory.h"
//#include "Launcher/DataLauncher.h"
#include "SplitItemConfig.h"
#include "ErrorCode.h"
#include "tstring.h"
#include "RapidXml\MeRapidXml.h"

#pragma warning( push, 0 )

bool CItemDetail::LoadSlkMount( const char* szFileName )
{
    CSlkReader pReader;
    if( !pReader.ReadFromFile( szFileName ) )
        return false;

    int iRow = 3;
    int iCol;
    int iRet;

    int   iValue = 0;
    float fValue = 0.0f;

    std::string strTemp;
    std::string strName;
    std::string strModelPath;
    std::string strMountEffectPath;
    std::string strDisMountEffectPath;
    std::string strRunSoundOfLeftFootPath;
    std::string strRunSoundOfRightFootPath;
    std::string strNeightSoundPath;
    std::string strHeadPic;

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( iRow++ ) ) ) 
    {
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        ItemDefine::SDrome* pMount = (ItemDefine::SDrome*)AllocItem( 0,  sizeof(ItemDefine::SDrome));        
        if( !pMount )
        {
            OutputSlkLoadingMessage( "Error:分配Mount需要的内存出错 [%d]\r\n", iRow );
            return false;
        }

        iCol = 1;

        // 索引
        if( !pReader.GetIntField( iCol, iValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑编号ID出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑编号ID出错", iRow );
            goto load_error;
        }
        pMount->stId = iValue;
        iCol ++;

        // 名称
        if( !pReader.GetStringField( iCol,strName ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑名称出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑名称出错", iRow );
            goto load_error;
        }
        pMount->dwNameAddr = AllocStringCopy( strName.c_str() );

        OutputSlkLoadingMessage( "\t Load Mount %s\r\n", strName.c_str() );

        iCol ++;

        // 模型文件路径
        if( !pReader.GetStringField( iCol, strModelPath ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑模型文件路径出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑模型文件路径出错", iRow );
            goto load_error;
        }
        pMount->dwModelAddr = AllocStringCopy( strModelPath.c_str() );
        iCol ++;

		// 模型ID
		int nend = iCol + SMountItem::MICD_MountMaxLevel;
		for (int i = 0; iCol <= nend && i <= SMountItem::MICD_MountMaxLevel; iCol++, i++)
		{
			if( !pReader.GetIntField( iCol, iValue ) )
			{
				OutputSlkLoadingMessage( "\t 载入坐骑模型ID出错!\r\n" );
				GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑模型ID出错", iRow );
				goto load_error;
			}
			pMount->modelID[i] = iValue;
		}

        // 类型
        if( !pReader.GetIntField(iCol, iValue ))
        {
            OutputSlkLoadingMessage( "\t 载入坐骑类型出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑类型出错", iRow );
            goto load_error;
        }
        pMount->stType = iValue;
        iCol ++;

        // 运载能力
        if( !pReader.GetIntField( iCol, iValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑运载能力出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑运载能力出错", iRow );
            goto load_error;
        }
        pMount->stCarry = iValue;
        iCol ++;

        // 飞行高度
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑飞行高度出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑飞行高度出错", iRow );
            goto load_error;
        }
        pMount->fFlyHeight = fValue;
        iCol ++;

        // 惯性
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑惯性出错!\r\n" );
            GetErrorLog()->logString( "Mount.slk 第%d行载入坐骑惯性出错", iRow );
            goto load_error;
        }
        pMount->fInertia = fValue;
        iCol ++;

        // 速度
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑速度出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑速度出错", iRow );
            goto load_error;
        }
        pMount->fSpeed = fValue;
        iCol ++;

        // Run步长
        //if( !pReader.GetFloatField( iCol, fValue ) )
        if( !pReader.GetFloatFieldByName( "RunStep", fValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑[Run步长]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑[Run步长]出错", iRow );
            goto load_error;
        }
        pMount->fRunningStep = fValue;
        iCol ++;

        // Walk步长
        if( !pReader.GetFloatFieldByName( "WalkStep", fValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑[Walk步长]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑[Walk步长]出错", iRow );
            goto load_error;
        }
        pMount->fWalkingStep = fValue;
        iCol ++;

        // 跳跃高度
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑[跳跃高度]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑[跳跃高度]出错", iRow );
            goto load_error;
        }
        pMount->fJumpingHeight = fValue;
        iCol ++;

        // 移动类型
        if( !pReader.GetStringFieldByName( "MoveType", strTemp ) )
        {
            OutputSlkLoadingMessage( "Error: Mount.slk 读取[移动类型]出错!\r\n" );
            GetErrorLog()->logString( "Mount.slk 中[移动类型]出错" );
            goto load_error;
        }
        iValue = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(), ItemDefine::g_szMoveTypeString,sizeof(ItemDefine::g_szMoveTypeString)/sizeof(char*) );

        if( -1 == iValue )
        {
            OutputSlkLoadingMessage( "Error: Mount.slk 读取[移动类型]出错!\r\n" );
            GetErrorLog()->logString( "Mount.slk 中[移动类型]出错" );
            goto load_error;
        }
        pMount->shMoveType = iValue;        
        iCol ++;

        // 坐骑体型修正
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入[坐骑体型修正]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入[坐骑体型修正]出错", iRow );
            goto load_error;
        }
        pMount->fDromeScaleCorrect = fValue;
        iCol ++;

        // 骑手体型修正
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入[骑手体型修正]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入[骑手体型修正]出错", iRow );
            goto load_error;
        }
        pMount->fRiderScaleCorrect = fValue;
        iCol ++;

        // 最大使用时间
        if( !pReader.GetIntField( iCol,iValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑最大使用时间出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑最大使用时间出错", iRow );
            goto load_error;
        }
        pMount->dwMaxLifeTime = iValue;
        iCol++;

        //宠物皮肤
        if( !pReader.GetStringFieldByName( "Skin", strTemp ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑[宠物皮肤]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑[宠物皮肤]出错", iRow );
            goto load_error;
        }
        pMount->dwSkinAddr = AllocStringCopy( strTemp.c_str() );
        iCol++;

        //附加的状态ID
        if( !pReader.GetIntFieldByName( "AddStatus", iValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑[附加状态ID]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑[附加状态ID]出错", iRow );
            goto load_error;
        }
        pMount->nAddStatusID = iValue;
        iCol++;

        // 上坐骑的特效路径
        if( !pReader.GetStringField( iCol, strMountEffectPath ) )
        {
            OutputSlkLoadingMessage( "\t 载入[上坐骑的特效路径]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入[上坐骑的特效路径]出错", iRow );
            goto load_error;
        }
        pMount->dwMountEffectAddr = AllocStringCopy( strMountEffectPath.c_str() );
        iCol ++;

        // 下坐骑的特效路径
        if( !pReader.GetStringField( iCol, strDisMountEffectPath ) )
        {
            OutputSlkLoadingMessage( "\t 载入[下坐骑的特效路径]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入[下坐骑的特效路径]出错", iRow );
            goto load_error;
        }
        pMount->dwDisMountEffectAddr = AllocStringCopy( strDisMountEffectPath.c_str() );
        iCol ++;

        //骑手空闲动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountDrive", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountDrive] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountDrive] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountDrive] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountDrive] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手行走动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountWalk", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountWalk] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountWalk] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountWalk] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountWalk] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手后退动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountWalkBackWards", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountWalkBackWards] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountWalkBackWards] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountWalkBackWards] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountWalkBackWards] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手奔跑动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountRun", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountRun] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountRun] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountRun] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountRun] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手跳跃动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountJump", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountJump] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountJump] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountJump] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountJump] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手落地跑动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountFallToTheGroundRun", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountFallToTheGroundRun] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountFallToTheGroundRun] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountFallToTheGroundRun] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountFallToTheGroundRun] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手落地动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountDrop", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountDrop] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountDrop] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountDrop] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountDrop] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手滑行动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountGlide", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountGlide] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountGlide] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountGlide] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountGlide] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手左转动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountShuffleLeft", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountShuffleLeft] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountShuffleLeft] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountShuffleLeft] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountShuffleLeft] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手右转动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountShuffleRight", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountShuffleRight] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountShuffleRight] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountShuffleRight] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountShuffleRight] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手原地跳动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountNeigh", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountNeigh] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountNeigh] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountNeigh] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountNeigh] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        //骑手行走动作
        strTemp.clear();
        if ( !pReader.GetStringFieldByName( "MountBackAttack", strTemp ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [MountBackAttack] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [MountBackAttack] Error!!", iRow );
            // ToLog( "Drome.slk Loading [MountBackAttack] Error!!" && false );
            goto load_error;
        }
        pMount->dwMountAction[ItemDefine::MountBackAttack] = AllocStringCopy( strTemp.c_str() );
        iCol ++;

        ////骑手战斗待机
        //strTemp.clear();
        //if ( !pReader.GetStringFieldByName( "MountAttackIdle", strTemp ) )
        //{
        //    OutputSlkLoadingMessage( "Drome.slk Loading [MountAttackIdle] Error!!\r\n" );
        //    GetErrorLog()->logString( "Drome.slk Row %d Loading [MountAttackIdle] Error!!", iRow );
        //    // ToLog( "Drome.slk Loading [MountAttackIdle] Error!!" && false );
        //    goto load_error;
        //}
        //pMount->dwMountAction[ItemDefine::MountAttackIdle] = AllocStringCopy( strTemp.c_str() );
        //iCol ++;

        ////骑手战斗跑
        //strTemp.clear();
        //if ( !pReader.GetStringFieldByName( "MountAttack_run", strTemp ) )
        //{
        //    OutputSlkLoadingMessage( "Drome.slk Loading [MountAttack_run] Error!!\r\n" );
        //    GetErrorLog()->logString( "Drome.slk Row %d Loading [MountAttack_run] Error!!", iRow );
        //    // ToLog( "Drome.slk Loading [MountAttack_run] Error!!" && false );
        //    goto load_error;
        //}
        //pMount->dwMountAction[ItemDefine::MountAttackRun] = AllocStringCopy( strTemp.c_str() );
        //iCol ++;

        ////骑手马上拔刀
        //strTemp.clear();
        //if ( !pReader.GetStringFieldByName( "MountScabbard", strTemp ) )
        //{
        //    OutputSlkLoadingMessage( "Drome.slk Loading [MountScabbard] Error!!\r\n" );
        //    GetErrorLog()->logString( "Drome.slk Row %d Loading [MountScabbard] Error!!", iRow );
        //    // ToLog( "Drome.slk Loading [MountScabbard] Error!!" && false );
        //    goto load_error;
        //}
        //pMount->dwMountAction[ItemDefine::MountScabbard] = AllocStringCopy( strTemp.c_str() );
        //iCol ++;

        ////骑手马上收刀
        //strTemp.clear();
        //if ( !pReader.GetStringFieldByName( "MountDraw", strTemp ) )
        //{
        //    OutputSlkLoadingMessage( "Drome.slk Loading [MountDraw] Error!!\r\n" );
        //    GetErrorLog()->logString( "Drome.slk Row %d Loading [MountDraw] Error!!", iRow );
        //    // ToLog( "Drome.slk Loading [MountDraw] Error!!" && false );
        //    goto load_error;
        //}
        //pMount->dwMountAction[ItemDefine::MountDraw] = AllocStringCopy( strTemp.c_str() );
        //iCol ++;

        //起跳动画播放时间
        if ( !pReader.GetIntFieldByName( "JumpAnimTime", iValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [JumpAnimTime] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [JumpAnimTime] Error!!", iRow );
            // ToLog( "Drome.slk Loading [JumpAnimTime] Error!!" && false );
            goto load_error;
        }
        pMount->dwJumpAnimTime = iValue;
        iCol ++;

        //落地动画播放时间
        if ( !pReader.GetIntFieldByName( "DropAnimTime", iValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [DropAnimTime] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [DropAnimTime] Error!!", iRow );
            // ToLog( "Drome.slk Loading [DropAnimTime] Error!!" && false );
            goto load_error;
        }
        pMount->dwDropAnimTime = iValue;
        iCol ++;

        //落地跑动画播放时间
        if ( !pReader.GetIntFieldByName( "FallToTheGroundRun", iValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [FallToTheGroundRun] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [FallToTheGroundRun] Error!!", iRow );
            // ToLog( "Drome.slk Loading [FallToTheGroundRun] Error!!" && false );
            goto load_error;
        }
        pMount->dwFallToTheGroundRunTime = iValue;
        iCol ++;

        //起跳速度
        if ( !pReader.GetFloatFieldByName( "JumpSpeed", fValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [JumpSpeed] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [JumpSpeed] Error!!", iRow );
            // ToLog( "Drome.slk Loading [JumpSpeed] Error!!" && false );
            goto load_error;
        }
        pMount->fJumpSpeed = fValue;
        iCol ++;

        //下落速度
        if ( !pReader.GetFloatFieldByName( "DropSpeed", fValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [DropSpeed] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [DropSpeed] Error!!", iRow );
            // ToLog( "Drome.slk Loading [DropSpeed] Error!!" && false );
            goto load_error;
        }
        pMount->fDropSpeed = fValue;
        iCol ++;

        //过渡到起跳动画的时间
        if ( !pReader.GetIntFieldByName( "BlendJumpTime", iValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [BlendJumpTime] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [BlendJumpTime] Error!!", iRow );
            // ToLog( "Drome.slk Loading [BlendJumpTime] Error!!" && false );
            goto load_error;
        }
        pMount->dwBlendJumpTime = iValue;
        //iCol ++;

        // 左脚脚步声
        //if( !pReader.GetStringField( iCol, strRunSoundOfLeftFootPath ) )
        if( !pReader.GetStringFieldByName( "RunSoundOfLeftFoot", strRunSoundOfLeftFootPath ) )
        {
            OutputSlkLoadingMessage( "\t 载入[左脚脚步声]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入[左脚脚步声]出错", iRow );
            goto load_error;
        }
        pMount->dwRunSoundOfLeftFootAddr = AllocStringCopy( strRunSoundOfLeftFootPath.c_str() );
        iCol ++;

        // 右脚脚步声
        //if( !pReader.GetStringField( iCol, strRunSoundOfRightFootPath ) )
        if( !pReader.GetStringFieldByName( "RunSoundOfRightFoot", strRunSoundOfRightFootPath ) )
        {
            OutputSlkLoadingMessage( "\t 载入[右脚脚步声]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入[右脚脚步声]出错", iRow );
            goto load_error;
        }
        pMount->dwRunSoundOfRightFootAddr = AllocStringCopy( strRunSoundOfRightFootPath.c_str() );
        iCol ++;

        // 原地叫声
        //if( !pReader.GetStringField( iCol, strNeightSoundPath ) )
        if( !pReader.GetStringFieldByName( "NeightSound", strNeightSoundPath ) )
        {
            OutputSlkLoadingMessage( "\t 载入[原地叫声]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入[原地叫声]出错", iRow );
            goto load_error;
        }
        pMount->dwNeightSoundAddr = AllocStringCopy( strNeightSoundPath.c_str() );
        iCol ++;

        // 相机抬高高度
        if( !pReader.GetIntFieldByName( "CameraHeight", iValue ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑[摄像机抬高高度]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑[摄像机抬高高度]出错", iRow );
            goto load_error;
        }
        pMount->nCameraHeight = iValue;
        iCol++;

        if( !pReader.GetStringFieldByName( "FrontFootPrint", strNeightSoundPath ) )
        {
            OutputSlkLoadingMessage( "\t 载入[前脚印]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入[前脚印]出错", iRow );
            goto load_error;
        }
        pMount->dwFrontFootPrintAddr = AllocStringCopy( strNeightSoundPath.c_str() );
        iCol ++;

        if( !pReader.GetStringFieldByName( "BackFootPrint", strNeightSoundPath ) )
        {
            OutputSlkLoadingMessage( "\t 载入[后脚印]出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入[后脚印]出错", iRow );
            goto load_error;
        }
        pMount->dwBackFootPrintAddr = AllocStringCopy( strNeightSoundPath.c_str() );
        iCol ++;

        // 头像文件路径
        if( !pReader.GetStringFieldByName( "HeadPicture", strHeadPic ) )
        {
            OutputSlkLoadingMessage( "\t 载入坐骑头像文件路径出错!\r\n" );
            GetErrorLog()->logString( " Mount.slk 第%d行载入坐骑头像文件路径出错", iRow );
            goto load_error;
        }
        pMount->dwHeadPicAddr = AllocStringCopy( strHeadPic.c_str() );
        iCol ++;

        SLK_GET_INT  ( pMount->takeLevel, "TakeLevel");
        SLK_GET_INT  ( pMount->quality,   "Quality");
        SLK_GET_FLOAT( pMount->growMin,   "GrowMin");
        SLK_GET_FLOAT( pMount->growMax,   "GrowMax");

        SLK_GET_FLOAT( pMount->baseSum,             "BaseSum"       );
        SLK_GET_FLOAT( pMount->baseMin[EBaseAttr_Strength], "InitLiLiangMin");
        SLK_GET_FLOAT( pMount->baseMax[EBaseAttr_Strength], "InitLiLiangMax");
        SLK_GET_FLOAT( pMount->baseMin[EBaseAttr_Agility],  "InitMinJieMin" );
        SLK_GET_FLOAT( pMount->baseMax[EBaseAttr_Agility],  "InitMinJieMax" );
        SLK_GET_FLOAT( pMount->baseMin[EBaseAttr_Stamina],   "InitTiZhiMin"  );
        SLK_GET_FLOAT( pMount->baseMax[EBaseAttr_Stamina],   "InitTiZhiMax"  );
        SLK_GET_FLOAT( pMount->baseMin[EBaseAttr_Intelligence],   "InitShuFaMin"  );
        SLK_GET_FLOAT( pMount->baseMax[EBaseAttr_Intelligence],   "InitShuFaMax"  );
        /*SLK_GET_FLOAT( pMount->baseMin[BA_JinGu],   "InitJinGuMin"  );
        SLK_GET_FLOAT( pMount->baseMax[BA_JinGu],   "InitJinGuMax"  );*/

        SLK_GET_FLOAT( pMount->addSum,             "AddSum"       );
        SLK_GET_FLOAT( pMount->addMin[EBaseAttr_Strength], "AddLiLiangMin");
        SLK_GET_FLOAT( pMount->addMax[EBaseAttr_Strength], "AddLiLiangMax");
        SLK_GET_FLOAT( pMount->addMin[EBaseAttr_Agility],  "AddMinJieMin" );
        SLK_GET_FLOAT( pMount->addMax[EBaseAttr_Agility],  "AddMinJieMax" );
        SLK_GET_FLOAT( pMount->addMin[EBaseAttr_Stamina],   "AddTiZhiMin"  );
        SLK_GET_FLOAT( pMount->addMax[EBaseAttr_Stamina],   "AddTiZhiMax"  );
        SLK_GET_FLOAT( pMount->addMin[EBaseAttr_Intelligence],   "AddShuFaMin"  );
        SLK_GET_FLOAT( pMount->addMax[EBaseAttr_Intelligence],   "AddShuFaMax"  );
        /*SLK_GET_FLOAT( pMount->addMin[BA_JinGu],   "AddJinGuMin"  );
        SLK_GET_FLOAT( pMount->addMax[BA_JinGu],   "AddJinGuMax"  );*/

        SLK_GET_INT( pMount->sawyMin, "SawyMin" );
        SLK_GET_INT( pMount->sawyMax, "SawyMax" );

        SLK_GET_INT  ( pMount->selfSpeedSkillId,  "SelfSpeedSkill");

        SLK_GET_INT  ( pMount->selfSkillNum,  "SelfSkillNum");
        SLK_GET_INT  ( pMount->selfSkillRate, "SelfSkillPro");
        for ( int i=0; i<ItemDefine::SDrome::DCD_SELFSKILLIDCOUNT; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "SelfSkill%d", i+1);
            SLK_GET_INT( pMount->selfSkillId[i],  szTemp);
        }

        SLK_GET_INT  ( pMount->masterSkillNum,  "MasterSkillNum");
        SLK_GET_INT  ( pMount->masterSkillRate, "MasterSkillPro");
        for ( int i=0; i<ItemDefine::SDrome::DCD_MASTERSKILLIDCOUNT; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "MasterSkill%d", i+1);
            SLK_GET_INT( pMount->masterSkillId[i],  szTemp);
        }

        SLK_GET_INT  ( pMount->masterUseSkillNum,  "MasterUseSkillNum");
        SLK_GET_INT  ( pMount->masterUseSkillRate, "MasterUseSkillPro");
        for ( int i=0; i<ItemDefine::SDrome::DCD_MASTERUSESKILLCOUNT; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "MasterUseSkill%d", i+1);
            SLK_GET_INT( pMount->masterUseSKillId[i],  szTemp);
        }

        // 洗点相关
        for ( int i = 0; i < 4; ++i )
        {
            char szProbability[21] = {0};
            sprintf_s( szProbability, sizeof( szProbability ) - 1, "Probability%d", i + 1 );
            SLK_GET_INT( pMount->arrayProbability[i],  szProbability );
        }

        for ( int i = 0; i < 4; ++i )
        {
            char szID[21] = {0};
            sprintf_s( szID, sizeof( szID ) - 1, "ResetMountID%d", i + 1 );
            SLK_GET_INT( pMount->arrayMountID[i],  szID );
        }

        SLK_GET_INT  ( pMount->nextGeneration,  "Generation");
        SLK_GET_INT  ( pMount->stOperaType,     "OperaType" );
        SLK_GET_INT  ( pMount->stMaxRange,      "MaxRange"  );

        pMount->stIndex = m_vecDrome.size();
        m_mapDrome.insert( mapDrome::value_type( pMount->GetName(), pMount->stIndex ) );

        m_vecDrome.push_back( pMount);
        continue;

load_error:
        OutputSlkLoadingMessage( "\t Mount.slk 第 %d 行载入失败!\r\n",iRow-1 );
        return false;
    }
    return true;
}

bool CItemDetail::LoadXmlMount( const char* szFileName )
{
    if (szFileName == NULL)
    { return false; }

    MeXmlDocument mMeXmlDoc;
    if (!mMeXmlDoc.LoadFile(szFileName))
    { return false; }

    MeXmlElement *pRoot = mMeXmlDoc.FirstChildElement("Project");
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pMountTree = pRoot->FirstChildElement("Mounts");
    if (pMountTree == NULL)
    { return false; }

    MeXmlElement *pItemMount = pMountTree->FirstChildElement("Mount");

    int iValue = 0;
    double dValue = 0.000000;

    while ( pItemMount != NULL)
    {
        ItemDefine::SDrome *pMount= (ItemDefine::SDrome *)AllocItem( 0, sizeof(ItemDefine::SDrome) );

        if ( pItemMount->Attribute("ID", &iValue) == NULL)
        { return false; }

        pMount->stId = iValue;

        Common::_tstring strMountName;
        strMountName.fromUTF8( pItemMount->Attribute("Name") );
        pMount->dwNameAddr = AllocStringCopy(strMountName.c_str());//名称

        Common::_tstring strModlePath;
        strModlePath.fromUTF8( pItemMount->Attribute("ModelPath") );
        pMount->dwModelAddr = AllocStringCopy(strModlePath.c_str());//模型地址

		for (int i = 0; i <= SMountItem::MICD_MountMaxLevel; ++i)
		{
			char szTmp[65] = {0};
			sprintf_s(szTmp, sizeof(szTmp) - 1,"ModelID%d", i);
			pItemMount->Attribute(szTmp, &iValue);
			pMount->modelID[i] = iValue;//坐骑模型ID
		}
		

        pItemMount->Attribute("OperaType", &iValue);
        pMount->stOperaType = iValue;//操作类型

        pItemMount->Attribute("Type", &iValue);
        pMount->stType = iValue;//类型

        pItemMount->Attribute("CarryNum", &iValue);
        pMount->stCarry = iValue; //运载能力

        pItemMount->Attribute("FlyHeight", &dValue);
        pMount->fFlyHeight = dValue; //飞行高度

        pItemMount->Attribute("Inertia", &dValue);
        pMount->fInertia = dValue;//惯性

        pItemMount->Attribute("Speed", &dValue);
        pMount->fSpeed = dValue;//速度

        pItemMount->Attribute("RunStep", &dValue);
        pMount->fRunningStep = dValue;//Run步长

        pItemMount->Attribute("WalkStep", &dValue);
        pMount->fWalkingStep = dValue;//Walk步长

        pItemMount->Attribute("JumpHeight", &dValue);
        pMount->fJumpingHeight = dValue; //跳跃高度

        pItemMount->Attribute("MaxRange", &iValue);
        pMount->stMaxRange = iValue;  

        pItemMount->Attribute("MoveType", &iValue);
        pMount->shMoveType = iValue;//移动类型

        pItemMount->Attribute("DromeScaleCorrect", &dValue);
        pMount->fDromeScaleCorrect = dValue;//坐骑体型修正

        pItemMount->Attribute("RiderScaleCorrect", &dValue);
        pMount->fRiderScaleCorrect = dValue; //骑手体型修正

        pItemMount->Attribute("UseTime", &iValue);
        pMount->dwMaxLifeTime = iValue;//最大使用时间

        Common::_tstring strSkin;
        strSkin.fromUTF8( pItemMount->Attribute("Skin") );
        pMount->dwSkinAddr = AllocStringCopy( strSkin.c_str() );//皮肤地址

        pItemMount->Attribute("AddStatus", &iValue);
        pMount->nAddStatusID = iValue;//附加状态ID

        Common::_tstring strRideEffect;
        strRideEffect.fromUTF8( pItemMount->Attribute("OnRideEffectPath") );
        pMount->dwMountEffectAddr = AllocStringCopy(strRideEffect.c_str());//上坐骑的特效路径

        Common::_tstring strOffRideEffect;
        strOffRideEffect.fromUTF8( pItemMount->Attribute("OffRideEffectPath") );
        pMount->dwDisMountEffectAddr = AllocStringCopy(strOffRideEffect.c_str());//下坐骑的特效路径

        Common::_tstring strMountDrive;
        strMountDrive.fromUTF8( pItemMount->Attribute("MountDrive") );
        pMount->dwMountAction[ItemDefine::MountDrive] = AllocStringCopy( strMountDrive.c_str() );//骑手空闲动作

        Common::_tstring strMountWalk;
        strMountWalk.fromUTF8( pItemMount->Attribute("MountWalk"));
        pMount->dwMountAction[ItemDefine::MountWalk] = AllocStringCopy( strMountWalk.c_str() );//骑手行走动作

        Common::_tstring strMountWalkBack;
        strMountWalkBack.fromUTF8( pItemMount->Attribute("MountWalkBackWards") );
        pMount->dwMountAction[ItemDefine::MountWalkBackWards] = AllocStringCopy( strMountWalkBack.c_str() );//骑手后退动作

        Common::_tstring strMountRun;
        strMountRun.fromUTF8( pItemMount->Attribute("MountRun") );
        pMount->dwMountAction[ItemDefine::MountRun] = AllocStringCopy( strMountRun.c_str() );//骑手奔跑动作

        Common::_tstring strMountJump;
        strMountJump.fromUTF8( pItemMount->Attribute("MountJump") );
        pMount->dwMountAction[ItemDefine::MountJump] = AllocStringCopy( strMountJump.c_str() );//骑手跳跃动作

        Common::_tstring strMountFallToGroundRun;
        strMountFallToGroundRun.fromUTF8( pItemMount->Attribute("MountFallToTheGroundRun") );
        pMount->dwMountAction[ItemDefine::MountFallToTheGroundRun] = AllocStringCopy( strMountFallToGroundRun.c_str() );//骑手落地跑动作

        Common::_tstring strMountDrop;
        strMountDrop.fromUTF8( pItemMount->Attribute("MountDrop") );
        pMount->dwMountAction[ItemDefine::MountDrop] = AllocStringCopy( strMountDrop.c_str() );//骑手落地动作

        Common::_tstring strMountGlide;
        strMountGlide.fromUTF8( pItemMount->Attribute("MountGlide") );
        pMount->dwMountAction[ItemDefine::MountGlide] = AllocStringCopy( strMountGlide.c_str() );//骑手滑行动作

        Common::_tstring strMountShuffleLeft;
        strMountShuffleLeft.fromUTF8( pItemMount->Attribute("MountShuffleLeft") );
        pMount->dwMountAction[ItemDefine::MountShuffleLeft] = AllocStringCopy( strMountShuffleLeft.c_str() );//骑手左转动作

        Common::_tstring strMountShuffleRight;
        strMountShuffleRight.fromUTF8( pItemMount->Attribute("MountShuffleRight") );
        pMount->dwMountAction[ItemDefine::MountShuffleRight] = AllocStringCopy( strMountShuffleRight.c_str() );//骑手右转动作

        Common::_tstring strMountNeigh;
        strMountNeigh.fromUTF8( pItemMount->Attribute("MountNeigh") );
        pMount->dwMountAction[ItemDefine::MountNeigh] = AllocStringCopy( strMountNeigh.c_str() );//骑手原地起跳动作

        Common::_tstring strMountBackAttack;
        strMountBackAttack.fromUTF8( pItemMount->Attribute("MountBackAttack") );
        pMount->dwMountAction[ItemDefine::MountBackAttack] = AllocStringCopy( strMountBackAttack.c_str() );//骑手行走动作

        pItemMount->Attribute("FallToTheGroundRun", &iValue);
        pMount->dwFallToTheGroundRunTime = iValue;//

        pItemMount->Attribute("JumpAnimTime", &iValue);
        pMount->dwJumpAnimTime = iValue;//跳跃动画播放时间

        pItemMount->Attribute("DropAnimTime", &iValue);
        pMount->dwDropAnimTime = iValue;//落地动画播放时间

        pItemMount->Attribute("JumpSpeed", &dValue);
        pMount->fJumpSpeed = dValue;//起跳速度

        pItemMount->Attribute("DropSpeed", &dValue);
        pMount->fDropSpeed = dValue;//落地速度

        pItemMount->Attribute("BlendJumpTime", &iValue);
        pMount->dwBlendJumpTime = iValue;// 起跳过渡时间

        Common::_tstring strRunSoundOfLeftFoot;
        strRunSoundOfLeftFoot.fromUTF8( pItemMount->Attribute("RunSoundOfLeftFoot") );
        pMount->dwRunSoundOfLeftFootAddr = AllocStringCopy( strRunSoundOfLeftFoot.c_str() );//左脚步声音

        Common::_tstring strRunSoundOfRightFoot;
        strRunSoundOfRightFoot.fromUTF8( pItemMount->Attribute("RunSoundOfRightFoot") );
        pMount->dwRunSoundOfRightFootAddr = AllocStringCopy( strRunSoundOfRightFoot.c_str() );//左脚步声音

        Common::_tstring strNeightSound;
        strNeightSound.fromUTF8( pItemMount->Attribute("NeightSound") );
        pMount->dwNeightSoundAddr = AllocStringCopy( strNeightSound.c_str() );//坐骑原地叫声

        pItemMount->Attribute("CameraHeight", &iValue);
        pMount->nCameraHeight = iValue;//摄像机抬高高度

        Common::_tstring strFrontFootPrint;
        strFrontFootPrint.fromUTF8( pItemMount->Attribute("FrontFootPrint") );
        pMount->dwFrontFootPrintAddr = AllocStringCopy( strFrontFootPrint.c_str() );//前脚印

        Common::_tstring strBackFootPrint;
        strBackFootPrint.fromUTF8( pItemMount->Attribute("BackFootPrint") );
        pMount->dwBackFootPrintAddr = AllocStringCopy( strBackFootPrint.c_str() );//后脚印

        Common::_tstring strHeadPicture;
        strHeadPicture.fromUTF8( pItemMount->Attribute("HeadPicture") );
        pMount->dwHeadPicAddr = AllocStringCopy( strHeadPicture.c_str() );//坐骑头像

        pItemMount->Attribute("TakeLevel", &iValue);
        pMount->takeLevel = iValue;//携带等级

        pItemMount->Attribute("Quality", &iValue);
        pMount->quality = iValue;//坐骑品质

        pItemMount->Attribute("GrowMin", &dValue);
        pMount->growMin = dValue;//成长最低值

        pItemMount->Attribute("GrowMax", &dValue);
        pMount->growMax = dValue;//成长最高值

        pItemMount->Attribute("BaseSum", &dValue);
        pMount->baseSum = dValue;//初始总和

        pItemMount->Attribute("InitLiLiangMin", &dValue);
        pMount->baseMin[EBaseAttr_Strength] = dValue;//初始力量最小值

        pItemMount->Attribute("InitLiLiangMax", &dValue);
        pMount->baseMax[EBaseAttr_Strength] = dValue;//初始力量最大值

        pItemMount->Attribute("InitMinJieMin", &dValue);
        pMount->baseMin[EBaseAttr_Agility] = dValue;//初始敏捷最小值

        pItemMount->Attribute("InitMinJieMax", &dValue);
        pMount->baseMax[EBaseAttr_Agility] = dValue;//初始敏捷最大值

        pItemMount->Attribute("InitTiZhiMin", &dValue);
        pMount->baseMin[EBaseAttr_Stamina] = dValue;//初始体制最小值

        pItemMount->Attribute("InitTiZhiMax", &dValue);
        pMount->baseMax[EBaseAttr_Stamina] = dValue;//初始体质最大值

        pItemMount->Attribute("InitShuFaMin", &dValue);
        pMount->baseMin[EBaseAttr_Intelligence] = dValue;//初始术法最小值

        pItemMount->Attribute("InitShuFaMax", &dValue);
        pMount->baseMax[EBaseAttr_Intelligence] = dValue;//初始术法最大值

        //pItemMount->Attribute("InitJinGuMin", &dValue);
        //pMount->baseMin[BA_JinGu] = dValue;//初始筋骨最小值

        //pItemMount->Attribute("InitJinGuMax", &dValue);
        //pMount->baseMax[BA_JinGu] = dValue;//初始筋骨最大值

        pItemMount->Attribute("AddSum", &dValue);
        pMount->addSum = dValue;//资质总和

        pItemMount->Attribute("AddLiLiangMin", &dValue);
        pMount->addMin[EBaseAttr_Strength] = dValue;//资质力量最小值

        pItemMount->Attribute("AddLiLiangMax", &dValue);
        pMount->addMax[EBaseAttr_Strength] = dValue;//资质力量最大值

        pItemMount->Attribute("AddMinJieMin", &dValue);
        pMount->addMin[EBaseAttr_Agility] = dValue;//资质敏捷最小值

        pItemMount->Attribute("AddMinJieMax", &dValue);
        pMount->addMax[EBaseAttr_Agility] = dValue;//资质敏捷最大值

        pItemMount->Attribute("AddTiZhiMin", &dValue);
        pMount->addMin[EBaseAttr_Stamina] = dValue;//资质体质最小值

        pItemMount->Attribute("AddTiZhiMax", &dValue);
        pMount->addMax[EBaseAttr_Stamina] = dValue;//资质体质最大值

        pItemMount->Attribute("AddShuFaMin", &dValue);
        pMount->addMin[EBaseAttr_Intelligence] = dValue;//资质术法最小值

        pItemMount->Attribute("AddShuFaMax", &dValue);
        pMount->addMax[EBaseAttr_Intelligence] = dValue;//资质术法最大值

        //pItemMount->Attribute("AddJinGuMin", &dValue);
        //pMount->addMin[BA_JinGu] = dValue;//资质筋骨最小值

        //pItemMount->Attribute("AddJinGuMax", &dValue);
        //pMount->addMax[BA_JinGu] = dValue;//资质筋骨最大值

        pItemMount->Attribute("SawyMin", &iValue);
        pMount->sawyMin = iValue;//悟性最小值

        pItemMount->Attribute("SawyMax", &iValue);
        pMount->sawyMax = iValue;//悟性最大值

        pItemMount->Attribute("SelfSpeedSkill", &iValue);
        pMount->selfSpeedSkillId = iValue;//悟性最大值

        pItemMount->Attribute("SelfSkillNum", &iValue);
        pMount->selfSkillNum = iValue;//自身的技能数

        pItemMount->Attribute("SelfSkillPro", &iValue);
        pMount->selfSkillRate = iValue;//自身的技能几率

        for (int i = 0; i < ItemDefine::SDrome::DCD_SELFSKILLIDCOUNT; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1,"SelfSkill%d", i+1);
            pItemMount->Attribute(szTmp, &iValue);
            pMount->selfSkillId[i] = iValue;//坐骑自身的技能
        }

        pItemMount->Attribute("MasterSkillNum", &iValue);
        pMount->masterSkillNum = iValue;//主人技能个数

        pItemMount->Attribute("MasterSkillPro", &iValue);
        pMount->masterSkillRate = iValue;//主人技能随机几率

        for (int i = 0; i < ItemDefine::SDrome::DCD_SELFSKILLIDCOUNT; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "MasterSkill%d", i+1);
            pItemMount->Attribute(szTmp, &iValue);
            pMount->masterSkillId[i] = iValue;//坐骑主人技能
        }

        pItemMount->Attribute("MasterUseSkillNum", &iValue);
        pMount->masterUseSkillNum = iValue;//主人释放技能个数

        pItemMount->Attribute("MasterUseSkillPro", &iValue);
        pMount->masterUseSkillRate = iValue;//主人产生技能随机几率

        for (int i = 0; i < ItemDefine::SDrome::DCD_SELFSKILLIDCOUNT; ++i)
        {
            char szTmp[64] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "MasterUseSkill%d", i+1);
            pItemMount->Attribute(szTmp, &iValue);
            pMount->masterUseSKillId[i] = iValue;//主人释放的技能
        }

        // 洗点相关
        for ( int i = 0; i < 4; ++i )
        {
            char szProbability[21] = {0};
            sprintf_s( szProbability, sizeof( szProbability ) - 1, "Probability%d", i + 1 );
            pItemMount->Attribute(szProbability, &iValue);
            pMount->arrayProbability[i] = iValue;
        }

        for ( int i = 0; i < 4; ++i )
        {
            char szID[21] = {0};
            sprintf_s( szID, sizeof( szID ) - 1, "ResetMountID%d", i + 1 );
            pItemMount->Attribute(szID, &iValue);
            pMount->arrayMountID[i] = iValue;
        }

        pItemMount->Attribute("Generation", &iValue);
        pMount->nextGeneration = iValue;//主人产生技能随机几率

        //pMount->stIndex = m_vecDrome.size();
        //m_mapDrome.insert( mapDrome::value_type( pMount->GetName(), pMount->stIndex ) );
        m_vecDrome.push_back( pMount);
        pItemMount = pItemMount->NextSiblingElement();
    }

    return true;
}


bool CItemDetail::SaveXmlMount( const char *szFileName)
{
    if (szFileName == NULL)
    { return false; }

    MeXmlDocument MountMeXml;
    MountMeXml.InsertEndChild(MeXmlDeclaration("1.0", "utf-8", "yes"));
    MeXmlElement *pRoot = MountMeXml.InsertEndChild(("Project"))->ToElement();
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pMounts = pRoot->InsertEndChild(("Mounts"))->ToElement();
    if (pMounts == NULL)
    { return false; }

    vectorDrome::iterator iterBegin = m_vecDrome.begin();
    vectorDrome::iterator iterEnd = m_vecDrome.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if ( *iterBegin == NULL )
        { continue;}
        ItemDefine::SDrome *pMountIter = *iterBegin;
        MeXmlElement *pMount = pMounts->InsertEndChild(("Mount"))->ToElement();
        if (pMount == NULL)
        { continue; }

        pMount->SetAttribute("ID", pMountIter->stId);

        Common::_tstring strName = pMountIter->GetName();
        pMount->SetAttribute("Name", strName.toUTF8().c_str());

        Common::_tstring strModelPath = pMountIter->GetModelPath();
        pMount->SetAttribute("ModelPath", strModelPath.toUTF8().c_str());

		for (int i=0; i <= SMountItem::MICD_MountMaxLevel; ++i)
		{
			char szTmp[65] = {0};
			sprintf_s(szTmp, sizeof(szTmp) - 1, "ModelID%d", i);
			pMount->SetAttribute(szTmp, pMountIter->modelID[i]);
		}

        pMount->SetAttribute("Type", pMountIter->stType);
        pMount->SetAttribute("OperaType", pMountIter->stOperaType);
        pMount->SetAttribute("CarryNum", pMountIter->stCarry);
        pMount->SetDoubleAttribute("FlyHeight", pMountIter->fFlyHeight);
        pMount->SetDoubleAttribute("Inertia", pMountIter->fInertia);
        pMount->SetDoubleAttribute("Speed", pMountIter->fSpeed);
        pMount->SetDoubleAttribute("RunStep", pMountIter->fRunningStep);
        pMount->SetDoubleAttribute("WalkStep", pMountIter->fWalkingStep);
        pMount->SetDoubleAttribute("JumpHeight", pMountIter->fJumpingHeight);
        pMount->SetAttribute("MaxRange", pMountIter->stMaxRange);
        pMount->SetAttribute("MoveType", pMountIter->shMoveType);
        pMount->SetDoubleAttribute("DromeScaleCorrect", pMountIter->fDromeScaleCorrect);
        pMount->SetDoubleAttribute("RiderScaleCorrect", pMountIter->fRiderScaleCorrect);
        pMount->SetAttribute("UseTime", pMountIter->dwMaxLifeTime);

        Common::_tstring strSkin = pMountIter->GetSkinName();
        pMount->SetAttribute("Skin", strSkin.toUTF8().c_str());

        pMount->SetAttribute("AddStatus", pMountIter->nAddStatusID);

        Common::_tstring strOnRideEffectPath = pMountIter->GetMountEffectPath();
        pMount->SetAttribute("OnRideEffectPath", strOnRideEffectPath.toUTF8().c_str());

        Common::_tstring strOffRideEffectPath = pMountIter->GetDisMountEffectPath();
        pMount->SetAttribute("OffRideEffectPath", strOffRideEffectPath.toUTF8().c_str());

        Common::_tstring strMountDrive = pMountIter->GetMountAction(ItemDefine::MountDrive);
        pMount->SetAttribute("MountDrive", strMountDrive.toUTF8().c_str());

        Common::_tstring strMountWalk = pMountIter->GetMountAction(ItemDefine::MountWalk);
        pMount->SetAttribute("MountWalk", strMountWalk.toUTF8().c_str());

        Common::_tstring strMountWalkBackWards = pMountIter->GetMountAction(ItemDefine::MountWalkBackWards);
        pMount->SetAttribute("MountWalkBackWards", strMountWalkBackWards.toUTF8().c_str());

        Common::_tstring strMountRun = pMountIter->GetMountAction(ItemDefine::MountRun);
        pMount->SetAttribute("MountRun", strMountRun.toUTF8().c_str());

        Common::_tstring strMountJump = pMountIter->GetMountAction(ItemDefine::MountJump);
        pMount->SetAttribute("MountJump", strMountJump.toUTF8().c_str());

        Common::_tstring strMountFallToTheGroundRun = pMountIter->GetMountAction(ItemDefine::MountFallToTheGroundRun);
        pMount->SetAttribute("MountFallToTheGroundRun", strMountFallToTheGroundRun.toUTF8().c_str());

        Common::_tstring strMountDrop = pMountIter->GetMountAction(ItemDefine::MountDrop);
        pMount->SetAttribute("MountDrop", strMountDrop.toUTF8().c_str());

        Common::_tstring strMountGlide = pMountIter->GetMountAction(ItemDefine::MountGlide);
        pMount->SetAttribute("MountGlide", strMountGlide.toUTF8().c_str());

        Common::_tstring strMountShuffleLeft = pMountIter->GetMountAction(ItemDefine::MountShuffleLeft);
        pMount->SetAttribute("MountShuffleLeft", strMountShuffleLeft.toUTF8().c_str());

        Common::_tstring strMountShuffleRight = pMountIter->GetMountAction(ItemDefine::MountShuffleRight);
        pMount->SetAttribute("MountShuffleRight", strMountShuffleRight.toUTF8().c_str());

        Common::_tstring strMountNeigh = pMountIter->GetMountAction(ItemDefine::MountNeigh);
        pMount->SetAttribute("MountNeigh", strMountNeigh.toUTF8().c_str());

        Common::_tstring strMountBackAttack = pMountIter->GetMountAction(ItemDefine::MountBackAttack);
        pMount->SetAttribute("MountBackAttack", strMountBackAttack.toUTF8().c_str());

        pMount->SetAttribute("JumpAnimTime", pMountIter->dwJumpAnimTime);
        pMount->SetAttribute("DropAnimTime", pMountIter->dwDropAnimTime);
        pMount->SetAttribute("FallToTheGroundRun", pMountIter->dwFallToTheGroundRunTime);
        pMount->SetDoubleAttribute("JumpSpeed", pMountIter->fJumpSpeed);
        pMount->SetDoubleAttribute("DropSpeed", pMountIter->fDropSpeed);
        pMount->SetAttribute("BlendJumpTime", pMountIter->dwBlendJumpTime);

        Common::_tstring strLeftFootSound = pMountIter->GetRunSoundOfLeftFootPath();
        pMount->SetAttribute("RunSoundOfLeftFoot", strLeftFootSound.toUTF8().c_str());

        Common::_tstring strRightFootSound = pMountIter->GetRunSoundOfRightFootPath();
        pMount->SetAttribute("RunSoundOfRightFoot", strRightFootSound.toUTF8().c_str());

        Common::_tstring strNeightSound = pMountIter->GetNeightSoundPath();
        pMount->SetAttribute("NeightSound", strNeightSound.toUTF8().c_str());

        pMount->SetAttribute("CameraHeight", pMountIter->GetMountCameraHeight());

        Common::_tstring strFrontFootPrint = pMountIter->GetFrontFootPrintPath();
        pMount->SetAttribute("FrontFootPrint", strFrontFootPrint.toUTF8().c_str());

        Common::_tstring strBackFootPrint = pMountIter->GetBackFootPrintPath();
        pMount->SetAttribute("BackFootPrint", strBackFootPrint.toUTF8().c_str());

        Common::_tstring strHeadPic = pMountIter->GetHeadPicPath();
        pMount->SetAttribute("HeadPicture", strHeadPic.toUTF8().c_str() );

        pMount->SetAttribute("TakeLevel", pMountIter->takeLevel);
        pMount->SetAttribute("Quality", pMountIter->quality);
        pMount->SetDoubleAttribute("GrowMin", pMountIter->growMin);
        pMount->SetDoubleAttribute("GrowMax", pMountIter->growMax);
        pMount->SetDoubleAttribute("BaseSum", pMountIter->baseSum);
        pMount->SetDoubleAttribute("InitLiLiangMin", pMountIter->baseMin[EBaseAttr_Strength]);
        pMount->SetDoubleAttribute("InitMinJieMin", pMountIter->baseMin[EBaseAttr_Agility]);
        pMount->SetDoubleAttribute("InitTiZhiMin", pMountIter->baseMin[EBaseAttr_Stamina]);
        pMount->SetDoubleAttribute("InitShuFaMin", pMountIter->baseMin[EBaseAttr_Intelligence]);
        //pMount->SetDoubleAttribute("InitJinGuMin", pMountIter->baseMin[BA_JinGu]);
        pMount->SetDoubleAttribute("InitLiLiangMax", pMountIter->baseMax[EBaseAttr_Strength]);
        pMount->SetDoubleAttribute("InitMinJieMax", pMountIter->baseMax[EBaseAttr_Agility]);
        pMount->SetDoubleAttribute("InitTiZhiMax", pMountIter->baseMax[EBaseAttr_Stamina]);
        pMount->SetDoubleAttribute("InitShuFaMax", pMountIter->baseMax[EBaseAttr_Intelligence]);
        /*pMount->SetDoubleAttribute("InitJinGuMax", pMountIter->baseMax[BA_JinGu]);*/
        pMount->SetDoubleAttribute("AddSum", pMountIter->addSum);
        pMount->SetDoubleAttribute("AddLiLiangMin", pMountIter->addMin[EBaseAttr_Strength]);
        pMount->SetDoubleAttribute("AddMinJieMin", pMountIter->addMin[EBaseAttr_Agility]);
        pMount->SetDoubleAttribute("AddTiZhiMin", pMountIter->addMin[EBaseAttr_Stamina]);
        pMount->SetDoubleAttribute("AddShuFaMin", pMountIter->addMin[EBaseAttr_Intelligence]);
        /*pMount->SetDoubleAttribute("AddJinGuMin", pMountIter->addMin[BA_JinGu]);*/
        pMount->SetDoubleAttribute("AddLiLiangMax", pMountIter->addMax[EBaseAttr_Strength]);
        pMount->SetDoubleAttribute("AddMinJieMax", pMountIter->addMax[EBaseAttr_Agility]);
        pMount->SetDoubleAttribute("AddTiZhiMax", pMountIter->addMax[EBaseAttr_Stamina]);
        pMount->SetDoubleAttribute("AddShuFaMax", pMountIter->addMax[EBaseAttr_Intelligence]);
        /*pMount->SetDoubleAttribute("AddJinGuMax", pMountIter->addMax[BA_JinGu]);*/
        pMount->SetAttribute("SawyMin", pMountIter->sawyMin);
        pMount->SetAttribute("SawyMax", pMountIter->sawyMax);
        pMount->SetAttribute("SelfSpeedSkill", pMountIter->selfSpeedSkillId);
        pMount->SetAttribute("SelfSkillNum", pMountIter->selfSkillNum);
        pMount->SetAttribute("SelfSkillPro", pMountIter->selfSkillRate);

        for (int i=0; i<ItemDefine::SDrome::DCD_SELFSKILLIDCOUNT; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "SelfSkill%d", i+1);
            pMount->SetAttribute(szTmp, pMountIter->selfSkillId[i]);
        }

        pMount->SetAttribute("MasterSkillNum", pMountIter->masterSkillNum);
        pMount->SetAttribute("MasterSkillPro", pMountIter->masterSkillRate);

        for (int i=0; i<ItemDefine::SDrome::DCD_MASTERSKILLIDCOUNT; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "MasterSkill%d", i+1);
            pMount->SetAttribute(szTmp, pMountIter->masterSkillId[i]);
        }

        pMount->SetAttribute("MasterUseSkillNum", pMountIter->masterUseSkillNum);
        pMount->SetAttribute("MasterUseSkillPro", pMountIter->masterUseSkillRate);

        for (int i=0; i<ItemDefine::SDrome::DCD_MASTERUSESKILLCOUNT; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "MasterUseSkill%d", i+1);
            pMount->SetAttribute(szTmp, pMountIter->masterUseSKillId[i]);
        }

        for (int i=0; i<4; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "Probability%d", i+1);
            pMount->SetAttribute(szTmp, pMountIter->arrayProbability[i]);
        }
        for (int i=0; i<4; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "ResetMountID%d", i+1);
            pMount->SetAttribute(szTmp, pMountIter->arrayMountID[i]);
        }

        pMount->SetAttribute("Generation", pMountIter->nextGeneration);
    }
    return MountMeXml.SaveFile(szFileName);
}

#pragma warning( pop )