#pragma once
#pragma warning(disable : 4005)
#include "Font3D.h"
#include "Font2D.h"
#include <list>
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/RendererDx.h"
#include "Me3d/Include.h"
#include "MeFont/MeFontSystem.h"

#pragma warning(default : 4005)

class Font3DManager 
{
public:
	struct RenderTargetInfo
	{
		LPDIRECT3DTEXTURE9 rt;
		LPDIRECT3DSURFACE9 offscreenSurf;

		RenderTargetInfo() : rt(0), offscreenSurf(0) {}
	};

    ~Font3DManager() {}

    static void Initialize(LPDIRECT3DDEVICE9 pd3dDevice)
    {
        m_pInst = new Font3DManager();
        m_pInst->m_pd3dDevice = pd3dDevice;

        D3DXCreateSprite(pd3dDevice, &m_pInst->m_sprite);
    }

    static void Shutdown()
    {
        if (m_pInst)
        {
            delete m_pInst;
            m_pInst = 0;
        }
    }

    static Font3DManager* Instance()
    {
        return m_pInst;
    }

    RTTFont* CreateFont3D(int rectWidth,
		const TCHAR* font, int fontSize, bool b3D = true,
        BOOL bold = false, BOOL italic = false)
    {
        RTTFont* newFont3D = 0;
		if( b3D )
			newFont3D = MeNew Font3D();
		else
			newFont3D = MeNew Font2D();

        if (FAILED(newFont3D->Create(m_pd3dDevice, rectWidth, font, fontSize, bold, italic)))
        {
            delete newFont3D;
            return 0;
        }

        m_font3DList.push_back(newFont3D);
        return newFont3D;
    }

    void DestroyFont3D(RTTFont* font)
    {
        Font3DList::iterator it, end = m_font3DList.end();
        for (it = m_font3DList.begin(); it != end; ++it)
        {
            if (*it == font)
            {
				ReleaseD3DTexture((*it)->GetD3DTexture());

                (*it)->Destroy();
                delete *it;
                m_font3DList.erase(it);
                break;
            }
        }
    }

    HRESULT OnResetDevice(LPDIRECT3DDEVICE9 pd3dDevice)
    {
        m_pd3dDevice = pd3dDevice;

        if (m_sprite)
            m_sprite->OnResetDevice();

        if (!m_d3dDepthSurf)
        {
            if (FAILED(pd3dDevice->CreateDepthStencilSurface(
                512,
                512,
                D3DFMT_D16,
                D3DMULTISAMPLE_NONE,
                0,
                TRUE,
                &m_d3dDepthSurf,
                NULL)))
            {
                assert(0 && "FAILED pd3dDevice->CreateDepthStencilSurface");
            }
        }

        {
            D3DXFonts::iterator it, end = m_fonts.end();
            for (it = m_fonts.begin(); it != end; ++it)
            {
				if( (*it).d3dFont )
					(*it).d3dFont->OnResetDevice();
            }
        }

        {
            Font3DList::iterator it, end = m_font3DList.end();
            for (it = m_font3DList.begin(); it != end; ++it)
            {
                (*it)->OnResetDevice(pd3dDevice);
            }
        }

        return S_OK;
    }

    HRESULT OnLostDevice()
    {
        HRESULT hr;
        {
            Font3DList::iterator it, end = m_font3DList.end();
            for (it = m_font3DList.begin(); it != end; ++it)
            {
                hr = (*it)->OnLostDevice();
                assert(hr == S_OK);
            }
        }

        {
            D3DXTextures::iterator it, end = m_textures.end();
            for (it = m_textures.begin(); it != end; ++it)
            {
                (*it).d3dTex->Release();
                (*it).d3dTex = 0;
            }
            m_textures.clear();
        }

        {
            D3DXFonts::iterator it, end = m_fonts.end();
            for (it = m_fonts.begin(); it != end; ++it)
            {
				if( (*it).d3dFont )
				{
					hr = (*it).d3dFont->OnLostDevice();
					assert(hr == S_OK);
				}
            }
		}

		{
			RenderTargets::iterator it, end = m_RTs.end();
			for (it = m_RTs.begin(); it != end; ++it)
			{
				it->second.rt->Release();
				it->second.offscreenSurf->Release();
			}
			m_RTs.clear();
		}

        if (m_d3dDepthSurf)
        {
            m_d3dDepthSurf->Release();
            m_d3dDepthSurf = 0;
        }

        if (m_sprite)
        {
            hr = m_sprite->OnLostDevice();
            assert(hr == S_OK);
        }
        return S_OK;
    }

