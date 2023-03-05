
struct OutputCollision_vs
{
	float4 position : POSITION;
};

// vertex shader.
OutputCollision_vs Collision_vs( Input_vs In )
{
	OutputCollision_vs Out = (OutputCollision_vs)0;
	
	Out.position = mul( In.position, worldViewProj );
	
	return Out;
}

// vertex shader.
float4 Collision_ps() : COLOR
{
	return lightColor;
}
