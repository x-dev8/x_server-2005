#include "Me3d/Me3d.h"
#include "Me3d/Global.h"
#include "Me3d/Vector.h"
#include "Me3d/Config.h"
#include "FilePath.h"
#include "funcperformancelog.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Tga.h"
//#include "SystemConfig.h"
// #include "VirtualFileSystem/vfs.h"
#include "Dxsdk/D3D9.h"
#include "Dxsdk/d3dx9.h"
#include "Me3d/D3dutil.h"
#include "MeUtility/tstring.h"

int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;

FLOAT g_fMipMap = 0.0f;
BOOL  g_bLock3DMemory = FALSE;
DWORD GProcessPriority = NORMAL_PRIORITY_CLASS;

std::vector<INT> GSpecularTexGroup;
std::vector<INT> GShieldSpecularTexGroup;
std::vector<INT> GEquipSpecularTexGroup;
void PushSurface(const LPDIRECT3DTEXTURE9 pTexture, short nAddMapID, short nShaderID,// 贴图/Shader
				 DWORD dwFvf,UINT nStride, BYTE * pVertices, WORD nVertCount,	// 顶点信息
				 BYTE * pIndeices, WORD nTriangleCount, DWORD dwFlag = 0,
				 DWORD dwPolyType = D3DPT_TRIANGLELIST, INT   nIBOffset = 0 );	

static char gs_szRootPath[MAX_PATH] = {0};

// 获取小写的资源相对路径
void GetLowerRelativePath( const char* pszFileName, std::string& strOutFileName )
{
    if( !pszFileName )
    {
        return;
    }

	std::string strInFileName = pszFileName;
	std::string strRootPath = GetRootPath();

    // 由于繁体中文的问题，转为小写需要先转成 wstring
    std::wstring wstrTmp = Common::_tstring::toWideString( strInFileName.c_str() );
    std::transform( wstrTmp.begin(), wstrTmp.end(), wstrTmp.begin(), towlower );
    strInFileName = Common::_tstring::toNarrowString( wstrTmp.c_str() );
    
    wstrTmp = Common::_tstring::toWideString( strRootPath.c_str() );
    std::transform( wstrTmp.begin(), wstrTmp.end(), wstrTmp.begin(), towlower );
    strRootPath = Common::_tstring::toNarrowString( wstrTmp.c_str() );

	// 从文件路径里面把根路径去除
	int nOffset = strInFileName.find( strRootPath.c_str(), 0 );

	// 如果找到了，传入的就是全路径，返回相对路径
    std::string strRelative;
    if( nOffset != std::string::npos )
	{
        int nRelativeBegin = nOffset + strRootPath.size();
		strRelative = strInFileName.substr( nRelativeBegin );
        
        // 去掉斜杠
        while( strRelative.size() > 0 && ( strRelative[0] == '/' || strRelative[0] == '\\' ) )
        {
            strRelative = strRelative.substr( 1 );
        }
	}
	else
	{
        strRelative = strInFileName;
    }

    // UI的资源传进来的可能是Ui开头的
    if( strRelative.find( "ui/", 0 ) == 0 || strRelative.find( "ui\\", 0 ) == 0 )
    {
        strOutFileName = std::string( "data\\" ) + strRelative;
    }
    else
    {
        strOutFileName = strRelative;
    }
}

// 获取小写的资源全路径
void GetLowerFullPath( const char* pszFileName, std::string& strOutFileName )
{
    if( !pszFileName )
    {
        return;
    }

    std::string strRelative;
    GetLowerRelativePath( pszFileName, strRelative );

    std::string strRootPath = GetRootPath();
    std::wstring wstrTmp = Common::_tstring::toWideString( strRootPath.c_str() );
    std::transform( wstrTmp.begin(), wstrTmp.end(), wstrTmp.begin(), towlower );
    strRootPath = Common::_tstring::toNarrowString( wstrTmp.c_str() );

	if (!strRootPath.empty())
	{
		strOutFileName = strRootPath;
		strOutFileName.append( "\\" );
	}
    strOutFileName.append( strRelative.c_str() );
}

