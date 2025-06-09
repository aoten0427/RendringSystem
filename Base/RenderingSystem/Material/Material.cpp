#include"pch.h"
#include"Material.h"
#include"Base/RenderingSystem/RenderingConfig.h"

Material::Material()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
void Material::Initialize(ID3D11Device* device)
{
    m_materialBuffer = std::make_unique<ConstantBuffer<MaterialData>>(device);
    InitializeShaders(device);
    InitializeInputLayout(device);
}

/// <summary>
/// 描画情報を設定
/// </summary>
/// <param name="context"></param>
void Material::Bind(ID3D11DeviceContext* context)
{
    // シェーダーの設定
    context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
    context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

    // 入力レイアウトの設定
    context->IASetInputLayout(m_inputLayout.Get());

    // 定数バッファの更新と設定
    m_materialBuffer->Update(context);
    ID3D11Buffer* pConstantBuffer = m_materialBuffer->GetBuffer();
    context->VSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, &pConstantBuffer);
    context->PSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, &pConstantBuffer);

    BindTexture(context);
}

/// <summary>
/// データをクリア
/// </summary>
/// <param name="context"></param>
void Material::Clean(ID3D11DeviceContext* context)
{
    // シェーダリソースをクリア
    ID3D11ShaderResourceView* nullSRVs[1] = { nullptr };
    context->PSSetShaderResources(0, (UINT)m_textures.size(), nullSRVs);

    // サンプラーをクリア
    ID3D11SamplerState* nullSamplers[1] = { nullptr };
    context->PSSetSamplers(RenderingConfig::SAMPLER_SLOT, 1, nullSamplers);

    // 定数バッファをクリア
    ID3D11Buffer* nullBuffers[1] = { nullptr };
    context->VSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, nullBuffers);
    context->PSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, nullBuffers);

    // シェーダをクリア
    context->VSSetShader(nullptr, nullptr, 0);
    context->PSSetShader(nullptr, nullptr, 0);
    context->IASetInputLayout(nullptr);
}

/// <summary>
/// テクスチャをセット
/// </summary>
/// <param name="context"></param>
void Material::BindTexture(ID3D11DeviceContext* context)
{
    if (m_textures.empty())return;
    context->PSSetShaderResources(0, (UINT)m_textures.size(),m_textures.data()->ReleaseAndGetAddressOf());
}
