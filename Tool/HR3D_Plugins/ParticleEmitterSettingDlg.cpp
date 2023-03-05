#include "resource.h"
#include <windows.h>
#include "hr3d_Plugins.h"
#include "hr3d_maxinterface.h"
#include "hr3d_maxinterface.h"
#include "particleemittersettingdlg.h"
#include "HR3D_Mdx2Candidate.h"

ParticleEmitterSettingDlg g_particleEmitterSetting;

INT_PTR CALLBACK ParticleEmitterSettingWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return g_particleEmitterSetting.MsgProc( hWnd, uMsg, wParam, lParam );
}

void ParticleEmitterSettingDlg::DefaultSetting()
{
	mComponents.clear();

	Value v;

	// count
	v.i = 20;
	CreateComponent("Count", eCount,eInt,&v,eEditCtrl,IDC_EDIT1 );

	// speed
	v.f = 50.0f;
	CreateComponent("Speed",eSpeed,eFloat,&v,eEditCtrl,IDC_EDIT2 );

	// variation
	v.f = 50;
	CreateComponent("Variation",eVaration,eFloat,&v,eEditCtrl,IDC_EDIT3 );

	// cone angle
	v.f = 0;
	CreateComponent("ConeAngle",eConeAngle,eFloat,&v,eEditCtrl,IDC_EDIT4 );

	// gravity
	v.f = 0.0f;
	CreateComponent("Gravity",eGravity,eFloat,&v,eEditCtrl,IDC_EDIT35 );

	// life
	v.f = 1.0f;
	CreateComponent("Life",eLife,eFloat,&v,eEditCtrl,IDC_EDIT7 );

	// parts, emission rate
	v.f = 5.0f;
	CreateComponent("Parts",eParts,eFloat,&v,eEditCtrl,IDC_EDIT8 );

	// squirt
	v.i = 0;
	CreateComponent("Squirt",eSquirt,eInt,&v,eCheckCtrl,IDC_CHECK1 );

	// In Model Space
	v.i = 0;
	CreateComponent("ParticlesInModelSpace",eParticlesInModelSpace,eInt,&v,eCheckCtrl,IDC_CHECK5 );

	// width
	v.f = 10.0f;
	CreateComponent("Width",eWidth,eFloat,&v,eEditCtrl,IDC_EDIT5 );

	// height
	v.f = 10.0f;
	CreateComponent("Height",eHeight,eFloat,&v,eEditCtrl,IDC_EDIT6 );

	// BlendMode
	strcpy( v.buffer, STRING_ADD );
	CreateComponent("BlendMode",eBlendMode,eString,&v,eComboCtrl,IDC_COMBO4 );

	// SortZ Check Box
	v.i = 0;
	CreateComponent("SortZ",eSortZ,eInt,&v,eCheckCtrl,IDC_CHECK3 );

	// texture filename
	v.buffer[0] = 0;
	CreateComponent("TextureFilename",eTextureName,eString,&v,eEditCtrl,IDC_EDIT10 );

	// row
	v.i = 1;
	CreateComponent("Row",eRow,eInt,&v,eEditCtrl,IDC_EDIT9 );

	// col
	v.i = 1;
	CreateComponent("Col",eCol,eInt,&v,eEditCtrl,IDC_EDIT11 );

	// particle part
	strcpy( v.buffer, STRING_HEAD );
	CreateComponent("ParticlePart",eParticlePart,eString,&v,eComboCtrl,IDC_COMBO3 );

	// tail length
	v.f = 1.0f;
	CreateComponent("TailLength",eTailLength,eFloat,&v,eEditCtrl,IDC_EDIT30 );

	// middle
	v.f = 0.5f;
	CreateComponent("Middle",eMiddle,eFloat,&v,eEditCtrl,IDC_EDIT32 );

	// color start
	v.color[0] = 255;
	v.color[1] = 255;
	v.color[2] = 255;
	CreateComponent("ColorStart",eColorStart,eColor,&v,eColorCtrl,IDC_BUTTON2 );

	// color middle
	v.color[0] = 255;
	v.color[1] = 255;
	v.color[2] = 255;
	CreateComponent("ColorMiddle",eColorMiddle,eColor,&v,eColorCtrl,IDC_BUTTON3 );

	// color end
	v.color[0] = 255;
	v.color[1] = 255;
	v.color[2] = 255;
	CreateComponent("ColorEnd",eColorEnd,eColor,&v,eColorCtrl,IDC_BUTTON4 );

	// alpha start
	v.i = 255;
	CreateComponent("AlphaStart",eAlphaStart,eInt,&v,eEditCtrl,IDC_EDIT12 );

	// alpha middle
	v.i = 255;
	CreateComponent("AlphaMiddle",eAlphaMiddle,eInt,&v,eEditCtrl,IDC_EDIT13 );

	// alpha end
	v.i = 0;
	CreateComponent("AlphaEnd",eAlphaEnd,eInt,&v,eEditCtrl,IDC_EDIT14 );

	// scale start
	v.f = 20.0f;
	CreateComponent("ScaleStart",eScaleStart,eFloat,&v,eEditCtrl,IDC_EDIT15 );

	// scale middle
	v.f = 20.0f;
	CreateComponent("ScaleMiddle",eScaleMiddle,eFloat,&v,eEditCtrl,IDC_EDIT16 );

	// scale end
	v.f = 20.0f;
	CreateComponent("ScaleEnd",eScaleEnd,eFloat,&v,eEditCtrl,IDC_EDIT17 );

	// uv anim interval
	v.i = 5;
	CreateComponent("UVAnimFps",eUVAnimFps,eInt,&v,eEditCtrl,IDC_EDIT34 );

	// life span head uv anim start
	v.i = 0;
	CreateComponent("LifeSpanHeadUVAnimStart",eLifeSpanHeadUVAnimStart,eInt,&v,eEditCtrl,IDC_EDIT18 );

	// life span head uv anim end
	v.i = 0;
	CreateComponent("LifeSpanHeadUVAnimEnd",eLifeSpanHeadUVAnimEnd,eInt,&v,eEditCtrl,IDC_EDIT19 );

	// life span head uv anim repeat
	v.i = 1;
	CreateComponent("LifeSpanHeadUVAnimRepeat",eLifeSpanHeadUVAnimRepeat,eInt,&v,eEditCtrl,IDC_EDIT20 );

	// decay head uv anim start
	v.i = 0; 
	CreateComponent("DecayHeadUVAnimStart",eDecayHeadUVAnimStart,eInt,&v,eEditCtrl,IDC_EDIT21 );

	// decay head uv anim end
	v.i = 0; 
	CreateComponent("DecayHeadUVAnimEnd",eDecayHeadUVAnimEnd,eInt,&v,eEditCtrl,IDC_EDIT22 );

	// decay head uv anim start
	v.i = 1; 
	CreateComponent("DecayHeadUVAnimRepeat",eDecayHeadUVAnimRepeat,eInt,&v,eEditCtrl,IDC_EDIT23 );

	// LifeSpan Tail UV Anim start
	v.i = 0;
	CreateComponent("LifeSpanTailUVAnimStart",eLifeSpanTailUVAnimStart,eInt,&v,eEditCtrl,IDC_EDIT24 );

	// LifeSpan Tail UV Anim end
	v.i = 0;
	CreateComponent("LifeSpanTailUVAnimEnd",eLifeSpanTailUVAnimEnd,eInt,&v,eEditCtrl,IDC_EDIT25 );

	// LifeSpan Tail UV Anim start
	v.i = 1;
	CreateComponent("LifeSpanTailUVAnimRepeat",eLifeSpanTailUVAnimRepeat,eInt,&v,eEditCtrl,IDC_EDIT26 );

	// Decay Tail UV Anim start
	v.i = 0;
	CreateComponent("DecayTailUVAnimStart",eDecayTailUVAnimStart,eInt,&v,eEditCtrl,IDC_EDIT27 );

	// Decay Tail UV Anim end
	v.i = 0;
	CreateComponent("DecayTailUVAnimEnd",eDecayTailUVAnimEnd,eInt,&v,eEditCtrl,IDC_EDIT28 );

	// LifeSpan Tail UV Anim start
	v.i = 1;
	CreateComponent("DecayTailUVAnimRepeat",eDecayTailUVAnimRepeat,eInt,&v,eEditCtrl,IDC_EDIT29 );

	// particle part
	strcpy( v.buffer, STRING_BINDNONE );
	CreateComponent("BindPartName",eBindPartName,eString,&v,eComboCtrl,IDC_COMBO_BINDPARTNAME );

	// lock emitter
	v.i = 0;
	CreateComponent("LockEmitter",eLockEmitter,eInt,&v,eCheckCtrl,IDC_CHECK_LOCKEMITTER );

	// lock emitter
	v.i = 0;
	CreateComponent("XYQuad",eXYQuad,eInt,&v,eCheckCtrl,IDC_CHECK_XYQUAD );

	// use time based cell
	v.i = 0;
	CreateComponent("UseTimeBasedCell",eUseTimeBasedCell,eInt,&v,eCheckCtrl,IDC_CHECK_USETIMEBASEDCELL );

	// seq loop times
	v.i = 1;
	CreateComponent("SeqLoopTimes",eSeqLoopTimes,eInt,&v,eEditCtrl,IDC_EDIT36 );

	// 新增参数

	// 旋转粒子
	v.i = 0;
	CreateComponent("Rotate", eRotate, eInt, &v, eCheckCtrl, IDC_CHECK8);

	// 旋转360度用时, 此处不能为0, 因为除数不能为0, 引擎里要用这个值来作除数
	v.i = 1000;
	CreateComponent("RotateCost", eRotateCost, eInt, &v, eEditCtrl, IDC_EDIT37);

	// 随机方向
	v.i = 0;
	CreateComponent("RandomDir", eRandomDir, eInt, &v, eCheckCtrl, IDC_CHECK9);

	// 跟随发射器变换
	v.i = 0;
	CreateComponent("FollowEmitter", eFollowEmitter, eInt, &v, eCheckCtrl, IDC_CHECK10);

	// 顶点色取反
	v.i = 0;
	CreateComponent("VertexColorInv", eVertexColorInv, eInt, &v, eCheckCtrl, IDC_CHECK14);

	// 随发射方向旋转
	v.i = 0;
	CreateComponent("RotateFollowDir", eRotateFollowDir, eInt, &v, eCheckCtrl, IDC_CHECK15);

	// 随发射方向旋转
	v.i = 0;
	CreateComponent("TailChange", eTailChange, eInt, &v, eCheckCtrl, IDC_CHECK11);
	{
		v.i = 0;
		CreateComponent("TailChangeStart", eTailChangeStart, eInt, &v, eEditCtrl, IDC_EDIT38);

		v.i = 0;
		CreateComponent("TailChangeMiddle", eTailChangeMiddle, eInt, &v, eEditCtrl, IDC_EDIT39);

		v.i = 0;
		CreateComponent("TailChangeEnd", eTailChangeEnd, eInt, &v, eEditCtrl, IDC_EDIT40);
	}

	// XYQuad模式下在世界中放平
	v.i = 1;
	CreateComponent("LaydownInWorld", eLaydownInWorld, eInt, &v, eCheckCtrl, IDC_CHECK12);

	// UV动画随机第1帧
	v.i = 0;
	CreateComponent("RandomFirstCell", eRandomFirstCell, eInt, &v, eCheckCtrl, IDC_CHECK13);

	// 生命随机最大值
	v.i = 0;
	CreateComponent("LifeMax", eLifeMax, eInt, &v, eEditCtrl, IDC_EDIT41);

	// 大小随机最小值
	v.i = 0;
	CreateComponent("ScaleMin", eScaleMin, eInt, &v, eEditCtrl, IDC_EDIT42);

	// 大小随机最大值
	v.i = 0;
	CreateComponent("ScaleMax", eScaleMax, eInt, &v, eEditCtrl, IDC_EDIT43);
}

