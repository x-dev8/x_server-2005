
texture baseTexture;
float offsetBrightness = 0;
float offsetContrastR = 1;
float offsetContrastG = 1;
float offsetContrastB = 1;

sampler baseSampler =  sampler_state
{
    Texture = <baseTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    //MIPMAPLODBIAS = 0.0f;
};

float4 PixNoLight( float2 Tex : TEXCOORD0 ) : COLOR
{
    return ( tex2D( baseSampler, Tex ) * float4( offsetContrastR, offsetContrastG, offsetContrastB, 1.f ) ) + offsetBrightness;
}

technique RenderQuad
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 PixNoLight();
        ZEnable = false;
        ZWRITEENABLE = false;
        FogEnable = false;
        AlphaBlendEnable = false;
        ALPHATESTENABLE = false;
        CullMode = CCW;
    }
}
