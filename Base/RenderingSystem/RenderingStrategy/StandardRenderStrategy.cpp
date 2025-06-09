#include"pch.h"
#include"StandardRenderStrategy.h"
#include"DeviceResources.h"
#include"Base/RenderingSystem/RenderData/RenderDatas.h"
#include"Base/RenderingSystem/Material/IMaterial.h"

StandardRenderStrategy::StandardRenderStrategy(ID3D11Device* device)
{
    m_worldBuffer = std::make_unique<ConstantBuffer<WorldBuffer>>(device);
}

void StandardRenderStrategy::Render(ID3D11DeviceContext* context, DirectX::DX11::CommonStates* states, Camera& camera, RenderDatas& renderdata)
{
    auto& renderdatas = renderdata.GetRenderData();

    for (auto& data : renderdatas)
    {
        if (data.m_matrixs.empty())continue;
        data.m_material->Bind(context);
        SetupRenderStates(context, states);
        for (auto& world : data.m_matrixs)
        {
            WorldBuffer worldData;
            worldData.world = world->Transpose();
            m_worldBuffer->SetData(worldData);
            m_worldBuffer->Update(context);

            ID3D11Buffer* pWorldBuffer = m_worldBuffer->GetBuffer();
            context->VSSetConstantBuffers(1, 1, &pWorldBuffer);
            context->PSSetConstantBuffers(1, 1, &pWorldBuffer);

            // 各メッシュを描画
            for (const auto& mesh : data.m_model->meshes)
            {
                for (const auto& meshPart : mesh->meshParts)
                {
                    RenderMeshPart(context, meshPart.get(), *world);
                }
            }
        }
        data.m_material->Clean(context);
    }
}

void StandardRenderStrategy::SetupRenderStates(ID3D11DeviceContext* context, DirectX::DX11::CommonStates* states)
{
    context->OMSetBlendState(states->Opaque(), nullptr, 0xffffffff);
    context->OMSetDepthStencilState(states->DepthDefault(), 0);

    ID3D11SamplerState* sampler = states->LinearWrap();
    context->PSSetSamplers(0, 1, &sampler);

    context->RSSetState(states->CullNone());
}

void StandardRenderStrategy::RenderMeshPart(ID3D11DeviceContext* context, DirectX::DX11::ModelMeshPart* meshPart, const DirectX::SimpleMath::Matrix& world)
{
    // 頂点バッファの設定
    UINT stride = sizeof(DirectX::VertexPositionNormalTangentColorTexture);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1,
        meshPart->vertexBuffer.GetAddressOf(), &stride, &offset);

    // インデックスバッファの設定
    context->IASetIndexBuffer(meshPart->indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

    // プリミティブトポロジーの設定
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 描画
    context->DrawIndexed(meshPart->indexCount, 0, 0);
}