ParticleEmitterSettingDlg::ParticleEmitterSettingDlg():
	UIComponents(NULL)
{
	DefaultSetting();
};

BOOL ParticleEmitterSettingDlg::SaveToFile( const char* pszFilename )
{
	FILE* fp = fopen( pszFilename, "w" );
	if( !fp )return FALSE;
	for( int i = 0; i < mComponents.size(); i++ )
	{
		Component* c = &mComponents[i];
		switch( c->valueType )
		{
		case eInt:
			fprintf( fp, "\n%s:%ld", c->szName, c->value.i );
			break;
		case eFloat:
			fprintf( fp, "\n%s:%f", c->szName, c->value.f );
			break;
		case eString:
			fprintf( fp, "\n%s:%s", c->szName, c->value.buffer );
			break;
		}
	}
	fclose( fp );
	return TRUE;
}

LRESULT	ParticleEmitterSettingDlg::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_INITDIALOG:
		mhWnd = hWnd;
		//DefaultSetting();
		LoadFromNode( GetMaxIP()->GetSelectedNode( 0 ) );
		RefreshAllComponentUI();
		{
			SIZE screenSize = { 0, 0 };
			screenSize.cx = ::GetSystemMetrics(SM_CXSCREEN);
			screenSize.cy = ::GetSystemMetrics(SM_CYSCREEN);

			RECT rcWnd;
			::GetWindowRect(hWnd, &rcWnd);

			rcWnd.left = (screenSize.cx - rcWnd.right) / 2;
			rcWnd.top = (screenSize.cy - rcWnd.bottom) / 2;

			// 窗口居中
			::SetWindowPos(hWnd, NULL, rcWnd.left, rcWnd.top, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED);
		}
		break;
	case WM_PAINT:
		{
			RedrawComponentUI();	
		}
		break;
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDC_BUTTON_SAVEEMITTERSETTING:
			{
				GetAllComponentValue();
				SaveToFile( "d:\\1.txt");
				INode* pNode = GetMaxIP()->GetSelectedNode( 0 );
				if( pNode )
				{
					SaveToNode( pNode );
				}
				return 0;
			}
			break;
		case IDC_BUTTON1:
			{
				static TCHAR filter[] = TEXT("DDS files (*.dds)\0*.dds\0") TEXT("All Files (*.*)\0*.*\0");
				std::string pszFilename = GetOpenOrSaveFileNameEx( filter, filter);
				if (!pszFilename.empty())
				{
					Component* c = GetComponentById( eTextureName );
					strcpy( c->value.buffer, pszFilename.c_str());
					RefreshComponentUI( c );
				}
			}
			break;
		case IDC_BUTTON2:
		case IDC_BUTTON3:
		case IDC_BUTTON4:
			{
				Component* c = GetComponentByCtrlId( LOWORD(wParam) );
				if( !c )break;
				
				CHOOSECOLOR cc;                 // common dialog box structure 
				static COLORREF acrCustClr[16]; // array of custom colors
				static DWORD rgbCurrent;        // initial color selection

				// Initialize CHOOSECOLOR 
				ZeroMemory(&cc, sizeof(CHOOSECOLOR));
				cc.lStructSize = sizeof(CHOOSECOLOR);
				cc.hwndOwner = mhWnd;
				cc.lpCustColors = (LPDWORD) acrCustClr;
				cc.rgbResult = rgbCurrent;
				cc.Flags = CC_FULLOPEN | CC_RGBINIT;

				rgbCurrent = 
					c->value.color[0]<<16|c->value.color[1]<<8|c->value.color[2];
				if (ChooseColor(&cc)==TRUE) 
				{
					c->value.color[2] = ( cc.rgbResult&0x00ff0000 )>>16;
					c->value.color[1] = ( cc.rgbResult&0x0000ff00 )>>8;
					c->value.color[0] = ( cc.rgbResult&0x000000ff )>>0;
					
				}	
				InvalidateRect( mhWnd, NULL, FALSE );
				//PostMessage( mhWnd, WM_PAINT, 0, 0 );
			}
			break;
		case IDOK:
			EndDialog( hWnd, 0 );
			break;
		case IDCANCEL:
			EndDialog( hWnd, 0 );
			break;
		};
		break;
	};
	return FALSE;
}

