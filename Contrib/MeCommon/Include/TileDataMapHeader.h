/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	TileDataMapHeader.h
* Create: 	10/27/07
* Desc:		mapͷ�ļ�
* Author:	yanli
*******************************************************************************/
#ifndef __COMMON_TILEDATAMAPHEADER_H__
#define __COMMON_TILEDATAMAPHEADER_H__

// Map�ļ�ͷ
struct TileDataMapHeader
{
	unsigned long version;				//��ͼ�汾��
	unsigned long size;					//�ļ���С,������Ϊ�ļ��Ƿ��𻵵ı�ʶ,��ʱ�����ļ�crc�Ľ���,��Ϊûʲô��Ҫ
	unsigned long rate_R;
	unsigned long rate_M;				//ʵ������Ե�ͼ����ı���	����� 1:2 �ĺ��������ʵ�ʵ�����1 10*10�ĳ��� ��20*20�ĵ�ͼ����ʾ
	unsigned long width;			//��ͼ���, ��������
	unsigned long height;				//��ͼ�߶�, ��������
};

struct TileHeightMapHeader : public TileDataMapHeader
{
	float minHeight;				//��ͼ�߶���Сֵ  yanli
	float maxHeight;				//��ͼ�߶����ֵ yanli
};

#endif