    HRESULT Destroy()
    {
        Font3DList::iterator it, end = m_font3DList.end();
        for (it = m_font3DList.begin(); it != end; ++it)
        {
            (*it)->Destroy();
            delete *it;
        }
        m_font3DList.clear();

        {
            D3DXTextures::iterator it, end = m_textures.end();
            for (it = m_textures.begin(); it != end; ++it)
            {
                (*it).d3dTex->Release();
                (*it).d3dTex = 0;
            }
            m_textures.clear();
        }

        {
            D3DXFonts::iterator it, end = m_fonts.end();
            for (it = m_fonts.begin(); it != end; ++it)
            {
				if( (*it).d3dFont )
				{
					(*it).d3dFont->Release();
					(*it).d3dFont = 0;
				}                
            }
            m_fonts.clear();
		}

		{
			RenderTargets::iterator it, end = m_RTs.end();
			for (it = m_RTs.begin(); it != end; ++it)
			{
				it->second.rt->Release();
				it->second.offscreenSurf->Release();
			}
			m_RTs.clear();
		}

        if (m_d3dDepthSurf)
        {
            m_d3dDepthSurf->Release();
            m_d3dDepthSurf = 0;
        }

        if (m_sprite)
        {
            m_sprite->Release();
            m_sprite = 0;
        }
        return S_OK;
    }

    void Render();

	int GetFontIndex( const TCHAR* font, int fontSize,
		BOOL bold = false, BOOL italic = false )
	{
		FontInfo info;
		info.font = font;
		info.fontSize = fontSize;
		info.bold = bold;
		info.italic = italic;
		info.d3dFont = 0;

		D3DXFonts::iterator it, end = m_fonts.end();
		for (it = m_fonts.begin(); it != end; ++it)
		{
			if (*it == info)
			{
				return (*it).fontindex;
			}
		}

		info.fontindex = FontSystem::CreateFont( font, fontSize );

		m_fonts.push_back(info);
		return info.fontindex;


	}

    LPD3DXFONT GetD3DFont(const TCHAR* font, int fontSize,
        BOOL bold = false, BOOL italic = false)
    {
        FontInfo info;
        info.font = font;
        info.fontSize = fontSize;
        info.bold = bold;
        info.italic = italic;
        info.d3dFont = 0;

        D3DXFonts::iterator it, end = m_fonts.end();
        for (it = m_fonts.begin(); it != end; ++it)
        {
            if (*it == info)
            {
                return (*it).d3dFont;
            }
        }

		HRESULT hr = D3DXCreateFont(
			m_pd3dDevice, fontSize, 0, bold ? FW_BOLD : FW_NORMAL, 1,
			italic, DEFAULT_CHARSET, 
			OUT_STRING_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			font, &info.d3dFont);
		if( FAILED( hr ) )
        {
			if( hr == D3DERR_INVALIDCALL )
			{
				assert(0 && "d3derr_invalidcall");
			}
			else if( hr == D3DXERR_INVALIDDATA )
			{
				assert( 0 && "invaliddata" );
			}
			else if( hr == E_OUTOFMEMORY )
			{
				assert( 0 && "outofmemory" );
			}
            if (FAILED(D3DXCreateFont(
                m_pd3dDevice, fontSize, 0, bold ? FW_BOLD : FW_NORMAL, 1,
                italic, DEFAULT_CHARSET, 
                OUT_STRING_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                _T("¿¬Ìå_GB2312"), &info.d3dFont)))
                return 0;
        }

        m_fonts.push_back(info);
        return info.d3dFont;
    }

	LPDIRECT3DTEXTURE9 GetD3DTexture(const TCHAR* text, const std::vector<D3DXCOLOR>& colors, UINT width, bool& dirty)
    {
        dirty = false;

        TextInfo info;
        info.text = text;
        info.width = width;
		info.colors = colors;
        info.d3dTex = 0;

        D3DXTextures::iterator it, end = m_textures.end();
        for (it = m_textures.begin(); it != end; ++it)
        {
            if (*it == info)
            {
				++((*it).ref);
                return (*it).d3dTex;
            }
        }

		if (FAILED(m_pd3dDevice->CreateTexture(
			width,
			width,
			1,
			0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED,
			&info.d3dTex,
			NULL)))
			return 0;

        dirty = true;
        m_textures.push_back(info);
        return info.d3dTex;
	}

