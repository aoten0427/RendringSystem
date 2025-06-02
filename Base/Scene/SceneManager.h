// ================================================================ 
// �t�@�C���� : SceneManager.h
// �쐬�� : �i�R�ɓV
// ���� :  �V�[���Ǘ��}�l�[�W���[
// ================================================================

#pragma once
#include"Base/Scene/Scene.h"

class CommonResources;
class UnbreakableManager;

class SceneManager
{
private:
	//���݂̃V�[��
	std::unique_ptr<Scene> m_currentScene;
	//��j��I�u�W�F�N�g
	UnbreakableManager* m_unbreakableManager;
	//�R�������\�[�X
	CommonResources* m_commonResources;
public:
	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//������
	void Initialize(CommonResources* resources);
	//�A�b�v�f�[�g
	void Update(float deltatime);
	//�`��
	void Render();
	//�I������
	void Finalize();

private:
	//�V�[���ύX
	void ChangeScene(Scene::SceneID sceneID);
	//�V�[���쐬
	void CreateScene(Scene::SceneID sceneID);
	//�V�[���폜
	void DeleteScene();
};