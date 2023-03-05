#ifndef __BATTLECONFIG_H__
#define __BATTLECONFIG_H__

#include <string>
#include <vector>

// ս����������Ϣ
class StartInfo
{
public:
    void SetServerID( unsigned char uchValue )  { uchServerID = uchValue; }
    void SetDayOfWeek( unsigned char uchValue ) { uchDayOfWeek = uchValue; }
    void SetStartTime( unsigned char uchValue ) { uchStartTime = uchValue; }


    unsigned char GetServerID() const  { return uchServerID; }
    unsigned char GetDayOfWeek() const { return uchDayOfWeek; }
    unsigned char GetStartTime() const { return uchStartTime; }


private:
    unsigned char uchServerID;          // ��ĳ���������Ͽ���
    unsigned char uchDayOfWeek;         // ÿ�ܼ�����
    unsigned char uchStartTime;         // ��ʼ�ľ���ʱ��
};

class BattleInfo
{
protected:
    typedef std::vector< StartInfo > StartInfoVector;
    typedef StartInfoVector::const_iterator StartInfoVectorConstIter;
public:
    BattleInfo() : uchFightMapID( -1 ), ustWaitMapID( -1 ), uchType( 0 ), uchSignTime( 0 ), ustFightTime( 0 ), strScript( "" ),
        uchUnitCount( 0 ), uchLeastUnit( 0 ), uchEachUnit( 0 ), ustLevel( 0 ), ustBroadCastID( 0 ), uchTurns( 0 ), uchCount( 0 )
    {
        vecStartInfo.clear();
    }

    void SetFightMapID( unsigned short ustValue ) { uchFightMapID = ustValue; }
    void SetWaitMapID( unsigned short ustValue )  { ustWaitMapID = ustValue; }
    void SetType( unsigned char uchValue )        { uchType = uchValue; }
    void SetTurns( unsigned char uchValue )     { uchTurns = uchValue; }
    void SetCount( unsigned char uchValue )     { uchCount = uchValue; }
    void SetSignTime( unsigned char uchValue )    { uchSignTime = uchValue; }
    void SetFightTime( unsigned char ustValue )   { ustFightTime = ustValue; }
    void SetScript( const char* szValue )         { strScript = szValue; }
    void SetUnitCount( unsigned char uchValue )   { uchUnitCount = uchValue; }
    void SetLeastUnit( unsigned char uchValue )   { uchLeastUnit = uchValue; }
    void SetEachUnit( unsigned char uchValue )    { uchEachUnit = uchValue; }
    void SetLevel( unsigned short ustValue )      { ustLevel = ustValue; }
    void SetBroadCast( unsigned short ustValue )  { ustBroadCastID = ustValue; }
    void AddStartInfo( const StartInfo& xInfo )   { vecStartInfo.push_back( xInfo ); }

    unsigned short GetFightMapID() const { return uchFightMapID; }
    unsigned short GetWaitMapID() const { return ustWaitMapID; }
    unsigned char GetType() const { return uchType; }
    unsigned char GetTurns() const     { return uchTurns; }
    unsigned char GetCount() const     { return uchCount; }
    unsigned char GetSignTime() const  { return uchSignTime; }
    unsigned char GetFightTime() const { return uchFightMapID; }
    const char* GetScript() const { return strScript.c_str(); }
    unsigned char GetUnitCount() const { return uchUnitCount; }
    unsigned char GetLeastUnit() const { return uchLeastUnit; }
    unsigned char GetEachUnit() const  { return uchEachUnit; }
    unsigned short GetLevel() const { return ustLevel; }
    const char* GetBroadCastID() const { return ustBroadCastID; }

    unsigned char GetStartInfoCount() { static_cast< unsigned char >( vecStartInfo.size() ); }
    const StartInfo* GetStartInfoByIndex( unsigned char uchIndex ) const
    {
        if ( uchIndex >= GetStartInfoCount() )
        { return NULL; }

        return &( vecStartInfo.at( uchIndex ) );
    }

private:
    unsigned short uchFightMapID;       // ս����ͼ
    unsigned short ustWaitMapID;        // �ȴ���ͼ
    unsigned char uchType;              // ���� 1 : ����, 2 : ���
    unsigned char uchSignTime;          // ��������ʱ��
    unsigned char ustFightTime;         // ս��ʱ��
    std::string strScript;              // �ű�·��
    unsigned char uchUnitCount;         // �����������λ
    unsigned char uchLeastUnit;         // ��������С��λ
    unsigned char uchEachUnit;          // ÿ����λ������
    unsigned short ustLevel;            // ���Ƶȼ�
    unsigned short ustBroadCastID;      // ϵͳ����
    unsigned char uchTurns;             // ÿ���м���ս��
    unsigned char uchCount;             // ÿ��ս����������
    StartInfoVector vecStartInfo;       // ս��������ʱ��
};

#endif