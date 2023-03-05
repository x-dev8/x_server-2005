/*******************************************************************************
*  Copyright ShenWang 2008 - All Rights Reserved
*
* File: 	MapDef.h
* Date: 	10/06/06
* Desc:		��ͼ���ݺ궨��
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_MAPDEF_H__
#define _MAP_MAPDEF_H__

/*
 * 2012.7.6 wangshuai
 * ������ע��
 */
#define WORLD_FILE_OLD_VERSION				(102)
#define WORLD_FILE_LAST_VERSION				(103)
#define WORLD_FILE_VERSION_104				(104)
#define WORLD_FILE_LASTEST_105				(105)
#define WORLD_FILE_LASTEST_106				(106)
#define WORLD_FILE_LASTEST_107				(107)	// ���ӵƹ�ͼ
#define WORLD_FILE_LASTEST_108				(108)	// ����ÿ��ģ�͵ƹ�ͼ���ݣ��༭����
#define WORLD_FILE_LASTEST_109				(109)	// ���ӵ��Դ����
#define WORLD_FILE_LASTEST_VERSION			(WORLD_FILE_LASTEST_109)
#define WORLD_NAME_LEN						(32)

// �������ű�
#define WORLD_SCALE						( 1 )
// ��ͼ��С
#define WORLD_TILESIZE					( 256.f*WORLD_SCALE )
// ��ͼchunk��С
#define WORLD_CHUNKSIZE					( 16.f*WORLD_SCALE)		// 16
#define WORLD_UNITSIZE					( WORLD_CHUNKSIZE / 8 )		// 	2
#define WORLD_ATOMSIZE					( WORLD_UNITSIZE / 8 )		//	0
#define WORLD_VERTSIZE					( WORLD_UNITSIZE / 2 )		//  1
#define WORLD_CHUNK_ORIGIN				( 4 * (WORLD_UNITSIZE) )
#define WORLD_UNIT_ORIGIN				( 4 * (WORLD_ATOMSIZE) )
#define WORLD_HEIGHT					40000.f
#define TILE_RES	8

#define TILE_RES_1	0.125	//1/8

#define ALPHA_RES	64
#define SHADOW_RES	64

#define MAP_CHUNK_CNT 16
#define ALPHA_PIXEL_PER_TILE (ALPHA_RES/TILE_RES)
#define CHUNK_VERTEX_COUNT ((TILE_RES+1)*(TILE_RES+1))
#define CHUNK_VERTEX_RES	8
#define TILE_METER 4.0f
#define eUnTerrainHeight 0.0f
#define TILE_SIZE 128

// World size. 64*16*8* WORLD_UNITSIZE	= 34133.3312;
// �����а���������ͼ��
#define WORLD_TILE_NUM					(64)

// ��ͼchunk�ĵ�λ
#define WORLD_TILE_CHUNK_UNIT_NUM		(8)
// ��ͼchunk�ĸ�����
#define WORLD_TILE_CHUNK_ATOM_NUM		(64)
#define WORLD_TILE_CHUNK_VERT_NUM		(16)

// used for TWIFTileTable 
#define TILE_NONE						(0)
#define TILE_NORMAL						(1)

// ��Դ������
#define RES_NAME_LEN					(64)
// ��Ч��Դ��ʶ��
#define RES_INVALID_ID					(0xFFFFFFFF)
// ��ͼ����
#define RES_LAYER_NUM					(4)
// �����Դ��
#define RES_MAX_NUM						(8192)
#define MASK_SIZE						(64)

// ��ǰ��ͼ
#define CURRENTTILE (SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile())
// ��ͼԭ��
#define TILEORIGIN(tile,i) (tile->GetOrigin()[i] )
// ��ǰ��ͼԭ��
#define CURRENTTILEORIGIN(i) (TILEORIGIN(CURRENTTILE,i))
// ����ԭ��
#define WORLDORIGIN(i) (0)				

// #define UINT8TOUINT32HIGH(i)  ( ((i)<<24L) + (0<<16L) + (0<<8L) + (0<<0L) )
// #define UINT32HIGHTOUINT8(i)  ((i) >> 24L)
#define UINT8TOUINT32HIGH(i)  (i)
#define UINT32HIGHTOUINT8(i)  (i)

#define CHUNK_VERTEX_NUMBER ((WORLD_TILE_CHUNK_UNIT_NUM+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1) + WORLD_TILE_CHUNK_UNIT_NUM*WORLD_TILE_CHUNK_UNIT_NUM)
#define CHUNK_LOD1T02_FACE_NUMBER (2*2*4 + 4*4)
#define CHUNK_LOD1T02_VERTEX_NUMBER (2*2 + 3*3 + 2*4)
#define CHUNK_LIQUID_VERTEX_NUMBER ((WORLD_TILE_CHUNK_UNIT_NUM+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1))

#endif	// _MAP_MAPDEF_H__