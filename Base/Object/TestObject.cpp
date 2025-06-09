#include"pch.h"
#include"TestObject.h"
#include"Base/Component/Model/Model3D.h"
#include"Base/RenderingSystem/Material/MaterialFactory.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Scene/Scene.h"

TestObject::TestObject(Scene* scene):Object(scene)
{
	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();

	auto testMaterial = MaterialFactory::GetInstance()->CreateMaterial("Normal",device);

	auto model = AddComponent<Model3D>(this);
	model->LoadModel("Box");
}
