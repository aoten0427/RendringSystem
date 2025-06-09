#include"pch.h"
#include"RenderingSystem.h"
#include"Base/RenderingSystem/Material/MaterialFactory.h"
#include"Base/RenderingSystem/RenderData/RenderDatas.h"
#include"Base/RenderingSystem/Material/MaterialManager.h"
#include"Base/RenderingSystem/Material/IMaterial.h"
#include"Base/Component/Model/Model3D.h"
#include"Base/Camera/Camera.h"
#include"Base/RenderingSystem/RenderingPass/ForwardRenderingPass.h"

RenderingSystem::RenderingSystem(ID3D11Device* device)
	:
	m_device{device}
{
	m_renderData = std::make_unique<RenderDatas>();

	m_materialManager = std::make_unique<MaterialManager>();

	m_commonBuffer = std::make_unique<ConstantBuffer<CommonBuffer>>(device);

	m_renderingPass.push_back(std::make_unique<ForwardRenderingPass>(device));
}

RenderingSystem::~RenderingSystem()
{

}

void RenderingSystem::AddInstance(Model3D* model)
{
	////既に登録されているか検索
	//auto itr = std::find_if(m_models.begin(), m_models.end(), [&](Model3D* pmodel) {
	//	return pmodel == model;
	//});

	DirectX::Model* mesh = model->GetModel();

	//マテリアルがなければ新しいものを生成する
	IMaterial* material = model->GetMaterial();
	if (material == nullptr)
	{
		//モデルのメッシュが登録されているか検索
		if (m_modelNormalMaterial.find(mesh) == m_modelNormalMaterial.end())
		{
			//新しいものを生成
			material = m_materialManager->AddMaterial(MaterialFactory::GetInstance()->CreateMaterial("Normal", m_device));
			//メッシュと登録
			m_modelNormalMaterial[mesh] = material;
		}
		else
		{
			material = m_modelNormalMaterial[mesh];
		}
		model->SetMaterial(material);
	}

	m_renderData->AddInstance(material, mesh, model->GetpMatrix());
}

void RenderingSystem::Render(ID3D11DeviceContext* context, DirectX::DX11::CommonStates* states, Camera& camera)
{
	//コモンバッファの更新
	CommonBuffer cb;
	cb.view = camera.GetViewMatrix().Transpose();
	cb.projection = camera.GetProjectionMatrix().Transpose();
	m_commonBuffer->SetData(cb);
	m_commonBuffer->Update(context);
	ID3D11Buffer* pWorldBuffer = m_commonBuffer->GetBuffer();
	context->VSSetConstantBuffers(0, 1, &pWorldBuffer);
	context->PSSetConstantBuffers(0, 1, &pWorldBuffer);

	for (auto& pass : m_renderingPass)
	{
		pass->Render(context, states, camera, *m_renderData);
	}
	
}


