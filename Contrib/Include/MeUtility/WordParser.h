/********************************************************************
    Filename:     WordParser.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_WORDPARSER_H__
#define __UTILITY_WORDPARSER_H__

#include "MeRTLibs.h"

class WordParser 
{
    enum EConstDefine
    {
        eMaxWord = 32
    };

    struct OneWord
    {
        OneWord():nStart(0),nLen(0),pszStart(NULL){}

        int   nStart;
        int   nLen;
        char* pszStart;
    };
    
public:
    WordParser();
    ~WordParser();
    static BOOL IsNumber( const char* s );
    static BOOL IsVariable( const char* s );

    int Parse( const char* pszScriptLine );
    //int Parse2( const char* pszScriptLine );
    //int GetWordCount(){ return (int)m_words.size(); }
    int GetWordCount();
    const char* GetWord( int i );

    BOOL IsNumber( int i );
    BOOL Compare( int i, const char* s );
    //void CombineWord1ToEnd( char* pszBuffer, int nBufferSize );
    BOOL CombineWordFromXToEnd( int x, char* pszBuffer, int nBufferSize );
    BOOL CreateFrom( int nStart, WordParser* pSrcWord );

protected:
    //std::vector<std::string> m_words; 
    OneWord m_words2[eMaxWord];
    int     m_nNumWord;
    char*   m_pszString;
    int     m_nLength;
};

#endif // __UTILITY_WORDPARSER_H__
