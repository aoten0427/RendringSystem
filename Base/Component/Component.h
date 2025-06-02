// ================================================================ 
// �t�@�C���� : Component.h
// �쐬�� : �i�R�ɓV
// ���� :  �R���|�[�l���g���N���X
// ================================================================

#pragma once

class Scene;
class Object;
class CommonResources;

class Component
{
public:
	//�I�u�W�F�N�g�擾
	Object* GetObject() const{ return m_object; }
	//�R�������\�[�X�擾
	CommonResources* GetCommonResources()const { return m_commonResources; }
	//�A�N�e�B�u�t���O�Z�b�g
	void SetActive(bool isactive) { m_isActive = isactive; }
	//�A�N�e�B�u�擾
	bool GetActive() const{ return m_isActive; }
	//�A�b�v�f�[�g�I�[�_�[�擾
	int GetUpdateOrder() const{ return m_updateOrder; }
	//�j��t���O�擾
	bool GetIsDestroy()const { return m_isDestroy; }
private:
	//�����I�u�W�F�N�g
	Object* m_object;
	//�R�������\�[�X
	CommonResources * m_commonResources;
	//�A�N�e�B�u�t���O
	bool m_isActive;
	//�A�b�v�f�[�g�I�[�_�[
	int m_updateOrder;
	//�j��t���O
	bool m_isDestroy;
public:
	//�R���X�g���N�^
	Component(Object* object, int updateOrder = 0);
	//�f�X�g���N�^
	virtual ~Component() = default;
	//�A�b�v�f�[�g
	virtual void Update(float deltatime);
	//�폜
	void Destroy();
	//�V�[���؂�ւ��C�x���g
	virtual void LoadScene(Scene* scene) { UNREFERENCED_PARAMETER(scene); };
};