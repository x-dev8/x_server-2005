#include "GameDefinePet.h"

void SPetItem::SBaseInfo::Write( CDataChunkWriter* w )
{
    w->StartChunk(DC_TAG('pi02'));
    w->Write ( szName,  sizeof(szName) , 1);
    w->WriteT( petId         );
    w->WriteT( itemId        );
    w->WriteT( petType       );
    w->WriteT( guid          );
    w->WriteT( isActive      );
    w->WriteT( level         );
    w->WriteT( quality       );
    w->WriteT( takeLevel     );
    w->WriteT( aptitudeLevel );
    w->WriteT( attackType    );
    w->WriteT( battleValue   );
    w->WriteT( sex           );
    w->WriteT( characterize  );
    w->WriteT( exp           );
    w->WriteT( daoxing       );
    w->WriteT( hp            );
    w->WriteT( loyalty       );
    w->WriteT( duration      );
    w->WriteT( savvy         );
    w->WriteT( bone          );
    w->WriteT( isShowGrow    );
    w->WriteT( growStar      );
    w->WriteT( growRate      );
    w->WriteT( phyle         );
    w->WriteT( element       );
    w->WriteT( breedNum      );
    w->WriteT( generation    );
    w->WriteT( regenerateTime    );
    w->WriteT( lastRealizeSkillLevel );
    w->WriteT( nPotentialPoint );

    w->Write ( baseAttribute,      sizeof(uint16) * EBaseAttr_MaxSize, 1);
    w->Write ( aptitudeAttribute,  sizeof(uint16) * EBaseAttr_MaxSize, 1);
    w->Write ( potentialAttribute, sizeof(uint16) * EBaseAttr_MaxSize, 1);

	w->WriteDword(PetModeID);
	w->WriteInt64(n64ModeUseTime);
	w->Write ( PetEquip, sizeof(SCharItem) * PetEquip_MaxSum, 1);
	
    w->EndChunk(DC_TAG('pi02'));
}

void SPetItem::SBaseInfo::Read( BYTE* szBuff,DWORD nSize )
{
    CDataChunkLoader l(szBuff,nSize);
    while( !l.IsEndOfMemory() )
    {
		if (l.IsChunk('pi01'))
        {
            l.StartChunk('pi01');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                r.ReadToBuffer((BYTE*)szName, sizeof(szName));
                r.ReadT( petId         );
                r.ReadT( itemId        );
                r.ReadT( petType       );
                r.ReadT( guid          );
                r.ReadT( isActive      );
                r.ReadT( level         );
                r.ReadT( quality       );
                r.ReadT( takeLevel     );
                r.ReadT( aptitudeLevel );
                r.ReadT( attackType    );
                r.ReadT( battleValue   );
                r.ReadT( sex           );
                r.ReadT( characterize  );
                r.ReadT( exp           );
                r.ReadT( daoxing       );
                r.ReadT( hp            );
                r.ReadT( loyalty       );
                r.ReadT( duration      );
                r.ReadT( savvy         );
                r.ReadT( bone          );
                r.ReadT( isShowGrow    );
                r.ReadT( growStar      );
                r.ReadT( growRate      );
                r.ReadT( phyle         );
                r.ReadT( element       );
                r.ReadT( breedNum      );
                r.ReadT( generation    );
                r.ReadT( regenerateTime    );
                r.ReadT( lastRealizeSkillLevel );
                r.ReadT( nPotentialPoint );

                r.ReadToBuffer((BYTE*)baseAttribute,      sizeof(uint16) * EBaseAttr_MaxSize);
                r.ReadToBuffer((BYTE*)aptitudeAttribute,  sizeof(uint16) * EBaseAttr_MaxSize);
                r.ReadToBuffer((BYTE*)potentialAttribute, sizeof(uint16) * EBaseAttr_MaxSize);
            }
            l.EndChunk('pi01');
        }
        else if (l.IsChunk('pi02'))
        {
            l.StartChunk('pi02');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                r.ReadToBuffer((BYTE*)szName, sizeof(szName));
                r.ReadT( petId         );
                r.ReadT( itemId        );
                r.ReadT( petType       );
                r.ReadT( guid          );
                r.ReadT( isActive      );
                r.ReadT( level         );
                r.ReadT( quality       );
                r.ReadT( takeLevel     );
                r.ReadT( aptitudeLevel );
                r.ReadT( attackType    );
                r.ReadT( battleValue   );
                r.ReadT( sex           );
                r.ReadT( characterize  );
                r.ReadT( exp           );
                r.ReadT( daoxing       );
                r.ReadT( hp            );
                r.ReadT( loyalty       );
                r.ReadT( duration      );
                r.ReadT( savvy         );
                r.ReadT( bone          );
                r.ReadT( isShowGrow    );
                r.ReadT( growStar      );
                r.ReadT( growRate      );
                r.ReadT( phyle         );
                r.ReadT( element       );
                r.ReadT( breedNum      );
                r.ReadT( generation    );
                r.ReadT( regenerateTime    );
                r.ReadT( lastRealizeSkillLevel );
                r.ReadT( nPotentialPoint );

                r.ReadToBuffer((BYTE*)baseAttribute,      sizeof(uint16) * EBaseAttr_MaxSize);
                r.ReadToBuffer((BYTE*)aptitudeAttribute,  sizeof(uint16) * EBaseAttr_MaxSize);
                r.ReadToBuffer((BYTE*)potentialAttribute, sizeof(uint16) * EBaseAttr_MaxSize);

				r.ReadT(PetModeID);
				r.ReadT(n64ModeUseTime);
				r.ReadToBuffer((BYTE*)PetEquip, sizeof(SCharItem) * PetEquip_MaxSum);
            }
            l.EndChunk('pi02');
        }
        else 
            l.SkipChunk();
    }
}

