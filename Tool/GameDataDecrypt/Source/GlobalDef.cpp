#include "GlobalDef.h"
#include "TimeEx.h"

void SRankManager::SRank::WriteRank(CDataChunkWriter *w)
{
    w->OpenChunk('rank');
    {        
        w->WriteByteChunk('ff01',first);
        w->WriteByteChunk('se01',second);
    }
    w->CloseChunk('rank');
}

void SRankManager::SRank::ReadRank(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('rank'))
        {
            l.OpenChunk();
            while (!l.IsEndOfChunk())
            {                
                if (l.TryReadByteChunk('ff01',first)){}
                else if (l.TryReadByteChunk('se01',second)){}
                else
                    l.SkipChunk();
            }
        }
        else
            l.SkipChunk();
    }
}

void SRankManager::WriteRankManager(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('ra01'));
    for (int nloop = 0; nloop < 16; nloop++)
    {
        w->StartChunk(DC_TAG('rk01'));
        rankArray[nloop].WriteRank(w);
        w->EndChunk(DC_TAG('rk01'));
    }
    w->EndChunk(DC_TAG('ra01'));
}

void SRankManager::ReadRankManager(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if(l.IsChunk('ra01'))
        {
            l.StartChunk('ra01');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                for (int n =0; n<16;n++ )
                {
                    if (r.IsChunk('rk01'))
                    {
                        r.StartChunk('rk01');
                        {
                            rankArray[n].ReadRank(r.GetPointer().byte,r.GetChunkSize());
                        }
                        r.EndChunk('rk01');
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }
                }
            }
            l.EndChunk('ra01');
        }
        else 
            l.SkipChunk();
    }
}

void SElement::WriteElement(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('ele1'));
    w->WriteShort(item_stAtt);
    w->WriteShort(item_stDef);
    w->WriteShort(exec_stAtt);
    w->WriteShort(exec_stDef);
    w->WriteShort(status_stAtt);
    w->WriteShort(status_stDef);
    w->WriteShort(final_Att);
    w->WriteShort(final_Def);
    w->EndChunk(DC_TAG('ele1'));
}

void SElement::ReadElement(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('ele1'))
        {
            l.StartChunk('ele1');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {

                item_stAtt = r.ReadShort();
                item_stDef= r.ReadShort();
                exec_stAtt= r.ReadShort();
                exec_stDef= r.ReadShort();
                status_stAtt= r.ReadShort();
                status_stDef= r.ReadShort();
                final_Att= r.ReadShort();
                final_Def= r.ReadShort();
            }
            l.EndChunk('ele1');
        }
        else
            l.SkipChunk();
    }
}

bool SCharItem::IsOverdue( bool bSetLeftTime /* = false */)
{
    if( itembaseinfo.ustItemID == InvalidLogicNumber )
    { return false; }

    if( itembaseinfo.n64UseTime == TimeEx::UNDEF_TIME )
    { return false; }

    TimeEx xItemTime( itembaseinfo.n64UseTime );    // 到期时间
    TimeEx xCurrentTime = TimeEx::GetCurrentTime(); // 当前时间
    if ( bSetLeftTime ) // 服务器计算剩余时间
    {
        if ( xItemTime > xCurrentTime )
        {
            TimeSpan xSpan = xItemTime - xCurrentTime;
            itembaseinfo.nLeftTime = xSpan.GetTimeSpan();   // 设置剩余时间
        }  
        else
        {
            itembaseinfo.nLeftTime = 0;
        }
    }

    return xItemTime <= xCurrentTime;
}

bool SCharItem::IsPassUnLockTime( bool bSetLeftTime/* = false*/ )
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

void SCharItem::Read(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    bCanUse = true;
    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('base'))
        {
            l.StartChunk('base');
            {
                ReadData p(l.GetPointer().c);
                ReadItemBaseInfo(p,l.GetChunkSize());
            }
            l.EndChunk('base');
        }
        else if (l.IsChunk('equi'))
        {
            l.StartChunk('equi');
            {
                ReadData p(l.GetPointer().c);
                ReadEquipInfo(p,l.GetChunkSize());
            }
            l.EndChunk('equi');
        }
        else if (l.IsChunk('stor'))
        {
            l.StartChunk('stor');
            {
                ReadData p(l.GetPointer().c);
                ReadStorgeInfo(p,l.GetChunkSize());
            }
            l.EndChunk('stor');
        }
        else if ( l.IsChunk('lck1') )
        {
            l.StartChunk('lck1');
            {
                ReadData p(l.GetPointer().c);
                ReadLockInfo(p,l.GetChunkSize());
            }
            l.EndChunk('lck1');
        }
        else
            l.SkipChunk();
    }
}

void SCharItem::Write(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('base'));
    {
        w->StartChunk(DC_TAG('bs05'));
        {
            w->WriteShort(itembaseinfo.ustItemID);
            w->WriteInt64(itembaseinfo.nOnlyInt);
            w->WriteShort(itembaseinfo.stPacketIdx);
            w->WriteShort(itembaseinfo.ustItemCount);
            w->WriteDword(itembaseinfo.value1);
            w->WriteInt64(itembaseinfo.n64UseTime);
            w->WriteDword(itembaseinfo.value2);
            w->WriteString( itembaseinfo.szCreaterName );
            w->WriteByte( itembaseinfo.flag           );
        }
        w->EndChunk(DC_TAG('bs05'));
    }
    w->EndChunk(DC_TAG('base'));

    w->StartChunk(DC_TAG('equi'));
    {        
        w->StartChunk(DC_TAG('eq02'));
        {
            w->WriteFloat( equipdata.usHP     );
            w->WriteInt  ( equipdata.usHpMax );
            for (int i=0; i<SCharItem::EConstDefine_BaseRandMaxCount; ++i)
            { w->WriteShort(equipdata.baseRands[i]); }
            for (int i=0; i<SCharItem::EConstDefine_PurpleRandMaxCount; ++i)
            { w->WriteShort(equipdata.purpleRands[i]); }
            for (int i=0; i<SCharItem::EConstDefine_SuitRandMaxCount; ++i)
            { w->WriteShort(equipdata.suitRands[i]); }
            for (int i=0; i<SCharItem::EConstDefine_GemHoleMaxCount; ++i)
            { w->WriteShort(equipdata.gemIds[i]); }
            if ( equipdata.gemHoleCount > SCharItem::EConstDefine_GemHoleMaxCount)
            { equipdata.gemHoleCount = 0; }
            w->WriteByte( equipdata.gemHoleCount  );
            w->WriteByte( equipdata.ucLevel        );
            w->WriteByte( equipdata.quality        );
        }
        w->EndChunk(DC_TAG('eq02'));
    }
    w->EndChunk(DC_TAG('equi'));

    w->StartChunk(DC_TAG('stor'));
    {
        w->StartChunk(DC_TAG('sr01'));
        {
            w->WriteInt(storageinfo.bIsLocked);
            w->WriteInt(storageinfo.nStorageNpcId);
        }
        w->EndChunk(DC_TAG('sr01'));
    }
    w->EndChunk(DC_TAG('stor'));

    w->StartChunk(DC_TAG('lck1'));
    {
        w->StartChunk(DC_TAG('lk01'));
        {   
            w->WriteInt64(xLockInfo.n64UnLockTime);
        }
        w->EndChunk(DC_TAG('lk01'));
    }
    w->EndChunk(DC_TAG('lck1'));
}

