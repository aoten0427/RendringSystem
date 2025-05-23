#include"Model.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);


float4 main(PS_INPUT input) : SV_TARGET
{
    //	指定された画像の表示
    float4 color = tex.Sample(samLinear, input.tex);
    
    return color;
}