bool SPetItem::SSkillInfo::AddSkill( unsigned short skillId, unsigned short skillLevel /*= 1 */ )
{
    int index      = -1;
    int emptyIndex = -1;
    for ( int i = 0; i < PetDefine_MaxSkillCount; ++i)
    {
        if ( skills[i].ustSkillID != InvalidLogicNumber )
        { // 不为空
            if ( skills[i].ustSkillID == skillId )
            { // 如果有此技能
                index = i;
                break;
            }
            continue; 
        }

        emptyIndex = i;
        break;
    }

    if ( index != -1 )
    { // 找到相同技能
        skills[index].ustSkillID   = skillId;
        skills[index].stSkillLevel = skillLevel;
        return true;
    }

    if ( emptyIndex != -1)
    { // 有空位
        skills[emptyIndex].ustSkillID   = skillId;
        skills[emptyIndex].stSkillLevel = skillLevel;
        return true;
    }

    return false;
}

bool SPetItem::SSkillInfo::ReplaceSkill( unsigned short skillId, unsigned short skillLevel, int nIndex )
{
    if ( nIndex<0 || nIndex>PetDefine_MaxSkillCount)
    { return false; }

    if ( skills[nIndex].ustSkillID == InvalidLogicNumber )
    { return false; }

    skills[nIndex].ustSkillID   = skillId;
    skills[nIndex].stSkillLevel = skillLevel;
    return true;
}

bool SPetItem::SSkillInfo::RemoveSkill( unsigned short skillId )
{
    int index = -1;
    for( int i=0 ; i<PetDefine_MaxSkillCount ; ++i)
    {
        if( skills[i].ustSkillID == skillId )
        {
            index = i;
            break;
        }
    }

    if ( index == -1)
    { return false;}

    skills[ index ].ustSkillID   = InvalidLogicNumber;
    skills[ index ].stSkillLevel = 0;

    for ( int i=index, I=index+1; I<PetDefine_MaxSkillCount; ++i, ++I )
    {
        if ( skills[I].ustSkillID == InvalidLogicNumber )
        { break; }

        skills[i] = skills[I];        
        skills[I].Reset();
    }

    return true;
}

const SCharSkill* SPetItem::SSkillInfo::GetSkill( unsigned short skillId )
{
    for( int i=0 ; i<PetDefine_MaxSkillCount ; ++i)
    {
        if( skills[i].ustSkillID == skillId )
        {
            return &skills[i];
        }
    }

    return NULL;
}

int SPetItem::SSkillInfo::GetCurrentSkillCount()
{
    int nCount = 0;
    for( int i=0 ; i<PetDefine_MaxSkillCount ; ++i)
    {
        if ( skills[i].ustSkillID == InvalidLogicNumber )
        { break; }

        ++nCount;
    }

    return nCount;
}

void SPetItem::SSkillInfo::Reset()
{
    for( int i=0 ; i<PetDefine_MaxSkillCount ; ++i)
    {
        if ( skills[i].ustSkillID == InvalidLogicNumber )
        { continue; }

        skills[i].Reset();
    }
}

void SPetItem::SSkillInfo::Write( CDataChunkWriter* w )
{    
    w->StartChunk(DC_TAG('ps01'));
    for ( int i=0; i<PetDefine_MaxSkillCount; ++i)
    {   
        w->StartChunk(DC_TAG('sk01'));
        skills[i].write( w );
        w->EndChunk(DC_TAG('sk01'));
    }

    w->StartChunk( DC_TAG('sn01'));
    w->WriteT( initiativeSkillNumber );
    w->EndChunk( DC_TAG('sn01'));

    w->EndChunk(DC_TAG('ps01'));
}