void SCharItem::ReadItemBaseInfo(ReadData inP,int nSize)
{
    CDataChunkLoader l(inP.byte,nSize);

    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('bs05'))
        {
            l.StartChunk( 'bs05' );            
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
                itembaseinfo.ustItemID    = r.ReadShort();
                itembaseinfo.nOnlyInt     = r.ReadInt64();
                itembaseinfo.stPacketIdx  = r.ReadShort();
                itembaseinfo.ustItemCount = r.ReadShort();
                itembaseinfo.value1       = r.ReadDword();
                itembaseinfo.n64UseTime   = r.ReadInt64();
                itembaseinfo.value2       = r.ReadDword();

                int nStrSize = r.ReadInt();
                memset( &itembaseinfo.szCreaterName, 0, sizeof( itembaseinfo.szCreaterName ) );
                if( nStrSize > 0 )
                {                    
                    memcpy_s( itembaseinfo.szCreaterName, sizeof( itembaseinfo.szCreaterName ), r.GetPointer().byte, min(sizeof(CHAR)*nStrSize, sizeof( itembaseinfo.szCreaterName ) - 1 ) );
                    r.GetPointer().c += nStrSize;
                }

                itembaseinfo.flag          = r.ReadByte();
            }
            l.EndChunk('bs05');
        }
        else 
        { l.SkipChunk(); }
    }
}

void SCharItem::ReadEquipInfo(ReadData inP,int nSize)
{
    CDataChunkLoader l(inP.byte,nSize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('eq02'))
        {
            l.StartChunk( 'eq02' );
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
                equipdata.usHP = r.ReadFloat();
                equipdata.usHpMax = r.ReadInt();
                for (int n = 0; n< SCharItem::EConstDefine_BaseRandMaxCount;n++ )
                { equipdata.baseRands[n] = r.ReadShort(); }
                for (int n = 0; n< SCharItem::EConstDefine_PurpleRandMaxCount;n++ )
                { equipdata.purpleRands[n] = r.ReadShort(); }
                for (int n = 0; n< SCharItem::EConstDefine_SuitRandMaxCount;n++ )
                { equipdata.suitRands[n] = r.ReadShort(); }
                for (int n = 0; n< SCharItem::EConstDefine_GemHoleMaxCount;n++ )
                { equipdata.gemIds[n] = r.ReadShort(); }
                equipdata.gemHoleCount = r.ReadByte();
                if (equipdata.gemHoleCount > SCharItem::EConstDefine_GemHoleMaxCount)
                { equipdata.gemHoleCount = 0; }
                equipdata.ucLevel         = r.ReadByte();
                equipdata.quality         = r.ReadByte();
            }
            l.EndChunk('eq02');
        }
        else 
        { l.SkipChunk(); }
    }
}

void SCharItem::ReadStorgeInfo(ReadData inP,int nSize)
{
    CDataChunkLoader l(inP.byte,nSize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('sr01'))
        {
            l.StartChunk( 'sr01' );            
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
                storageinfo.bIsLocked = r.ReadInt();
                storageinfo.nStorageNpcId = r.ReadInt();
            }
            l.EndChunk('sr01');
        }        
        else
        { l.SkipChunk(); }
    }
}

void SCharItem::ReadLockInfo(ReadData inP,int nSize)
{
    CDataChunkLoader l(inP.byte,nSize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('lk01'))
        {
            l.StartChunk( 'lk01' );            
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {                
                xLockInfo.n64UnLockTime = r.ReadInt64();
            }
            l.EndChunk('lk01');
        }        
        else
            l.SkipChunk();
    }
}

void SMountItem::SBaseInfo::Write( CDataChunkWriter* w )
{
    w->StartChunk(DC_TAG('ba02'));
    w->Write ( szName,  sizeof(szName) , 1);
    w->WriteT( id       );
    w->WriteT( guid     );
    w->WriteT( isActive );
    w->WriteT( level    );
    w->WriteT( exp      );
    w->WriteT( hp       );
    w->WriteT( hpMax    );
    w->WriteT( savvy    );
    w->WriteT( generation );
    w->WriteT( nextId   );
    w->WriteT( quality  );
    w->WriteT( nPotentialPoint );
    w->Write ( baseAttribute,     sizeof(float) * EBaseAttr_MaxSize, 1);
    w->Write ( aptitudeAttribute, sizeof(float) * EBaseAttr_MaxSize, 1);
    w->Write ( potentialAttribute,sizeof(float) * EBaseAttr_MaxSize, 1);
    w->Write ( currentAttribute,  sizeof(float) * EBaseAttr_MaxSize, 1);
    w->EndChunk(DC_TAG('ba02'));
}

void SMountItem::SBaseInfo::Read( BYTE* szBuff,DWORD nSize )
{
    CDataChunkLoader l(szBuff,nSize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('ba02'))
        {
            l.StartChunk('ba02');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                r.ReadToBuffer((BYTE*)szName, sizeof(szName));
                r.ReadT( id       );
                r.ReadT( guid     );
                r.ReadT( isActive );
                r.ReadT( level    );
                r.ReadT( exp      );
                r.ReadT( hp       );
                r.ReadT( hpMax    );
                r.ReadT( savvy    );
                r.ReadT( generation );
                r.ReadT( nextId     );
                r.ReadT( quality    );
                r.ReadT( nPotentialPoint );
                r.ReadToBuffer((BYTE*)baseAttribute,     sizeof(float) * EBaseAttr_MaxSize);
                r.ReadToBuffer((BYTE*)aptitudeAttribute, sizeof(float) * EBaseAttr_MaxSize);
                r.ReadToBuffer((BYTE*)potentialAttribute,sizeof(float) * EBaseAttr_MaxSize);
                r.ReadToBuffer((BYTE*)currentAttribute,  sizeof(float) * EBaseAttr_MaxSize);
            }
            l.EndChunk('ba02');
        }
        else 
            l.SkipChunk();
    }
}

