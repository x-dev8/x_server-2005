#pragma once
#include <afxtempl.h>
#include <assert.h>
/*

  管理GDI+使用图片资源

*/
class SkinImgMgr
{
public:
    SkinImgMgr(void);
	~SkinImgMgr(void);
	struct imginfo
	{
		Image *img;
		CString name;            //根据文件名读取
		CString path;            //根据路径读取
		CString s_md5;           //以md5作为文件标识    
	};
	Image * AddImgR(HMODULE hInst, UINT nResourceID, LPCTSTR lpType);//添加一副图片到管理器
	Image * AddImg(CString path);//添加一副图片到管理器
    Image * GetImg(CString name);//从管理器得到一副图片
	bool RemoveImg(CString name);//从管理器移除一副图片
	void Release(void);          //释放管理器所有资源
	
	CPtrArray imgptr;
	
	bool ImageFromR(HMODULE hInst, UINT nResourceID, LPCTSTR lpType,Image * &pImg)
	{
		if(lpType == RT_BITMAP)
		{
			//GDI+ can not load RT_BITMAP resouce, 
			//because they are predefined resource, 
			//they don't contains the image file header.
			assert(FALSE);
		{pImg=NULL;return false;}
		}

		HRSRC hResource = ::FindResource(hInst, MAKEINTRESOURCE(nResourceID), lpType);
		if (!hResource)
		{pImg=NULL;return false;}

		DWORD imageSize = ::SizeofResource(hInst, hResource);
		if (!imageSize)
		{pImg=NULL;return false;}

		const void* pResourceData = ::LockResource(::LoadResource(hInst, hResource));
		if (!pResourceData)
		{pImg=NULL;return false;}

		HGLOBAL hBuffer = ::GlobalAlloc(GMEM_FIXED, imageSize);
		if (NULL == hBuffer)
		{pImg=NULL;return false;}

		void* pBuffer = ::GlobalLock(hBuffer);
		if (pBuffer)
		{
			CopyMemory(pBuffer, pResourceData, imageSize);
			IStream* pStream = NULL;
			if (::CreateStreamOnHGlobal(hBuffer, FALSE, &pStream) == S_OK)
			{
				pImg = Gdiplus::Image::FromStream(pStream);
				pStream->Release();
				if (pImg)
				{ 
					if (pImg->GetLastStatus() == Gdiplus::Ok &&
						pImg->GetWidth() > 0)
					{
						
						return true;
					}

					delete pImg;
				}
			}
			::GlobalUnlock(hBuffer);
		}
		::GlobalFree(hBuffer);

		{pImg=NULL;return false;}
	}

	BOOL ImageFromF(LPCTSTR sTR,Image * &pImg)
	{
		//	CFile mFile1(sTR,CFile::modeRead); 
		CFile mFile;
		if(!mFile.Open(sTR,CFile::modeRead))
		{
			CString pic=sTR;
			pic+=_T("加载失败：路径不存在");
			AfxMessageBox(pic);
			pImg=NULL;
			goto fail;
		}
		int len=mFile.GetLength();
		char * lpRsrc=new char[mFile.GetLength()];
		mFile.Read(lpRsrc,mFile.GetLength()); 
		mFile.Close(); 


		Status stat;

		/*FILE * file;
		file = fopen(sTR,"a+");
		if(!file)
		{
		AfxMessageBox("File open fail!\n");
		return false;
		}
		fseek(file,0,SEEK_END);     //定位到文件末  
		int len = ftell(file);
		fseek(file,0,SEEK_SET );     //定位到文件末  

		CString ss;ss.Format("%d",len);//AfxMessageBox(ss+sTR);
		char * lpRsrc=new char[len+1];
		fread(lpRsrc,len,1 ,file);//共读取200*12=2400个字节
		*/

		// Allocate global memory on which to create stream
		HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
		BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
		memcpy(pmem,lpRsrc,len);

		delete lpRsrc;

		IStream* pstm;
		CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);

		// load from stream
		pImg=Gdiplus::Image::FromStream(pstm);

		stat = pImg->GetLastStatus();  
		if(stat != Ok)
		{
			CString pic=sTR;
			pic+=_T("加载失败：内存分配失败");
			AfxMessageBox(pic);
			pImg=NULL;
			goto fail;
		}

		// free/release stuff
		GlobalUnlock(m_hMem);
		pstm->Release();
		FreeResource(lpRsrc);
		return true;
fail:
		return false;

	}
};
