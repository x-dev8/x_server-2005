/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldTile.h
* Create: 	10/06/2006
* Desc:		��ͼTile�ṹ����
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_WORLDTILE_H__
#define _MAP_WORLDTILE_H__
#include "MeTerrain/TileQuadTree.h"
#include "SwMap.h"
#include "Me3d\Bsp.h"
class CEditRender;
class CWorldChunk;
class CWorldBuffer;
class CWorldEditDoc;
class CNdlEditWorldPicker;
class CNdlWorldEditor;
class CWorldReadStream;
class CWorldWriteStream;
class TileQuadTree;
class BspTree;
class LightMapTexture;
class LMColorData;
class CHeightMapData;

namespace wrt
{
	DWORD WINAPI	WorldReadThreadFunc(LPVOID lpParam);
}
////////////////////////////////////////////////////////////////////////////////
class CWorldTile 
{
	friend			CEditRender;
	friend class	CResMgr;
	friend class	CWorldEditView;
	friend class	CTextureNavigationWnd;
	friend			CWorldChunk;
	friend			CWorldBuffer;
	friend			CWorldEditDoc;
	friend			CNdlWorldEditor;
	friend			CWorldReadStream;
	friend			CWorldWriteStream;
	friend class	CServerMapStream;
	friend class	CWorldBuffer;
	friend DWORD WINAPI	wrt::WorldReadThreadFunc(LPVOID lpParam);
public:
					CWorldTile(const char* pPath);
					~CWorldTile();

	void			FreeChunckTable();

	bool			Create( CWorldBuffer* worldBuffer,CResMgr* pndlResMgr );		

	CWorldChunk*	GetChunk( sInt32 chunkX, sInt32 chunkY );
	CWorldChunk*	GetChunk( sInt32 index);
	CWorldChunk*	GetChunkFromPos( flt32 posX, flt32 posY );

	bool			CheckChunk( sInt32 chunkX, sInt32 chunkY );

	void			CalcHeight();
	void			UpdateHeightByChunk(int nChunkIndex);
	void			UpdateHeightByChunk(CWorldChunk* pChunk);
	void			CalcNormal();
	
	void			Reset();
	void			OnDeviceLost();
	void			OnDeviceReset( bool bBeforeReset);

	bool			IsLoad() const { return m_isLoad; }
	void			SetLoad(bool val) { m_isLoad = val; }

	void			SetRolePosition(int nRoleX ,int nRoleY){m_nRolePosition[0] = nRoleX; m_nRolePosition[1] = nRoleY;}
	bool			IsRolePositionInitialize() const { return m_nRolePosition[0] != -1; }

	void			RefreshChunkLoadLevel(flt32 fRadius,bool bRefreshPart);

	CResMgr*		GetCResMgr() const { return m_ndlResMgr; }
	flt32			GetWidth() const { return m_rowColumn[0] * WORLD_CHUNKSIZE;}
	flt32			GetDepth() const { return m_rowColumn[1] * WORLD_CHUNKSIZE;}
	sInt32*				GetRowColumn() {return m_rowColumn;}
	sInt32				GetChunkTotal() const { return m_rowColumn[1]*m_rowColumn[0];}
// #ifdef WORLD_EDIT
	sInt32			GetObjectCount();
	void			AttachHelperModel();
	void			DetachHelperModel();
	bool			CalPFWeight();
// #endif	// WORLD_EDIT
	flt32*			GetOrigin()  { return m_origin; }
	flt32*			GetHeight()  { return m_height; }

	char*			GetPathName()  { return m_pathName; }
	flt32			GetReachableAngle() const;
	void			SetReachableAngle(flt32 val);

	sInt32			GetMapId() const { return m_MapId; }
	void			SetMapId(sInt32 val) { m_MapId = val; }

	void			SetRowColumn( sInt32 row, sInt32 column );
	void			SetTileName(const char* val);
	const char*		GetTileName() const { return m_tileName; }

	bool			IsLoadReachableMap() const { return m_bLoadReachableMap; }
	SwMap&			ReachableMap();

	void			CreateFloorAndCollision();//worldedit ����

	bool			LoadMinimap( );
	bool			LoadRegionMap( );
	sInt32			GetMinimapId() const { return m_nMinimapId; }
	sInt32			GetRegionMapId() const { return m_nRegionMapId; }
	void			SetReachablePath(const char* pPath);
	const char*		GetReachablePathName() const { return m_reachablePathName; }
	const char*		GetMonsterPath() const { return m_MonsterPath; }
	void			SetMonsterPath(const char* pPath);
	void			LoadReachableMap(bool isFreeData = true);
 	const char*		GetSkyBoxPath(){return m_skyboxPath;}
	void			SetSkyBoxPath(const char* skyboxPath){ strcpy_s( m_skyboxPath, MAX_PATH, skyboxPath ); }

