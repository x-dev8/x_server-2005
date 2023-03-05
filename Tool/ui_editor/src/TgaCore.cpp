#include "stdafx.h"
#include "TgaCore.h"
#include <assert.h>

//unsigned char	m_id_length;        /* 0 */
//unsigned char	m_color_map_type;   /* 1 */
//unsigned char	m_type;				/* 2 */
//unsigned short	m_cm_index;         /* 3 4 */
//unsigned short	m_cm_length;        /* 5 6 */
//unsigned char	m_cm_entry_size;    /* 7 */
//unsigned short	m_x_org;			/* 8 9 */
//unsigned short	m_y_org;			/* 10 11 */
//unsigned char	m_desc;				/* 17 */



#define UL_TGA_LR 0x10
#define UL_TGA_BT 0x20




#define UL_GFX_SWAP_RGB     0x0001
#define UL_GFX_PAD          0x0004
#define UL_GFX_COMPRESSED   0x0008
#define UL_GFX_SIGNEDPAD    0x0010
#define UL_GFX_INVERT_VERT  0x0020
#define UL_GFX_INVERT_HORIZ 0x0040


#define UL_GFX_565          0x00020000

#ifndef bread
#define bread() ((BYTE)fgetc(f))
#endif
#ifndef wread
#define wread() ( ((BYTE)bread()) | (((BYTE)bread())<<8) )
#endif

//int s_Width,s_Height;
//bool g_IsBuilding = false;

CGraphicsFileData::CGraphicsFileData(void)
{
	m_pFileData=NULL;
	memset(&m_FileHeader,0,sizeof(m_FileHeader));
	m_bValid = false;
}

CGraphicsFileData::~CGraphicsFileData(void)
{
	Release();
}

void CGraphicsFileData::Release()
{
	if (m_pFileData)
	{
		delete[] m_pFileData;
		m_pFileData = NULL;
	}
}

