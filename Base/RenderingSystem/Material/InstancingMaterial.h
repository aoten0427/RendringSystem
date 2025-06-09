#pragma once
#include "Material.h"
#include "IInstancing.h"
#include "Base/Mylib/ConstantBuffer.h"
#include <vector>

class InstancingMaterial : public Material, public IInstancing
{
public:
    //インスタンシング用インプットレイアウト
    static const std::vector<D3D11_INPUT_ELEMENT_DESC> INSTANCE_INPUT_LAYOUT;
protected:
    //インスタンシング用頂点シェーダー
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_instanceVertexShader;
    //インスタンシング用インプットレイアウト
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_instanceInputLayout;
    //インスタンシング用バッファ
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_instanceBuffer;
    //最大インスタンス数
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
