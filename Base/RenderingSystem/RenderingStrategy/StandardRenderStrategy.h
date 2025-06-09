#pragma once
#include"IRenderingStrategy.h"
#include"Base/Mylib/ConstantBuffer.h"

class StandardRenderStrategy :public IRenderingStrategy
{
private:
	struct WorldBuffer
	{
		DirectX::SimpleMath::Matrix world;
	};

	std::unique_ptr<ConstantBuffer<WorldBuffer>> m_worldBuffer;
public:
	StandardRenderStrategy(ID3D11Device* device);
	virtual ~StandardRenderStrategy() = default;

	void Render(ID3D11DeviceContext* context,
		DirectX::DX11::CommonStates* states,
		Camera& camera,
		RenderDatas& renderdata);

private:
	void SetupRenderStates(ID3D11DeviceContext* context, DirectX::DX11::CommonStates* states);
	void RenderMeshPart(ID3D11DeviceContext* context,
		DirectX::DX11::ModelMeshPart* meshPart,
		const DirectX::SimpleMath::Matrix& world);
};