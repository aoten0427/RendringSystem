// ================================================================ 
// �t�@�C���� : Scene.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �V�[�����N���X
// ================================================================

#include "pch.h"
#include "Scene.h"
#include "Base/CommonResources.h"
#include "DeviceResources.h"
#include "Base/Object/Object.h"
#include "Base/Object/UnbreakableManager.h"
#include "Base/Scene/SceneState.h"
#include "Base/Camera/Camera.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
Scene::Scene(CommonResources* resources,std::string name)
	:
	m_name{name},
	m_nextSceneID{SceneID::NONE},
	m_commonResources{nullptr},
	m_objects{},
	m_pendingObjects{},
	m_updating{ false },
	m_isObjectDestroy{false},
	m_state{nullptr}
{
	assert(resources);
	m_commonResources = resources;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//�e�}�l�[�W���[����
	//�X�e�[�g�쐬
	m_state = AddObject<SceneState>(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Scene::~Scene()
{
	for (auto& object : m_objects)
	{
		object->Finalize();
	}
	m_objects.clear();
	m_pendingObjects.clear();
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">�R�������\�[�X</param>
void Scene::Initialize()
{
	
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void Scene::Update(float deltaTime)
{
	//UI���X�V
	
	//�X�V�t���O��true��
	m_updating = true;
	//�I�u�W�F�N�g���A�b�v�f�[�g
	for (auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
	//��j��I�u�W�F�N�g�A�b�v�f�[�g
	UnbreakableManager::GetInstance()->Update(deltaTime);
	//�V�[���ʃA�b�v�f�[�g
	SceneUpdate(deltaTime);
	//�X�V�t���O��false��
	m_updating = false;

	//���W�b�h�{�f�B�A�Փ˔�����A�b�v�f�[�g
	if (GetState() == State::PLAY)
	{
		
	}
	

	//�J�����X�V
	GetCamera()->CalculationView();

	//�ۗ��I�u�W�F�N�g���X�V�I�u�W�F�N�g�ֈړ�
	std::move(m_pendingObjects.begin(), m_pendingObjects.end(), std::back_inserter(m_objects));
	m_pendingObjects.clear();

	//�I�u�W�F�N�g�폜
	RemoveObject();

	//��Ԃ̍X�V
	m_state->ChangeState();
}

/// <summary>
/// �`��
/// </summary>
void Scene::Render()
{

}

/// <summary>
/// �I������
/// </summary>
void Scene::Finalize()
{

}

/// <summary>
/// �I�u�W�F�N�g�폜
/// </summary>
void Scene::RemoveObject()
{
	//�폜�v�����Ȃ���ΕԂ�
	if (!m_isObjectDestroy)return;
	//�폜�v�f���폜
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [&]
	(std::unique_ptr<Object>& obj) {
			return obj->GetIsDestroy();
		}),m_objects.end());
	//�폜�v�����I�t��
	m_isObjectDestroy = false;
}

/// <summary>
/// ��Ԑ؂�ւ�
/// </summary>
/// <param name="state">�ύX�X�e�[�g��</param>
void Scene::ChangeState(Scene::State state)
{
	m_state->ChangeState(state);
}

/// <summary>
/// ��Ԃ�Ԃ�
/// </summary>
/// <returns>���݂̏��</returns>
Scene::State Scene::GetState() const
{
	return m_state->GetState();
}