void SPetItem::SSkillInfo::Read( BYTE* szBuff, DWORD nSize )
{
    CDataChunkLoader l(szBuff,nSize);
    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('ps01'))
        {
            l.StartChunk('ps01');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                for (int i = 0; i < PetDefine_MaxSkillCount; ++i)
                {
                    if (r.IsChunk('sk01'))
                    {
                        r.StartChunk('sk01');
                        skills[i].read(r.GetPointer().byte,r.GetChunkSize());
                        r.EndChunk('sk01');
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }	
                }

                if ( r.IsChunk('sn01'))
                {
                    r.StartChunk( DC_TAG('sn01'));
                    CDataChunkLoader r1(r.GetPointer().byte, r.GetChunkSize());
                    r1.ReadT( initiativeSkillNumber );
                    r.EndChunk( DC_TAG('sn01'));
                }
                else
                {
                    r.SkipChunk();
                }

            }
            l.EndChunk('ps01');
        }
        else
            l.SkipChunk();
    }
}

void SPetItem::Write( CDataChunkWriter* w)
{   
    w->StartChunk(DC_TAG('ptba'));
    baseInfo.Write( w );
    w->EndChunk(DC_TAG('ptba'));

    w->StartChunk(DC_TAG('ptsk'));
    skillInfo.Write( w );
    w->EndChunk(DC_TAG('ptsk'));

    w->StartChunk(DC_TAG('ptlk'));
    xLockInfo.Write( w );
    w->EndChunk(DC_TAG('ptlk'));

    w->StartChunk(DC_TAG('ptbr'));
    breedInfo.Write( w );
    w->EndChunk(DC_TAG('ptbr'));
}

void SPetItem::Read( BYTE* szBuff, DWORD nSize )
{
    CDataChunkLoader l( szBuff, nSize );
    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('ptba'))
        {
            l.StartChunk('ptba');
            baseInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('ptba');
        }
        else if( l.IsChunk('ptsk'))
        {
            l.StartChunk('ptsk');
            skillInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('ptsk');
        }
        else if ( l.IsChunk('ptlk') )
        {
            l.StartChunk('ptlk');
            xLockInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('ptlk');
        }
        else if ( l.IsChunk('ptbr') )
        {
            l.StartChunk('ptbr');
            breedInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('ptbr');
        }
        else
            l.SkipChunk();
    }
}

void SPetItem::SLockInfo::Write( CDataChunkWriter* w )
{
    w->StartChunk(DC_TAG('lock'));
    w->StartChunk(DC_TAG('lk01'));
    w->WriteInt( bIsLocked );
    w->WriteInt64( n64UnLockTime );
    w->EndChunk(DC_TAG('lk01'));
    w->EndChunk(DC_TAG('lock'));
}

void SPetItem::SLockInfo::Read( BYTE* szBuff, DWORD nSize )
{
    CDataChunkLoader l(szBuff,nSize);
    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('lock'))
        {
            l.StartChunk('lock');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                {
                    if (r.IsChunk('lk01'))
                    {
                        r.StartChunk('lk01');
                        bIsLocked = r.ReadInt();
                        n64UnLockTime = r.ReadInt64();
                        r.EndChunk('lk01');
                    }
                    else
                    {
                        r.SkipChunk();
                    }	
                }
            }
            l.EndChunk('lock');
        }
        else
            l.SkipChunk();
    }
}

void SPetItem::SBreedInfo::Write( CDataChunkWriter* w )
{

    w->StartChunk(DC_TAG('br01'));

    w->WriteInt64( targetGuid );
    w->WriteDword( targetCharDBID );
    w->WriteByte ( targetQuality );
    w->WriteInt64( commitTime );

    w->EndChunk(DC_TAG('br01'));

}

void SPetItem::SBreedInfo::Read( BYTE* szBuff, DWORD nSize )
{
    CDataChunkLoader l(szBuff,nSize);
    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('br01'))
        {
            l.StartChunk('br01');
            {
                targetGuid     = l.ReadInt64();
                targetCharDBID = l.ReadDword();
                targetQuality  = l.ReadByte() ;
                commitTime     = l.ReadInt64();
 
            }
            l.EndChunk('br01');
        }
        else
            l.SkipChunk();
    }
}

bool SPetItem::IsPassUnLockTime( bool bSetLeftTime/* = false*/ )
{
    if ( GetUnLockTime() == 0 )
    { return false; }

    TimeEx xItemTime( GetUnLockTime() );    // 到期时间
    TimeEx xCurrentTime = TimeEx::GetCurrentTime(); // 当前时间
    if ( bSetLeftTime )
    {
        if ( xItemTime > xCurrentTime )
        {
            TimeSpan xSpan = xItemTime - xCurrentTime;
            SetUnLockLeftTime( xSpan.GetTimeSpan() );   // 设置剩余时间
        }  
        else
        {
            SetUnLockLeftTime( 0 );
        }
    }

    return xItemTime <= xCurrentTime;
}
