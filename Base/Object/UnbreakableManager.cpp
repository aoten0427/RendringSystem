// ================================================================ 
// �t�@�C���� : UnbreakableManager.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �V�[�����܂����ł��j�󂳂�Ȃ��I�u�W�F�N�g���Ǘ�
// ================================================================
#include"pch.h"
#include"UnbreakableManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UnbreakableManager::UnbreakableManager()
	:
	m_objects{}
{
}



/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void UnbreakableManager::Update(float deltatime)
{
	for (auto& object : m_objects)
	{
		object.second->Update(deltatime);
	}
}

/// <summary>
/// �폜����
/// </summary>
void UnbreakableManager::Delete()
{
	for (auto& object : m_objects)
	{
		object.second->Finalize();
	}
	m_objects.clear();
}

/// <summary>
/// �V�[���؂�ւ��C�x���g
/// </summary>
/// <param name="scene">�ؑ֌�V�[��</param>
void UnbreakableManager::LoadScene(Scene* scene)
{
	for (auto& object : m_objects)
	{
		//�I�u�W�F�N�g�ɃV�[����o�^
		object.second->SetScene(scene);
		//�V�[���؂�ւ��C�x���g
		object.second->LoadScene(scene);
	}
}