//void CGraphicsFileData::LoadTGAFile(const char* filename)
//{
//	CGraphicsFileData &m = *this;
//	FILE *f;
//
//	f = fopen(filename, "rb");
//	assert(f);
//
//	f = f;
//
//	unsigned char *data;
//
//	const int flags = 0;
//
//	int i, rle;
//	int a, r, g, b;
//	int right, top;
//	unsigned short bits16;
//
//	m_id_length = bread();
//	m_color_map_type = bread();
//	m_type = bread();
//
//	assert(m_type == 2 || m_type == 10 || m_type == 3);
//
//	m_cm_index = wread();
//	m_cm_length = wread();
//
//	m_cm_entry_size = bread();
//
//	m_x_org = wread();
//	m_y_org = wread();
//	m.dwWidth = wread();
//	m.dwHeight = wread();
//
//	s_Width = m.dwWidth;
//	s_Height = m.dwHeight;
//
//	m.bits_per_pixel = bread();
//	switch(m.bits_per_pixel)
//	{
//	case 8:
//		m_BytesPerPixel = 4;
//		break;
//	case 16:
//		m_BytesPerPixel = 2;
//		break;
//	case 24:
//		m_BytesPerPixel = 3;
//		break;
//	case 32:
//		m_BytesPerPixel = 4;
//		break;
//	}
//
//	m_desc = bread();
//
//	if (m_pFileData)
//		delete m_pFileData;
//	m_pFileData = (unsigned char *) new unsigned long[m.dwWidth * m.dwHeight];
//	assert(m_pFileData);
//
//	right = m_desc & UL_TGA_LR;
//	top = m_desc & UL_TGA_BT;
//
//	fread((char *) arId, m_id_length, 1, f);
//	fread((char *) arColorPalette, m_cm_length, m_cm_entry_size >> 3, f);
//
//	data = (unsigned char *)m_pFileData;
//
//	hxw = m.dwHeight * m.dwWidth;
//	switch (m_type)
//	{
//	case 3:
//		for (i = 0; i < hxw; i++)
//		{
//			a = bread();
//
//			*data++ = a;
//			*data++ = a;
//			*data++ = a;
//			/*
//			if (a == 0)
//			{
//			*data++ = 255;
//			}
//			else
//			{
//			*data++ = a;
//			}
//			*/
//			*data++ = a;
//		}
//		break;
//
//	case 2:
//		switch(m.bits_per_pixel)
//		{
//		case 16:
//			for (i = 0; i < hxw; i++)
//			{
//				bits16 = wread();
//				b = bits16 & 0x1F;
//				g = (bits16 >> 5) & 0x1F;
//				r = (bits16 >> 10) & 0x1F;
//
//				b <<= 3;
//				g <<= 3;
//				r <<= 3;
//				if (flags & UL_GFX_SWAP_RGB)
//				{
//					*data++ = r;
//					*data++ = g;
//					*data++ = b;
//				}
//				else
//				{
//					*data++ = b;
//					*data++ = g;
//					*data++ = r;
//				}
//
//				if (flags & UL_GFX_PAD)
//					*data++ = 0xFF;
//				else if (flags & UL_GFX_SIGNEDPAD)
//				{
//					if (r & 0x80)
//						*data++ = 0xFF;
//					else
//						*data++ = 0;
//				}
//				else
//					*data++ = 0;
//
//
//			}
//			break;
//
//		case 24:
//			for (i = 0; i < hxw; i++)
//			{
//				b = bread();
//				g = bread();
//				r = bread();
//				if (flags & UL_GFX_SWAP_RGB)
//				{
//					*data++ = r;
//					*data++ = g;
//					*data++ = b;
//				}
//				else
//				{
//					*data++ = b;
//					*data++ = g;
//					*data++ = r;
//				}
//
//				if (flags & UL_GFX_PAD)
//					*data++ = 0xFF;
//				else if (flags & UL_GFX_SIGNEDPAD)
//				{
//					if (r & 0x80)
//						*data++ = 0xFF;
//					else
//						*data++ = 0;
//				}
//				else
//					*data++ = 0;
//
//			}
//			break;
//		case 32:
//			for (i = 0; i < hxw; i++)
//			{
//				b = bread();
//				g = bread();
//				r = bread();
//				a = bread();
//				if (flags & UL_GFX_SWAP_RGB)
//				{
//					*data++ = r;
//					*data++ = g;
//					*data++ = b;
//					*data++ = a;
//				}
//				else
//				{
//					*data++ = b;
//					*data++ = g;
//					*data++ = r;
//					*data++ = a;
//				}
//			}
//		}
//		break;
//
//case 10:   //RLE TRUE color
//	switch(m.bits_per_pixel)
//	{
//	case 24:
//		i = 0;
//		while (i < hxw)
//		{
//
//			rle = bread();
//			if (rle < 0x80)
//			{
//				// Raw data
//				// encoded as n - 1
//				rle++;
//				// # of pixels
//				while (rle)
//				{
//					b = bread();
//					g = bread();
//					r = bread();
//					if (flags & UL_GFX_SWAP_RGB)
//					{
//						*data++ = r;
//						*data++ = g;
//						*data++ = b;
//					}
//					else
//					{
//						*data++ = b;
//						*data++ = g;
//						*data++ = r;
//					}
//					if (flags & UL_GFX_PAD)
//						*data++ = 0xFF;
//					else if (flags & UL_GFX_SIGNEDPAD)
//					{
//						if (r & 0x80)
//							*data++ = 0xFF;
//						else
//							*data++ = 0;
//					}
//					else
//						*data++ = 0;
//
//
//					rle--;
//					i++;
//					if (i > hxw)
//					{
//						//printf("RLE overflow\n");
//						delete m_pFileData;
//
//						assert(false);
//					}
//				}
//			}
//			else
//			{
//				rle -= 127;
//				b = bread();
//				g = bread();
//				r = bread();
//
//				// # of rle
//				while (rle)
//				{
//					if (flags & UL_GFX_SWAP_RGB)
//					{
//						*data++ = r;
//						*data++ = g;
//						*data++ = b;
//					}
//					else
//					{
//						*data++ = b;
//						*data++ = g;
//						*data++ = r;
//					}
//					if (flags & UL_GFX_PAD)
//						*data++ = 0xFF;
//					else if (flags & UL_GFX_SIGNEDPAD)
//					{
//						if (r & 0x80)
//							*data++ = 0xFF;
//						else
//							*data++ = 0;
//					}
//					else
//						*data++ = 0;
//
//
//
//					i++;
//					if (i > hxw)
//					{
//						//printf("RLE overflow\n");
//						delete m_pFileData;
//
//						assert(false);
//					}
//					rle--;
//				}
//			}
//
//		}
//		break;
//
//case 32: // RLE
//	i = 0;
//	while (i < hxw)
//	{
//
//		rle = bread();
//		if (rle < 0x80)
//		{
//			rle++;
//			while (rle)
//			{
//				if (flags & UL_GFX_SWAP_RGB)
//				{
//					b = bread();
//					g = bread();
//					r = bread();
//					a = bread();
//					*data++ = r;
//					*data++ = g;
//					*data++ = b;
//					*data++ = a;
//				}
//				else
//				{
//
//					*data++ = bread();
//					*data++ = bread();
//					*data++ = bread();
//					*data++ = bread();
//				}
//				rle--;
//				i++;
//				if (i > hxw)
//				{
//					//printf("RLE overflow\n");
//					//exit(116);
//					delete m_pFileData;
//
//					assert(false);
//				}
//
//			}
//		}
//		else
//		{
//			rle -= 127;
//			b = bread();
//			g = bread();
//			r = bread();
//			a = bread();
//
//			while (rle)
//			{
//				if (flags & UL_GFX_SWAP_RGB)
//				{
//					*data++ = r;
//					*data++ = g;
//					*data++ = b;
//					*data++ = a;
//				}
//				else
//				{
//					*data++ = b;
//					*data++ = g;
//					*data++ = r;
//					*data++ = a;
//				}
//				rle--;
//				i++;
//				if (i > hxw)
//				{
//					//printf("RLE overflow\n");
//					delete m_pFileData;
//
//					assert(false);
//				}
//			}
//		}
//
//	}
//	break;
//}
//}
//
//fclose(f);
//f = f = NULL;
//
//if (!top)
//{
//	unsigned long *swap = (unsigned long *) new unsigned long[hxw];
//
//	memcpy(swap, m_pFileData, hxw * sizeof(unsigned long));
//
//	unsigned long * src, * dest;
//	unsigned long * src_data = (unsigned long *)m_pFileData;
//
//	for (i = 0; i < m.dwHeight; i++)
//	{
//		src = &swap[(m.dwHeight - i - 1) * m.dwWidth];
//		dest = &src_data[i * m.dwWidth];
//
//		memcpy(dest, src, m.dwWidth * sizeof(unsigned long) );
//	}
//
//	delete swap;
//}
//}

