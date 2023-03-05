#pragma once

//#define PIC_ROOT	"\\Pic\\"

typedef struct _TAGFILEHEADER{
	unsigned char	IdLength;
	unsigned char	ColorMapType;
	unsigned char   Type;
	unsigned short	CmIndex;
	unsigned short	CmLength;
	unsigned char	CmEntrySize;
	unsigned short	XOrg;
	unsigned short	YOrg;
	unsigned short	Width;
	unsigned short	Height;
	unsigned char	BitsPrePixel;
	unsigned char   Desc;
	_TAGFILEHEADER()
	{
		IdLength=0;
		ColorMapType=0;
		Type=2;
		CmIndex=0;
		CmLength=0;
		CmEntrySize=0;
		XOrg=0;
		YOrg=0;
		Width=0;
		Height=0;
		BitsPrePixel=32;
		Desc=0;
	}
	void Load(CArchive& ar)
	{
		ar>>IdLength>>ColorMapType>>Type>>CmIndex>>
			CmLength>>CmEntrySize>>XOrg>>YOrg>>Width
			>>Height>>BitsPrePixel>>Desc;
	}
	void Save(CArchive& ar)
	{
		ar<<IdLength<<ColorMapType<<Type<<CmIndex<<
			CmLength<<CmEntrySize<<XOrg<<YOrg<<Width
			<<Height<<BitsPrePixel<<Desc;
	}
	void Load(FILE* f)
	{
		fread(&IdLength,sizeof(IdLength),1,f);
		fread(&ColorMapType,sizeof(ColorMapType),1,f);
		fread(&Type,sizeof(Type),1,f);
		fread(&CmIndex,sizeof(CmIndex),1,f);
		fread(&CmLength,sizeof(CmLength),1,f);
		fread(&CmEntrySize,sizeof(XOrg),1,f);
		fread(&YOrg,sizeof(YOrg),1,f);
		fread(&Width,sizeof(Width),1,f);
		fread(&Height,sizeof(Height),1,f);
		fread(&BitsPrePixel,sizeof(BitsPrePixel),1,f);
		fread(&Desc,sizeof(Desc),1,f);
	}
}TGAFILEHEADER, FAR * LPTGAFILEHEADER;

class CGraphicsFileData
{
public:
	enum E_DrawType
	{
		TYPE_NO_ALPHA
		,TYPE_ALPHA
	};

public:
	unsigned short	GetWidth(){return m_FileHeader.Width;}
	unsigned short	GetHeight(){return m_FileHeader.Height;}
	void			LoadTGAFile(const char* );
	bool			IsValid(){ return m_bValid; }
	HBITMAP			GetBitmap(COLORREF ct = RGB(255,0,255) );
	//	void Draw(HDC hDC, RECT * pRect, COLORREF ct);
	void			Draw( CDC* pDC, int x, int y, E_DrawType enType = TYPE_NO_ALPHA );
	CString			GetFileName(){ return m_strFileName; }
	void			Release();

private:
	void			LoadTGAFile(CArchive& ar);

private:
	TGAFILEHEADER m_FileHeader;
	typedef struct _stFileData
	{
		BYTE B;
		BYTE G;
		BYTE R;
		BYTE A;
	}stFileData;
	union
	{
		stFileData* m_pstFileData;
		unsigned char *m_pFileData;
	};
	int m_BytesPerPixel;
	unsigned char *endptr;

	CBitmap		m_bmp;
	bool		m_bValid;
	CString		m_strFileName;

public:
	CGraphicsFileData(void);
	~CGraphicsFileData(void);
};