void ParticleEmitterSettingDlg::SaveToNode( INode* pNode )
{
	for( int i = 0; i < mComponents.size(); i++ )
	{
		Component* c = &mComponents[i];
		
		switch( c->valueType )
		{
		case eInt:
			pNode->SetUserPropInt( c->szName, c->value.i );
			break;
		case eFloat:
			pNode->SetUserPropFloat( c->szName, c->value.f );
			break;
		case eString:
			pNode->SetUserPropString( c->szName, c->value.buffer );
			break;
		case eColor:
			{
				int color = (int)(c->value.color[0]<<16|c->value.color[1]<<8|c->value.color[2]);

				pNode->SetUserPropInt( c->szName, color );
			}
			break;
		};
	}
}

void ParticleEmitterSettingDlg::LoadFromNode( INode* pNode )
{
	DefaultSetting();
	for( int i = 0; i < mComponents.size(); i++ )
	{
		Component* c = &mComponents[i];
		if( !pNode->UserPropExists( c->szName ) )continue;
		switch( c->valueType )
		{
		case eInt:
			pNode->GetUserPropInt( c->szName, c->value.i );
			break;
		case eFloat:
			pNode->GetUserPropFloat( c->szName, c->value.f );
			break;
		case eString:
			{
				CStr str;
				pNode->GetUserPropString( c->szName, str );
				strcpy( c->value.buffer, str.data() );
			}
			break;
		case eColor:
			{
				int color;
				pNode->GetUserPropInt( c->szName, color );
				DWORD dwColor = (DWORD)color;
				c->value.color[0] = ( dwColor&0x00ff0000 )>>16;
				c->value.color[1] = ( dwColor&0x0000ff00 )>>8;
				c->value.color[2] = ( dwColor&0x000000ff )>>0;

			}
			break;
		};
	}
	//RefreshAllComponentUI();
}

