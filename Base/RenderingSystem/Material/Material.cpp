#include"pch.h"
#include"Material.h"
#include"Base/RenderingSystem/RenderingConfig.h"

Material::Material()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="device"></param>
void Material::Initialize(ID3D11Device* device)
{
    m_materialBuffer = std::make_unique<ConstantBuffer<MaterialData>>(device);
    InitializeShaders(device);
    InitializeInputLayout(device);
}

/// <summary>
/// �`�����ݒ�
/// </summary>
/// <param name="context"></param>
void Material::Bind(ID3D11DeviceContext* context)
{
    // �V�F�[�_�[�̐ݒ�
    context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
    context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

    // ���̓��C�A�E�g�̐ݒ�
    context->IASetInputLayout(m_inputLayout.Get());

    // �萔�o�b�t�@�̍X�V�Ɛݒ�
    m_materialBuffer->Update(context);
    ID3D11Buffer* pConstantBuffer = m_materialBuffer->GetBuffer();
    context->VSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, &pConstantBuffer);
    context->PSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, &pConstantBuffer);

    BindTexture(context);
}

/// <summary>
/// �f�[�^���N���A
/// </summary>
/// <param name="context"></param>
void Material::Clean(ID3D11DeviceContext* context)
{
    // �V�F�[�_���\�[�X���N���A
    ID3D11ShaderResourceView* nullSRVs[1] = { nullptr };
    context->PSSetShaderResources(0, (UINT)m_textures.size(), nullSRVs);

    // �T���v���[���N���A
    ID3D11SamplerState* nullSamplers[1] = { nullptr };
    context->PSSetSamplers(RenderingConfig::SAMPLER_SLOT, 1, nullSamplers);

    // �萔�o�b�t�@���N���A
    ID3D11Buffer* nullBuffers[1] = { nullptr };
    context->VSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, nullBuffers);
    context->PSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, nullBuffers);

    // �V�F�[�_���N���A
    context->VSSetShader(nullptr, nullptr, 0);
    context->PSSetShader(nullptr, nullptr, 0);
    context->IASetInputLayout(nullptr);
}

/// <summary>
/// �e�N�X�`�����Z�b�g
/// </summary>
/// <param name="context"></param>
void Material::BindTexture(ID3D11DeviceContext* context)
{
    if (m_textures.empty())return;
    context->PSSetShaderResources(0, (UINT)m_textures.size(),m_textures.data()->ReleaseAndGetAddressOf());
}
