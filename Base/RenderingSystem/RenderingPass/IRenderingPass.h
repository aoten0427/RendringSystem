#pragma once
class Camera;
class RenderDatas;

class IRenderingPass
{
public:
	virtual ~IRenderingPass() = default;

	virtual void Render(ID3D11DeviceContext* context,
		DirectX::DX11::CommonStates* states,
		Camera& camera,
		RenderDatas& renderdata) = 0;
};