void SetRootPath( const char* pszPath )
{
	guardfunc;
	strcpy( gs_szRootPath, pszPath );
	unguard;
}
const char* GetRootPath()
{
	guardfunc;
	return gs_szRootPath;
	unguard;
}

HRESULT LoadAndCreateShader(LPDIRECT3DDEVICE9 m_pD3DDev,
							const std::string& strFilePath, 
							const DWORD* pDeclaration,
							DWORD Usage, 
							BOOL bType, 
							DWORD* pHandle)
{
	guardfunc;
	assert(m_pD3DDev);
	std::string m_strLastError;
	try	
	{
		HANDLE hFile;
		HRESULT hr;

		hFile = CreateFile(strFilePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE) 
		{
			m_strLastError = "Could not find file " + strFilePath;
			return E_FAIL;
		}

		DWORD dwFileSize = GetFileSize(hFile, NULL);

		const DWORD* pShader = (DWORD*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwFileSize);
		if (!pShader) 
		{
			m_strLastError = "Failed to allocate memory to load shader " + strFilePath;
			return E_FAIL;
		}

		ReadFile(hFile, (void*)pShader, dwFileSize, &dwFileSize, NULL);

		CloseHandle(hFile);

		if(bType) 
		{
			//virtual HRESULT STDMETHODCALLTYPE
			//	CreateVertexShader (
			//	THIS_ CONST DWORD* pFunction,
			//	IDirect3DVertexShader9** ppShader
			//	) PURE
			hr = S_FALSE;
			//hr = m_pD3DDev->CreateVertexShader(pDeclaration, pShader, pHandle, Usage);
		} 
		else 
		{

		}

		HeapFree(GetProcessHeap(), 0, (void*)pShader);

		if (FAILED(hr))	
		{
			m_strLastError = "Failed to create shader " + strFilePath + '\n'; 
			return E_FAIL;
		}
	} 
	catch(...) 
	{
		m_strLastError = "Error opening file " + strFilePath;
		return E_FAIL;
	}

	return S_OK;
	unguard;
};


HRESULT LoadSkinMeshVertexShader( LPDIRECT3DDEVICE9 pd3dDevice, 
								 const char* pszFilename, DWORD* pdwVertexShader )
{
	guardfunc;
	//std::vector<DWORD>  decl;
	//decl.push_back(D3DVSD_STREAM(0));
	//decl.push_back(D3DVSD_REG(0, D3DVSDT_FLOAT3));
	//decl.push_back(D3DVSD_REG(1, D3DVSDT_FLOAT3)); //normal
	//decl.push_back(D3DVSD_REG(2, D3DVSDT_FLOAT2)); //texcoord
	//decl.push_back(D3DVSD_REG(3, D3DVSDT_FLOAT1)); //1 blend weight
	//decl.push_back(D3DVSD_REG(4, D3DVSDT_FLOAT1)); //2 blend weight
	//decl.push_back(D3DVSD_REG(5, D3DVSDT_FLOAT1)); //3 blend weight
	//decl.push_back(D3DVSD_REG(6, D3DVSDT_FLOAT1)); //4 blend weight
	//decl.push_back(D3DVSD_REG(7, D3DVSDT_FLOAT4)); //index 1,2,3,4
	////decl.push_back(D3DVSD_REG(8, D3DVSDT_D3DCOLOR)); //index 1 and 2)
	//decl.push_back(D3DVSD_END());

	////const D3DVERTEXELEMENT9 SHADOWVERT::Decl[3] =
	////{
	////	{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	////	{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
	////	D3DDECL_END()
	////};

	//// DWORD FvF = ;

	//HRESULT hr = LoadAndCreateShader(
	//	pd3dDevice,
	//	//"data\\shader\\PaletteSkin.vso", 
	//	pszFilename,
	//	&decl[0], 
	//	0, 
	//	TRUE, 
	//	pdwVertexShader );

	//if( FAILED(hr) )
	//{
	//	//assert( false && "load e:\\PaletteSkin.vso failed" );
	//	return hr;
	//}

	//D3DXVECTOR4 constNums(0.0f, 0.5f, 1.0f, 0.2f);
	//pd3dDevice->SetVertexShaderConstant(CV_CONSTANTS, &constNums, 1);
	HRESULT hr = S_FALSE;
	return hr;
	unguard;
}

