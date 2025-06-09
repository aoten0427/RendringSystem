#pragma once

class IMaterial;
class Model3D;
class RenderData;
class MaterialManager;
class RenderDatas;
class Camera;
class IRenderingPass;

#include"Base/Mylib/ConstantBuffer.h"


class RenderingSystem
{
private:
	struct CommonBuffer
	{
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
		DirectX::SimpleMath::Vector4 cameraPosition;
	};
private:
	//デバイス
	ID3D11Device* m_device;
	//登録されているモデル
	std::vector<Model3D*> m_models;
	//モデルと基本マテリアル
	std::unordered_map<DirectX::Model*,IMaterial*> m_modelNormalMaterial;
	//描画データ(モデルとマテリアルを保存)
	std::unique_ptr<RenderDatas> m_renderData;
	//マテリアル管理
	std::unique_ptr<MaterialManager> m_materialManager;
	//
	std::vector<std::unique_ptr<IRenderingPass>> m_renderingPass;
	std::unique_ptr<ConstantBuffer<CommonBuffer>> m_commonBuffer;

	
public:
	RenderingSystem(ID3D11Device* device);
	~RenderingSystem();

	void AddInstance(Model3D* model);

	void Render(ID3D11DeviceContext* context,
		DirectX::DX11::CommonStates* states,
		Camera& camera);
};