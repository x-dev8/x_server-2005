texture baseTexture; //ԭͼ  ��С���

texture luminance;  //��С�������ͼ
texture bloom1;     //��С���ģ��


texture bloom2;       //�߹�ͨ��ͼ ��Ļ��С��ģ��ͼ
texture ScrSceneTexture; // ��Ļ��С��ԭͼ
texture BloomScrSceneTextrue;

float ScreenW;
float ScreenH;

static const int g_cKernelSize = 13;
float2 PixelKernelH[g_cKernelSize] =
{



    { -6, 0 },
    { -5, 0 },
    { -4, 0 },
    { -3, 0 },
    { -2, 0 },
    { -1, 0 },
    {  0, 0 },
    {  1, 0 },
    {  2, 0 },
    {  3, 0 },
    {  4, 0 },
    {  5, 0 },
    {  6, 0 },

};

float2 PixelKernelV[g_cKernelSize] =
{


    { 0, -6 },
    { 0, -5 },
    { 0, -4 },
    { 0, -3 },
    { 0, -2 },
    { 0, -1 },
    { 0,  0 },
    { 0,  1 },
    { 0,  2 },
    { 0,  3 },
    { 0,  4 },
    { 0,  5 },
    { 0,  6 },
    

};


//��Ļ��С��ģ��ͼ
sampler2D G_SamBloomTexture = sampler_state
{
    Texture = <bloom2>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

//��Ļ��С��ԭͼ
sampler2D G_SamScrScene = sampler_state
{
    Texture = <ScrSceneTexture>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};


sampler2D G_SamScrSceneBloom = sampler_state
{
    Texture = <BloomScrSceneTextrue>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};





//ԭͼ��С���
sampler2D G_SamBaseTexture = sampler_state
{
    Texture = <baseTexture>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};



//ƽ������ͼ
sampler2D G_Samluminance = sampler_state
{
    Texture = <luminance>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};


//�߹�ͨ��ͼ ģ����
sampler2D G_SamBloomTexture0 = sampler_state
{
    Texture = <bloom1>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

static const float rL = 0.27f;
static const float gL = 0.67f;
static const float bL = 0.06f;




//��ƽ������ ����������ԭͼ

float4 luminance_( in float2 Tex : TEXCOORD0 ) : COLOR0
{
    float _Color = 0.1f;  
   
    float4 ScrColor = tex2D( G_SamBloomTexture0, float2(1,1) );  //1x1������ͼ
    float pixLuminace = 0.f;
    pixLuminace += ScrColor.r*rL;
    pixLuminace += ScrColor.g*gL;
    pixLuminace += ScrColor.b*bL;   
    _Color = pixLuminace / 3.f; //��ǰ�������
     
      return float4( _Color,_Color,_Color, 1.0f );
}



//�Ը߹�ͨ��ͼ����ģ�� ����
float4 BrightPassFilterBlurH_(in float2 Tex : TEXCOORD0) : COLOR
{
   float4 Color = 0;
   float x = 1.0f/ScreenW;
    for (int i = 0; i < g_cKernelSize; i++)
    {    
        Color += tex2D( G_Samluminance, Tex + float2(PixelKernelH[i].x*x,0.f));
       
    }

     Color /= g_cKernelSize;
     Color.w = 1;
    return Color;
    //�����ģ��ͼ1��bloom1
}


//����ģ�� ����� ����ͼ��
float4 BrightPassFilterBlurV_(in float2 Tex : TEXCOORD0) : COLOR
{
   float4 Color = 0;
   float x = 1.0f/ScreenH;

    for (int i = 0; i < g_cKernelSize; i++)
    {    
       Color += tex2D( G_SamBloomTexture0, Tex + float2(0.f,PixelKernelV[i].y *x ));
      
    }
     Color /= g_cKernelSize;
     Color.w = 1;
    return Color;
  
}


//��������ȥ�� ����ͼ���
float4 Pix_( float2 Tex : TEXCOORD0 ) : COLOR
{
    float3 ScrColor   = tex2D( G_SamScrScene, Tex ).xyz; //ԭͼ
    
    float3 LBloomColor = tex2D( G_SamBloomTexture, Tex ).xyz;//��ԭͼ��С��ͬ�� �߹�ͨ��ģ��ͼ 
    
    float3 CLuminace  = tex2D( G_Samluminance, Tex ).xyz; //����ͼ
       
    float LBloomPixLuminace = 0.f; //ģ��ͼ������
    LBloomPixLuminace += LBloomColor.r*rL;
    LBloomPixLuminace += LBloomColor.g*gL;
    LBloomPixLuminace += LBloomColor.b*bL;
    LBloomPixLuminace /= 3.f;
   
 
    // float _value =  LBloomPixLuminace - CLuminace.r;
   //  if(_value > 0)
     //ScrColor = (ScrColor) + LBloomColor*_value*2.5f;
     // else
    // ScrColor = (ScrColor)- LBloomColor*abs(_value)*0.5f;
  


 //ScrColor = ScrColor+ max(0.f, LBloomPixLuminace - CLuminace.r)*LBloomColor*3.5f;
 ScrColor = ScrColor+  (LBloomPixLuminace - 0.12f )*LBloomColor*2.f;
  
   
    return float4(ScrColor,1.f);
    
    
  
}


technique TLuminance
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 luminance_();
        ZEnable = false;
        ZWRITEENABLE = false;
        FogEnable = false;
        AlphaBlendEnable = false;
        ALPHATESTENABLE = false;
        CullMode = CCW;
    }
}



technique BrightPassFilterBlurH
{

  pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 BrightPassFilterBlurH_();
        ZEnable = false;
        ZWRITEENABLE = false;
        FogEnable = false;
        AlphaBlendEnable = false;
        ALPHATESTENABLE = false;
        CullMode = CCW;
    }
}


technique BrightPassFilterBlurV
{

  pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 BrightPassFilterBlurV_();
        ZEnable = false;
        ZWRITEENABLE = false;
        FogEnable = false;
        AlphaBlendEnable = false;
        ALPHATESTENABLE = false;
        CullMode = CCW;
    }
}






technique TRenderQuad
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 Pix_();
        ZEnable = false;
        ZWRITEENABLE = false;
        FogEnable = false;
        AlphaBlendEnable = false;
        ALPHATESTENABLE = false;
        CullMode = CCW;
    }
}





