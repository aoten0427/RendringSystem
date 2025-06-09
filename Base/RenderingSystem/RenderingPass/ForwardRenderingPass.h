#pragma once
#include"IRenderingPass.h"

#include"Base/RenderingSystem/RenderingStrategy/StandardRenderStrategy.h"
#include"Base/RenderingSystem/RenderingStrategy/InstancingRenderStrategy.h"

class ForwardRenderingPass :public IRenderingPass
{
private:
	std::unique_ptr<StandardRenderStrategy> m_standardStrategy;
	std::unique_ptr<InstancingRenderStrategy> m_instancingStrategy;
public:
	ForwardRenderingPass(ID3D11Device* device);
	virtual ~ForwardRenderingPass() = default;

	void Render(ID3D11DeviceContext* context,
		DirectX::DX11::CommonStates* states,
		Camera& camera,
		RenderDatas& renderdata);
};