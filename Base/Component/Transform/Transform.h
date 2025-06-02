// ================================================================ 
// �t�@�C���� : Transform.h
// �쐬�� : �i�R�ɓV
// ���� :  �ʒu�A��]�A�傫��������
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class Transform:public Component
{
private:
	//�|�W�V����
	DirectX::SimpleMath::Vector3 m_position;
	//�X�P�[��
	DirectX::SimpleMath::Vector3 m_scale;
	//��]
	DirectX::SimpleMath::Quaternion m_rotate;
	//matrix
	DirectX::SimpleMath::Matrix m_matrix;
	//matrix�v�Z���f
	bool m_isCompute;
	//�e
	Transform* m_parent;
	//�q��
	std::vector<Transform*> m_children;
public:
	//�R���X�g���N�g
	Transform(Object* object);
	//�f�X�g���N�^
	~Transform() = default;

	//���g�̍s���Ԃ�
	DirectX::SimpleMath::Matrix GetWorldMatrix();
	//���[���hPosition��Ԃ�
	DirectX::SimpleMath::Vector3 GetWorldPosition();
	//���[���hScale��Ԃ�
	DirectX::SimpleMath::Vector3 GetWorldScale();
	//���[���hRotate��Ԃ�
	DirectX::SimpleMath::Quaternion GetWorldRotate();

	//�|�W�V�����Z�b�g
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	//�|�W�V�����Q�b�g
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	//�|�W�V�������ړ�������(���Z)
	void Translate(const DirectX::SimpleMath::Vector3& position);
	//�X�P�[���Z�b�g
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
	//�X�P�[���Q�b�g
	DirectX::SimpleMath::Vector3 GetScale()const { return m_scale; }
	//�傫����ύX����(���Z)
	void TransScale(const DirectX::SimpleMath::Vector3& scale);
	//�傫����ύX����(��Z)
	void TransScale(const float& scale);
	//��]�Z�b�g
	void SetRotate(const DirectX::SimpleMath::Quaternion& roteto);
	//��]�Q�b�g
	DirectX::SimpleMath::Quaternion GetRotate()const { return m_rotate; }
	//��]��ύX����
	//�N�H�[�^�j�I����]
	void TransRotate(const DirectX::SimpleMath::Quaternion& roteto);
	//���Ɗp�x�ŉ�]
	void TransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle);
	//���[�J���̎��Ɗp�x�ŉ�]
	void LocalTransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle);
	//���g�̎p���ɑ΂��鎲�̕�����Ԃ�
	DirectX::SimpleMath::Vector3 GetWorldAxisFromLocal(const DirectX::SimpleMath::Vector3& axis);
	//��]�l���̃|�W�V����
	DirectX::SimpleMath::Vector3 GetRotatePosition();
	//�e���Z�b�g
	void SetParent(Transform* parent);
	//�q���擾
	Transform* GetChild(int num);
	//�S�Ă̎q����Ԃ�
	std::vector<Transform*>& GetAllChild()  { return m_children; };
private:
	//�q���Z�b�g
	void SetChild(Transform* child) { m_children.push_back(child); }
	//�q������
	void ReMoveChild(Transform* child);

	//�e�ݒ莞�̏��ύX
	void CalculationSetParent();
	//�e�������̏��ύX
	void CalculationReMoveParent();
};