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
	//�f�o�C�X
	ID3D11Device* m_device;
	//�o�^����Ă��郂�f��
	std::vector<Model3D*> m_models;
	//���f���Ɗ�{�}�e���A��
	std::unordered_map<DirectX::Model*,IMaterial*> m_modelNormalMaterial;
	//�`��f�[�^(���f���ƃ}�e���A����ۑ�)
	std::unique_ptr<RenderDatas> m_renderData;
	//�}�e���A���Ǘ�
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