	int					GetTextureForcedMaxLevel() const { return m_TextureForcedMaxLevel; }
	void				SetTextureForcedMaxLevel(int val) { m_TextureForcedMaxLevel = val; }

	int					GetForcedMaxLOD() const { return m_ForcedMinLOD; }
	void				SetForcedMaxLOD(int val) { m_ForcedMinLOD = val; }

	void				MarkNPCPosOnReachableMap(float x,float y);
	bool				GetPointSoundPlay() const { return m_bPointSoundPlay; }
	void				SetPointSoundPlay(bool val) { m_bPointSoundPlay = val; }
	bool				GetShowFootPrint() const { return m_bShowFootPrint; }
	void				SetShowFootPrint(bool val) { m_bShowFootPrint = val; }
    void				SetTotalHeight(float minZ, float maxZ) { m_TotalHeight[0] = minZ; m_TotalHeight[1] = maxZ; }
    flt32*				GetTotalHeight() { return m_TotalHeight; }

	void				SetMinLevel(int level) { m_nMinLevel = level; }
	int					GetMinLevel() { return m_nMinLevel; }

	int					GetRegionOffsetX() const { return m_nRegionOffsetX; }
	void				SetRegionOffsetX(int val) { m_nRegionOffsetX = val; }
	int					GetRegionOffsetY() const { return m_nRegionOffsetY; }
	void				SetRegionOffsetY(int val) { m_nRegionOffsetY = val; }
	int					GetRegionEdge() const { return m_nRegionEdge; }
	void				SetRegionEdge(int val) { m_nRegionEdge = val; }

	int					GetOrder() const { return m_nOrder; }
	void				SetOrder(int val) { m_nOrder = val; }

	void				SetMapType(int type) { m_nType = type; }
	int					GetMapType() { return m_nType; }

	void				SetRide(bool ride) { m_bRide = ride; }
	bool				GetRide() { return m_bRide; }

	void				SetCanPk(int canpk) { m_bCanPk = canpk; }
	int 			    GetCanPk() { return m_bCanPk; }

	void				SetCanDuel(int canDuel) { m_bduel = canDuel; }
	int 			    GetCanDuel() { return m_bduel; }

	void				SetDuration(int duration) { m_nDuration = duration; }
	int					GetDuration() { return m_nDuration; }

	void				SetCount(int count) { m_nCount = count; }
	int					GetCount() { return m_nCount; }

	void				SetUnitCount(int unitcount) { m_nUnitCount = unitcount; }
	int					GetUnitCount() { return m_nUnitCount; }

	const char*			GetEffectPath() { return m_strEffectPath.c_str(); }
	void				SetEffectPath(std::string val) { m_strEffectPath = val; }

    const char*         GetMapNameColor() { return m_MapNameColor.c_str();}
    void                SetMapNameColor(std::string StrColor){ m_MapNameColor = StrColor;}

    const char*         GetMapTip() { return m_MapTip.c_str();}
    void                SetMapTip(std::string StrTip){ m_MapTip = StrTip;}

    void                SetSystemCreate(bool bSelect){ m_bSystemCreate = bSelect; }
    bool                GetSystemCreate(){ return m_bSystemCreate; }
	bool				IsSunLightRender() const { return m_bSunLightRender; }
	void				SetSunLightRender(bool val) { m_bSunLightRender = val; }
	void				SetBloomScale(float scale){ m_BloomScale = scale; }
	float				GetBloomScale(){ return m_BloomScale; }

	void				SetLuminance(float lum){ m_Luminance = lum; }
	float				GetLuminance(){ return m_Luminance; }
	uint8				GetCountry() const { return m_Country; }
	void				SetCountry(uint8 val) { m_Country = val; }

	void				SetBrightnessOffset( float offset ){ m_fBrightnessOffset = offset; }
	float				GetBrightnessOffset() const{ return m_fBrightnessOffset; }

	void				SetContrastOffset( float fR, float fG, float fB ){ 
		m_fContrastOffsetR = fR;
		m_fContrastOffsetG = fG;
		m_fContrastOffsetB = fB; }
	float				GetContrastOffsetR() const{ return m_fContrastOffsetR; }
	float				GetContrastOffsetG() const{ return m_fContrastOffsetG; }
	float				GetContrastOffsetB() const{ return m_fContrastOffsetB; }

	const std::string&	GetScriptFilePath() const {return m_strScriptFilePath;}
	void				SetScripFilePath( const std::string& strScripFile ){ m_strScriptFilePath = strScripFile; }

