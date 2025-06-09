#include"pch.h"
#include"InstancingRenderStrategy.h"
#include"Base/RenderingSystem/Material/InstancingMaterial.h"
#include"Base/RenderingSystem/RenderData/RenderDatas.h"

InstancingRenderStrategy::InstancingRenderStrategy(ID3D11Device* device)
{

}

void InstancingRenderStrategy::Render(ID3D11DeviceContext* context, DirectX::DX11::CommonStates* states, Camera& camera, RenderDatas& renderdata)
{
    auto& renderdatas = renderdata.GetRenderData();

    SetupRenderStates(context,states);

    for (auto& data : renderdatas)
    {
        IInstancing* instancingMaterial = dynamic_cast<IInstancing*>(data.m_material);
        if (!instancingMaterial)return;

        if (data.m_matrixs.empty())continue;
        // 各メッシュを描画
        for (const auto& mesh : data.m_model->meshes)
        {
            for (const auto& meshPart : mesh->meshParts)
            {
                // インスタンシング用のバインド
                instancingMaterial->BindInstanced(context, meshPart.get(),data.m_matrixs);

                // インスタンシング描画
                context->DrawIndexedInstanced(meshPart->indexCount,
                    static_cast<UINT>(data.m_matrixs.size()), 0, 0, 0);
            }
        }
        
        data.m_material->Clean(context);
    }
}

void InstancingRenderStrategy::SetupRenderStates(ID3D11DeviceContext* context, DirectX::DX11::CommonStates* states)
{
    context->OMSetBlendState(states->Opaque(), nullptr, 0xffffffff);
    context->OMSetDepthStencilState(states->DepthDefault(), 0);

    ID3D11SamplerState* sampler = states->LinearWrap();
    context->PSSetSamplers(0, 1, &sampler);

    context->RSSetState(states->CullNone());
}
