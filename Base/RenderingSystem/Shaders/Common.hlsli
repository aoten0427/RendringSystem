
cbuffer CommonConstBuffer : register(b0)
{
    matrix View;
    matrix Projection;
    float3 CameraPositionWS;
}

cbuffer World : register(b1)
{
    matrix mat;
}

struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Normal : NORMAL;
    float3 Tangetnt : TANGENT;
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
};

struct INSTANCING_INPUT
{
    float4 Pos : POSITION;
    float3 Normal : NORMAL;
    float3 Tangetnt : TANGENT;
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
    float4x4 mat : MATRIX;
    uint InstanceId : SV_InstanceID;
};


struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float2 Tex : TEXCOORD;
};