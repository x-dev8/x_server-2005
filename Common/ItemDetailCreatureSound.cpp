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

bool CItemDetail::LoadSlkCreatureSound( const char* szFile )
{
    CSlkReader reader;
    if( !reader.ReadFromFile( szFile ) )
        return false;

    int iCol   = 0;
    int iRow   = 3;
    int iRet   = 0;
    int iValue = 0;
    std::string strCreatureName;

    while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
    {
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        ItemDefine::SCreatureSound* pCreature = (ItemDefine::SCreatureSound*)AllocItem( 0, sizeof( ItemDefine::SCreatureSound ));
        if ( !pCreature)
        {
            OutputSlkLoadingMessage( "Error:分配CreatureSound需要的内存出错 [%d]\r\n", iRow );
            return false;
        }

        iCol = 1;
        if( !reader.GetStringField( iCol ++, strCreatureName ) )
        {
            OutputSlkLoadingMessage( "Error:读名字出错 [%d]\r\n", iCol );
            continue;
        }        
        pCreature->dwCreatureNameAddr = AllocStringCopy( strCreatureName.c_str() );

        //忽略 说明
        iCol ++;

        for( int iLoop = 0 ; iLoop < ItemDefine::CreatureSound_Max ; ++ iLoop )
        {		
            if( !reader.GetIntField( iCol ++,iValue ) )
            {
                OutputSlkLoadingMessage( "Error: 读入creaturesound.slk:row:%d col:%d Error!\r\n",iRow,iCol - 1 );
                goto load_error;
            }
            pCreature->SoundNum[ iLoop ] = iValue;
        }

        _creatureSounds.insert( CreatureSoundContainer::value_type( strCreatureName, pCreature ) );
        continue;

load_error:      
        OutputSlkLoadingMessage( "\t CreatureSound.slk 第 %d 行载入失败!\r\n",iRow-1 );
        return false;
    }

    return true;
}

bool CItemDetail::LoadXmlCreatureSound( const char* szFileName)
{
    int iValue = 0;

    if (szFileName == NULL )
    { return false; }

    MeXmlDocument mMeXmlDoc;
    if (!mMeXmlDoc.LoadFile(szFileName))
    { return false; }

    MeXmlElement *pRoot = mMeXmlDoc.FirstChildElement("Project");
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pCreatureSoundTree = pRoot->FirstChildElement("CreatureSounds");
    if (pCreatureSoundTree == NULL)
    { return false; }

    MeXmlElement *pCreatureSoundElement = pCreatureSoundTree->FirstChildElement("CreatureSound");

    while ( pCreatureSoundElement != NULL )
    {
        ItemDefine::SCreatureSound *pCreatureSound = (ItemDefine::SCreatureSound *)AllocItem( 0, sizeof(ItemDefine::SCreatureSound) );

        if ( pCreatureSound == NULL )
        { return false; }

        Common::_tstring strMonsterName;
        strMonsterName.fromUTF8( pCreatureSoundElement->Attribute("MonsterName") );
        pCreatureSound->dwCreatureNameAddr = AllocStringCopy( strMonsterName.c_str() );

        pCreatureSoundElement->Attribute("FreeSoundNum", &iValue);
        pCreatureSound->SoundNum[ItemDefine::CreatureSound_Idle] = iValue;

        pCreatureSoundElement->Attribute("AtkSoundNum", &iValue);
        pCreatureSound->SoundNum[ItemDefine::CreatureSound_Attack] = iValue;

        pCreatureSoundElement->Attribute("HurtSoundNum", &iValue);
        pCreatureSound->SoundNum[ItemDefine::CreatureSound_BeHit] = iValue;

        pCreatureSoundElement->Attribute("DeathSound", &iValue);
        pCreatureSound->SoundNum[ItemDefine::CreatureSound_Dead] = iValue;

        _creatureSounds.insert( CreatureSoundContainer::value_type( pCreatureSound->GetName(), pCreatureSound ) );

        pCreatureSoundElement = pCreatureSoundElement->NextSiblingElement();
    }

    return true;
}

bool CItemDetail::SaveXmlCreatureSound( const char* szFileName )
{
    if (szFileName == NULL || *szFileName == 0)
    { return false; }
    MeXmlDocument CreatureSoundMeXml;
    CreatureSoundMeXml.InsertEndChild(MeXmlDeclaration("1.0", "utf-8", "yes"));
    MeXmlElement *pRoot = CreatureSoundMeXml.InsertEndChild(("Project"))->ToElement();
    if (pRoot == NULL)
        return false;
    MeXmlElement *pCreatureSounds = pRoot->InsertEndChild(("CreatureSounds"))->ToElement();
    if (pCreatureSounds == NULL)
        return false;

    CreatureSoundContainer::iterator iterBegin = _creatureSounds.begin();
    CreatureSoundContainer::iterator iterEnd = _creatureSounds.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if ( iterBegin->second == NULL )
        { continue;}
        ItemDefine::SCreatureSound *pCSndIter = iterBegin->second;
        MeXmlElement *pCSnd = pCreatureSounds->InsertEndChild(("CreatureSound"))->ToElement();
        if (pCSnd == NULL)
        { continue; }

        Common::_tstring strName = pCSndIter->GetName();
        pCSnd->SetAttribute("MonsterName", strName.toUTF8().c_str());

        pCSnd->SetAttribute("FreeSoundNum", pCSndIter->SoundNum[ItemDefine::CreatureSound_Idle]);
        pCSnd->SetAttribute("AtkSoundNum", pCSndIter->SoundNum[ItemDefine::CreatureSound_Attack]);
        pCSnd->SetAttribute("HurtSoundNum", pCSndIter->SoundNum[ItemDefine::CreatureSound_BeHit]);
        pCSnd->SetAttribute("DeathSound", pCSndIter->SoundNum[ItemDefine::CreatureSound_Dead]);
    }
    return CreatureSoundMeXml.SaveFile(szFileName);
}

#pragma warning( pop )