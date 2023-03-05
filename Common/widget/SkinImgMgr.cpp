#include "widget.h"
#include "SkinImgMgr.h"
#include "md5.h"

CString GetFileNameByFilePath(CString filepath)
{
	CString FileName;
	FileName=filepath.Right(filepath.GetLength()-filepath.ReverseFind('\\')-1);

	return FileName;
}

int CalcFileMD5Hash(CString sFileName, CString& sMD5Hash)
{
	FILE* f = NULL;
	BYTE buff[512];
	MD5 md5;
//	MD5_CTX md5_ctx;
	unsigned char md5_hash[16];
	int i;

	sMD5Hash.Empty();

#if _MSC_VER<1400
	f = _tfopen(sFileName.GetBuffer(0), _T("rb"));
#else
	_tfopen_s(&f, sFileName.GetBuffer(0), _T("rb"));
#endif

	if(f==NULL) 
		return -1;

//	md5.MD5Init(&md5_ctx);

	while(!feof(f))
	{
		size_t count = fread(buff, 1, 512, f);
		if(count>0)
		{
	//		md5.update(buff, (unsigned int)count);
		//	md5.MD5Update(&md5_ctx, buff, (unsigned int)count);
		}
	}

	fclose(f);
/*	md5.MD5Final(md5_hash, &md5_ctx);

	for(i=0; i<16; i++)
	{
		CString number;
		number.Format(_T("%02x"), md5_hash[i]);
		sMD5Hash += number;
	}
*/

	sMD5Hash.Format("%s",md5.toString());
	
	return 0;
}

SkinImgMgr::SkinImgMgr(void)
{
	imgptr.RemoveAll();
}

SkinImgMgr::~SkinImgMgr(void)
{
    Release();
}
Image * SkinImgMgr::AddImg(CString path)
{
	CString s_md5;
//	CalcFileMD5Hash(path,s_md5);
	
	for(int i=0;i<imgptr.GetCount();i++)
	{
		imginfo * node=(imginfo *)imgptr.GetAt(i);
		if(node->s_md5==s_md5||node->path==path)
		{
	//		return node->img;
		}
	}
	CString name=GetFileNameByFilePath(path);
	imginfo *node =new imginfo;
    
	ImageFromF(path,node->img);
	node->name=name;
	node->path=path;
	node->s_md5=s_md5;
	imgptr.InsertAt(imgptr.GetCount(),node);

	return node->img;
}
Image * SkinImgMgr::AddImgR(HMODULE hInst, UINT nResourceID, LPCTSTR lpType)
{
// 	CString s_md5;
// 	CalcFileMD5Hash(path,s_md5);
// 
// 	for(int i=0;i<imgptr.GetCount();i++)
// 	{
// 		imginfo * node=(imginfo *)imgptr.GetAt(i);
// 		if(node->s_md5==s_md5)
// 		{
// 			return node->img;
// 		}
// 	}
//    CString name=GetFileNameByFilePath(path);
	imginfo *node =new imginfo;

	ImageFromR(hInst,nResourceID,lpType,node->img);
//	node->name=name;
//	node->path=path;
//	node->s_md5=s_md5;
	imgptr.InsertAt(imgptr.GetCount(),node);

	return node->img;
}
Image * SkinImgMgr::GetImg(CString name)
{
	for(int i=0;i<imgptr.GetCount();i++)
	{
		imginfo * node=(imginfo *)imgptr.GetAt(i);
		if(node->name==name||node->path==name)
		{
              return node->img;
		}
	}
	return NULL;
}

bool SkinImgMgr::RemoveImg(CString name)
{
	for(int i=0;i<imgptr.GetCount();i++)
	{
		imginfo * node=(imginfo*)imgptr.GetAt(i);
		if(node->name==name||node->path==name)
		{
			delete node->img;
			imgptr.RemoveAt(i);

		}
    }
	return false;
}

void SkinImgMgr::Release(void)
{ 
	for(int i=0;i<imgptr.GetCount();i++)
	{
		imginfo * node=(imginfo*)imgptr.GetAt(i);
		if(node->img)
		delete node->img;
		delete node;
		

	}
	imgptr.RemoveAll();
}
