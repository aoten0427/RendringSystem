#pragma once

class IInstancing
{
public:
    virtual ~IInstancing() = default;

    virtual void Initialize(ID3D11Device* device, int maxInstances) = 0;
    virtual void BindInstanced(ID3D11DeviceContext* context,
        DirectX::DX11::ModelMeshPart* part,
        std::vector<const DirectX::SimpleMath::Matrix*>& worlds) = 0;
    virtual bool SupportsInstancing() const = 0;
    virtual int GetMaxInstances() const = 0;
};