bool SMountItem::SSkillInfo::AddSkill( unsigned short skillId, unsigned short skillLevel /*= 1 */,uint8 beginIndex)
{
    int index      = -1;
    int emptyIndex = -1;
    for ( int i = beginIndex; i < MICD_MaxSkillCount; ++i)
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

    // 如果是主动技能 不能大于开启槽数
    if ( (beginIndex == MICD_InitiativeSkillIndex) && ( emptyIndex >= initiativeSkillNumber ) )
    { return false; }

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

bool SMountItem::SSkillInfo::ReplaceSkill( unsigned short skillId, unsigned short skillLevel, int nIndex )
{
    if ( nIndex<0 || nIndex>MICD_MaxSkillCount)
    { return false; }

    if ( skills[nIndex].ustSkillID == InvalidLogicNumber )
    { return false; }

    skills[nIndex].ustSkillID   = skillId;
    skills[nIndex].stSkillLevel = skillLevel;
    return true;
}

bool SMountItem::SSkillInfo::RemoveSkill( unsigned short skillId )
{
    int index = -1;
    for( int i=0 ; i<MICD_MaxSkillCount ; ++i)
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

    for ( int i=index, I=index+1; I<MICD_MaxSkillCount; ++i, ++I )
    {
        if ( skills[I].ustSkillID == InvalidLogicNumber )
        { break; }

        skills[i] = skills[I];        
        skills[I].Reset();
    }

    return true;
}

const SCharSkill* SMountItem::SSkillInfo::GetSkill( unsigned short skillId )
{
    for( int i=0 ; i<MICD_MaxSkillCount ; ++i)
    {
        if( skills[i].ustSkillID == skillId )
        {
            return &skills[i];
        }
    }

    return NULL;
}

int SMountItem::SSkillInfo::GetCurrentSkillCount()
{
    int nCount = 0;
    for( int i=0 ; i<MICD_MaxSkillCount ; ++i)
    {
        if ( skills[i].ustSkillID == InvalidLogicNumber )
        { break; }

        ++nCount;
    }

    return nCount;
}

void SMountItem::SSkillInfo::Reset()
{
    for( int i=0 ; i<MICD_MaxSkillCount ; ++i)
    {
        if ( skills[i].ustSkillID == InvalidLogicNumber )
        { continue; }

        skills[i].Reset();
    }
}

void SMountItem::SSkillInfo::Write( CDataChunkWriter* w )
{    
    w->StartChunk(DC_TAG('misk'));
    for ( int i=0; i<MICD_MaxSkillCount; ++i)
    {   
        w->StartChunk(DC_TAG('sk01'));
        skills[i].write( w );
        w->EndChunk(DC_TAG('sk01'));
    }

    w->StartChunk( DC_TAG('isn1'));
    w->WriteT( initiativeSkillNumber );
    w->EndChunk( DC_TAG('isn1'));

    w->EndChunk(DC_TAG('misk'));
}

void SMountItem::SSkillInfo::Read( BYTE* szBuff, DWORD nSize )
{
    CDataChunkLoader l(szBuff,nSize);
    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('misk'))
        {
            l.StartChunk('misk');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                for (int i = 0; i < MICD_MaxSkillCount; ++i)
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

                if ( r.IsChunk('isn1'))
                {
                    r.StartChunk( DC_TAG('isn1'));
                    CDataChunkLoader r1(r.GetPointer().byte, r.GetChunkSize());
                    r1.ReadT( initiativeSkillNumber );
                    r.EndChunk( DC_TAG('isn1'));
                }
                else
                {
                    r.SkipChunk();
                }
            }
            l.EndChunk('misk');
        }
        else
            l.SkipChunk();
    }
}

void SMountItem::LockInfo::Write( CDataChunkWriter* w )
{
    w->StartChunk(DC_TAG('lock'));
    w->StartChunk(DC_TAG('lk01'));
    w->WriteInt( bIsLocked );
    w->WriteInt64( n64UnLockTime );
    w->EndChunk(DC_TAG('lk01'));
    w->EndChunk(DC_TAG('lock'));
}

void SMountItem::LockInfo::Read( BYTE* szBuff, DWORD nSize )
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

bool SMountItem::IsPassUnLockTime( bool bSetLeftTime/* = false*/ )
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

void SMountItem::Write( CDataChunkWriter* w)
{   
    w->StartChunk(DC_TAG('miba'));
    baseInfo.Write( w );
    w->EndChunk(DC_TAG('miba'));

    w->StartChunk(DC_TAG('misk'));
    skillInfo.Write( w );
    w->EndChunk(DC_TAG('misk'));

    w->StartChunk(DC_TAG('stin'));
    xLockInfo.Write( w );
    w->EndChunk(DC_TAG('stin'));
}

void SMountItem::Read( BYTE* szBuff, DWORD nSize )
{
    CDataChunkLoader l( szBuff, nSize );
    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('miba'))
        {
            l.StartChunk('miba');
            baseInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('miba');
        }
        else if( l.IsChunk('misk'))
        {
            l.StartChunk('misk');
            skillInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('misk');
        }
        else if ( l.IsChunk('stin') )
        {
            l.StartChunk('stin');
            xLockInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('stin');
        }
        else
            l.SkipChunk();
    }
}


void SPanzerItem::SBaseInfo::Write( CDataChunkWriter* w )
{
    w->StartChunk(DC_TAG('ba01'));
    w->Write ( szName,  sizeof(szName) , 1);
    w->WriteT( id           );
    w->WriteT( type         );
    w->WriteT( level        );
    w->WriteT( takeLevel    );
    w->WriteT( nHp          );
    w->WriteT( nMp          );
    w->WriteT( nHpMax       );
    w->WriteT( nMpMax       );
    w->WriteT( defendShort  );
    w->WriteT( defendLong   );
    w->WriteT( repairCount  );
    w->WriteT( repairMaxCount   );
    w->WriteT( loadNumber   );
    w->WriteT( moveSpeed    );
    w->WriteT( guid         );
    w->EndChunk(DC_TAG('ba01'));
}

void SPanzerItem::SBaseInfo::Read( BYTE* szBuff,DWORD nSize )
{
    CDataChunkLoader l(szBuff,nSize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('ba01'))
        {
            l.StartChunk('ba01');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                r.ReadToBuffer((BYTE*)szName, sizeof(szName));
                r.ReadT( id           );
                r.ReadT( type         );
                r.ReadT( level        );
                r.ReadT( takeLevel    );
                r.ReadT( nHp          );
                r.ReadT( nMp          );
                r.ReadT( nHpMax       );
                r.ReadT( nMpMax       );
                r.ReadT( defendShort  );
                r.ReadT( defendLong   );
                r.ReadT( repairCount  );
                r.ReadT( repairMaxCount   );
                r.ReadT( loadNumber   );
                r.ReadT( moveSpeed    );
                r.ReadT( guid         );
            }
            l.EndChunk('ba01');
        }
        else 
            l.SkipChunk();
    }
}

void SPanzerItem::SSkillInfo::Write( CDataChunkWriter* w )
{    
    w->StartChunk(DC_TAG('pnz1'));

    for ( int i=0; i<PCD_PanzerSkillMaxSize; ++i)
    {   
        w->StartChunk(DC_TAG('sk01'));
        skills[i].write( w );
        w->EndChunk(DC_TAG('sk01'));
    }

    w->EndChunk(DC_TAG('pnz1'));
}

void SPanzerItem::SSkillInfo::Read( BYTE* szBuff, DWORD nSize )
{
    CDataChunkLoader l(szBuff,nSize);
    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('pnz1'))
        {
            l.StartChunk('pnz1');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                for (int i = 0; i < PCD_PanzerSkillMaxSize; ++i)
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
            }
            l.EndChunk('pnz1');
        }
        else
            l.SkipChunk();
    }
}

void SPanzerItem::LockInfo::Write( CDataChunkWriter* w )
{
    w->StartChunk(DC_TAG('lock'));
    w->StartChunk(DC_TAG('lk01'));
    w->WriteInt( bIsLocked );
    w->WriteInt64( n64UnLockTime );
    w->EndChunk(DC_TAG('lk01'));
    w->EndChunk(DC_TAG('lock'));
}

void SPanzerItem::LockInfo::Read( BYTE* szBuff, DWORD nSize )
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

void SPanzerItem::Write( CDataChunkWriter* w)
{   
    w->StartChunk(DC_TAG('pnbi'));
    baseInfo.Write( w );
    w->EndChunk(DC_TAG('pnbi'));

    w->StartChunk(DC_TAG('pnsi'));
    skillInfo.Write( w );
    w->EndChunk(DC_TAG('pnsi'));

    w->StartChunk(DC_TAG('pnli'));
    lockInfo.Write( w );
    w->EndChunk(DC_TAG('pnli'));
}