//char g_szUCDataPath[256];

char* GetFileName( const char* pszPath )
{
	guardfunc;
	static char szBuf[256];
	int nLength = strlen( pszPath );
	for( int pos = nLength; pos >= 0; pos-- )
	{
		if( pszPath[pos] == '\\' )
		{
			strcpy( szBuf, &pszPath[pos+1] );
			return szBuf;
		}
	}
	return 0;
	unguard;
}

//void PushSurface(short nMainMapID, short nAddMapID, short nShaderID,			// 贴图/Shader
//				 DWORD dwFvf,UINT nStride, BYTE * pVertices, WORD nVertCount,	// 顶点信息
//				 BYTE * pIndeices, WORD nTriangleCount, DWORD dwFlag,
//				 DWORD dwPolyType, INT   nIBOffset )
//{
//	//guardfunc;
//	//TRUETIMEFUNC();
//
//}
//
////----------------------------- PushSurface -----------------------------    at [8/14/2003]
//void PushSurface(const LPDIRECT3DTEXTURE9 pTexture, 
//				 short nAddMapID, 
//				 short nShaderID,			// 贴图/Shader
//				 DWORD dwFvf,
//				 UINT nStride, 
//				 BYTE * pVertices, 
//				 WORD nVertCount,	// 顶点信息
//				 BYTE * pIndeices, 
//				 WORD nTriangleCount, 
//				 DWORD dwFlag,
//				 DWORD dwPolyType,
//				 INT   nIBOffset )
//{
//	guardfunc;
//	TRUETIMEFUNC();
//	//return;
//
//	unguard;
//}

void SetWordMatrix(float * matrix)
{
	guardfunc;
	//D3DXPLANE plane;
	//D3DXPlaneFromPointNormal( &plane, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,0,0) );
	//D3DXMATRIX matWorld, matReflect;
	//D3DXMatrixReflect( &matReflect, &plane );

	//if( matrix == 0 )
	//{
	//	D3DXMATRIX matWorld;
	//	D3DXMatrixIdentity( &matWorld );
	//	//D3DXMatrixMultiply( &matWorld, &matReflect, &matWorld );
	//	g_pMe3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	//}
	//else
	//{

	//	//D3DXMatrixMultiply( &matWorld, &matReflect, (D3DXMATRIX*)matrix );
	//	g_pMe3dDevice->SetTransform( D3DTS_WORLD, (D3DXMATRIX*)matrix );
	//	//g_pMe3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	//}
	//g_pMe3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	unguard;
}


