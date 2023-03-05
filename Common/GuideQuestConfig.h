#ifndef __GUIDEQUESTCONFIG_H__
#define __GUIDEQUESTCONFIG_H__

#include <string>
#include <vector>

class GuideQuest
{
public:

    enum EConstDefine
    {
        Guide_Expression = 0,   // ������
        Guide_Team,             // ���
        Guide_Friend,           // �Ӻ���
        Guide_Guild,            // �ӹ���
    };

    int GetType() const { return m_nType; }
    const char* GetScript() const { return m_strScript.c_str(); }
    int GetEnter() const { return m_nEnter; }

    void SetType( int nValue ) { m_nType = nValue; }
    void SetScript( const char* szValue ) { m_strScript = szValue; }
    void SetEnter( int nValue ) { m_nEnter = nValue; }

private:
    int m_nType;              // ָ����������
    std::string m_strScript;  // �������ű�·��
    int m_nEnter;             // �ű�·���ӿ�
};


#define theGuideQuestConfig GuideQuestConfig::Instance()
class GuideQuestConfig
{
public:
    static GuideQuestConfig& Instance()
    {
        static GuideQuestConfig s_xConfig;
        return s_xConfig;
    }

    const GuideQuest* GetGuideQuest( unsigned int nType ) const
    {
        if ( nType >= m_vecGuildQuest.size() )
        { return NULL; }

        return &( m_vecGuildQuest.at( nType ) );
    }

    unsigned int GetGuideQuestCount() const { return static_cast< unsigned int >( m_vecGuildQuest.size() ); }

    bool LoadGuideQuestConfig( const char* szFile );

protected:
    GuideQuestConfig(){}
    
private:
    typedef std::vector< GuideQuest > GuideQuestVector;

    GuideQuestConfig( const GuideQuestConfig& );
    GuideQuestConfig& operator = ( const GuideQuestConfig& );

    GuideQuestVector m_vecGuildQuest;
};

#endif