void SPanzerItem::Read( BYTE* szBuff, DWORD nSize )
{
    CDataChunkLoader l( szBuff, nSize );
    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('pnbi'))
        {
            l.StartChunk('pnbi');
            baseInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('pnbi');
        }
        else if( l.IsChunk('pnsi'))
        {
            l.StartChunk('pnsi');
            skillInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('pnsi');
        }
        else if ( l.IsChunk('pnli') )
        {
            l.StartChunk('pnli');
            lockInfo.Read( l.GetPointer().byte, l.GetChunkSize() );
            l.EndChunk('pnli');
        }
        else
            l.SkipChunk();
    }
}

void SCharVisual::WriteVisual(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('hai1'));
        w->WriteShort( hairId );
    w->EndChunk(DC_TAG('hai1'));

    w->StartChunk(DC_TAG('fac1'));
        w->WriteShort( faceId );
    w->EndChunk(DC_TAG('fac1'));

    w->StartChunk(DC_TAG('shf1'));
        w->WriteByte( showFlag );
    w->EndChunk(DC_TAG('shf1'));
    
    w->StartChunk( DC_TAG('fmp1') );
        w->WriteFloat( fModelPercent );
    w->EndChunk( DC_TAG('fmp1') );

    w->StartChunk(DC_TAG('ite2')); // modified 
        for (int i=0; i<EEquipPartType_MaxEquitPart;  ++i)
        {
            w->StartChunk(DC_TAG('itm1'));
                equipitem[i].Write(w);
            w->EndChunk(DC_TAG('itm1'));
        }
    w->EndChunk(DC_TAG('ite2'));
}

void SCharVisual::ReadVisual( BYTE* bybuff, DWORD dwsize )
{
	CDataChunkLoader l( bybuff, dwsize );
	while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('hai1'))
        {
            l.StartChunk('hai1');
            {
                CDataChunkLoader r(l);
                hairId = r.ReadShort();
            }
            l.EndChunk('hai1');
        }
        else if (l.IsChunk('fac1'))
        {
            l.StartChunk('fac1');
            {
                CDataChunkLoader r(l);
                faceId = r.ReadShort();
            }
            l.EndChunk('fac1');
        }
        else if (l.IsChunk('shf1'))
        {
            l.StartChunk('shf1');
            {
                CDataChunkLoader r(l);
                showFlag = r.ReadByte();
            }
            l.EndChunk('shf1');
        }
        else if ( l.IsChunk('fmp1') )
        {
            l.StartChunk('fmp1');
            {
                CDataChunkLoader r(l);
                fModelPercent = r.ReadFloat();
            }
            l.EndChunk('fmp1');
        }
        else if (l.IsChunk('ite2'))
        {
            l.StartChunk('ite2'); // 多个自定义套装的版本
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                for ( int i=0; i<EEquipPartType_MaxEquitPart; ++i )
                {	
                    if( r.IsChunk('itm1') )
                    {
                        r.StartChunk('itm1');
                        equipitem[i].Read(r.GetPointer().byte,r.GetChunkSize());
                        r.EndChunk('itm1');		
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }
                }
            }
            l.EndChunk('ite2');
        }
		else
        { l.SkipChunk(); }
	}
}

#define DC_TAG(x) (DWORD)(  (((DWORD)x&0x0000ff00)<<8)+(((DWORD)x&0x000000ff)<<24)+(((DWORD)x&0x00ff0000)>>8)+(((DWORD)x&0xff000000)>>24) )
//////////////////////////////////////////////////////////////////////////
void SCharSkill::write(CDataChunkWriter *w)
{   
    w->WriteChunkT('sllv', stSkillLevel);
    w->WriteChunkT('slid', ustSkillID);
    w->WriteChunkT('exp1', dwCurSkillExp);
    w->WriteChunkT('scd1', nColdTime);
}

void SCharSkill::read( BYTE* buffer,DWORD size )
{
    CDataChunkLoader l(buffer,size);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('sllv'))
        {
            l.StartChunk('sllv');
            CDataChunkLoader r(l.GetPointer().byte, l.GetChunkSize());
            r.ReadT( stSkillLevel );
            l.EndChunk('sllv');
        }
        else if (l.IsChunk('slid'))
        {
            l.StartChunk('slid');
            CDataChunkLoader r(l.GetPointer().byte, l.GetChunkSize());
            r.ReadT( ustSkillID );
            l.EndChunk('slid');
        }
        else if (l.IsChunk('exp1'))
        {
            l.StartChunk('exp1');            
            CDataChunkLoader r(l.GetPointer().byte, l.GetChunkSize());
            r.ReadT( dwCurSkillExp );
            l.EndChunk('exp1');
        }
        else if ( l.IsChunk('scd1') )
        {
            l.StartChunk('scd1');            
            CDataChunkLoader r(l.GetPointer().byte, l.GetChunkSize());
            r.ReadT( nColdTime );
            l.EndChunk('scd1');
        }
        else 
            l.SkipChunk();
    }
}

void SCharSkills::write(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('skll'));
    for (int n = 0; n < More_iMaxSkillKnown;n++)
    {
        w->StartChunk(DC_TAG('sl01'));
        skill[n].write(w);
        w->EndChunk(DC_TAG('sl01'));
    }
    w->EndChunk(DC_TAG('skll'));
}

void SCharSkills::read(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('skll'))
        {
            l.StartChunk('skll');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            for (int n = 0; n < More_iMaxSkillKnown;n++)
            {
                if (r.IsChunk('sl01'))
                {
                    r.StartChunk('sl01');
                    skill[n].read(r.GetPointer().byte,r.GetChunkSize());
                    r.EndChunk('sl01');
                }
                else
                {
                    r.SkipChunk();
                    break;
                }

            }
            l.EndChunk('skll');
        }
        else
            l.SkipChunk();
    }
}

void SShortCut::writeShortCut(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('type'));
    {	
        w->WriteInt(BagType);
    }
    w->EndChunk(DC_TAG('type'));

    w->StartChunk(DC_TAG('inde'));
    {
        w->WriteInt(BagIndex);
    }
    w->EndChunk(DC_TAG('inde'));
}

void SHotKey::writeMouseItem(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('cut1'));
    {
        ShortCut.writeShortCut(w);
    }
    w->EndChunk(DC_TAG('cut1'));
}

void SMouseItem::writeMouseItem(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('item'));
    {
        ItemData.Write(w);
    }
    w->EndChunk(DC_TAG('item'));

    w->StartChunk(DC_TAG('cut1'));
    {
        ShortCut.writeShortCut(w);
    }
    w->EndChunk(DC_TAG('cut1'));
}

void SCharHotKeys::writeCharHotKeys(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('moi4'));
    {
        for (int n = 0; n < More_iHotkey;n++)
        {
            w->StartChunk(DC_TAG('om01'));
            itemHotKey[n].writeMouseItem(w);
            w->EndChunk(DC_TAG('om01'));
        }
    }
    w->EndChunk(DC_TAG('moi4'));
}

void SCharPosData::WritePosData (CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('mpid'));
    {
        w->WriteDword(dwMapID);
    }
    w->EndChunk(DC_TAG('mpid'));

    w->StartChunk(DC_TAG('posx'));
    {
        w->WriteShort(stX);
    }
    w->EndChunk(DC_TAG('posx'));

    w->StartChunk(DC_TAG('posy'));
    {
        w->WriteShort(stY);
    }
    w->EndChunk(DC_TAG('posy'));

    w->StartChunk(DC_TAG('d3dx'));
    {
        w->WriteFloat(vPos.x);
    }
    w->EndChunk(DC_TAG('d3dx'));

    w->StartChunk(DC_TAG('d3dy'));
    {
        w->WriteFloat(vPos.y);
    }
    w->EndChunk(DC_TAG('d3dy'));

    w->StartChunk(DC_TAG('d3dz'));
    {
        w->WriteFloat(vPos.z);
    }
    w->EndChunk(DC_TAG('d3dz'));
}

