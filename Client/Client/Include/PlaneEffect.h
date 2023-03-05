/********************************************************************
	         Created by Zhuomeng.Hu  [11/15/2010]
	            ƽ������֡��Ч��������UI�ؼ�
                ������ԴҪ��:�ȴ���������������

                Example:    1  2  3  4  5  6
                            7  8  9 10 11 12
                           13 14 15
               
               nRowCount   =  3
               nColCount   =  6
               nCount      = 15
               bOrderByRow = true
*********************************************************************/

#pragma once
#include <string>
#include <vector>
#include <windows.h>

class CPlaneEffect
{
public:
    struct SrcRect
    {
        SrcRect()
        {
            pNext = NULL;
            rcSrc.left = 0;
            rcSrc.top = 0;
            rcSrc.right = 0;
            rcSrc.bottom = 0;
        }
        SrcRect*    pNext;
        RECT        rcSrc;
    };

public:
    CPlaneEffect();
    ~CPlaneEffect();

    bool Initialize( const std::string& strPicPath,             // ͼƬ·�� \Data\Ui\֮����"Common\xxx.tga"
                                    int nRowCount,              // ����֡�м���
                                    int nColCount,              // ����֡�м���
                                    int nCount,                 // �ܹ��м���
                            const RECT& rcFirst,                // ��һ������֡����Դ����
                                  DWORD dwTotalTime,            // ������һ��ѭ������ʱ�� (����)
                                   bool bOrderByRow = true,     // �����ṩ������֡�Ƿ�Ϊ��������
                                   bool bReverse = false );     // ����ʱ�Ƿ���

    void Display( const RECT& rcDest );                       // ÿ֡��Ҫ����
	void Restart();

protected:
    const RECT& GetNextSrcRect();

private:
    // �ⲿ���ò���
    std::string             m_strPicPath;               // ͼƬ·��
    DWORD                   m_dwTimePerFrame;           // ������һ��ѭ������ʱ��

    // �ڲ��߼�
    bool                    m_bInited;                  // �Ƿ��Ѿ���ʼ��
    std::vector<SrcRect>    m_rectVec;                  // ��ԴͼƬ�������
    SrcRect*                m_pCurRect;                 // ��ǰ��Դ����
    DWORD                   m_dwLastPicTime;            // �Ϸ�ͼ�Ĳ���ʱ��
};