long SaveBmpFile(char *filename,long sx,long sy,long xl,long yl,BYTE *bitmap)
{
	guardfunc;
	int   i,j;
	long offset;
	long img_xl,img_yl;
	BITMAPFILEHEADER bmpfilehdr;
	BITMAPINFOHEADER bmpinfohdr;
	FILE  *fp;
	BYTE  *line_buffer;


	img_xl=xl-sx;
	img_yl=yl-sy;
	bmpfilehdr.bfType=0x4D42; //"BM"
	bmpfilehdr.bfSize=img_xl*img_yl*3+sizeof(bmpfilehdr)+sizeof(bmpinfohdr);
	bmpfilehdr.bfReserved1=0;
	bmpfilehdr.bfReserved2=0;
	bmpfilehdr.bfOffBits=0x36;


	bmpinfohdr.biSize=sizeof(BITMAPINFOHEADER);
	bmpinfohdr.biWidth=img_xl;
	bmpinfohdr.biHeight=img_yl;
	bmpinfohdr.biPlanes=1;
	bmpinfohdr.biBitCount=24;
	bmpinfohdr.biCompression=0;
	bmpinfohdr.biSizeImage=img_xl*img_yl*3;
	bmpinfohdr.biXPelsPerMeter=0x0B12;
	bmpinfohdr.biYPelsPerMeter=0x0B12;
	bmpinfohdr.biClrUsed=0;
	bmpinfohdr.biClrImportant=0;

	line_buffer=MeDefaultNew BYTE[img_xl*3+10];
	if(line_buffer==NULL)
		return false;

	fp=fopen((char *)filename,"wb");
	if(fp==NULL)
	{
		return false;
	}
	fwrite(&bmpfilehdr,sizeof(bmpfilehdr),1,fp);
	fwrite(&bmpinfohdr,sizeof(bmpinfohdr),1,fp);


	for(i=yl-1;i>=sy;i--)
	{
		offset=i*xl+sx;
		for(j=0;j<img_xl;j++)
		{

			line_buffer[j*3+2]=bitmap[(offset+j)*3];
			line_buffer[j*3+1]=bitmap[(offset+j)*3+1];
			line_buffer[j*3]=bitmap[(offset+j)*3+2];

		}
		fwrite(line_buffer,3,img_xl,fp);
	}

	fclose(fp);
	if(line_buffer!=NULL)
		delete line_buffer;

	return true;
	unguard;
}
static  void    _hi2rgb_0565(WORD iColor,BYTE *r,BYTE *g,BYTE *b)
{
	guardfunc;
	*r = (BYTE )( ( iColor & 0xF800 ) >> 11 << 3 );
	*g = (BYTE )( ( iColor & 0X7e0 ) >> 5 << 2 );
	*b = (BYTE )( ( iColor & 0x1F ) << 3 );
	unguard;
}

static void		_hi2rgb_r8g8b8( WORD *pColor,BYTE *r,BYTE *g,BYTE *b)
{
	guardfunc;
	*r = (BYTE )pColor[1] & 0x00ff;
	*g = (pColor[0] & 0xff00) >> 8;
	*b = (BYTE )pColor[0] & 0x00ff;
	unguard;
}

static void		_hi2rgb_a8r8g8b8( WORD *pColor,BYTE *r,BYTE *g,BYTE *b)
{
	guardfunc;
	*r = (BYTE )pColor[1] & 0x00ff;
	*g = (pColor[0] & 0xff00)  >> 8;
	*b = (BYTE )pColor[0] & 0x00ff;
	unguard;
}