void SCharOtherDataClient0::WriteOtherDataClient0(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('pos1'));
    pos.WritePosData(w);
    w->EndChunk(DC_TAG('pos1'));

    w->StartChunk(DC_TAG('bpos'));
    sBornPos.WritePosData(w);
    w->EndChunk(DC_TAG('bpos'));
}


void SCharOtherDataClient::writeOtherdataClient(CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('clt0'));
    SCharOtherDataClient0::WriteOtherDataClient0(w);
    w->EndChunk(DC_TAG('clt0'));

    w->StartChunk(DC_TAG('skil'));
    skills.write(w);
    w->EndChunk(DC_TAG('skil'));

    w->StartChunk(DC_TAG('hkey'));
    hotkeys.writeCharHotKeys(w);
    w->EndChunk(DC_TAG('hkey'));

    w->StartChunk(DC_TAG('fida'));
    w->WriteShort(stMountId);
    w->WriteFloat(fDirX);
    w->WriteFloat(fDirY);
    w->EndChunk(DC_TAG('fida'));

    w->StartChunk(DC_TAG('bbb1'));
    for (int nloop = 0; nloop < BodyStatusType_Max;nloop ++)
    {
        w->StartChunk(DC_TAG('by01'));
        sCharBodyStatus[nloop].WriteBodyStatus(w);
        w->EndChunk(DC_TAG('by01'));
    }
    w->EndChunk(DC_TAG('bbb1'));

    w->StartChunk(DC_TAG('rec1'));
    w->Write( recipes, sizeof(unsigned short) * MAX_RECIPE_COUNT, 1);
    w->EndChunk(DC_TAG('rec1'));

    w->StartChunk( DC_TAG('plt1') );
    w->WriteByte( chProtectLockTime );
    w->EndChunk( DC_TAG('plt1') );

    w->StartChunk( DC_TAG('bst1') );
    w->WriteDword( dwBanSpeakTime );
    w->EndChunk( DC_TAG('bst1') );
}

void SSysVars::writeVars( CDataChunkWriter *w )
{
    w->Write(&szVars,sizeof(short)*More_iMaxVars,1);
}

void SCharOtherData::WriteOtherDataBlob (CDataChunkWriter *w)
{
    w->StartChunk(DC_TAG('clit'));
    SCharOtherDataClient::writeOtherdataClient(w);
    w->EndChunk(DC_TAG('clit'));	

    w->StartChunk(DC_TAG('vars'));
    vars.writeVars(w);
    w->EndChunk(DC_TAG('vars'));

    w->StartChunk(DC_TAG('otim'));
    w->StartChunk(DC_TAG('om07'));
    w->WriteChar(bNewChar);
    w->WriteDword( dwHighShoutCDTime );
    w->WriteDword( dwRecordKillMonsterTime );
    w->WriteDword( dwRecordKillMonsterCount );
    w->WriteDword( nRecordHonourTime );
    w->WriteShort( nRecordHonourCount );
    w->WriteString( const_cast< char* >( xSecondPassword.GetPassword() ) );
    w->WriteChar( xSecondPassword.GetHaveCheck() );
    w->WriteInt64( xSecondPassword.GetRemoveTime() );
    w->WriteDword( xSecondPassword.GetProtectFlag() );
    w->WriteDword( nGuildID );
    w->WriteDword( dwLeaveGuildTime );
    w->EndChunk(DC_TAG('om07'));
    w->EndChunk(DC_TAG('otim'));
}

void  SCharOtherData::ReadOtherDataBlob( BYTE* bybuff, DWORD dwsize )
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('clit'))
        {
            l.StartChunk('clit');
            CDataChunkLoader p(l.GetPointer().byte,l.GetChunkSize());
            SCharOtherDataClient::readOtherdataClient(p.GetPointer().byte, p.GetBufferSize());
            l.EndChunk('clit');
        }
        else if( l.IsChunk('vars') )
        {
            l.StartChunk('vars');
            {
                /*CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());*/
                //if( r.IsChunk('va01') )
                //{
                //	r.StartChunk('va01');
                ReadData p(l.GetPointer().c);
                vars.readVars(p,l.GetChunkSize());
                //	r.EndChunk('va01');
                //}
            }
            l.EndChunk('vars');						
        }
        else if (l.IsChunk('otim'))
        {
            l.StartChunk('otim');
            {
                ReadData p(l.GetPointer().c);
                ReadOtherImport(p,l.GetChunkSize());
            }
            l.EndChunk('otim');
        }
        else
            l.SkipChunk();
    }
}

void SCharOtherData::ReadOtherImport(ReadData inP,int nsize)
{
    CDataChunkLoader l(inP.byte,nsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('om06'))
        {
            l.StartChunk('om06');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
                bNewChar                 = r.ReadChar();
                dwHighShoutCDTime        = r.ReadDword();
                dwRecordKillMonsterTime  = r.ReadDword();
                dwRecordKillMonsterCount = r.ReadDword();
                nRecordHonourTime        = r.ReadDword();
                nRecordHonourCount       = r.ReadShort();

                // 2级密码
                int nStrSize = r.ReadInt();
                char szPassword[ 128 ] = { 0 };
                memcpy_s( szPassword, sizeof( szPassword ), r.GetPointer().byte, min( sizeof( szPassword ) - 1, sizeof( CHAR ) * nStrSize ) );
                xSecondPassword.SetPassword( szPassword );
                r.GetPointer().c += nStrSize;

                xSecondPassword.SetHaveCheck( r.ReadChar() );
                xSecondPassword.SetRemoveTime( r.ReadInt64() );
                nGuildID                = r.ReadDword();
                dwLeaveGuildTime        = r.ReadDword();
            }
            l.EndChunk('om06');
        }
        else if (l.IsChunk('om07'))
        {
            l.StartChunk('om07');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
                bNewChar                 = r.ReadChar();
                dwHighShoutCDTime        = r.ReadDword();
                dwRecordKillMonsterTime  = r.ReadDword();
                dwRecordKillMonsterCount = r.ReadDword();
                nRecordHonourTime        = r.ReadDword();
                nRecordHonourCount       = r.ReadShort();

                // 2级密码
                int nStrSize = r.ReadInt();
                char szPassword[ 128 ] = { 0 };
                memcpy_s( szPassword, sizeof( szPassword ), r.GetPointer().byte, min( sizeof( szPassword ) - 1, sizeof( CHAR ) * nStrSize ) );
                xSecondPassword.SetPassword( szPassword );
                r.GetPointer().c += nStrSize;

                xSecondPassword.SetHaveCheck( r.ReadChar() );
                xSecondPassword.SetRemoveTime( r.ReadInt64() );
                xSecondPassword.SetProtectFlag( r.ReadDword() ); // 读取保护类型
                nGuildID                = r.ReadDword();
                dwLeaveGuildTime        = r.ReadDword();
            }
            l.EndChunk('om07');
        }
        else
            l.SkipChunk();
    }
}

void TitleCounter::Write( CDataChunkWriter* w )
{   
    w->StartChunk(DC_TAG('cc01'));
    w->WriteT( titleid );
    w->WriteT( type    );
    w->WriteT( value   );
    w->WriteT( count   );
    w->EndChunk(DC_TAG('cc01'));
}

