#pragma once
#include <afxtempl.h>
#include <assert.h>
/*

  ����GDI+ʹ��ͼƬ��Դ

*/
class SkinImgMgr
{
public:
    SkinImgMgr(void);
	~SkinImgMgr(void);
	struct imginfo
	{
		Image *img;
		CString name;            //�����ļ�����ȡ
		CString path;            //����·����ȡ
		CString s_md5;           //��md5��Ϊ�ļ���ʶ    
	};
	Image * AddImgR(HMODULE hInst, UINT nResourceID, LPCTSTR lpType);//���һ��ͼƬ��������
	Image * AddImg(CString path);//���һ��ͼƬ��������
    Image * GetImg(CString name);//�ӹ������õ�һ��ͼƬ
	bool RemoveImg(CString name);//�ӹ������Ƴ�һ��ͼƬ
	void Release(void);          //�ͷŹ�����������Դ
	
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
			pic+=_T("����ʧ�ܣ�·��������");
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
		fseek(file,0,SEEK_END);     //��λ���ļ�ĩ  
		int len = ftell(file);
		fseek(file,0,SEEK_SET );     //��λ���ļ�ĩ  

		CString ss;ss.Format("%d",len);//AfxMessageBox(ss+sTR);
		char * lpRsrc=new char[len+1];
		fread(lpRsrc,len,1 ,file);//����ȡ200*12=2400���ֽ�
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
			pic+=_T("����ʧ�ܣ��ڴ����ʧ��");
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
