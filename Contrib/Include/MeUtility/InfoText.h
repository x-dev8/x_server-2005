/********************************************************************
	Filename: 	InfoText.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_INFOTEXT_H__
#define __COMMON_INFOTEXT_H__

#include "MeRTLibs.h"

// ��Ϣ�ļ���ȡ��
class CInfoText
{
public:

    // ��ʼ��
    bool Open( const char* szFileName, int iBufSize );
    // �ͷ�
    void Close();

    // ˳���������
    bool NextData( const char *szDst, const char *szDataName );
    bool NextData( int &iDst, const char *szDataName );
	bool NextData( float &fDst, const char* szDataName );
	bool NextKeyword();

    // /	�����ؽ���,���ظ��к�        /
    int FindKeyWord( char *keyword, char *buf );

    // /	�������ñ���                 /
    int FindData( char *DataName, char *buf );

    // �ڶ�����
    int FindDataInPara( char *DataName, char *buf );

    // /	������ñ��� �ַ���ֵ        /
    bool GetDataStr( char *buf, char *outstr );

    // /	������ñ��� ����ֵ          /
    int GetDataInt( char *buf );

	// /	������ñ��� ������			/
	float GetDataFloat ( char *buf );


    // /	��ȡ��Ч��,������ע���кͿ��С� /
    bool ReadAvailableLine( char *buf );
    // /	��õ���                        /
    bool GetWordInString( char *dst, char *str, int n );

    // ��û���ָ��
    char* GetBuffer() { return (char*)m_szBuffer; }
//////////////////////////////////////////////////////////////////////////
    
    CInfoText():
    fp(NULL),
    m_szBuffer(NULL),
    m_iBufferSize(0)
    {}
    virtual ~CInfoText()
    {}

//////////////////////////////////////////////////////////////////////////
    // ��ȡ������Ϣ
    bool ReadLine( char *buf );

protected:

    // �Ƿ�Ϊע����
    bool IsDimLine( char *szLine );
    // �Ƿ�Ϊ����
    bool IsBlankLine( char *szLine );

    // �ҵ�һ���ַ��������ַ�����λ��
    int FindLetter( char *buf, char fc );
    // �ҵ�������
    int FindLeftBracket( char *buf );
    //�ҵ�������
    int FindRightBracket( char *buf );

private:

    FILE *fp;                       //�ļ�ָ��
    unsigned char *m_szBuffer;      //�ļ�������
    int m_iBufferSize;              //��������С

};

#endif // _INFOTEXT_H