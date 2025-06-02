#pragma once
#include"Scene.h"

class DebugScene :public Scene
{
public:
	//カメラ取得
	Camera* GetCamera()const { return m_camera; }
private:
	//カメラ
	Camera* m_camera;
public:
	DebugScene(CommonResources* resoureces);
	~DebugScene() = default;
	//シーンID取得
	SceneID GetSceneID() { return SceneID::DEBUG; }
};