void ParticleEmitterSettingDlg::RefreshAllComponentUI()
{
	InvalidateRect( mhWnd, NULL, FALSE );
	for( int i = 0; i < mComponents.size(); i++ )
	{
		RefreshComponentUI( &mComponents[i] );
	}
}

void ParticleEmitterSettingDlg::RefreshComponentUI( Component* c )
{
	HWND hItem = GetDlgItem( mhWnd, c->ctrlId );
	switch( c->ctrlType )
	{
	case eEditCtrl:
		{
			char s[256];
			switch( c->valueType )
			{
			case eInt:
				sprintf( s, "%ld", c->value.i );
				break;
			case eFloat:
				sprintf( s, "%f", c->value.f );
				break;
			case eString:
				strcpy( s, c->value.buffer );
				break;
			};
			SetWindowText( hItem, s );
		}
		break;
	case eCheckCtrl:
		{
			if( c->value.i )
				Button_SetCheck( hItem, TRUE );
			else
				Button_SetCheck( hItem, FALSE );
		}
		break;
	case eComboCtrl:
		{
			ComboBox_ResetContent( hItem );
			switch( c->id )
			{
			case eBlendMode:
				{
					ComboBox_AddString( hItem, STRING_BLEND );
					ComboBox_AddString( hItem, STRING_ADD );
					ComboBox_AddString( hItem, STRING_MODULATE );
					ComboBox_AddString( hItem, STRING_MOD2X );
					ComboBox_AddString( hItem, STRING_ALPHAKEY );
					ComboBox_SelectString( hItem, 0, c->value.buffer );
				}

				break;
			case eParticlePart:
				{
					ComboBox_AddString( hItem, STRING_HEAD );
					ComboBox_AddString( hItem, STRING_TAIL );
					ComboBox_AddString( hItem, STRING_BOTH );

					ComboBox_SelectString( hItem, 0, c->value.buffer );

				}
				break;
			case eBindPartName:
				{
					ComboBox_AddString( hItem, STRING_BINDNONE );
					ComboBox_AddString( hItem, STRING_BINDLEFTHAND );
					ComboBox_AddString( hItem, STRING_BINDRIGHTHAND );
					ComboBox_AddString( hItem, STRING_BINDLEFTBACK );
					ComboBox_AddString( hItem, STRING_BINDRIGHTBACK );

					ComboBox_SelectString( hItem, 0, c->value.buffer );
				}
				break;
			}

		}
		break;
	case eSpinCtrl:
		break;
	case eColorCtrl:
		{
			InvalidateRect( mhWnd, NULL, FALSE );
		}
		break;
	};
}

