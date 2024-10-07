struct VS_IN
{
    float4 pos : POSITION0;
    float4 col : COLOR0;
    float4 norm : NORMAL0;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
    float4 norm : NORMAL;
    float4 worldPos : W_POSITION;
};

cbuffer ConstantBuffer : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Proj;
};


cbuffer LightBuffer : register(b1)
{
    float3 Direction;
    float Ambient;
    
    float4 CameraPos;
};

PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    
    output.worldPos = mul(World, input.pos);
    output.pos = mul(Proj, mul(View, output.worldPos));
    
    output.col = input.col;
    
    output.norm = mul(World, input.norm);

    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
    
    float diffuse = max(0.0f, dot(Direction, input.norm.xyz));
    float specular = pow(max(0.0f, dot(normalize(CameraPos.xyz - input.worldPos.xyz / input.worldPos.w), reflect(-Direction, input.norm.xyz))), 32);
    
    float4 col = input.col;
#ifdef TEST
	if (input.pos.x > 400) col = TCOLOR;
#endif
    return col * (diffuse + Ambient + specular);
}