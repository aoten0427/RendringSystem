#include"pch.h"
#include"DebugScene.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Camera/DebugCamera.h"
#include"Base/Object/TestObject.h"


DebugScene::DebugScene(CommonResources* resoureces):Scene(resoureces,"Debug")
{
	m_camera = AddObject<DebugCamera>(this);

	AddObject<TestObject>(this);

	auto device = resoureces->GetDeviceResources()->GetD3DDevice();
}
