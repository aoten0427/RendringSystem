#pragma once

class Camera;
class RenderDatas;

class IRenderingStrategy
{
public:
	virtual ~IRenderingStrategy() = default;

	virtual void Render(ID3D11DeviceContext* context,
		DirectX::DX11::CommonStates* states,
		Camera& camera,
		RenderDatas& renderdata) = 0;
};