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
            OutputSlkLoadingMessage( "Error:����Mount��Ҫ���ڴ���� [%d]\r\n", iRow );
            return false;
        }

        iCol = 1;

        // ����
        if( !pReader.GetIntField( iCol, iValue ) )
        {
            OutputSlkLoadingMessage( "\t ����������ID����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������������ID����", iRow );
            goto load_error;
        }
        pMount->stId = iValue;
        iCol ++;

        // ����
        if( !pReader.GetStringField( iCol,strName ) )
        {
            OutputSlkLoadingMessage( "\t �����������Ƴ���!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d�������������Ƴ���", iRow );
            goto load_error;
        }
        pMount->dwNameAddr = AllocStringCopy( strName.c_str() );

        OutputSlkLoadingMessage( "\t Load Mount %s\r\n", strName.c_str() );

        iCol ++;

        // ģ���ļ�·��
        if( !pReader.GetStringField( iCol, strModelPath ) )
        {
            OutputSlkLoadingMessage( "\t ��������ģ���ļ�·������!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d����������ģ���ļ�·������", iRow );
            goto load_error;
        }
        pMount->dwModelAddr = AllocStringCopy( strModelPath.c_str() );
        iCol ++;

		// ģ��ID
		int nend = iCol + SMountItem::MICD_MountMaxLevel;
		for (int i = 0; iCol <= nend && i <= SMountItem::MICD_MountMaxLevel; iCol++, i++)
		{
			if( !pReader.GetIntField( iCol, iValue ) )
			{
				OutputSlkLoadingMessage( "\t ��������ģ��ID����!\r\n" );
				GetErrorLog()->logString( " Mount.slk ��%d����������ģ��ID����", iRow );
				goto load_error;
			}
			pMount->modelID[i] = iValue;
		}

        // ����
        if( !pReader.GetIntField(iCol, iValue ))
        {
            OutputSlkLoadingMessage( "\t �����������ͳ���!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d�������������ͳ���", iRow );
            goto load_error;
        }
        pMount->stType = iValue;
        iCol ++;

        // ��������
        if( !pReader.GetIntField( iCol, iValue ) )
        {
            OutputSlkLoadingMessage( "\t ��������������������!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d����������������������", iRow );
            goto load_error;
        }
        pMount->stCarry = iValue;
        iCol ++;

        // ���и߶�
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t ����������и߶ȳ���!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������������и߶ȳ���", iRow );
            goto load_error;
        }
        pMount->fFlyHeight = fValue;
        iCol ++;

        // ����
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t ����������Գ���!\r\n" );
            GetErrorLog()->logString( "Mount.slk ��%d������������Գ���", iRow );
            goto load_error;
        }
        pMount->fInertia = fValue;
        iCol ++;

        // �ٶ�
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t ���������ٶȳ���!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d�����������ٶȳ���", iRow );
            goto load_error;
        }
        pMount->fSpeed = fValue;
        iCol ++;

        // Run����
        //if( !pReader.GetFloatField( iCol, fValue ) )
        if( !pReader.GetFloatFieldByName( "RunStep", fValue ) )
        {
            OutputSlkLoadingMessage( "\t ��������[Run����]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d����������[Run����]����", iRow );
            goto load_error;
        }
        pMount->fRunningStep = fValue;
        iCol ++;

        // Walk����
        if( !pReader.GetFloatFieldByName( "WalkStep", fValue ) )
        {
            OutputSlkLoadingMessage( "\t ��������[Walk����]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d����������[Walk����]����", iRow );
            goto load_error;
        }
        pMount->fWalkingStep = fValue;
        iCol ++;

        // ��Ծ�߶�
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t ��������[��Ծ�߶�]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d����������[��Ծ�߶�]����", iRow );
            goto load_error;
        }
        pMount->fJumpingHeight = fValue;
        iCol ++;

        // �ƶ�����
        if( !pReader.GetStringFieldByName( "MoveType", strTemp ) )
        {
            OutputSlkLoadingMessage( "Error: Mount.slk ��ȡ[�ƶ�����]����!\r\n" );
            GetErrorLog()->logString( "Mount.slk ��[�ƶ�����]����" );
            goto load_error;
        }
        iValue = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(), ItemDefine::g_szMoveTypeString,sizeof(ItemDefine::g_szMoveTypeString)/sizeof(char*) );

        if( -1 == iValue )
        {
            OutputSlkLoadingMessage( "Error: Mount.slk ��ȡ[�ƶ�����]����!\r\n" );
            GetErrorLog()->logString( "Mount.slk ��[�ƶ�����]����" );
            goto load_error;
        }
        pMount->shMoveType = iValue;        
        iCol ++;

        // ������������
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t ����[������������]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������[������������]����", iRow );
            goto load_error;
        }
        pMount->fDromeScaleCorrect = fValue;
        iCol ++;

        // ������������
        if( !pReader.GetFloatField( iCol, fValue ) )
        {
            OutputSlkLoadingMessage( "\t ����[������������]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������[������������]����", iRow );
            goto load_error;
        }
        pMount->fRiderScaleCorrect = fValue;
        iCol ++;

        // ���ʹ��ʱ��
        if( !pReader.GetIntField( iCol,iValue ) )
        {
            OutputSlkLoadingMessage( "\t �����������ʹ��ʱ�����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d�������������ʹ��ʱ�����", iRow );
            goto load_error;
        }
        pMount->dwMaxLifeTime = iValue;
        iCol++;

        //����Ƥ��
        if( !pReader.GetStringFieldByName( "Skin", strTemp ) )
        {
            OutputSlkLoadingMessage( "\t ��������[����Ƥ��]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d����������[����Ƥ��]����", iRow );
            goto load_error;
        }
        pMount->dwSkinAddr = AllocStringCopy( strTemp.c_str() );
        iCol++;

        //���ӵ�״̬ID
        if( !pReader.GetIntFieldByName( "AddStatus", iValue ) )
        {
            OutputSlkLoadingMessage( "\t ��������[����״̬ID]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d����������[����״̬ID]����", iRow );
            goto load_error;
        }
        pMount->nAddStatusID = iValue;
        iCol++;

        // ���������Ч·��
        if( !pReader.GetStringField( iCol, strMountEffectPath ) )
        {
            OutputSlkLoadingMessage( "\t ����[���������Ч·��]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������[���������Ч·��]����", iRow );
            goto load_error;
        }
        pMount->dwMountEffectAddr = AllocStringCopy( strMountEffectPath.c_str() );
        iCol ++;

        // ���������Ч·��
        if( !pReader.GetStringField( iCol, strDisMountEffectPath ) )
        {
            OutputSlkLoadingMessage( "\t ����[���������Ч·��]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������[���������Ч·��]����", iRow );
            goto load_error;
        }
        pMount->dwDisMountEffectAddr = AllocStringCopy( strDisMountEffectPath.c_str() );
        iCol ++;

        //���ֿ��ж���
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

        //�������߶���
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

        //���ֺ��˶���
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

        //���ֱ��ܶ���
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

        //������Ծ����
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

        //��������ܶ���
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

        //������ض���
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

        //���ֻ��ж���
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

        //������ת����
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

        //������ת����
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

        //����ԭ��������
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

        //�������߶���
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

        ////����ս������
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

        ////����ս����
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

        ////�������ϰε�
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

        ////���������յ�
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

        //������������ʱ��
        if ( !pReader.GetIntFieldByName( "JumpAnimTime", iValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [JumpAnimTime] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [JumpAnimTime] Error!!", iRow );
            // ToLog( "Drome.slk Loading [JumpAnimTime] Error!!" && false );
            goto load_error;
        }
        pMount->dwJumpAnimTime = iValue;
        iCol ++;

        //��ض�������ʱ��
        if ( !pReader.GetIntFieldByName( "DropAnimTime", iValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [DropAnimTime] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [DropAnimTime] Error!!", iRow );
            // ToLog( "Drome.slk Loading [DropAnimTime] Error!!" && false );
            goto load_error;
        }
        pMount->dwDropAnimTime = iValue;
        iCol ++;

        //����ܶ�������ʱ��
        if ( !pReader.GetIntFieldByName( "FallToTheGroundRun", iValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [FallToTheGroundRun] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [FallToTheGroundRun] Error!!", iRow );
            // ToLog( "Drome.slk Loading [FallToTheGroundRun] Error!!" && false );
            goto load_error;
        }
        pMount->dwFallToTheGroundRunTime = iValue;
        iCol ++;

        //�����ٶ�
        if ( !pReader.GetFloatFieldByName( "JumpSpeed", fValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [JumpSpeed] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [JumpSpeed] Error!!", iRow );
            // ToLog( "Drome.slk Loading [JumpSpeed] Error!!" && false );
            goto load_error;
        }
        pMount->fJumpSpeed = fValue;
        iCol ++;

        //�����ٶ�
        if ( !pReader.GetFloatFieldByName( "DropSpeed", fValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [DropSpeed] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [DropSpeed] Error!!", iRow );
            // ToLog( "Drome.slk Loading [DropSpeed] Error!!" && false );
            goto load_error;
        }
        pMount->fDropSpeed = fValue;
        iCol ++;

        //���ɵ�����������ʱ��
        if ( !pReader.GetIntFieldByName( "BlendJumpTime", iValue ) )
        {
            OutputSlkLoadingMessage( "Drome.slk Loading [BlendJumpTime] Error!!\r\n" );
            GetErrorLog()->logString( "Drome.slk Row %d Loading [BlendJumpTime] Error!!", iRow );
            // ToLog( "Drome.slk Loading [BlendJumpTime] Error!!" && false );
            goto load_error;
        }
        pMount->dwBlendJumpTime = iValue;
        //iCol ++;

        // ��ŽŲ���
        //if( !pReader.GetStringField( iCol, strRunSoundOfLeftFootPath ) )
        if( !pReader.GetStringFieldByName( "RunSoundOfLeftFoot", strRunSoundOfLeftFootPath ) )
        {
            OutputSlkLoadingMessage( "\t ����[��ŽŲ���]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������[��ŽŲ���]����", iRow );
            goto load_error;
        }
        pMount->dwRunSoundOfLeftFootAddr = AllocStringCopy( strRunSoundOfLeftFootPath.c_str() );
        iCol ++;

        // �ҽŽŲ���
        //if( !pReader.GetStringField( iCol, strRunSoundOfRightFootPath ) )
        if( !pReader.GetStringFieldByName( "RunSoundOfRightFoot", strRunSoundOfRightFootPath ) )
        {
            OutputSlkLoadingMessage( "\t ����[�ҽŽŲ���]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������[�ҽŽŲ���]����", iRow );
            goto load_error;
        }
        pMount->dwRunSoundOfRightFootAddr = AllocStringCopy( strRunSoundOfRightFootPath.c_str() );
        iCol ++;

        // ԭ�ؽ���
        //if( !pReader.GetStringField( iCol, strNeightSoundPath ) )
        if( !pReader.GetStringFieldByName( "NeightSound", strNeightSoundPath ) )
        {
            OutputSlkLoadingMessage( "\t ����[ԭ�ؽ���]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������[ԭ�ؽ���]����", iRow );
            goto load_error;
        }
        pMount->dwNeightSoundAddr = AllocStringCopy( strNeightSoundPath.c_str() );
        iCol ++;

        // ���̧�߸߶�
        if( !pReader.GetIntFieldByName( "CameraHeight", iValue ) )
        {
            OutputSlkLoadingMessage( "\t ��������[�����̧�߸߶�]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d����������[�����̧�߸߶�]����", iRow );
            goto load_error;
        }
        pMount->nCameraHeight = iValue;
        iCol++;

        if( !pReader.GetStringFieldByName( "FrontFootPrint", strNeightSoundPath ) )
        {
            OutputSlkLoadingMessage( "\t ����[ǰ��ӡ]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������[ǰ��ӡ]����", iRow );
            goto load_error;
        }
        pMount->dwFrontFootPrintAddr = AllocStringCopy( strNeightSoundPath.c_str() );
        iCol ++;

        if( !pReader.GetStringFieldByName( "BackFootPrint", strNeightSoundPath ) )
        {
            OutputSlkLoadingMessage( "\t ����[���ӡ]����!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d������[���ӡ]����", iRow );
            goto load_error;
        }
        pMount->dwBackFootPrintAddr = AllocStringCopy( strNeightSoundPath.c_str() );
        iCol ++;

        // ͷ���ļ�·��
        if( !pReader.GetStringFieldByName( "HeadPicture", strHeadPic ) )
        {
            OutputSlkLoadingMessage( "\t ��������ͷ���ļ�·������!\r\n" );
            GetErrorLog()->logString( " Mount.slk ��%d����������ͷ���ļ�·������", iRow );
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

        // ϴ�����
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
        OutputSlkLoadingMessage( "\t Mount.slk �� %d ������ʧ��!\r\n",iRow-1 );
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
        pMount->dwNameAddr = AllocStringCopy(strMountName.c_str());//����

        Common::_tstring strModlePath;
        strModlePath.fromUTF8( pItemMount->Attribute("ModelPath") );
        pMount->dwModelAddr = AllocStringCopy(strModlePath.c_str());//ģ�͵�ַ

		for (int i = 0; i <= SMountItem::MICD_MountMaxLevel; ++i)
		{
			char szTmp[65] = {0};
			sprintf_s(szTmp, sizeof(szTmp) - 1,"ModelID%d", i);
			pItemMount->Attribute(szTmp, &iValue);
			pMount->modelID[i] = iValue;//����ģ��ID
		}
		

        pItemMount->Attribute("OperaType", &iValue);
        pMount->stOperaType = iValue;//��������

        pItemMount->Attribute("Type", &iValue);
        pMount->stType = iValue;//����

        pItemMount->Attribute("CarryNum", &iValue);
        pMount->stCarry = iValue; //��������

        pItemMount->Attribute("FlyHeight", &dValue);
        pMount->fFlyHeight = dValue; //���и߶�

        pItemMount->Attribute("Inertia", &dValue);
        pMount->fInertia = dValue;//����

        pItemMount->Attribute("Speed", &dValue);
        pMount->fSpeed = dValue;//�ٶ�

        pItemMount->Attribute("RunStep", &dValue);
        pMount->fRunningStep = dValue;//Run����

        pItemMount->Attribute("WalkStep", &dValue);
        pMount->fWalkingStep = dValue;//Walk����

        pItemMount->Attribute("JumpHeight", &dValue);
        pMount->fJumpingHeight = dValue; //��Ծ�߶�

        pItemMount->Attribute("MaxRange", &iValue);
        pMount->stMaxRange = iValue;  

        pItemMount->Attribute("MoveType", &iValue);
        pMount->shMoveType = iValue;//�ƶ�����

        pItemMount->Attribute("DromeScaleCorrect", &dValue);
        pMount->fDromeScaleCorrect = dValue;//������������

        pItemMount->Attribute("RiderScaleCorrect", &dValue);
        pMount->fRiderScaleCorrect = dValue; //������������

        pItemMount->Attribute("UseTime", &iValue);
        pMount->dwMaxLifeTime = iValue;//���ʹ��ʱ��

        Common::_tstring strSkin;
        strSkin.fromUTF8( pItemMount->Attribute("Skin") );
        pMount->dwSkinAddr = AllocStringCopy( strSkin.c_str() );//Ƥ����ַ

        pItemMount->Attribute("AddStatus", &iValue);
        pMount->nAddStatusID = iValue;//����״̬ID

        Common::_tstring strRideEffect;
        strRideEffect.fromUTF8( pItemMount->Attribute("OnRideEffectPath") );
        pMount->dwMountEffectAddr = AllocStringCopy(strRideEffect.c_str());//���������Ч·��

        Common::_tstring strOffRideEffect;
        strOffRideEffect.fromUTF8( pItemMount->Attribute("OffRideEffectPath") );
        pMount->dwDisMountEffectAddr = AllocStringCopy(strOffRideEffect.c_str());//���������Ч·��

        Common::_tstring strMountDrive;
        strMountDrive.fromUTF8( pItemMount->Attribute("MountDrive") );
        pMount->dwMountAction[ItemDefine::MountDrive] = AllocStringCopy( strMountDrive.c_str() );//���ֿ��ж���

        Common::_tstring strMountWalk;
        strMountWalk.fromUTF8( pItemMount->Attribute("MountWalk"));
        pMount->dwMountAction[ItemDefine::MountWalk] = AllocStringCopy( strMountWalk.c_str() );//�������߶���

        Common::_tstring strMountWalkBack;
        strMountWalkBack.fromUTF8( pItemMount->Attribute("MountWalkBackWards") );
        pMount->dwMountAction[ItemDefine::MountWalkBackWards] = AllocStringCopy( strMountWalkBack.c_str() );//���ֺ��˶���

        Common::_tstring strMountRun;
        strMountRun.fromUTF8( pItemMount->Attribute("MountRun") );
        pMount->dwMountAction[ItemDefine::MountRun] = AllocStringCopy( strMountRun.c_str() );//���ֱ��ܶ���

        Common::_tstring strMountJump;
        strMountJump.fromUTF8( pItemMount->Attribute("MountJump") );
        pMount->dwMountAction[ItemDefine::MountJump] = AllocStringCopy( strMountJump.c_str() );//������Ծ����

        Common::_tstring strMountFallToGroundRun;
        strMountFallToGroundRun.fromUTF8( pItemMount->Attribute("MountFallToTheGroundRun") );
        pMount->dwMountAction[ItemDefine::MountFallToTheGroundRun] = AllocStringCopy( strMountFallToGroundRun.c_str() );//��������ܶ���

        Common::_tstring strMountDrop;
        strMountDrop.fromUTF8( pItemMount->Attribute("MountDrop") );
        pMount->dwMountAction[ItemDefine::MountDrop] = AllocStringCopy( strMountDrop.c_str() );//������ض���

        Common::_tstring strMountGlide;
        strMountGlide.fromUTF8( pItemMount->Attribute("MountGlide") );
        pMount->dwMountAction[ItemDefine::MountGlide] = AllocStringCopy( strMountGlide.c_str() );//���ֻ��ж���

        Common::_tstring strMountShuffleLeft;
        strMountShuffleLeft.fromUTF8( pItemMount->Attribute("MountShuffleLeft") );
        pMount->dwMountAction[ItemDefine::MountShuffleLeft] = AllocStringCopy( strMountShuffleLeft.c_str() );//������ת����

        Common::_tstring strMountShuffleRight;
        strMountShuffleRight.fromUTF8( pItemMount->Attribute("MountShuffleRight") );
        pMount->dwMountAction[ItemDefine::MountShuffleRight] = AllocStringCopy( strMountShuffleRight.c_str() );//������ת����

        Common::_tstring strMountNeigh;
        strMountNeigh.fromUTF8( pItemMount->Attribute("MountNeigh") );
        pMount->dwMountAction[ItemDefine::MountNeigh] = AllocStringCopy( strMountNeigh.c_str() );//����ԭ����������

        Common::_tstring strMountBackAttack;
        strMountBackAttack.fromUTF8( pItemMount->Attribute("MountBackAttack") );
        pMount->dwMountAction[ItemDefine::MountBackAttack] = AllocStringCopy( strMountBackAttack.c_str() );//�������߶���

        pItemMount->Attribute("FallToTheGroundRun", &iValue);
        pMount->dwFallToTheGroundRunTime = iValue;//

        pItemMount->Attribute("JumpAnimTime", &iValue);
        pMount->dwJumpAnimTime = iValue;//��Ծ��������ʱ��

        pItemMount->Attribute("DropAnimTime", &iValue);
        pMount->dwDropAnimTime = iValue;//��ض�������ʱ��

        pItemMount->Attribute("JumpSpeed", &dValue);
        pMount->fJumpSpeed = dValue;//�����ٶ�

        pItemMount->Attribute("DropSpeed", &dValue);
        pMount->fDropSpeed = dValue;//����ٶ�

        pItemMount->Attribute("BlendJumpTime", &iValue);
        pMount->dwBlendJumpTime = iValue;// ��������ʱ��

        Common::_tstring strRunSoundOfLeftFoot;
        strRunSoundOfLeftFoot.fromUTF8( pItemMount->Attribute("RunSoundOfLeftFoot") );
        pMount->dwRunSoundOfLeftFootAddr = AllocStringCopy( strRunSoundOfLeftFoot.c_str() );//��Ų�����

        Common::_tstring strRunSoundOfRightFoot;
        strRunSoundOfRightFoot.fromUTF8( pItemMount->Attribute("RunSoundOfRightFoot") );
        pMount->dwRunSoundOfRightFootAddr = AllocStringCopy( strRunSoundOfRightFoot.c_str() );//��Ų�����

        Common::_tstring strNeightSound;
        strNeightSound.fromUTF8( pItemMount->Attribute("NeightSound") );
        pMount->dwNeightSoundAddr = AllocStringCopy( strNeightSound.c_str() );//����ԭ�ؽ���

        pItemMount->Attribute("CameraHeight", &iValue);
        pMount->nCameraHeight = iValue;//�����̧�߸߶�

        Common::_tstring strFrontFootPrint;
        strFrontFootPrint.fromUTF8( pItemMount->Attribute("FrontFootPrint") );
        pMount->dwFrontFootPrintAddr = AllocStringCopy( strFrontFootPrint.c_str() );//ǰ��ӡ

        Common::_tstring strBackFootPrint;
        strBackFootPrint.fromUTF8( pItemMount->Attribute("BackFootPrint") );
        pMount->dwBackFootPrintAddr = AllocStringCopy( strBackFootPrint.c_str() );//���ӡ

        Common::_tstring strHeadPicture;
        strHeadPicture.fromUTF8( pItemMount->Attribute("HeadPicture") );
        pMount->dwHeadPicAddr = AllocStringCopy( strHeadPicture.c_str() );//����ͷ��

        pItemMount->Attribute("TakeLevel", &iValue);
        pMount->takeLevel = iValue;//Я���ȼ�

        pItemMount->Attribute("Quality", &iValue);
        pMount->quality = iValue;//����Ʒ��

        pItemMount->Attribute("GrowMin", &dValue);
        pMount->growMin = dValue;//�ɳ����ֵ

        pItemMount->Attribute("GrowMax", &dValue);
        pMount->growMax = dValue;//�ɳ����ֵ

        pItemMount->Attribute("BaseSum", &dValue);
        pMount->baseSum = dValue;//��ʼ�ܺ�

        pItemMount->Attribute("InitLiLiangMin", &dValue);
        pMount->baseMin[EBaseAttr_Strength] = dValue;//��ʼ������Сֵ

        pItemMount->Attribute("InitLiLiangMax", &dValue);
        pMount->baseMax[EBaseAttr_Strength] = dValue;//��ʼ�������ֵ

        pItemMount->Attribute("InitMinJieMin", &dValue);
        pMount->baseMin[EBaseAttr_Agility] = dValue;//��ʼ������Сֵ

        pItemMount->Attribute("InitMinJieMax", &dValue);
        pMount->baseMax[EBaseAttr_Agility] = dValue;//��ʼ�������ֵ

        pItemMount->Attribute("InitTiZhiMin", &dValue);
        pMount->baseMin[EBaseAttr_Stamina] = dValue;//��ʼ������Сֵ

        pItemMount->Attribute("InitTiZhiMax", &dValue);
        pMount->baseMax[EBaseAttr_Stamina] = dValue;//��ʼ�������ֵ

        pItemMount->Attribute("InitShuFaMin", &dValue);
        pMount->baseMin[EBaseAttr_Intelligence] = dValue;//��ʼ������Сֵ

        pItemMount->Attribute("InitShuFaMax", &dValue);
        pMount->baseMax[EBaseAttr_Intelligence] = dValue;//��ʼ�������ֵ

        //pItemMount->Attribute("InitJinGuMin", &dValue);
        //pMount->baseMin[BA_JinGu] = dValue;//��ʼ�����Сֵ

        //pItemMount->Attribute("InitJinGuMax", &dValue);
        //pMount->baseMax[BA_JinGu] = dValue;//��ʼ������ֵ

        pItemMount->Attribute("AddSum", &dValue);
        pMount->addSum = dValue;//�����ܺ�

        pItemMount->Attribute("AddLiLiangMin", &dValue);
        pMount->addMin[EBaseAttr_Strength] = dValue;//����������Сֵ

        pItemMount->Attribute("AddLiLiangMax", &dValue);
        pMount->addMax[EBaseAttr_Strength] = dValue;//�����������ֵ

        pItemMount->Attribute("AddMinJieMin", &dValue);
        pMount->addMin[EBaseAttr_Agility] = dValue;//����������Сֵ

        pItemMount->Attribute("AddMinJieMax", &dValue);
        pMount->addMax[EBaseAttr_Agility] = dValue;//�����������ֵ

        pItemMount->Attribute("AddTiZhiMin", &dValue);
        pMount->addMin[EBaseAttr_Stamina] = dValue;//����������Сֵ

        pItemMount->Attribute("AddTiZhiMax", &dValue);
        pMount->addMax[EBaseAttr_Stamina] = dValue;//�����������ֵ

        pItemMount->Attribute("AddShuFaMin", &dValue);
        pMount->addMin[EBaseAttr_Intelligence] = dValue;//����������Сֵ

        pItemMount->Attribute("AddShuFaMax", &dValue);
        pMount->addMax[EBaseAttr_Intelligence] = dValue;//�����������ֵ

        //pItemMount->Attribute("AddJinGuMin", &dValue);
        //pMount->addMin[BA_JinGu] = dValue;//���ʽ����Сֵ

        //pItemMount->Attribute("AddJinGuMax", &dValue);
        //pMount->addMax[BA_JinGu] = dValue;//���ʽ�����ֵ

        pItemMount->Attribute("SawyMin", &iValue);
        pMount->sawyMin = iValue;//������Сֵ

        pItemMount->Attribute("SawyMax", &iValue);
        pMount->sawyMax = iValue;//�������ֵ

        pItemMount->Attribute("SelfSpeedSkill", &iValue);
        pMount->selfSpeedSkillId = iValue;//�������ֵ

        pItemMount->Attribute("SelfSkillNum", &iValue);
        pMount->selfSkillNum = iValue;//����ļ�����

        pItemMount->Attribute("SelfSkillPro", &iValue);
        pMount->selfSkillRate = iValue;//����ļ��ܼ���

        for (int i = 0; i < ItemDefine::SDrome::DCD_SELFSKILLIDCOUNT; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1,"SelfSkill%d", i+1);
            pItemMount->Attribute(szTmp, &iValue);
            pMount->selfSkillId[i] = iValue;//��������ļ���
        }

        pItemMount->Attribute("MasterSkillNum", &iValue);
        pMount->masterSkillNum = iValue;//���˼��ܸ���

        pItemMount->Attribute("MasterSkillPro", &iValue);
        pMount->masterSkillRate = iValue;//���˼����������

        for (int i = 0; i < ItemDefine::SDrome::DCD_SELFSKILLIDCOUNT; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "MasterSkill%d", i+1);
            pItemMount->Attribute(szTmp, &iValue);
            pMount->masterSkillId[i] = iValue;//�������˼���
        }

        pItemMount->Attribute("MasterUseSkillNum", &iValue);
        pMount->masterUseSkillNum = iValue;//�����ͷż��ܸ���

        pItemMount->Attribute("MasterUseSkillPro", &iValue);
        pMount->masterUseSkillRate = iValue;//���˲��������������

        for (int i = 0; i < ItemDefine::SDrome::DCD_SELFSKILLIDCOUNT; ++i)
        {
            char szTmp[64] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "MasterUseSkill%d", i+1);
            pItemMount->Attribute(szTmp, &iValue);
            pMount->masterUseSKillId[i] = iValue;//�����ͷŵļ���
        }

        // ϴ�����
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
        pMount->nextGeneration = iValue;//���˲��������������

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