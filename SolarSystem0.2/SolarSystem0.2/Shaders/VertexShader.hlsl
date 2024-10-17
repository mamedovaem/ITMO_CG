struct VS_IN
{
    float4 pos : POSITION0;
    float4 col : COLOR0;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
};

cbuffer ConstantBuffer : register(b0)
{
    float4x4 MVP;
};

cbuffer ConstantBufferColor : register(b1)
{
    float4 Color1;
};

PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;

    output.pos = mul(MVP, input.pos);
   // output.col = input.col;
    //output.col = ;
    
    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
    return Color1;
//    float4 col = input.col;
//#ifdef TEST
//	if (input.pos.x > 400) col = TCOLOR;
//#endif
//    return col;
}