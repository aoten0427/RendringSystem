#pragma once
#include"IRenderingStrategy.h"
#include"Base/Mylib/ConstantBuffer.h"

class InstancingRenderStrategy :public IRenderingStrategy
{
private:
public:
	InstancingRenderStrategy(ID3D11Device* device);
	virtual ~InstancingRenderStrategy() = default;

	void Render(ID3D11DeviceContext* context,
		DirectX::DX11::CommonStates* states,
		Camera& camera,
		RenderDatas& renderdata);
private:
	void SetupRenderStates(ID3D11DeviceContext* context, DirectX::DX11::CommonStates* states);
};