BOOL ParticleEmitterSettingDlg::Convert( const char* s, DWORD* value )
{
	if( stricmp( s, STRING_BLEND ) == 0 )
	{
		*value = HR3D_MDX2_BLEND;
		return TRUE;
	}
	if( stricmp( s, STRING_ADD ) == 0  )
	{
		*value = HR3D_MDX2_ADD;
		return TRUE;
	}
	if( stricmp( s, STRING_MODULATE )  == 0 )
	{
		*value = HR3D_MDX2_MODULATE;
		return TRUE;
	}
	if( stricmp( s, STRING_MOD2X ) == 0  )
	{
		*value = HR3D_MDX2_MODULATE2X;
		return TRUE;
	}
	if( stricmp( s, STRING_ALPHAKEY )  == 0 )
	{
		*value = HR3D_MDX2_ALPHAKEY;
		return TRUE;
	}

	if( stricmp( s, STRING_HEAD ) == 0  )
	{
		*value = MEX2_PARTICLE_EMITTER_HEAD;
		return TRUE;
	}
	if( stricmp( s, STRING_TAIL ) == 0  )
	{
		*value = MEX2_PARTICLE_EMITTER_TAIL;
		return TRUE;
	}
	if( stricmp( s, STRING_BOTH ) == 0  )
	{
		*value = MEX2_PARTICLE_EMITTER_BOTH;
		return TRUE;
	}
	return FALSE;
}

