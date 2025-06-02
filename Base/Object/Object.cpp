// ================================================================ 
// �t�@�C���� : Object.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �I�u�W�F�N�g���N���X
// ================================================================
#include"pch.h"
#include"Object.h"
#include"Base/Scene/Scene.h"
#include"Base/Component/Transform/Transform.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
Object::Object(Scene* scene)
	:
	m_scene{scene},
	m_components{},
	m_transform{nullptr},
	m_isActive{true},
	m_isDestroy{false},
	m_isComponentDestroy{false}
{
	assert(scene);
	m_commonResources = scene->GetCommonResources();
	m_transform = AddComponent<Transform>(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Object::~Object()
{
	m_components.clear();
}



/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Object::Update(float deltatime)
{
	//�R���|�[�l���g�A�b�v�f�[�g
	ComponentUpdate(deltatime);
	//�ʃA�b�v�f�[�g
	ObjectUpdate(deltatime);
	//�R���|�[�l���g�폜
	RemoveComponent();
}

/// <summary>
/// �R���|�[�l���g�A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Object::ComponentUpdate(float deltatime)
{
	for (auto& component : m_components)
	{
		if (!component->GetActive())continue;
		component->Update(deltatime);
	}
}

/// <summary>
/// ���g��j��
/// </summary>
void Object::Destroy()
{
	//�V�[���ɃI�u�W�F�N�g�j��w��
	GetScene()->ObjectDestroyOn();
	//�j��t���O���I����
	m_isDestroy = true;
	//�A�N�e�B�u���I�t
	SetActive(false);
}

/// <summary>
/// �j��R���|�[�l���g�̌����ƍ폜
/// </summary>
void Object::RemoveComponent()
{
	//�j��v�����I�t�Ȃ�p�X
	if (m_isComponentDestroy)return;
	//�폜�v�f���폜
	m_components.erase(std::remove_if(m_components.begin(), m_components.end(), [&]
	(std::unique_ptr<Component>& comp) {
			return comp->GetIsDestroy();
		}), m_components.end());
	//�j��v�����I�t��
	m_isComponentDestroy = true;
}

/// <summary>
/// �����o������
/// </summary>
/// <param name="pushback">�����o����</param>
void Object::PushBack(DirectX::SimpleMath::Vector3 pushback)
{
	m_transform->Translate(pushback);
}

/// <summary>
/// �A�N�e�B�u��ύX
/// </summary>
/// <param name="active">�A�N�e�B�u</param>
void Object::SetActive(bool active)
{
	m_isActive = active;
	//�q�֓`�d
	for (auto& children : m_transform->GetAllChild())
	{
		children->GetObject()->SetActive(active);
	}
	//�R���|�[�l���g
	for (auto& component : m_components)
	{
		component.get()->SetActive(active);
	}
}


