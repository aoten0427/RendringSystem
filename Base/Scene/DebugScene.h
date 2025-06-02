#pragma once
#include"Scene.h"

class DebugScene :public Scene
{
public:
	//�J�����擾
	Camera* GetCamera()const { return m_camera; }
private:
	//�J����
	Camera* m_camera;
public:
	DebugScene(CommonResources* resoureces);
	~DebugScene() = default;
	//�V�[��ID�擾
	SceneID GetSceneID() { return SceneID::DEBUG; }
};