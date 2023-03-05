#include "WordParser.h"
#include "FuncPerformanceLog.h"
#include "tstring.h"

using Common::_tstring;
//
WordParser::WordParser():
m_nNumWord(0),
m_pszString(NULL),
m_nLength(0)
{
    guardfunc
    unguard;
}
WordParser::~WordParser()
{
    guardfunc
    if( m_pszString )
    {
        delete[] m_pszString;
        m_pszString = NULL;
    }
    unguard;
}
int    WordParser::GetWordCount()
{
    guardfunc
    return m_nNumWord;
    unguard;
}
const char*    WordParser::GetWord( int i )
{ 
    guardfunc
    //if( i < 0 || i >= m_words.size() )
    //    return "";
    //return m_words[i].c_str(); 
    if( i < 0 || i >= m_nNumWord )
        return "";
    return m_words2[i].pszStart;
    unguard;
}

BOOL WordParser::IsNumber( const char* s )
{
    if( s == 0 )
        return false;
    char* p = (char*)s;
    if( *p == '-' )
        *p++;
    
    if( *p == 0 )
        return false;

    while( *p != 0 )
    {
        if( *p < '0' || *p > '9' )
            return false;
        p++;
    }
    return true; 
}

BOOL IsVariable( const char* s )
{
    if( s == 0 )
        return false;

    char* p = (char*)s;

    if( *p == 0 )
        return false;

    if ( *p == '$')
    {
        return true;
    }
    return false; 
}