void TitleCounter::Read( BYTE* buffer, DWORD size )
{
    CDataChunkLoader l(buffer,size);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('cc01'))
        {
            l.StartChunk('cc01');
            {
                CDataChunkLoader r(l.GetPointer().byte, l.GetChunkSize());
                r.ReadT( titleid );
                r.ReadT( type    );
                r.ReadT( value   );
                r.ReadT( count   );
            }
            l.EndChunk('cc01');
        }
        else 
            l.SkipChunk();
    }
}

void SRunTimeInfoToDB::Write( CDataChunkWriter* w )
{   
    w->StartChunk(DC_TAG('cc02'));
    w->WriteT( nEneryTime );
    w->WriteT( nVigorTime );
    w->WriteT( nMountActionTime    );
    w->EndChunk(DC_TAG('cc02'));
}

void SRunTimeInfoToDB::Read( BYTE* buffer, DWORD size )
{
    CDataChunkLoader l(buffer,size);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('cc02'))
        {
            l.StartChunk('cc02');
            {
                CDataChunkLoader r(l.GetPointer().byte, l.GetChunkSize());
                r.ReadT( nEneryTime );
                r.ReadT( nVigorTime );
                r.ReadT( nMountActionTime );
            }
            l.EndChunk('cc02');
        }
        else 
            l.SkipChunk();
    }
}

void SpecialQuestInfo::Write( CDataChunkWriter* w )
{   
    w->StartChunk(DC_TAG('cc04'));
    w->WriteT( nNpcID );
    w->WriteT( dwTime );
    w->EndChunk(DC_TAG('cc04'));
}

void SpecialQuestInfo::Read( BYTE* buffer, DWORD size )
{
    CDataChunkLoader l(buffer,size);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('cc04'))
        {
            l.StartChunk('cc04');
            {
                CDataChunkLoader r(l.GetPointer().byte, l.GetChunkSize());
                r.ReadT( nNpcID );
                r.ReadT( dwTime );
            }
            l.EndChunk('cc04');
        }
        else 
            l.SkipChunk();
    }
}

void SPressKeySuit::Write( CDataChunkWriter* w )
{   
    w->StartChunk(DC_TAG('pk01'));
        w->Write ( keySuitName, sizeof(keySuitName) , 1);
        w->Write ( &equipitem,  sizeof(int64)*EEquipPartType_MaxEquitPart, 1);
    w->EndChunk(DC_TAG('pk01'));
}

void SPressKeySuit::Read( BYTE* buffer, DWORD size )
{
    CDataChunkLoader l(buffer,size);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('pk01'))
        {
            l.StartChunk('pk01');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                r.ReadToBuffer( (BYTE*)keySuitName, sizeof(keySuitName) );
                r.ReadToBuffer( (BYTE*)equipitem  , sizeof(int64) * EEquipPartType_MaxEquitPart);
            }
            l.EndChunk('pk01');
        }
        else 
            l.SkipChunk();
    }
}

void SExtendData::Write(CDataChunkWriter *w)
{ 
    w->StartChunk(DC_TAG('exil'));

    for ( int i=0; i<MAX_TITLE_COUNT; ++i)
    {
        w->StartChunk(DC_TAG('ex01'));
        nTitleCounters[i].Write( w );
        w->EndChunk(DC_TAG('ex01'));
    }

    w->StartChunk(DC_TAG('ex02'));
    xRunTime.Write( w );
    w->EndChunk(DC_TAG('ex02'));

    w->StartChunk( DC_TAG('of03'));
    w->WriteT( dwGuideQuestInfo );
    w->EndChunk( DC_TAG('of03'));

    for ( int i = 0; i < MAX_SPECIALQUEST_COUNT; ++i )
    {
        w->StartChunk(DC_TAG('ex04'));
        xPubQuestInfo[i].Write( w );
        w->EndChunk(DC_TAG('ex04'));
    }

    for ( int i = 0; i < MAX_SPECIALQUEST_COUNT; ++i )
    {
        w->StartChunk(DC_TAG('ex05'));
        xConQuestInfo[i].Write( w );
        w->EndChunk(DC_TAG('ex05'));
    }

    w->StartChunk( DC_TAG('of06'));
    w->WriteT( isOfflineHook );
    w->WriteT( totalHookTime );
    w->EndChunk( DC_TAG('of06') );

    for ( int i = 0; i < MAX_PRESSKEYSUIT_COUNT; ++i )
    {
        w->StartChunk(DC_TAG('ks07'));
        xPressKeySuit[i].Write( w );
        w->EndChunk(DC_TAG('ks07'));
    }

    w->StartChunk(DC_TAG('tv08'));
    w->Write ( &n64TimeVars,  sizeof(int64)*ECT_MaxTimeVar, 1);
    w->EndChunk(DC_TAG('tv08'));

    w->EndChunk(DC_TAG('exil'));
}

void SExtendData::Read( BYTE* buffer, DWORD size )
{
    CDataChunkLoader l(buffer,size);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('exil'))
        { // ToNotify 此读方法 变成不支持顺序的随意了 不好
            l.StartChunk('exil');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                for (int i = 0; i < MAX_TITLE_COUNT; ++i)
                {
                    if (r.IsChunk('ex01'))
                    {
                        r.StartChunk('ex01');
                        nTitleCounters[i].Read(r.GetPointer().byte,r.GetChunkSize());
                        r.EndChunk('ex01');
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }	
                }

                if ( r.IsChunk('ex02') )
                {
                    r.StartChunk('ex02');
                    xRunTime.Read( r.GetPointer().byte, r.GetChunkSize() );
                    r.EndChunk('ex02');
                }
                else
                {
                    r.SkipChunk();
                }

                if ( r.IsChunk('of03'))
                {
                    r.StartChunk( DC_TAG('of03'));
                    CDataChunkLoader r1(r.GetPointer().byte, r.GetChunkSize());
                    r1.ReadT( dwGuideQuestInfo );
                    r.EndChunk( DC_TAG('of03'));
                }
                else
                {
                    r.SkipChunk();
                }

                for ( int i = 0; i < MAX_SPECIALQUEST_COUNT; ++i )
                {
                    if (r.IsChunk('ex04'))
                    {
                        r.StartChunk('ex04');
                        xPubQuestInfo[i].Read(r.GetPointer().byte,r.GetChunkSize());
                        r.EndChunk('ex04');
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }	
                }

                for ( int i = 0; i < MAX_SPECIALQUEST_COUNT; ++i )
                {
                    if (r.IsChunk('ex05'))
                    {
                        r.StartChunk('ex05');
                        xConQuestInfo[i].Read(r.GetPointer().byte,r.GetChunkSize());
                        r.EndChunk('ex05');
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }	
                }
                
                if ( r.IsChunk('of06'))
                {
                    r.StartChunk( DC_TAG('of06'));
                    CDataChunkLoader r1(r.GetPointer().byte, r.GetChunkSize());
                    r1.ReadT( isOfflineHook );
                    r1.ReadT( totalHookTime );
                    r.EndChunk( DC_TAG('of06'));
                }
                else
                {
                    r.SkipChunk();
                }

                for ( int i = 0; i < MAX_PRESSKEYSUIT_COUNT; ++i )
                {
                    if (r.IsChunk('ks07'))
                    {
                        r.StartChunk('ks07');
                        xPressKeySuit[i].Read(r.GetPointer().byte,r.GetChunkSize());
                        r.EndChunk('ks07');
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }	
                }

                if (r.IsChunk('tv08'))
                {
                    r.StartChunk('tv08');
                    {
                        CDataChunkLoader r1(r.GetPointer().byte,r.GetChunkSize());
                        r1.ReadToBuffer( (BYTE*)&n64TimeVars, sizeof(int64) * ECT_MaxTimeVar);
                    }
                    r.EndChunk('tv08');
                }
                else 
                {
                    r.SkipChunk();
                }
                
            }
            l.EndChunk('exil');
        }
        else
            l.SkipChunk();
    }
}

