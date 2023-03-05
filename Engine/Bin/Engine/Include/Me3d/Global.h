#ifndef _3DENGINE_H__
#define _3DENGINE_H__

#include "MeRTLibs.h"
#include "Engine/Renderer.h"
#include <windows.h>
#include "Dxsdk/d3dx9.h"
#include "TileDataMapHeader.h"
//class TextureDx8;
#define FORCE_DWORD 0x7fffffff
//#define DEFINE_MEX_PATH	"Data\\mex\\npc\\cunzhang\\cunzhang.mex2" //commneted out, jiayi, [09.04.07]
// #define DEFINE_MEX_PATH "Data\Character\\npc\\cunzhuang\\cunzhang.mex2" //added, jiayi, [09.04.07]

typedef unsigned __int64	QWORD;		// 64-bit unsigned.

// Texture/shader/font manager
//TextureDx8* GetTexture(short index);
short RegisterFont(LPCTSTR lpszName, DWORD dwHeight, BOOL bBold = FALSE, BOOL bItalic = FALSE);
void UnregisterFont(short index);
BOOL DrawText( short index, int x, int y, DWORD dwColor, LPCTSTR strText );
DWORD GetFontHeight( short index );

// Render
void SetWordMatrix(float * matrix);

extern void GetLowerRelativePath( const char* pszFileName, std::string& strOutFileName );
extern void GetLowerFullPath( const char* pszFileName, std::string& strOutFileName );
extern void SetRootPath( const char* pszPath );
extern const char* GetRootPath();
extern const char* GetFullName(const char* filename);
extern HRESULT LoadAndCreateShader(LPDIRECT3DDEVICE9 m_pD3DDev,
							const std::string& strFilePath, 
							const DWORD* pDeclaration,
							DWORD Usage, 
							BOOL bType, 
							DWORD* pHandle);
extern HRESULT LoadSkinMeshVertexShader( LPDIRECT3DDEVICE9 pd3dDevice, 
								 const char* pszFilename, DWORD* pdwVertexShader );



namespace String_Util
{
	void StripEXT	( char *szFile	);
	void StripPath	( char *name	);
	void StripName	( char *name	);
};

//VOID Lock3DMemory();
//VOID UnLockMemory();
//BOOL IsLock3DMemory();

class CRenderPass
{
public:
	enum
	{
		eMaxLayer = 4,
		eMaxAlpha = 3
	};
public:
	CRenderPass():nTexID(-1),nAplhaTexID(-1),dwVectorStart(0),dwVectorCnt(0),dwIndexStart(0),dwIndexCnt(0),
		m_pVB(NULL),m_pIB( NULL ),dwRenderFlag(0)
	{
	}
public:
	INT	  nTexID;
	INT	  nAplhaTexID;
	DWORD dwRenderFlag;
	DWORD dwVectorStart;
	DWORD dwVectorCnt;

	DWORD dwIndexStart;
	DWORD dwIndexCnt;

	VOID* m_pVB;
	VOID* m_pIB;
};

#define TERRAIN_EXT	"tr2"
#define SCENE_EXT	"sc1"

#define SCENEOBJECT_PATH "Data\\SceneObjs\\"
#define SCENEOBJECT_PATH_BUILDING "Data\\SceneObjs\\Building\\"
#define SCENEOBJECT_PATH_BIOLOGY "Data\\SceneObjs\\Biology\\"
#define SCENEOBJECT_PATH_STONE "Data\\SceneObjs\\Stone\\"
#define SCENEOBJECT_PATH_WALL "Data\\SceneObjs\\Wall\\"
#define SCENEOBJECT_PATH_ACTOR "Data\\SceneObjs\\Actor\\"

#define SCENEOBJECT_PATH_HugeObject "Data\\SceneObjs\\HugeObject\\"
#define SCENEOBJECT_PATH_SingleFloor "Data\\SceneObjs\\SingleFloor\\"

#define SCENEOBJECT_PATH_Tree "Data\\SceneObjs\\Biology\\tree"
#define SCENEOBJECT_PATH_Decorate "Data\\SceneObjs\\Biology"
#define SCENEOBJECT_PATH_Ani "DATA\\SCENEOBJS\\Ani"

#define SCENEOBJECT_PATH_Interface "Data\\SceneObjs\\Interface"

#define SCENEOBJECT_PATH_dynamicFloor "Data\\SceneObjs\\dynamicFloor"



#define WORLD_PACK "Data\\world.vfs"
#define WORLD_PACKEX "Data\\worldex.vfs"

#define WORLD_PACKHead "Data\\world"
#define WORLD_PACKExHead "Data\\worldex"

#define TEXTURE_PACK "Data\\TEXTURES.vfs"
#define TEXTURE_PACKHead "Data\\TEXTURE"

#define SLK_PATH	"..\\Data\\Config\\"

#define SLK_PACK	"Data\\slk.vfs"
#define SLK_PACK_TEMP	"Data\\temp.temp"
#define SLK_PACKHead "Data\\slk"

#define MODEL_PACK	"Data\\Model.vfs"
#define MODEL_PACKHead "Data\\Model"

#define THREAD_LOADMAP_SLEEP Sleep(1);


VOID	InitVFS( BOOL bUseTexGroupMap );
void	SkinMeshParam ( LPDIRECT3DDEVICE9 pd3dDevice, D3DLIGHT9 *lgtSun, class MeCamera *MeCamera, float fAlpha = 1.0f );

#define MAX(a, b) (((a) > (b)) ? (a): (b))

//!!!!!!!!#include "ModelRender\D3dRes.h"

extern std::vector<INT> GSpecularTexGroup;
extern std::vector<INT> GShieldSpecularTexGroup;
extern std::vector<INT> GEquipSpecularTexGroup;

extern DWORD GProcessPriority;// = NORMAL_PRIORITY_CLASS;

// Map文件头
//struct TileDataMapHeader
//{
//	DWORD version;				//地图版本号
//	DWORD size;					//文件大小,可以做为文件是否损坏的标识,暂时不做文件crc的较验,因为没什么必要
//	DWORD rate_R;
//	DWORD rate_M;				//实际坐标对地图坐标的比率	如果是 1:2 的含义代表着实际的坐标1 10*10的场景 用20*20的地图来表示
//	DWORD width;				//地图宽度, 并非坐标
//	DWORD height;				//地图高度, 并非坐标
//};

//union UPointer
//{
//	int*			i;
//	DWORD*			dw;
//	char*			c;
//	void*			p;
//	float*			f;
//	BYTE*			by;
//	UPointer(void* in) :p(in)
//	{
//	}
//};
#endif