	bool				IsGrassDestBlendOne() const { return m_bGrassDestBlendOne; }
	void				SetGrassDestBlendOne(bool val) { m_bGrassDestBlendOne = val; }
public:
	TileQuadTree	m_tileQuadTree;	// �Ĳ�����¼����chunk��ˮ���ģ�ͣ����ڿ��Ӽ���

	bool IsModify() const { return m_isModify; }
	void SetModify(bool val) { m_isModify = val; }

	// ��̬ģ�͵ƹ�ͼ
	int					GetLightMapNum() { return m_vecLightMaps.size(); }	// ��ȡ�ƹ�ͼʵ������
	void				LoadLightMap( int nlightmap );							// ����ģ�͵ƹ�ͼ
	void				ClearLightMaps();
	std::vector<LightMapTexture*>& GetLightMaps() { return m_vecLightMaps; }
	LightMapTexture*	GetLightMap( int index ) 
	{
		if( index < m_vecLightMaps.size() )
			return m_vecLightMaps[index];
		return NULL;
	}

	void				RefreshLightmapTexId();

	/// ��ȡ����Ϊ��λ�ĸ߶�ͼ��Ϣ��
	void				LoadHeightMapData();
	CHeightMapData* GetHeightMapData() const { return m_pHeightMapData; }

protected:
	CWorldBuffer*	m_worldBuffer;

	char			m_pathName[MAX_PATH];
	char			m_tileName[64];
	bool			m_isLoad;
//#ifdef WORLD_EDIT
	bool			m_isModify;
	// #endif	// WORLD_EDIT
	flt32			m_origin[2];

	int32			m_nRolePosition[2];
	sInt32			m_rowColumn[2];

	flt32			m_height[2];	// m_height[0]=minHeight, m_height[1]=maxHeight
    flt32           m_TotalHeight[2];   // �����ر�ģ�ͣ���ˮ��������СZֵ
	CWorldChunk**	m_chunckTable;
	char*			m_cNewChunkLoadLevel;
	
	CResMgr*	    m_ndlResMgr;

	flt32			m_reachableAngle;


	SwMap			m_reachableMap;			
	bool				m_bLoadReachableMap;							// ��ȡ�ɵ����ͼ�Ƿ�ɹ���־
protected:
	sInt32			m_MapId;

	sInt32			m_nMinimapId;
	sInt32			m_nRegionMapId;
	char			m_reachablePathName[MAX_PATH];
	char			m_MonsterPath[MAX_PATH];
	// add, jiayi, [2009.4.14],skybox
	char			m_skyboxPath[MAX_PATH];

	int					m_TextureForcedMaxLevel;
	int					m_ForcedMinLOD;

	//add lxb [2009-8-1]
	int m_nType;			//��ͼ����
	int m_nMinLevel;		//��ҽ������С�ȼ�
	int m_nOrder;			//��ͼ������
	int m_bCanPk;			//����PK
	int m_bduel;			//�����д�
	int m_nDuration;		//�����ĳ���ʱ��
	int m_nCount;			//����������������
	int m_nUnitCount;		//�����������λ����
	std::string    m_strEffectPath;    //��Ч��·��
	int m_nRegionOffsetX;		//�����ͼ���������ͼxƫ���λ����
	int m_nRegionOffsetY;		//�����ͼ���������ͼyƫ���λ����
	int m_nRegionEdge;			//�����ͼ�߳�����λ����
	std::string m_strScriptFilePath;//�ű�·��
    std::string m_MapNameColor; //
    std::string m_MapTip;       //
	float m_BloomScale;													//Bloom���� ģ������
	float m_Luminance;													//Bloom���� ����ǿ��
	
	// ռ��1�ֽڱ�����һ�𣬽�ʡ�ڴ�
	bool		m_bPointSoundPlay;
	bool		m_bShowFootPrint;
	bool		m_bRide;			//�ܷ����
	bool		m_bSystemCreate;
	bool		m_bSunLightRender;
	uint8		m_Country;
	bool		m_bGrassDestBlendOne;

	//  [11/18/2010 zhangjiayi]
	float m_fBrightnessOffset;		// ����ƫ��
	float m_fContrastOffsetR;		// �Աȶ�Rƫ��
	float m_fContrastOffsetG;		// �Աȶ�Gƫ��
	float m_fContrastOffsetB;		// �Աȶ�Bƫ��


	// ��̬ģ�͵ƹ�ͼ
	std::vector<LightMapTexture*> m_vecLightMaps;
	// ÿ��ģ�͵ƹ�ͼ��ɫ����
	sInt32		m_nLMColorDataLastNo;	// m_mapLMColorData��Key��ǰ�����ֵ
	std::map<sInt32, LMColorData*> m_mapLMColorData;

	// ���ӵĸ߶���Ϣ��
	CHeightMapData* m_pHeightMapData;
};

#endif	// _MAP_WORLDTILE_H__

