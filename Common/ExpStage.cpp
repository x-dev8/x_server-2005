#include "ExpStage.h"
#include "Slkreader.h"
#include "FuncPerformanceLog.h"
#include "LevelExperienceConfig.h"

CExpStage theExpStage;

CExpStage::CExpStage() : _charExp("CExpStage._charExp"),_mountExp("CExpStage._mountExp")
                         //m_skillexp("CExpStage.m_skillexp")
{
	_maxCharLevel    = 1;
    _maxMountLevel   = 1;
	//m_iMaxSkillLevel = 1;
}

CExpStage::~CExpStage() 
{
}

bool CExpStage::LoadFromConfig( const char* pszFile )
{
    if( !theLevelExperienceConfig.LoadLevelExperienceConfig(pszFile) )
    { return false; }

    int iLevel = 1;
    _charExp[0].dwTotalExp = 0;
    _charExp[0].dwPerExp   = 0;

    while( iLevel < const_iCharMaxLevel )
    {
        LevelExperienceConfig::LevelExperience* pExp = theLevelExperienceConfig.GetCharacterLevelExperienceByLevel(iLevel);
        if( !pExp )
            break;
        
        _charExp[ iLevel ].dwPerExp = pExp->Experience;                                                // �ȼ�iLevel������Ҫ����
        _charExp[ iLevel ].dwTotalExp = _charExp[ iLevel-1 ].dwTotalExp + _charExp[ iLevel ].dwPerExp; // ��1������iLevel��Ҫ���ܹ�����
        iLevel++;
    }
	_maxCharLevel = iLevel-1;

    iLevel = 1;
    while( iLevel < const_iCharMaxLevel )
    {
        LevelExperienceConfig::LevelExperience* pExp = theLevelExperienceConfig.GetMountLevelExperienceByLevel(iLevel);
        if( !pExp )
            break;
        
        _mountExp[ iLevel ].dwPerExp   = pExp->Experience;                                                // �ȼ�iLevel������Ҫ����
        _mountExp[ iLevel ].dwTotalExp = _mountExp[ iLevel-1 ].dwTotalExp + _mountExp[ iLevel ].dwPerExp; // ��1������iLevel��Ҫ���ܹ�����
        iLevel++;
    }
	_maxMountLevel = iLevel-1;

    iLevel = 1;
    while( iLevel < const_iCharMaxLevel )
    {
        LevelExperienceConfig::LevelExperience* pExp = theLevelExperienceConfig.GetPetLevelExperienceByLevel(iLevel);
        if( !pExp )
            break;

        _petExp[ iLevel ].dwPerExp   = pExp->Experience;                                                // �ȼ�iLevel������Ҫ����
        _petExp[ iLevel ].dwTotalExp = _petExp[ iLevel-1 ].dwTotalExp + _petExp[ iLevel ].dwPerExp;     // ��1������iLevel��Ҫ���ܹ�����
        iLevel++;
    }
    _maxPetLevel = iLevel-1;

	return true;
}

//�õ���������ľ���ֵ
int64 CExpStage::GetLevelupExp( int iLevel )
{
    if( iLevel == 0 )
        return 0;
	if( iLevel <= 0 || iLevel >= const_iCharMaxLevel )
        return 0xffffffff;
    return _charExp[ iLevel ].dwTotalExp; 
}

//�õ���ǰ����ֵ��Ӧ�ĵȼ�
int CExpStage::GetLevel( int64 iCurExp )
{
    int iLevel = 0;
    for(int i=1;i<_maxCharLevel; ++i)
    {
        if( _charExp[i].dwTotalExp > iCurExp )
        {
            iLevel = i;
            break;
        }
    }
    return iLevel;
}

uint32	CExpStage::GetExpDistance( int iLevel )
{
    if( iLevel <= 0 || iLevel >= const_iCharMaxLevel )
        return 0xffffffff;
    return _charExp[iLevel].dwPerExp;
}


//�õ�������������ľ���ֵ
DWORD CExpStage::GetPLevelupExp( int iLevel )
{
	if( iLevel <= 0 || iLevel >= const_iCharMaxLevel )
		return 0xffffffff;
	return _charExp[ iLevel].dwPerExp;
}

int CExpStage::GetMountLevel( int64 iCurExp )
{
    int iLevel = 0;
    for(int i=1;i<_maxMountLevel; ++i)
    {
        if( iCurExp <= _mountExp[i].dwTotalExp )
        {
            iLevel = i;
            break;
        }
    }
    return iLevel;
}