void SExtendData::AddTitleCounter(TitleCounter &xcounter)
{
    for (int i = 0; i < MAX_TITLE_COUNT; ++i)
    {
        if (nTitleCounters[i].IsEmpty())
        {
            nTitleCounters[i] = xcounter;
            break;
        }
    }
}

void SExtendData::RemoveTitleCounter(short nTitleID)
{
    for (int i = 0; i < MAX_TITLE_COUNT; ++i)
    {
        if (nTitleCounters[i].GetTitleID() == nTitleID)
        {
            nTitleCounters[i].Clear(); 
            break;
        }
    }
}

TitleCounter* SExtendData::GetTitleCounterByTitleID(short nID)
{
    for (int i = 0; i < MAX_TITLE_COUNT; ++i)
    {
        if (nTitleCounters[i].GetTitleID() == nID)
        {
            return &nTitleCounters[i];
        }
    }

    return NULL;
}

TitleCounter* SExtendData::GetTitleCounterByIndex(short nIndex)
{
    if (nIndex < 0 || nIndex >= MAX_TITLE_COUNT) { return NULL; }

    return &nTitleCounters[nIndex];
}

TitleCounter* SExtendData::GetTitleCounterByConditionType(short nType, short nValue)
{
    for (int i = 0; i < MAX_TITLE_COUNT; ++i)
    {
        if (nTitleCounters[i].GetType() == nType && nTitleCounters[i].GetValue() == nValue)
        {
            return &nTitleCounters[i];
        }
    }

    return NULL;
}

void  SCharAchieve::Write(CDataChunkWriter *w)
{ 
    w->StartChunk(DC_TAG('fst1'));
    w->WriteT( finishState );
    w->WriteT( finishTime  );
    w->EndChunk(DC_TAG('fst1'));
}

void SCharAchieve::Read( BYTE* buffer, DWORD size )
{
    CDataChunkLoader l(buffer,size);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('fst1'))
        {
            l.StartChunk('fst1');
            {
                CDataChunkLoader r(l.GetPointer().byte, l.GetChunkSize());
                r.ReadT( finishState );
                r.ReadT( finishTime  );
            }

            l.EndChunk('fst1');
        }
        else 
            l.SkipChunk();
    }
}

void SAchieveData::Write(CDataChunkWriter *w)
{ 
    w->StartChunk(DC_TAG('acdt'));

    w->StartChunk( DC_TAG('poit'));
    w->WriteT( achievePoint );
    w->EndChunk( DC_TAG('poit'));

    w->StartChunk(DC_TAG('var1'));
    w->Write( achieveVars, sizeof(uint32) * More_iMaxAchieveVars, 1);
    w->EndChunk(DC_TAG('var1'));

    for ( int i = 0; i < MAX_ACHIVEVMENT_COUNT; ++i )
    {
        w->StartChunk(DC_TAG('xaci'));
        xAchievements[i].Write( w );
        w->EndChunk(DC_TAG('xaci'));
    }

    w->EndChunk(DC_TAG('acdt'));
}

void SAchieveData::Read( BYTE* buffer, DWORD size )
{
    CDataChunkLoader l(buffer,size);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('acdt'))
        { 
            l.StartChunk('acdt');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());

                if ( r.IsChunk('poit'))
                {
                    r.StartChunk( DC_TAG('poit'));
                    CDataChunkLoader r1(r.GetPointer().byte, r.GetChunkSize());
                    r1.ReadT( achievePoint );
                    r.EndChunk( DC_TAG('poit'));
                }
                else
                {
                    r.SkipChunk();
                }

                if ( r.IsChunk('var1'))
                {
                    r.StartChunk('var1');
                    CDataChunkLoader r1(r.GetPointer().byte, r.GetChunkSize());
                    r1.ReadToBuffer((BYTE*)achieveVars, sizeof(uint32) * More_iMaxAchieveVars );
                    r.EndChunk('var1');
                }
                else 
                {
                    r.SkipChunk();
                }

                for ( int i = 0; i < MAX_ACHIVEVMENT_COUNT; ++i )
                {
                    if (r.IsChunk('xaci'))
                    {
                        r.StartChunk('xaci');
                        xAchievements[i].Read(r.GetPointer().byte,r.GetChunkSize());
                        r.EndChunk('xaci');
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }	
                }

            }
            l.EndChunk('acdt');
        }
        else
            l.SkipChunk();
    }
}


//void SExtendData::RemoveCounter(short nType, short nValue)
//{
//    for (int i = 0; i < MAX_TITLE_COUNT; ++i)
//    {
//        if(counters[i].IsEmpty()) { continue; }
//
//        if (counters[i].GetType() == nType && counters[i].GetValue() == nValue)
//        {
//            counters[i].Clear();
//        }
//        break;
//    }
//}


void SCharPosData::ReadPosData (BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('mpid'))		
        {
            l.StartChunk('mpid');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            dwMapID = r.ReadDword();
            l.EndChunk('mpid');
        }
        else if (l.IsChunk('posx'))
        {
            l.StartChunk('posx');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            stX = r.ReadShort();
            l.EndChunk('posx');
        }
        else if (l.IsChunk('posy'))
        {
            l.StartChunk('posy');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            stY = r.ReadShort();
            l.EndChunk('posy');
        }
        else if (l.IsChunk('d3dx'))
        {
            l.StartChunk('d3dx');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            vPos.x = r.ReadFloat();
            l.EndChunk('d3dx');
        }
        else if (l.IsChunk('d3dy'))
        {
            l.StartChunk('d3dy');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            vPos.y = r.ReadFloat();
            l.EndChunk('d3dy');
        }
        else if (l.IsChunk('d3dz'))
        {
            l.StartChunk('d3dz');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            vPos.z = r.ReadFloat();
            l.EndChunk('d3dz');
        }
        else 
            l.SkipChunk();
    }
}

void SCharOtherDataClient0::ReadOtherDataClient0(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('pos1'))
        {
            l.StartChunk('pos1');
            pos.ReadPosData(l.GetPointer().byte,l.GetChunkSize());
            l.EndChunk('pos1');
        }
        else if (l.IsChunk('bpos'))
        {
            l.StartChunk('bpos');
            sBornPos.ReadPosData(l.GetPointer().byte,l.GetChunkSize());
            l.EndChunk('bpos');
        }
        else 
            l.SkipChunk();
    }	
}

void SShortCut::readShortCut(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('type'))
        {
            l.StartChunk('type');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            BagType = r.ReadInt();
            l.EndChunk('type');
        }
        else if (l.IsChunk('inde'))
        {
            l.StartChunk('inde');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            BagIndex = r.ReadInt();
            l.EndChunk('inde');
        }
        else
            l.SkipChunk();
    }
}

void SHotKey::readMouseItem(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('cut1'))
        {
            l.StartChunk('cut1');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
                ShortCut.readShortCut(r.GetPointer().byte,r.GetBufferSize());
            }
            l.EndChunk('cut1');
        }
        else
            l.SkipChunk();
    }
}