extern char g_stPath[MAX_PATH];
void CGraphicsFileData::LoadTGAFile(const char* filename)
{
	m_strFileName = filename;
	CString strPathName = g_stPath;
	strPathName += "\\";
	strPathName += m_strFileName;

	CFile file;
	if ( file.Open(strPathName,CFile::modeRead) == false )
	{
		strPathName = g_stPath;
		for( int n=strlen(strPathName); n>0; n-- )
		{
			if ( strPathName[n]=='\\' || strPathName[n]=='/' )
			{
				strPathName = strPathName.Left(n);
				break;
			}
		}
		strPathName += "\\Common\\";
		strPathName += m_strFileName;
		if ( file.Open(strPathName,CFile::modeRead) == false )
		{
			MessageBox( AfxGetMainWnd()->m_hWnd, filename,"打开文件失败",MB_OK );
			return;
		}
	}

	CArchive ar(&file,CArchive::load);
	LoadTGAFile(ar);
	ar.Close();
	file.Close();
}

void CGraphicsFileData::LoadTGAFile(CArchive& ar)
{
//	m_strFileName = ar.m_strFileName;

	//ar.Read(&m_FileHeader,sizeof(m_FileHeader));
	m_FileHeader.Load(ar);
	unsigned char *data;

	const int flags = 0;

	int i;
	unsigned char rle;
	unsigned char  r, g, b;
	int right, top;

	assert(m_FileHeader.Type == 2 || m_FileHeader.Type == 10 || m_FileHeader.Type == 3);

	switch(m_FileHeader.BitsPrePixel)
	{
	case 8:
		m_BytesPerPixel = 4;
		break;
	case 16:
		m_BytesPerPixel = 2;
		break;
	case 24:
		m_BytesPerPixel = 3;
		break;
	case 32:
		m_BytesPerPixel = 4;
		break;
	}

	delete[] m_pFileData;

	m_pFileData = (unsigned char *) new unsigned long[m_FileHeader.Width * m_FileHeader.Height];
	assert(m_pFileData);

	right = m_FileHeader.Desc & UL_TGA_LR;
	top = m_FileHeader.Desc & UL_TGA_BT;

	unsigned char	arId[256];
	unsigned char	arColorPalette[256 * 3];

	if(m_FileHeader.IdLength>0)
		ar.Read(arId,m_FileHeader.IdLength);
	if(m_FileHeader.CmLength>0 && (m_FileHeader.CmEntrySize >> 3)>0 )
		ar.Read(arColorPalette,m_FileHeader.CmLength*(m_FileHeader.CmEntrySize >> 3));

	data = (unsigned char *)m_pFileData;

	int hxw = m_FileHeader.Height * m_FileHeader.Width;
	switch (m_FileHeader.Type)
	{
	case 3:
		for (i = 0; i < hxw; i++)
		{
			unsigned char a;

			ar>>a;

			*data++ = a;
			*data++ = a;
			*data++ = a;
			/*
			if (a == 0)
			{
			*data++ = 255;
			}
			else
			{
			*data++ = a;
			}
			*/
			*data++ = a;
		}
		break;

	case 2:
		switch(m_FileHeader.BitsPrePixel)
		{
		case 16:
			for (i = 0; i < hxw; i++)
			{
				unsigned short bits16;
				ar>>bits16;
				b = bits16 & 0x1F;
				g = (bits16 >> 5) & 0x1F;
				r = (bits16 >> 10) & 0x1F;

				b <<= 3;
				g <<= 3;
				r <<= 3;
				if (flags & UL_GFX_SWAP_RGB)
				{
					*data++ = r;
					*data++ = g;
					*data++ = b;
				}
				else
				{
					*data++ = b;
					*data++ = g;
					*data++ = r;
				}

				if (flags & UL_GFX_PAD)
					*data++ = 0xFF;
				else if (flags & UL_GFX_SIGNEDPAD)
				{
					if (r & 0x80)
						*data++ = 0xFF;
					else
						*data++ = 0;
				}
				else
					*data++ = 0;
			}
			break;

		case 24:
			for (i = 0; i < hxw; i++)
			{
				ar>>b>>g>>r;
				if (flags & UL_GFX_SWAP_RGB)
				{
					*data++ = r;
					*data++ = g;
					*data++ = b;
				}
				else
				{
					*data++ = b;
					*data++ = g;
					*data++ = r;
				}

				if (flags & UL_GFX_PAD)
					*data++ = 0xFF;
				else if (flags & UL_GFX_SIGNEDPAD)
				{
					if (r & 0x80)
						*data++ = 0xFF;
					else
						*data++ = 0;
				}
				else
					*data++ = 0xFF;

			}
			break;
		case 32:
			for (i = 0; i < hxw; i++)
			{
				unsigned char a;
				ar>>b>>g>>r>>a;
				if (flags & UL_GFX_SWAP_RGB)
				{
					*data++ = r;
					*data++ = g;
					*data++ = b;
					*data++ = a;
				}
				else
				{
					*data++ = b;
					*data++ = g;
					*data++ = r;
					*data++ = a;
				}
			}
		}
		break;

	case 10:   //RLE TRUE color
		switch(m_FileHeader.BitsPrePixel)
		{
		case 24:
			i = 0;
			while (i < hxw)
			{
				ar>>rle;
				if (rle < 0x80)
				{
					// Raw data
					// encoded as n - 1
					rle++;
					// # of pixels
					while (rle)
					{
						ar>>b>>g>>r;
						if (flags & UL_GFX_SWAP_RGB)
						{
							*data++ = r;
							*data++ = g;
							*data++ = b;
						}
						else
						{
							*data++ = b;
							*data++ = g;
							*data++ = r;
						}
						if (flags & UL_GFX_PAD)
							*data++ = 0xFF;
						else if (flags & UL_GFX_SIGNEDPAD)
						{
							if (r & 0x80)
								*data++ = 0xFF;
							else
								*data++ = 0;
						}
						else
							*data++ = 0xFF;


						rle--;
						i++;
						if (i > hxw)
						{
							//printf("RLE overflow\n");
							delete[] m_pFileData;

							assert(false);
						}
					}
				}
				else
				{
					rle -= 127;
					ar>>b>>g>>r;

					// # of rle
					while (rle)
					{
						if (flags & UL_GFX_SWAP_RGB)
						{
							*data++ = r;
							*data++ = g;
							*data++ = b;
						}
						else
						{
							*data++ = b;
							*data++ = g;
							*data++ = r;
						}
						if (flags & UL_GFX_PAD)
							*data++ = 0xFF;
						else if (flags & UL_GFX_SIGNEDPAD)
						{
							if (r & 0x80)
								*data++ = 0xFF;
							else
								*data++ = 0;
						}
						else
							*data++ = 0xFF;



						i++;
						if (i > hxw)
						{
							//printf("RLE overflow\n");
							delete[] m_pFileData;

							assert(false);
						}
						rle--;
					}
				}

			}
			break;

		case 32: // RLE
			i = 0;
			while (i < hxw)
			{
				ar>>rle;
				if (rle < 0x80)
				{
					rle++;
					while (rle)
					{
						unsigned char a;
						if (flags & UL_GFX_SWAP_RGB)
						{
							ar>>b>>g>>r>>a;

							*data++ = r;
							*data++ = g;
							*data++ = b;
							*data++ = a;
						}
						else
						{
							
							ar>>*data++;
							ar>>*data++;
							ar>>*data++;
							ar>>*data++;
						}
						rle--;
						i++;
						if (i > hxw)
						{
							//printf("RLE overflow\n");
							//exit(116);
							delete[] m_pFileData;

							assert(false);
						}

					}
				}
				else
				{
					unsigned char a;
					rle -= 127;
					ar>>b>>g>>r>>a;

					while (rle)
					{
						if (flags & UL_GFX_SWAP_RGB)
						{
							*data++ = r;
							*data++ = g;
							*data++ = b;
							*data++ = a;
						}
						else
						{
							*data++ = b;
							*data++ = g;
							*data++ = r;
							*data++ = a;
						}
						rle--;
						i++;
						if (i > hxw)
						{
							//printf("RLE overflow\n");
							delete[] m_pFileData;

							assert(false);
						}
					}
				}

			}
			break;
		}
	}


	if (!top)
	{
		unsigned long *swap = (unsigned long *) new unsigned long[hxw];

		memcpy(swap, m_pFileData, hxw * sizeof(unsigned long));

		unsigned long * src, * dest;
		unsigned long * src_data = (unsigned long *)m_pFileData;

		for (i = 0; i < m_FileHeader.Height; i++)
		{
			src = &swap[(m_FileHeader.Height - i - 1) * m_FileHeader.Width];
			dest = &src_data[i * m_FileHeader.Width];

			memcpy(dest, src, m_FileHeader.Width * sizeof(unsigned long) );
		}

		delete swap;
	}

	m_bValid = true;

	m_bmp.DeleteObject();
	m_bmp.Attach( GetBitmap(RGB(255,0,255)) );
}


