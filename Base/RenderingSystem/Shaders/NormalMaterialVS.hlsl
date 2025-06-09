#include"Common.hlsli"

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT result;
    //頂点の位置を変換
    float4 pos = float4(input.Pos.xyz, 1.0f);
	//ワールド変換
    pos = mul(pos, mat);
	//ビュー変換
    pos = mul(pos, View);
	//射影変換
    pos = mul(pos, Projection);
	//ピクセルシェーダに渡す変数に設定
    result.Pos = pos;
	//ライティング
    result.Normal = mul(input.Normal, (float3x3) mat);
    result.Normal = normalize(result.Normal);
	//テクスチャUV
    result.Tex = input.Tex;
    return result;
}