static void		_hi2argb_a8r8g8b8( DWORD *pColor,BYTE *a, BYTE *r,BYTE *g,BYTE *b)
{
	guardfunc;
//	DWORD color = Color[c];
	*a = (*pColor&0xff000000)>>24;
	*r = (*pColor&0x00ff0000)>>16;
	*g = (*pColor&0x0000ff00)>>8;
	*b = (*pColor&0x000000ff)>>0;
	unguard;
}
void SaveSurfaceAsBmp(	LPDIRECT3DDEVICE9 pd3dDevice, 
					  LPDIRECT3DSURFACE9 pBackBuffer,
					  char* pszFilename, BYTE* pBuffer )
{
	guardfunc;
	//D3DSURFACE_DESC desc;
	//memset( &desc, 0x00, sizeof( desc ) );
	//pBackBuffer->GetDesc( &desc );
	//LPDIRECT3DSURFACE8 surface;
	//if( pd3dDevice->CreateImageSurface(	desc.Width, 
	//	desc.Height, 
	//	desc.Format, 
	//	&surface ) == D3D_OK )
	//{
	//	if( pd3dDevice->CopyRects(	pBackBuffer, 
	//		NULL, 
	//		0, 
	//		surface, 
	//		NULL ) == D3D_OK )
	//	{
	//		D3DLOCKED_RECT rcLocked;
	//		if( surface->LockRect( &rcLocked, NULL, D3DLOCK_READONLY  ) == D3D_OK )
	//		{
	//			BYTE* buffer = MeDefaultNew BYTE[desc.Width*desc.Height*3];
	//			//static BYTE buffer[1600*1200*3];
	//			BYTE*	dst = buffer;
	//			WORD*	src = (WORD*)rcLocked.pBits;
	//			WORD*	srcData;

	//			for( int y = 0; y < desc.Height; y++ )
	//			{
	//				srcData = src;
	//				for( int x = 0; x < desc.Width; x++ )
	//				{
	//					/*BYTE b = src[x*4+0];
	//					BYTE g = src[x*4+1];
	//					BYTE r = src[x*4+2];*/

	//					BYTE r, g, b;
	//					switch( desc.Format )
	//					{
	//					case D3DFMT_R5G6B5:
	//						_hi2rgb_0565( *srcData, &r, &g, &b );							
	//						srcData ++;
	//						break;
	//					case D3DFMT_R8G8B8:
	//						_hi2rgb_r8g8b8( srcData,&r, &g, &b );
	//						srcData = (WORD*)((char*)srcData + 3);
	//						break;
	//					case D3DFMT_A8R8G8B8:
	//					case D3DFMT_X8R8G8B8:
	//						_hi2rgb_a8r8g8b8( srcData,&r, &g, &b );
	//						srcData = (WORD*)((char*)srcData + 4);
	//						break;
	//					default:
	//						r = 255;
	//						g = 255;
	//						b = 255;
	//						break;
	//					}

	//					*dst++ = r;
	//					*dst++ = g;
	//					*dst++ = b;
	//					
	//				}
	//				src += rcLocked.Pitch/sizeof(WORD);
	//			}

	//			{
	//				if( pBuffer )
	//					memcpy( pBuffer, buffer, desc.Width*desc.Height*3*sizeof(BYTE) );
	//				SaveBmpFile( pszFilename, 0, 0, desc.Width, desc.Height, buffer );
	//			}

	//			delete buffer;
	//		}			
	//		/*if( surface->LockRect( &rcLocked, NULL, D3DLOCK_READONLY  ) == D3D_OK )
	//		{
	//		BYTE* buffer = MeDefaultNew BYTE[desc.Width*desc.Height*3];
	//		//static BYTE buffer[1600*1200*3];
	//		BYTE*	dst = buffer;
	//		BYTE*	src = (BYTE*)rcLocked.pBits;

	//		for( int y = 0; y < desc.Height; y++ )
	//		{
	//		for( int x = 0; x < desc.Width; x++ )
	//		{
	//		BYTE b = src[x*4+0];
	//		BYTE g = src[x*4+1];
	//		BYTE r = src[x*4+2];
	//		*dst++ = r;
	//		*dst++ = g;
	//		*dst++ = b;
	//		}
	//		src += rcLocked.Pitch;
	//		}
	//		SaveBmpFile( pszFilename, 0, 0, desc.Width, desc.Height, buffer );
	//		delete buffer;
	//		}*/
	//		surface->UnlockRect();
	//	}
	//	surface->Release();
	//}


	unguard;
}


namespace String_Util
{
	void StripEXT(char *name)
	{
		guardfunc;
		for(int i=strlen(name)-1; i>=0; i--)
		{
			if(name[i]=='.')
			{
				name[i]=NULL;
				return;
			}
		}
		unguard;
	}

	void StripPath(char *name)
	{
		guardfunc;
		char r_name[256] = {0};

		int i = 0;
		for(i=strlen(name)-1; i>=0; i--)
		{
			if(name[i]=='\\')
			{
				break;
			}
		}
		int st=i+1;
		for( i=st; i<(int)strlen(name); i++)
		{
			r_name[i-st]=name[i];
		}
		r_name[i-st]=NULL;
		strcpy(name,r_name);
		unguard;
	}

	void StripName(char *name)
	{
		guardfunc;
		int i = 0;
		for(i=strlen(name)-1; i>=0; i--)
		{
			if(name[i]=='\\')
			{
				break;
			}
		}
		if( i==0 )
			return;
		name[i+1]=NULL;
		unguard;
	}
}