//void CGraphicsFileData::Draw(HDC hDC, RECT * pRect, COLORREF ct)
//{
//	int x,y;
//
//	float fW=GetWidth()/(pRect->right-pRect->left);
//	float fH=GetHeight()/(pRect->bottom-pRect->top);
//
//	for(y=pRect->top;y<=pRect->bottom;y++)
//	{
//		for(x=pRect->left;x<=pRect->right;x++)
//		{
//			int x1,y1;
//			x1=x*fW;
//			y1=y*fH;
//			int index=y1*GetWidth()+x1;
//			float f1,f2;
//			f1=m_pstFileData[index].A/255.0f;
//			f2=1-f1;
//			COLORREF c1=::GetPixel(hDC,x,y);
//			COLORREF color=RGB(this->m_pstFileData[index].R*f1+GetRValue(c1)*f2,
//				this->m_pstFileData[index].G*f1+GetGValue(c1)*f2,
//				this->m_pstFileData[index].B*f1+GetBValue(c1)*f2);
//			::SetPixel(hDC,x,y,color);
//		}
//	}
//}

void CGraphicsFileData::Draw( CDC* pDC, int x, int y, E_DrawType enType )
{
	if ( m_bValid == false )
		return;

	switch( enType )
	{
	case TYPE_NO_ALPHA:
		{
			CDC memDC;
			memDC.CreateCompatibleDC(pDC);
			HBITMAP hOldBmp=(HBITMAP)memDC.SelectObject((HBITMAP)m_bmp);

			pDC->StretchBlt(x,y,GetWidth(),GetHeight(),&memDC,0,0,GetWidth(),GetHeight(),SRCCOPY);

			memDC.SelectObject(hOldBmp);
			memDC.DeleteDC();
		}
		break;
	case TYPE_ALPHA:
		{
			int nIndex = 0;
			float f1,f2 =0;

			for( int nSrcY=0; nSrcY<GetHeight(); nSrcY++ )
			{
				for( int nSrcX=0; nSrcX<GetWidth(); nSrcX++ )
				{
					nIndex = nSrcY*GetWidth()+nSrcX;
					f1=m_pstFileData[nIndex].A/255.0f;
					f2=1-f1;
					COLORREF c1= pDC->GetPixel(x+nSrcX,y+nSrcY);
					COLORREF color=RGB(m_pstFileData[nIndex].R*f1+GetRValue(c1)*f2,
						m_pstFileData[nIndex].G*f1+GetGValue(c1)*f2,
						m_pstFileData[nIndex].B*f1+GetBValue(c1)*f2);
					pDC->SetPixel( x+nSrcX,y+nSrcY,color );
				}
			}
		}
		break;
	default:
		{
			assert(false&&"未知类型");
		}
		break;
	}

}