BOOL WordParser::IsNumber( int i )
{
    guardfunc
    //if( i < 0 || i >= (int)m_words.size() )
    if( i < 0 || i >= m_nNumWord )
        return FALSE;
    return IsNumber( GetWord( i ) );
    unguard;
}
BOOL WordParser::CombineWordFromXToEnd( int x, char* pszBuffer, int nBufferSize )
{
    guardfunc
    memset( pszBuffer, 0x00, nBufferSize );
    int nSize = 0;
    //for( int i = x; i < m_words.size(); i++ )
    for( int i = x; i < m_nNumWord; i++ )
    {
        //nSize += m_words[i].size();
        nSize += m_words2[i].nLen;
        if ( nSize >= nBufferSize )
        { return FALSE; }

        size_t freesize = nBufferSize - strlen(pszBuffer);
        strncat( pszBuffer, m_words2[i].pszStart, freesize-1 );

        freesize = nBufferSize - strlen(pszBuffer);
        strncat( pszBuffer, " ", freesize-1 );
    }
    return TRUE;
    unguard;
}
//void WordParser::CombineWord1ToEnd( char* pszBuffer, int nBufferSize )
//{
//    memset( pszBuffer, 0x00, nBufferSize );
//    for( int i = 1; i < m_words.size(); i++ )
//        strcat( pszBuffer, m_words[i].c_str() );
//}
BOOL WordParser::CreateFrom( int nStart, WordParser* pSrcWord )
{
    guardfunc
    if( nStart < 0 || nStart >=  pSrcWord->GetWordCount() )
    {
        return FALSE;
    }
    //int nLen = strlen( pSrcWord->m_pszString )
    m_nLength = pSrcWord->m_nLength;
    m_pszString = new char[m_nLength+1];
    memcpy( m_pszString, pSrcWord->m_pszString, m_nLength+1 );
    m_nNumWord = 0;
    for( int i = nStart; i < pSrcWord->GetWordCount() && m_nNumWord < eMaxWord; i++ )
    {
        //m_words.push_back( pSrcWord->GetWord( i ) );
        m_words2[m_nNumWord].nStart = pSrcWord->m_words2[i].nStart;
        m_words2[m_nNumWord].nLen = pSrcWord->m_words2[i].nLen;
        m_words2[m_nNumWord].pszStart = &m_pszString[m_words2[m_nNumWord].nStart];
        m_nNumWord++;
    }
    return TRUE;
    unguard;
}
BOOL WordParser::Compare( int i, const char* s )
{
    guardfunc
    if( s == NULL )
    {
        return FALSE;
    }
    //if( i < 0 || i >= m_words.size() )
    if( i < 0 || i >= m_nNumWord )
    {
        return FALSE;
    }
    return stricmp( GetWord( i ), s ) == 0;
    unguard;
    
}
int WordParser::Parse( const char* pszScriptLine )
{
    guardfunc
    if( !pszScriptLine )
    { return 0; }

    std::wstring strunicode = _tUNICODECHAR(pszScriptLine);
    wchar_t* pszStr = const_cast<wchar_t*>(strunicode.c_str());
    int nLength = wcslen(pszStr);

    for( int i = 0; i < nLength; i++)
    {
        // 由于' '(空格)是关键字,与英文中的语句会冲突.
        // 所以用'^'来替换,在这里要替换回来
        if ( pszStr[i] == L'^' /*&& i < m_nLength-1 && m_pszString[i+1] != (char)-40*/ )
        {
            pszStr[i] = L' ';
        }
    }

    _tstring str = pszStr;

    //static char szBuf[1024];
    m_nLength = (int)str.length();
    //if( nLength == 0 || nLength >= 1024 )
    //{
    //    return 0;
    //}
    m_pszString = new char[m_nLength+1];
    memset(m_pszString, 0, m_nLength+1);

    char* pszTemp;
    pszTemp = new char[m_nLength+1];
    memset(pszTemp, 0, m_nLength+1);

    strncpy_s(pszTemp, m_nLength + 1, pszScriptLine, m_nLength);
    strncpy_s(m_pszString, m_nLength + 1, str.c_str(), m_nLength);

    m_nNumWord = 0;
    //std::vector<char> word;
    for( int i = 0; i < m_nLength; )
    {
        while( (unsigned char)pszTemp[i] <= ' ' )
        {
            i++;
            if( i >= m_nLength )
                break;
        }

        m_words2[m_nNumWord].nStart = i;
        m_words2[m_nNumWord].pszStart = &m_pszString[i];
        while( (unsigned char)pszTemp[i] > ' ' )
        {                
            m_words2[m_nNumWord].nLen++;
            i++;
            if( i >= m_nLength )
                break;
        }

        //if( word.size() > 0 )
        if( m_words2[m_nNumWord].nLen > 0 )
        {
            int nOffset = m_words2[m_nNumWord].nStart+m_words2[m_nNumWord].nLen;
            if (nOffset < 0 || nOffset >= m_nLength+1)
            { continue; }

            pszTemp[nOffset] = 0;
            m_pszString[nOffset] = 0;
            //word.push_back( 0 );
            //m_words.push_back( &word[0] );
            m_nNumWord++;
            if( m_nNumWord >= eMaxWord )
            {
                break;
            }
        }
        //word.clear();
    }
    delete[] pszTemp;
    //return (int)m_words.size();
    return m_nNumWord;
    unguard;
}

//int WordParser::Parse2( const char* pszScriptLine )
//{
//    guardfunc
//    if( !pszScriptLine )
//    {
//        return 0;
//    }
//    static char szBuf[1024];
//    int nLength = (int)strlen( pszScriptLine );
//    if( nLength == 0 || nLength >= 1024 )
//    {
//        return 0;
//    }
//    strncpy(szBuf, pszScriptLine, sizeof(szBuf)-1);
//
//    std::vector<char> word;
//    for( int i = 0; i < nLength; )
//    {
//        while( (unsigned char)szBuf[i] <= ' ' )
//        {
//            i++;
//            if( i >= nLength )
//                break;
//        }
//        
//        while( (unsigned char)szBuf[i] > ' ' )
//        {
//            word.push_back( szBuf[i++] );
//            if( i >= nLength )
//                break;
//        }
//
//        if( word.size() > 0 )
//        {
//            word.push_back( 0 );
//            m_words.push_back( &word[0] );
//        }
//        word.clear();
//    }
//    return (int)m_words.size();
//    unguard;
//}