//FileIO::CVFS	g_WorldVfs;
// extern FileIO::CVFS	g_SlkVFS;
//FileIO::CVFS	g_ModelVfs;
//FileIO::CVFS	g_TextureVFS;

/////////////////////////////////////////////////////
//unsigned char* GetVfs()
//{
//	struct _stat st;
//	if( ::_stat( SLK_PACK, &st ) != -1 )
//	{
//		unsigned char* globalbuffer = MeDefaultNew unsigned char[st.st_size];
//		FILE* fp = fopen(SLK_PACK,"rb");
//
//		fread(globalbuffer,sizeof(unsigned char),st.st_size,fp);
//
//		fclose(fp);
//		return globalbuffer;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//bool SaveVfsTemp(unsigned char vfs[],unsigned long vfslength)
//{
//	FILE* fp = fopen(SLK_PACK_TEMP,"wb");
//	fwrite(vfs,sizeof(unsigned char),vfslength,fp);
//	fclose(fp);
//	return true;
//}
//
//BOOL DeCodeVfsFile()
//{
//	Cipher::DecoderInterface* decoder = NULL;	
//	if ( NULL == ( decoder = Cipher::CipherFactory::Instance().CreateDecoder( Cipher::CIPHERTYPE_BLOWFISH ) ) )
//	{
//		return FALSE;
//	}
//
//	struct _stat st;
//	_stat(SLK_PACK,&st);
//	const unsigned char* text = GetVfs();
//	if (text == 0)
//	{
//		return FALSE;
//	}
//
//	std::vector<unsigned char> input;
//
//	for (int loop = 0;loop < st.st_size;loop++)
//	{
//		input.push_back(text[loop]);
//	}
//	input.resize( decoder->GetOutputLength( (unsigned long)input.size() ) );
//
//	std::vector<unsigned char> output( decoder->GetOutputLength( (unsigned long)input.size() ) );
//
//	try
//	{
//		unsigned long outputLength = decoder->Decode( (unsigned char*)&output[0], (unsigned char*)&input[0], (unsigned long)input.size() );
//
//		SaveVfsTemp((unsigned char*)&output[0],outputLength);
//
//	}
//	catch( Cipher::DecodeException& reason )
//	{
//		std::cout << "decode exception and problem is " << reason.what() << std::endl;
//		return FALSE;
//	}
//
//	Cipher::CipherFactory::Instance().ReleaseDecoder( &decoder );
//
//	return true;
//}
//////////////////////////////////////////////////////////////////////////////////////////////

