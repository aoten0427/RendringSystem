#pragma once
#include "Material.h"
#include "IInstancing.h"
#include "Base/Mylib/ConstantBuffer.h"
#include <vector>

class InstancingMaterial : public Material, public IInstancing
{
public:
    //�C���X�^���V���O�p�C���v�b�g���C�A�E�g
    static const std::vector<D3D11_INPUT_ELEMENT_DESC> INSTANCE_INPUT_LAYOUT;
protected:
    //�C���X�^���V���O�p���_�V�F�[�_�[
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_instanceVertexShader;
    //�C���X�^���V���O�p�C���v�b�g���C�A�E�g
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_instanceInputLayout;
    //�C���X�^���V���O�p�o�b�t�@
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_instanceBuffer;
    //�ő�C���X�^���X��
    int m_maxInstances;
    bool m_instancingInitialized = false;

public:
    InstancingMaterial();
    virtual ~InstancingMaterial() = default;

    // IInstancingCapable implementation
    void Initialize(ID3D11Device* device, int maxInstances = 10000);
    void BindInstanced(ID3D11DeviceContext* context,
        DirectX::DX11::ModelMeshPart* part,
        std::vector<const DirectX::SimpleMath::Matrix*>& worlds) override;
    bool SupportsInstancing() const override { return m_instancingInitialized; }
    int GetMaxInstances() const override { return m_maxInstances; }

public:
    virtual void InitializeInstanceShaders(ID3D11Device* device) = 0;
    virtual void InitializeInstanceInputLayout(ID3D11Device* device) = 0;
    void SetInstance(ID3D11DeviceContext* context, const std::vector<const DirectX::SimpleMath::Matrix*>& worlds);

private:
    void CreateInstanceBuffer(ID3D11Device* device);

};