	void ReleaseD3DTexture(LPDIRECT3DTEXTURE9 tex)
	{
		D3DXTextures::iterator itTex, endTex = m_textures.end();
		for (itTex = m_textures.begin(); itTex != endTex; ++itTex)
		{
			if (itTex->d3dTex == tex)
			{
				if (--((*itTex).ref) < 1)
				{
					(*itTex).d3dTex->Release();
					(*itTex).d3dTex = 0;
					itTex = m_textures.erase(itTex);
				}
				break;
			}
		}
	}

	RenderTargetInfo* GetRenderTargetInfo(UINT width)
	{
		RenderTargets::iterator it = m_RTs.find(width);
		if (it != m_RTs.end())
			return &it->second;

		LPDIRECT3DTEXTURE9 tex = 0;
		if (FAILED(m_pd3dDevice->CreateTexture(
			width,
			width,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&tex,
			NULL)))
			return 0;

		LPDIRECT3DSURFACE9 offScreenSurf = 0;
		if (FAILED(m_pd3dDevice->CreateOffscreenPlainSurface(
			width,
			width,
			D3DFMT_A8R8G8B8,
			D3DPOOL_SYSTEMMEM,
			&offScreenSurf,
			NULL)))
		{
			tex->Release();
			return 0;
		}

		RenderTargetInfo rti;
		rti.rt = tex;
		rti.offscreenSurf = offScreenSurf;
		m_RTs.insert(RenderTargets::value_type(width, rti));
		return &m_RTs[width];
	}

    LPDIRECT3DSURFACE9 GetD3DDepthSurface()
    {
        return m_d3dDepthSurf;
    }

    LPD3DXSPRITE GetD3DXSprite()
    {
        return m_sprite;
    }

protected:
    Font3DManager()
    {
        m_sprite = 0;
        m_d3dDepthSurf = 0;
    }
    Font3DManager(const Font3DManager&);
    Font3DManager& operator= (const Font3DManager&);

private:
    static Font3DManager* m_pInst;

    LPDIRECT3DDEVICE9 m_pd3dDevice;

    typedef std::list<RTTFont*> Font3DList;
    Font3DList m_font3DList;

    struct FontInfo
    {
#ifdef UNICODE
        std::wstring font;
#else
        std::string font;
#endif
		int fontindex;
        int fontSize;
        BOOL bold;
        BOOL italic;

        LPD3DXFONT d3dFont;

        FontInfo() { d3dFont = 0; }

        bool operator< (const FontInfo& v) const
        {
            return font < v.font &&
                fontSize < v.fontSize &&
                bold < v.bold &&
                v.italic < italic;
        }

        bool operator> (const FontInfo& v) const
        {
            return !operator<(v);
        }

        bool operator== (const FontInfo& v) const
        {
            return font == v.font &&
                fontSize == v.fontSize &&
                bold == v.bold &&
                v.italic == italic;
        }
    };

    struct TextInfo 
    {
#ifdef UNICODE
        std::wstring text;
#else
        std::string text;
#endif
		UINT width;

		std::vector<D3DXCOLOR> colors;

        LPDIRECT3DTEXTURE9 d3dTex;

		int ref;

        TextInfo() { width = 0; d3dTex = 0; ref = 1; }

        bool operator< (const TextInfo& v) const
        {
            return text < v.text && width < v.width;
        }

        bool operator> (const TextInfo& v) const
        {
            return !operator<(v);
        }

        bool operator== (const TextInfo& v) const
        {
            return text == v.text && width == v.width && colors == v.colors;
        }
    };

    typedef std::list<FontInfo> D3DXFonts;
    D3DXFonts m_fonts;

    typedef std::list<TextInfo> D3DXTextures;
    D3DXTextures m_textures;

	typedef std::map<size_t, RenderTargetInfo> RenderTargets;
	RenderTargets m_RTs;

    LPD3DXSPRITE m_sprite;
    LPDIRECT3DSURFACE9 m_d3dDepthSurf;
};