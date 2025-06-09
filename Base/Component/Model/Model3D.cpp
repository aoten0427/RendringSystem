#include"pch.h"
#include"Model3D.h"
#include"Base/Object/Object.h"
#include"Base/Scene/Scene.h"
#include"Base/Resources/GameResources.h"
#include"Base/RenderingSystem/RenderingSystem.h"
#include"Base/Object/Object.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/RenderingSystem/Material/IMaterial.h"


Model3D::Model3D(Object* object):Component(object)
	,
	m_renderingSystem{nullptr},
	m_model{nullptr},
	m_material{nullptr}
{
	//レンダリングシステムを取得
	m_renderingSystem = object->GetScene()->GetRenderingSystem();
}

void Model3D::LoadModel(const std::string& name)
{
	m_model = GameResources::GetInstance()->GetModel(name);
	m_renderingSystem->AddInstance(this);
}

DirectX::SimpleMath::Matrix& Model3D::GetMatrix()
{
	m_worldMatrix = m_loaclMatrix * GetObject()->GetTransform()->GetWorldMatrix();
	return m_worldMatrix;
}

const DirectX::SimpleMath::Matrix* Model3D::GetpMatrix()
{
	return &m_worldMatrix;
}

void Model3D::Setmaterial(std::unique_ptr<IMaterial> material)
{
	
}