HBITMAP CGraphicsFileData::GetBitmap(COLORREF ct)
{
	HBITMAP ret=NULL;
	if(m_pFileData==NULL)
		return ret;
	
	HDC hdc=GetDC(NULL);
	
    int cx=GetWidth();
	int cy=GetHeight();

	int bitWidth=cx * 3;
	
	if(bitWidth % 4)
	{
		bitWidth +=( 4 - (bitWidth % 4));
	}

	BYTE* pBmp=new BYTE[bitWidth * cy];

	int x,y;
	int index=0;
	int ix=0;
	for(y=0;y<cy;y++)
	{
		int ix1=ix;
		for(x=0;x<cx;x++)
		{
			UINT f1,f2;
			f1=m_pstFileData[index].A;
			f2=255-f1;
			pBmp[ ix1 + 0] = this->m_pstFileData[index].B * f1/255 + GetBValue(ct) *f2/255;
			pBmp[ ix1 + 1] = this->m_pstFileData[index].G * f1/255 + GetGValue(ct) *f2/255;
			pBmp[ ix1 + 2] = this->m_pstFileData[index].R * f1/255 + GetRValue(ct) *f2/255;
			index++;
			ix1+=3;
		}
		ix+=bitWidth;
	}

	BITMAPINFO bmi;
	memset(&bmi,0,sizeof(bmi));
	bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = cx;
    bmi.bmiHeader.biHeight      = -cy; // top-down image
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 24;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage   = 0;

	ret=CreateDIBitmap(hdc,&bmi.bmiHeader,CBM_INIT,(void*)pBmp,&bmi,DIB_RGB_COLORS);
	
	delete [] pBmp;
	
	::ReleaseDC(NULL,hdc);

	return ret;
}

