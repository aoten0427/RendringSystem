#include"pch.h"
#include"InstancingMaterial.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> InstancingMaterial::INSTANCE_INPUT_LAYOUT =
{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TANGENT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
};

InstancingMaterial::InstancingMaterial()
    :
    m_instanceVertexShader{nullptr},
    m_instanceInputLayout{nullptr}
{

}

void InstancingMaterial::Initialize(ID3D11Device* device, int maxInstances)
{
    m_maxInstances = maxInstances;
    CreateInstanceBuffer(device);
    InitializeInstanceShaders(device);
    InitializeInstanceInputLayout(device);
}

void InstancingMaterial::BindInstanced(ID3D11DeviceContext* context, DirectX::DX11::ModelMeshPart* part,std::vector<const DirectX::SimpleMath::Matrix*>& worlds)
{
    if (worlds.empty())return;

    // インスタンスデータを設定
    SetInstance(context, worlds);

    // 頂点バッファとインスタンスバッファを設定
    ID3D11Buffer* buffers[2] = { part->vertexBuffer.Get(), m_instanceBuffer.Get() };
    UINT strides[2] = { part->vertexStride, sizeof(DirectX::SimpleMath::Matrix) };
    UINT offsets[2] = { 0, 0 };

    context->IASetVertexBuffers(0, 2, buffers, strides, offsets);
    context->IASetIndexBuffer(part->indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // インスタンシング用シェーダーの設定
    context->VSSetShader(m_instanceVertexShader.Get(), nullptr, 0);
    context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
    context->IASetInputLayout(m_instanceInputLayout.Get());

    BindTexture(context);
    //auto mbuffer = 
    //// 定数バッファの更新
    //mbuffer->UpdateIfDirty(context);
    //ID3D11Buffer* pConstantBuffer = mbuffer->GetBuffer();
    //context->VSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, &pConstantBuffer);
    //context->PSSetConstantBuffers(RenderingConfig::MATERIAL_CBUFFER_SLOT, 1, &pConstantBuffer);
}

void InstancingMaterial::SetInstance(ID3D11DeviceContext* context, const std::vector<const DirectX::SimpleMath::Matrix*>& worlds)
{
    if (worlds.empty() || !context || !m_instanceBuffer) return;

    int numInstances = std::min(m_maxInstances, static_cast<int>(worlds.size()));

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    context->Map(m_instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    DirectX::SimpleMath::Matrix* instanceData =
        static_cast<DirectX::SimpleMath::Matrix*>(mappedResource.pData);

    for (int i = 0; i < numInstances; ++i) {
        instanceData[i] = *worlds[i];
    }

    context->Unmap(m_instanceBuffer.Get(), 0);
}

void InstancingMaterial::CreateInstanceBuffer(ID3D11Device* device)
{
    D3D11_BUFFER_DESC instanceBufferDesc = {};
    instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    instanceBufferDesc.ByteWidth = sizeof(DirectX::SimpleMath::Matrix) * m_maxInstances;
    instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    instanceBufferDesc.MiscFlags = 0;
    instanceBufferDesc.StructureByteStride = 0;

    device->CreateBuffer(&instanceBufferDesc, nullptr, &m_instanceBuffer);
}