void ParticleEmitterSettingDlg::GetSetting(Mex2ParticleEmitterSetting4* pSetting, void *particleEmitter)
{
	HR3D_Mdx2Candidate::ParticleEmitter *pe = (HR3D_Mdx2Candidate::ParticleEmitter *) particleEmitter;
	if (particleEmitter == NULL)
		return;

	Component* c;

	// squirt
	c = GetComponentById( ParticleEmitterSettingDlg::eSquirt );
	if( c->value.i )
		pSetting->dwFlag |= MEX2_PARTICLE_EMITTER_SQUIRT;

	// model space
	c = GetComponentById( ParticleEmitterSettingDlg::eParticlesInModelSpace );
	if( c->value.i )
		pSetting->dwFlag |= MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE;

	// lock emitter
	c = GetComponentById( ParticleEmitterSettingDlg::eLockEmitter );
	if( c->value.i )
		pSetting->dwFlag |= MEX2_PARTICLE_EMITTER_LOCKEMITTER;
	// xy quad
	c = GetComponentById( ParticleEmitterSettingDlg::eXYQuad );
	if( c->value.i )
		pSetting->dwFlag |= MEX2_PARTICLE_EMITTER_XYQUAD;

	// count
	c = GetComponentById( ParticleEmitterSettingDlg::eCount );
	pSetting->nCount = c->value.i;

	// speed
	c = GetComponentById( ParticleEmitterSettingDlg::eSpeed );
	pSetting->fSpeed = c->value.f;

	// varation
	c = GetComponentById( ParticleEmitterSettingDlg::eVaration );
	pSetting->fVariation = c->value.f;

	// cone angle
	c = GetComponentById( ParticleEmitterSettingDlg::eConeAngle );
	pSetting->fConeAngle = c->value.f;

	// gravity
	c = GetComponentById( ParticleEmitterSettingDlg::eGravity );
	pSetting->fGravity = c->value.f;

	// life span
	c = GetComponentById( ParticleEmitterSettingDlg::eLife );
	pSetting->fLifeSpan = c->value.f;

	// emission rate
	c = GetComponentById( ParticleEmitterSettingDlg::eParts );
	pSetting->fEmissionRate = c->value.f;

	// width
	c = GetComponentById( ParticleEmitterSettingDlg::eWidth );
	pSetting->fWidth = c->value.f;

	// height
	c = GetComponentById( ParticleEmitterSettingDlg::eHeight );
	pSetting->fHeight = c->value.f;

	// blend mode
	//pSetting->dwBlendMode = m_dwBlendMode;
	c = GetComponentById( ParticleEmitterSettingDlg::eBlendMode );
	
	Convert( c->value.buffer, &pSetting->dwBlendMode );

	// sort z
	//c = GetComponentById( ParticleEmitterSettingDlg::eSortZ );
	//pSetting->dwFlag |= HR3D_MDX2_SORTBYFARZ;

	// row
	c = GetComponentById( ParticleEmitterSettingDlg::eRow );
	pSetting->nRow = c->value.i;

	// col
	c = GetComponentById( ParticleEmitterSettingDlg::eCol );
	pSetting->nCol = c->value.i;

	// particle part
	c = GetComponentById( ParticleEmitterSettingDlg::eParticlePart );
	//pSetting->dwPart = (DWORD)c->value.i;
	Convert( c->value.buffer, &pSetting->dwPart );

	// tail length
	c = GetComponentById( ParticleEmitterSettingDlg::eTailLength );
	pSetting->fTailLength = c->value.f;

	// middle time
	c = GetComponentById( ParticleEmitterSettingDlg::eMiddle );
	pSetting->fMiddleTime = c->value.f;

	// segment color
	//float sc[9];	// 3vector
	//w.Write( sc, sizeof( float )*9, 1 );
	c = GetComponentById( ParticleEmitterSettingDlg::eColorStart );
	pSetting->nSegmentColor[0][0] = c->value.color[0];
	pSetting->nSegmentColor[0][1] = c->value.color[1];
	pSetting->nSegmentColor[0][2] = c->value.color[2];

	c = GetComponentById( ParticleEmitterSettingDlg::eColorMiddle );
	pSetting->nSegmentColor[1][0] = c->value.color[0];
	pSetting->nSegmentColor[1][1] = c->value.color[1];
	pSetting->nSegmentColor[1][2] = c->value.color[2];

	c = GetComponentById( ParticleEmitterSettingDlg::eColorEnd );
	pSetting->nSegmentColor[2][0] = c->value.color[0];
	pSetting->nSegmentColor[2][1] = c->value.color[1];
	pSetting->nSegmentColor[2][2] = c->value.color[2];

	// alpha start
	c = GetComponentById( ParticleEmitterSettingDlg::eAlphaStart );
	pSetting->nAlpha[0] = c->value.i;

	// alpha middle 
	c = GetComponentById( ParticleEmitterSettingDlg::eAlphaMiddle );
	pSetting->nAlpha[1] = c->value.i;

	// alpha end
	c = GetComponentById( ParticleEmitterSettingDlg::eAlphaEnd );
	pSetting->nAlpha[2] = c->value.i;

	// scale start
	c = GetComponentById( ParticleEmitterSettingDlg::eScaleStart );
	pSetting->fParticleScaling[0] = c->value.f;

	// scale middle
	c = GetComponentById( ParticleEmitterSettingDlg::eScaleMiddle );
	pSetting->fParticleScaling[1] = c->value.f;

	// scale end
	c = GetComponentById( ParticleEmitterSettingDlg::eScaleEnd );
	pSetting->fParticleScaling[2] = c->value.f;

	// uv anim interval
	c = GetComponentById( ParticleEmitterSettingDlg::eUVAnimFps );
	pSetting->dwUVAnimFps = c->value.dw;

	// lifespan head uv anim start
	c = GetComponentById( ParticleEmitterSettingDlg::eLifeSpanHeadUVAnimStart );
	pSetting->dwLifeSpanHeadUVAnim[0] = c->value.i;

	// lifespan head uv anim end
	c = GetComponentById( ParticleEmitterSettingDlg::eLifeSpanHeadUVAnimEnd );
	pSetting->dwLifeSpanHeadUVAnim[1] = c->value.i;

	// lifespan head uv anim repeat
	c = GetComponentById( ParticleEmitterSettingDlg::eLifeSpanHeadUVAnimRepeat );
	pSetting->dwLifeSpanHeadUVAnim[2] = c->value.i;

	// decay head uv anim start
	c = GetComponentById( ParticleEmitterSettingDlg::eDecayHeadUVAnimStart );
	pSetting->dwDecayHeadUVAnim[0] = c->value.i;

	// decay head uv anim end
	c = GetComponentById( ParticleEmitterSettingDlg::eDecayHeadUVAnimEnd );
	pSetting->dwDecayHeadUVAnim[1] = c->value.i;

	// decay head uv anim repeat
	c = GetComponentById( ParticleEmitterSettingDlg::eDecayHeadUVAnimRepeat );
	pSetting->dwDecayHeadUVAnim[2] = c->value.i;

	// lifespan tail uv anim start
	c = GetComponentById( ParticleEmitterSettingDlg::eLifeSpanTailUVAnimStart );
	pSetting->dwLifeSpanTailUVAnim[0] = c->value.i;

	// lifespan tail uv anim end
	c = GetComponentById( ParticleEmitterSettingDlg::eLifeSpanTailUVAnimEnd );
	pSetting->dwLifeSpanTailUVAnim[1] = c->value.i;

	// lifespan tail uv anim repeat
	c = GetComponentById( ParticleEmitterSettingDlg::eLifeSpanTailUVAnimRepeat );
	pSetting->dwLifeSpanTailUVAnim[2] = c->value.i;

	// decay tail uv anim start
	c = GetComponentById( ParticleEmitterSettingDlg::eDecayTailUVAnimStart );
	pSetting->dwDecayTailUVAnim[0] = c->value.i;

	// decay tail uv anim end
	c = GetComponentById( ParticleEmitterSettingDlg::eDecayTailUVAnimEnd );
	pSetting->dwDecayTailUVAnim[1] = c->value.i;

	// decay tail uv anim tail
	c = GetComponentById( ParticleEmitterSettingDlg::eDecayTailUVAnimRepeat );
	pSetting->dwDecayTailUVAnim[2] = c->value.i;

	// 绑定部位
	c = GetComponentById( ParticleEmitterSettingDlg::eBindPartName );
	strcpy( pe->szBindPartName, c->value.buffer );

	// 使用序列帧
	c = GetComponentById( ParticleEmitterSettingDlg::eUseTimeBasedCell );
	pe->bUseTimeBasedCell = c->value.i;

	// 序列帧循环次数
	c = GetComponentById( ParticleEmitterSettingDlg::eSeqLoopTimes );
	pe->nSeqLoopTimes = c->value.i;

	// 新增参数
	
	// 粒子旋转
	c = GetComponentById(ParticleEmitterSettingDlg::eRotate);
	pe->m_bRotateParticle = c->value.i;

	// 旋转360度所需时间
	c = GetComponentById(ParticleEmitterSettingDlg::eRotateCost);
	pe->m_nRotate360DegreeCostTime = c->value.i;

	// 随机方向
	c = GetComponentById(ParticleEmitterSettingDlg::eRandomDir);
	pe->m_bRandomDir = c->value.i;

	// 跟随发射器变换
	c = GetComponentById(ParticleEmitterSettingDlg::eFollowEmitter);
	pe->m_bNoSelfRotate = (c->value.i == 1 ? 0 : 1);

	// 顶点颜色取反
	c = GetComponentById(ParticleEmitterSettingDlg::eVertexColorInv);
	pSetting->bContraryColor = c->value.i;

	// 随发射器方向旋转
	c = GetComponentById(ParticleEmitterSettingDlg::eRotateFollowDir);
	pSetting->bAngleChangeByCone = c->value.i;

	// 拖尾变化
	c = GetComponentById(ParticleEmitterSettingDlg::eTailChange);
	pSetting->bTailLengthChange = c->value.i;
	{
		// 拖尾变化Start
		c = GetComponentById(ParticleEmitterSettingDlg::eTailChangeStart);
		pSetting->fTailLengthChange[0] = c->value.i;

		// 拖尾变化Middle
		c = GetComponentById(ParticleEmitterSettingDlg::eTailChangeMiddle);
		pSetting->fTailLengthChange[1] = c->value.i;

		// 拖尾变化End
		c = GetComponentById(ParticleEmitterSettingDlg::eTailChangeEnd);
		pSetting->fTailLengthChange[2] = c->value.i;
	}

	// XYQuad模式中在世界中放平
	c = GetComponentById(ParticleEmitterSettingDlg::eLaydownInWorld);
	pe->m_bXYInWorldSpace = c->value.i;

	// UV动画随机第1帧
	c = GetComponentById(ParticleEmitterSettingDlg::eRandomFirstCell);
	pe->m_bUVRandomFirstCell = c->value.i;

	// 粒子生命最大值
	c = GetComponentById(ParticleEmitterSettingDlg::eLifeMax);
	pSetting->fLifeSpanMax = c->value.i;

	// 大小变化最小值
	c = GetComponentById(ParticleEmitterSettingDlg::eScaleMin);
	pSetting->fScaleRateMin = c->value.i;

	// 大小变化最大值
	c = GetComponentById(ParticleEmitterSettingDlg::eScaleMax);
	pSetting->fScaleRateMax = c->value.i;
}