void SMouseItem::readMouseItem(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('item'))
        {
            l.StartChunk('item');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
                ItemData.Read(r.GetPointer().byte,r.GetBufferSize());
            }
            l.EndChunk('item');
        }
        else if (l.IsChunk('cut1'))
        {
            l.StartChunk('cut1');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
                ShortCut.readShortCut(r.GetPointer().byte,r.GetBufferSize());
            }
            l.EndChunk('cut1');
        }
        else
            l.SkipChunk();
    }
}

void SCharHotKeys::readCharHotKeys(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('moi4'))
        {
            l.StartChunk('moi4');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            for (int n = 0; n < More_iHotkey;n++)
            {
                if (r.IsChunk('om01'))
                {
                    r.StartChunk('om01');
                    itemHotKey[n].readMouseItem(r.GetPointer().byte,r.GetChunkSize());
                    r.EndChunk('om01');
                }
                else
                {
                    r.SkipChunk();
                    break;
                }					
            }
            l.EndChunk('moi4');
        }
        else 
            l.SkipChunk();
    }
}

void SCharOtherDataClient::readFightData(ReadData inP,int nsize)
{
    CDataChunkLoader r(inP.byte,nsize);
    stMountId = r.ReadShort();	
    fDirX     = r.ReadFloat();
    fDirY     = r.ReadFloat();
}

void SCharOtherDataClient::readOtherdataClient(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('clt0'))
        {
            l.StartChunk('clt0');
            CDataChunkLoader p(l.GetPointer().byte,l.GetChunkSize());
            SCharOtherDataClient0::ReadOtherDataClient0(p.GetPointer().byte,p.GetBufferSize());
            l.EndChunk('clt0');
        }
        else if (l.IsChunk('skil'))
        {
            l.StartChunk('skil');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            skills.read(r.GetPointer().byte,r.GetBufferSize());
            l.EndChunk('skil');
        }
        else if (l.IsChunk('hkey'))
        {
            l.StartChunk('hkey');
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            hotkeys.readCharHotKeys(r.GetPointer().byte,r.GetBufferSize());
            l.EndChunk('hkey');
        }
        else if (l.IsChunk('fida'))
        {
            l.StartChunk('fida');
            ReadData p(l.GetPointer().c);
            readFightData(p,l.GetChunkSize());
            l.EndChunk('fida');
        }
        else if (l.IsChunk('bbbf'))
        {
            l.StartChunk('bbbf');
            {
                SCharBuff sCharBodyStatusTemp[128];
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                for (int n = 0;n < 128;n++)
                {
                    if (r.IsChunk('by01'))
                    {
                        r.StartChunk('by01');
                        sCharBodyStatusTemp[n].ReadBodyStatus(r.GetPointer().byte,r.GetChunkSize());
                        r.EndChunk('by01');
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }						
                }				
            }
            l.EndChunk('bbbf');
        }
        else if (l.IsChunk('bbb1'))
        {
            l.StartChunk('bbb1');
            {				
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                for (int n = 0;n < BodyStatusType_Max;n++)
                {
                    if (r.IsChunk('by01'))
                    {
                        r.StartChunk('by01');
                        sCharBodyStatus[n].ReadBodyStatus(r.GetPointer().byte,r.GetChunkSize());
                        r.EndChunk('by01');
                    }
                    else
                    {
                        r.SkipChunk();
                        break;
                    }
                }
            }
            l.EndChunk('bbb1');
        }
        else if ( l.IsChunk('rec1'))
        {
            l.StartChunk('rec1');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                r.ReadToBuffer((BYTE*)recipes, sizeof(recipes));
            }
            l.EndChunk('rec1');
        }
        else if ( l.IsChunk('plt1') )
        {
            l.StartChunk('plt1');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                chProtectLockTime = r.ReadByte();
            }
            l.EndChunk('plt1');
        }
        else if ( l.IsChunk('bst1') )
        {
            l.StartChunk('bst1');
            {
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                dwBanSpeakTime = r.ReadDword();
            }
            l.EndChunk('bst1');
        }
        else
            l.SkipChunk();
    }
}

void SSysVars::readVars(ReadData inP,int nSize)
{	
    CDataChunkLoader l(inP.byte,nSize);
    memcpy(&szVars, l.GetPointer().c, min(sizeof(short)*More_iMaxVars, sizeof(szVars)));
    l.GetPointer().byte += sizeof(short)*More_iMaxVars;
}

void SCharBuff::WriteBodyStatus(CDataChunkWriter *w)
{
    w->OpenChunk('bbs3');
    w->WriteShortChunk('stid', StatusID       );
    w->WriteShortChunk('levl', iLevel         );
    w->WriteShortChunk('msid', stMasterID     );
    w->WriteIntChunk  ('efid', nEffectID      );
    w->WriteByteChunk ('blat', bLastEffect    );
    w->WriteDwordChunk('sttm', dwStartTime    );
    w->WriteDwordChunk('pdtm', dwPreDamage    );
    w->WriteDwordChunk('dtt1', dwDurationTime );
    w->WriteIntChunk  ('bret', restoreType    );
    w->WriteDwordChunk('dbid', dwPlayerDBID   );
    w->WriteInt64Chunk('64st', nInt64StartTime);
    w->WriteByteChunk ('bsto', bStop          );
    w->WriteIntChunk  ('evtp', eventType    );
    w->WriteIntChunk  ('evvl', eventValue   );
    w->CloseChunk('bbs3');
}

void SCharBuff::ReadBodyStatus(BYTE* bybuff,DWORD dwsize)
{
    CDataChunkLoader l(bybuff,dwsize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('bbs3'))
        {
            l.OpenChunk();
            while (!l.IsEndOfChunk())
            {
                DWORD dwtime =0;				
                if (l.TryReadShortChunk('stid',StatusID)){}
                else if (l.TryReadShortChunk('levl',iLevel)){}
                else if(l.TryReadShortChunk('msid',stMasterID)){}
                else if(l.TryReadIntChunk('efid',nEffectID)){}
                else if(l.TryReadByteChunk('blat',bLastEffect)){}
                else if(l.TryReadDwordChunk('sttm',dwStartTime)){}
                else if(l.TryReadDwordChunk('pdtm',dwPreDamage)){}
                else if(l.TryReadDwordChunk('dttm',dwtime)){}
                else if(l.TryReadIntChunk('bret',restoreType)){}
                else if(l.TryReadDwordChunk('dtt1',dwDurationTime)){}
                else if(l.TryReadDwordChunk('dbid',dwPlayerDBID)){}
                else if(l.TryReadInt64Chunk('64st',nInt64StartTime)){}
                else if(l.TryReadByteChunk('bsto',bStop)){}     
                else if(l.TryReadByteChunk('evtp',eventType)){}
                else if(l.TryReadWordChunk('evvl',eventValue)){}
                else { l.SkipChunk(); }
            }
        }
        else
        { l.SkipChunk(); }
    }
}

//void	SReputeRank::sv_openrepute(WORD id,WORD level)
//{
//	if (id)
//	{
//		this->flags |= 1<<id;
//	}else{
//		this->flags |= 1;
//	}
//	this->level = 0;
//}
//
//void SReputeRank::sv_setcurrent(WORD id,WORD level)
//{
//	this->current = id;
//	this->level = level;
//}
//
//void SReputeRank::sv_save(DWORD* pdw)
//{
//	::CopyMemory(pdw,this,sizeof(DWORD));
//}
