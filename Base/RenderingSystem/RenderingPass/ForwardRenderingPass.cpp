#include"pch.h"
#include"ForwardRenderingPass.h"
#include"Base/RenderingSystem/RenderData/RenderDatas.h"

ForwardRenderingPass::ForwardRenderingPass(ID3D11Device* device)
{
	m_standardStrategy = std::make_unique<StandardRenderStrategy>(device);
	m_instancingStrategy = std::make_unique<InstancingRenderStrategy>(device);
}

void ForwardRenderingPass::Render(ID3D11DeviceContext* context, DirectX::DX11::CommonStates* states, Camera& camera, RenderDatas& renderdata)
{
	m_standardStrategy->Render(context, states, camera, renderdata);
	m_instancingStrategy->Render(context, states, camera, renderdata);
}
