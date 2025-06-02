#include"pch.h"
#include"DebugScene.h"
#include"Base/Camera/DebugCamera.h"

DebugScene::DebugScene(CommonResources* resoureces):Scene(resoureces,"Debug")
{
	m_camera = AddObject<DebugCamera>(this);
}
