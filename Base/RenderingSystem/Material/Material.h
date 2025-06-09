#pragma once
#include"IMaterial.h"
#include"Base/Mylib/ConstantBuffer.h"

class Material :public IMaterial
{
public:
    //��{�}�e���A���f�[�^
    struct MaterialData
    {
        DirectX::SimpleMath::Vector4 LightDir;
        DirectX::SimpleMath::Vector4 Emissive;
        DirectX::SimpleMath::Vector4 Diffuse;
        DirectX::SimpleMath::Vector4 Specular;
    };
protected:
    //���_�V�F�[�_�[
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
    //�s�N�Z���V�F�[�_
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
    //�C���v�b�g���C�A�E�g
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
    //�g�p�e�N�X�`��
    std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;
    //�}�e���A���o�b�t�@
    std::unique_ptr<ConstantBuffer<MaterialData>> m_materialBuffer;
public:
    //�R���X�g���N�^
    Material();
    //�f�X�g���N�^
    virtual ~Material() = default;
    //������
    void Initialize(ID3D11Device* device);
    //�V�F�[�_�[�ݒ�
    void Bind(ID3D11DeviceContext* context) override;
    //�f�[�^���Z�b�g
    void Clean(ID3D11DeviceContext* context) override;
    //�摜�ݒ�
    void BindTexture(ID3D11DeviceContext* context);
    //�h����V�F�[�_�[�ݒ�
    virtual void InitializeShaders(ID3D11Device* device) = 0;
    //�h����C���v�b�g���C�A�E�g�ݒ�
    virtual void InitializeInputLayout(ID3D11Device* device) = 0;
};