VOID	InitVFS( BOOL bUseTexGroupMap )
{
	guardfunc;

	//Init World Map
// 	if( !g_WorldVfs.IsOpen() )
// 	{
// 	//	if( bUseTexGroupMap )
// 		{
// 			SetFileAttributes( WORLD_PACK, FILE_ATTRIBUTE_NORMAL );
// 			g_WorldVfs.LoadVFS( WORLD_PACK );
// 			int nCnt = GetSystemConfig()->GetPackCnt( CSystemConfig::eWorldPack );
// 			for( int i=0; i<nCnt; i++ )
// 			{
// 				char szBuffer[MAX_PATH] = {0};
// 				sprintf( szBuffer, "%s%d.vfs", WORLD_PACKHead, i );
// 				SetFileAttributes( szBuffer, FILE_ATTRIBUTE_NORMAL );
// 				g_WorldVfs.AppendVFS( szBuffer );
// 			}
// 		}
// 		//else
// 		//{
// 		//	SetFileAttributes( WORLD_PACKEX, FILE_ATTRIBUTE_NORMAL );
// 		//	g_WorldVfs.LoadVFS( WORLD_PACKEX );
// 		//	int nCnt = GetSystemConfig()->GetPackCnt( CSystemConfig::eWorldPack );
// 		//	for( int i=0; i<nCnt; i++ )
// 		//	{
// 		//		char szBuffer[MAX_PATH] = {0};
// 		//		sprintf( szBuffer, "%s%d.vfs", WORLD_PACKExHead, i );
// 		//		SetFileAttributes( szBuffer, FILE_ATTRIBUTE_NORMAL );
// 		//		g_WorldVfs.AppendVFS( szBuffer );
// 		//	}
// 		//}
// 
// 	}
// 
// 	/////////////////////////////////////////////////////////////////////
// 	if( !g_SlkVFS.IsOpen() )
// 	{
// 		/*if (DeCodeVfsFile())*/
// 		{
// 			SetFileAttributes( SLK_PACK, FILE_ATTRIBUTE_NORMAL );
// 			g_SlkVFS.SetPassword( "evbgp_gdgk" ); //.SetPassWorld("");
// 			//g_SlkVFS.se
// 			if( g_SlkVFS.LoadVFS( SLK_PACK ) )
// 			{	
// 				//return true;
// 				int nCnt = GetSystemConfig()->GetPackCnt( CSystemConfig::eSlkPack );
// 				for( int i=0; i<nCnt; i++ )
// 				{
// 					char szBuffer[MAX_PATH] = {0};
// 					sprintf( szBuffer, "%s%d.vfs", SLK_PACKHead, i );
// 					SetFileAttributes( szBuffer, FILE_ATTRIBUTE_NORMAL );
// 					g_SlkVFS.AppendVFS( szBuffer );
// 				}				
// 			}
// 		}
// 	}
// 	/////////////////////////////////////////////////////////////////
// 
// 	if( !g_ModelVfs.IsOpen() )
// 	{
// 		SetFileAttributes( MODEL_PACK, FILE_ATTRIBUTE_NORMAL );
// 		g_ModelVfs.LoadVFS( MODEL_PACK );
// 		int nCnt = GetSystemConfig()->GetPackCnt( CSystemConfig::eModelPack );
// 		for( int i=0; i<nCnt; i++ )
// 		{
// 			char szBuffer[MAX_PATH] = {0};
// 			sprintf( szBuffer, "%s%d.vfs", MODEL_PACKHead, i );
// 			SetFileAttributes( szBuffer, FILE_ATTRIBUTE_NORMAL );
// 			g_ModelVfs.AppendVFS( szBuffer );
// 		}		
// 	}
// 
// 	if ( !g_TextureVFS.IsOpen() )
// 	{
// 		SetFileAttributes( TEXTURE_PACK, FILE_ATTRIBUTE_NORMAL );
// 		g_TextureVFS.LoadVFS( TEXTURE_PACK );
// 		int nCnt = GetSystemConfig()->GetPackCnt( CSystemConfig::eTexturesPack );
// 		for( int i=0; i<nCnt; i++ )
// 		{
// 			char szBuffer[MAX_PATH] = {0};
// 			sprintf( szBuffer, "%s%d.vfs", TEXTURE_PACKHead, i );
// 			SetFileAttributes( szBuffer, FILE_ATTRIBUTE_NORMAL );
// 			g_TextureVFS.AppendVFS( szBuffer );
// 		}
// 	}
	unguard;

}

VOID Lock3DMemory()
{	
	while(g_bLock3DMemory)
	{
	//	OutputDebugString("Wait 3d Memory");
	//	Sleep(1);
	}
	g_bLock3DMemory = TRUE;
}

VOID UnLockMemory()
{
	g_bLock3DMemory = FALSE;
}

BOOL IsLock3DMemory()
{
	return g_bLock3DMemory;
}

const char* GetFullName( const char* filename )
{
	static char fullname[MAX_PATH];
	sprintf(fullname, "%s\\data\\%s", GetRootPath(), filename );
	return fullname;

}

const WCHAR* GetFullName( const WCHAR* filename )
{
	static WCHAR fullname[MAX_PATH];
	const int nWLen = 10240;
	static WCHAR wChar[MAX_PATH];
	wChar[0] = L'\0';
	MultiByteToWideChar(CP_ACP,0,GetRootPath(),-1,wChar,MAX_PATH -1); 

	wsprintfW(fullname, L"%s\\data\\%s", wChar, filename );
	return fullname;

}