DWORD CExpStage::GetMountExpDistance( int nLevel )
{
	if( nLevel == 0 )
		return 0;
	if( nLevel <= 0 || nLevel >= const_iCharMaxLevel )
		return 0xffffffff;
	return _mountExp[ nLevel ].dwPerExp; 
}
//�õ���������ľ���ֵ
__int64 CExpStage::GetMountLevelupExp( int iLevel )
{
	if( iLevel == 0 )
		return 0;
	if( iLevel <= 0 || iLevel >= const_iCharMaxLevel )
		return 0xffffffff;
	return _mountExp[ iLevel ].dwTotalExp; 
}

int CExpStage::GetPetLevel( int64 iCurExp )
{
    int iLevel = 0;
    for(int i=1;i<_maxPetLevel; ++i)
    {
        if( iCurExp <= _petExp[i].dwTotalExp )
        {
            iLevel = i;
            break;
        }
    }
    return iLevel;
}

DWORD CExpStage::GetPetExpDistance( int nLevel )
{
    if( nLevel == 0 )
        return 0;
    if( nLevel <= 0 || nLevel >= const_iCharMaxLevel )
        return 0xffffffff;
    return _petExp[ nLevel ].dwPerExp; 
}
//�õ���������ľ���ֵ
__int64 CExpStage::GetPetLevelupExp( int iLevel )
{
    if( iLevel == 0 )
        return 0;
    if( iLevel <= 0 || iLevel >= const_iCharMaxLevel )
        return 0xffffffff;
    return _petExp[ iLevel ].dwTotalExp; 
}

//bool CExpStage::LoadSkillExp(char *pszFile)
//{
//	CSlkReader reader;
//	if( !reader.ReadFromFile( pszFile ) )
//		return false;
//	int iLevel = 1;
//	m_skillexp[0].dwSkillExp = 0;
//	m_skillexp[0].dwLevelUpExp = 0;
//	
//	CSlkReader::SField *pField;
//	while( 
//		CSlkReader::ret_succ == reader.GotoNextLine( iLevel+2 )		
//		&& ( iLevel < const_iMaxSkillLevel ) )
//	{
//		pField = reader.GetFieldOfLine( 1 );
//		if( !pField || pField->iFieldType != CSlkReader::field_int )
//		{
//			// ToLog( false );
//			return false;
//		}
//		m_skillexp[ iLevel ].dwLevelUpExp = pField->data.iValue;
//
//		pField = reader.GetFieldOfLine( 2 );
//		if( !pField || pField->iFieldType != CSlkReader::field_int )
//		{
//			// ToLog( false );
//			return false;
//		}
//		m_skillexp[iLevel].dwSkillExp = pField->data.iValue;
//		iLevel ++;
//	}
//	m_iMaxSkillLevel = iLevel-1;
//	return true;
//
//}
////�õ���������ľ���ֵ
//DWORD CExpStage::GetSkillLevelExp( int iLevel )
//{
//	if( iLevel == 0 )
//		return 0;
//	if( iLevel <= 0 || iLevel > const_iMaxSkillLevel )
//		return 0xffffffff;
//	return m_skillexp[ iLevel ].dwSkillExp; 
//}
//
////�õ�������������ľ���ֵ
//DWORD CExpStage::GetSkillLevelUpExp( int iLevel )
//{
//	if( iLevel <= 0 || iLevel > const_iMaxSkillLevel )
//		return 0xffffffff;
//	return m_skillexp[ iLevel].dwLevelUpExp;
//}
//
////�õ���ǰ����ֵ��Ӧ�ĵȼ�
//int CExpStage::GetSkillLevel( int iCurExp )
//{
//	int iResultLevel = 0;
//
//	for( int i=1;i<m_iMaxSkillLevel;i++)
//	{
//		if( iCurExp < m_skillexp[i].dwSkillExp )
//        {
//            iResultLevel = i;
//			break;
//        }
//	}
//	return iResultLevel;
//}
//
////�õ�ָ���ȼ���ǰһ�ȼ������辭��ֵ�Ĳ�
//int	CExpStage::GetSkillExpDistance( int iLevel )
//{
//	if( iLevel <= 0 || iLevel > const_iMaxSkillLevel )
//		return 0xffffffff;
//	return m_skillexp[iLevel].dwLevelUpExp;
//}
//

