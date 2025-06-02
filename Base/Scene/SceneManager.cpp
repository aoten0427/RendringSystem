// ================================================================ 
// �t�@�C���� : SceneManager.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �V�[���Ǘ��}�l�[�W��
// ================================================================

#include"pch.h"
#include"SceneManager.h"
#include"Base/CommonResources.h"
#include"Base/Object/UnbreakableManager.h"
#include"DebugScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene{nullptr},
	m_unbreakableManager{nullptr},
	m_commonResources{nullptr}
{
	ShowCursor(false);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
	
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources"�R�������\�[�X></param>
void SceneManager::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	m_unbreakableManager = UnbreakableManager::GetInstance();

	ChangeScene(Scene::SceneID::DEBUG);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void SceneManager::Update(float deltatime)
{
	// �����p�ϐ��F���̃V�[��
	const Scene::SceneID nextSceneID = m_currentScene->GetNextSceneID();
	// �V�[����ύX���Ȃ��Ƃ�
	if (nextSceneID != Scene::SceneID::NONE)
	{
		// �V�[����ύX����Ƃ�
		ChangeScene(nextSceneID);
	}
	//�V�[���A�b�v�f�[�g
	m_currentScene->Update(deltatime);
}

/// <summary>
/// �`��
/// </summary>
void SceneManager::Render()
{
	m_currentScene->Render();
}

/// <summary>
/// �I������
/// </summary>
void SceneManager::Finalize()
{
	//���݉ғ����̃V�[���̑O�ɔ�j��I�u�W�F�N�g������
	m_unbreakableManager->Delete();
	//���݂̃V�[���̍폜
	m_currentScene.reset();
}

/// <summary>
/// �V�[���ύX
/// </summary>
/// <param name="sceneID"></param>
void SceneManager::ChangeScene(Scene::SceneID sceneID)
{
	DeleteScene();
	CreateScene(sceneID);
}

/// <summary>
/// �V�[������
/// </summary>
/// <param name="sceneID">�ύXID</param>
void SceneManager::CreateScene(Scene::SceneID sceneID)
{
	//ID�ɍ��킹�ăV�[���𐶐�
	switch (sceneID)
	{
	case Scene::SceneID::NONE:
		break;
	case Scene::SceneID::TITLE:
		
		break;
	case Scene::SceneID::SELECT:
		
		break;
	case Scene::SceneID::PLAY:
		
		break;
	case Scene::SceneID::RESULT:
		
		break;
	case Scene::SceneID::EDITOR:
		
		break;
	case Scene::SceneID::DEBUG:
		m_currentScene = std::make_unique<DebugScene>(m_commonResources);
		break;
	default:
		assert(!"SceneManager::CreateScene::�V�[���������݂��܂���I");
		break;
	}

	//�V�[����������
	m_currentScene->Initialize();
	//��j��I�u�W�F�N�g�̃��[�h
	m_unbreakableManager->LoadScene(m_currentScene.get());
}

/// <summary>
/// �V�[���폜
/// </summary>
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
	}
}
