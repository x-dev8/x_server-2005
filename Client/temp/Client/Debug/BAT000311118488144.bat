@echo off
cd E:\Dev\x_server-2005\Client\\Client\Source\Scripts\tolua_pkg
//E:\Dev\x_server-2005\Client\\..\Contrib\Bin\tolua++\tolua++ -1 -H client_tolua.h -o E:\Dev\x_server-2005\Client\\Client\Source\Scripts\client_tolua.cpp compile.pkg

md  E:\Dev\x_server-2005\Client\\..\Bin\Client\Data\Shader
md  E:\Dev\x_server-2005\Client\\..\Bin\Client\Data\Shader\PostProcess
attrib -r E:\Dev\x_server-2005\Client\\..\Bin\Client\Data\Shader\*.fxo
attrib -r E:\Dev\x_server-2005\Client\\..\Bin\Client\Data\Shader\PostProcess\*.fxo
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/Instancing.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/Instancing.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/Scene.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/Scene.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /LD /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/TerrainBlender.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/TerrainBlender.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/World.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/World.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/RenderObject.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/RenderObject.fx

E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_ColorBloomH.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/PP_ColorBloomH.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_ColorBloomV.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/PP_ColorBloomV.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_ColorBrightPass.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/PP_ColorBrightPass.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_ColorCombine4.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/PP_ColorCombine4.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_ColorDownFilter4.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/PP_ColorDownFilter4.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_ColorUpFilter4.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/PP_ColorUpFilter4.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /LD /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_LightShaft.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/PP_LightShaft.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_DofCombine.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/PP_DofCombine.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_LightShaft_Pre.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/PP_LightShaft_Pre.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/Quad.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/Quad.fx
E:\Dev\x_server-2005\Client\\..\Contrib\Bin\fxc.exe /T fx_2_0 /Fo E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/PostProcess/PP_Hdr.fxo e:\Dev\x_server-2005\Client\Client\/Source/Shader/PostProcess/Hdr.fx
xcopy /AEFRSY "e:\Dev\x_server-2005\Client\Client\/Source/Shader/*.hlsl" "E:\Dev\x_server-2005\Client\/../Bin/Client/Data/Shader/"


if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: A tool returned an error code from "Performing Pre-Build Event..."
exit 1
:VCEnd