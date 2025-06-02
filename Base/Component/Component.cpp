// ================================================================ 
// �t�@�C���� : Component.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �R���|�[�l���g���N���X
// ================================================================
#include"pch.h"
#include"Component.h"
#include"Base/Object/Object.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
Component::Component(Object* object,int updateorder)
	:
	m_object{object},
	m_isActive{true},
	m_updateOrder{updateorder},
	m_isDestroy{false}
{
	assert(object);
	m_commonResources = object->GetCommonResources();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Component::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

/// <summary>
/// ���g��j��
/// </summary>
void Component::Destroy()
{
	GetObject()->ComponentDestroyOn();
	m_isDestroy = true;
	SetActive(false);
}


