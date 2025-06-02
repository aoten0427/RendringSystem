// ================================================================ 
// �t�@�C���� : Camera.h
// �쐬�� : �i�R�ɓV
// ���� :  �J�������N���X
// ================================================================

#pragma once
#include"Base/Object/Object.h"


class Camera :public Object
{
public:
	//�v���W�F�N�V����matrix�擾
	virtual const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }
	//�r���[matrix�擾
	virtual const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_view; }
	//���_�擾
	virtual const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }
	//�^�[�Q�b�g�擾
	virtual const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }
	//�������擾
	virtual const DirectX::SimpleMath::Vector3& GetUpPosition() const { return m_up; }
private:
	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	//�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projection;
	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	// �J�����̓��̕���
	DirectX::SimpleMath::Vector3 m_up;
public:
	//�R���X�g���N�^
	Camera(Scene* scene);
	//�f�X�g���N�^
	~Camera()override = default;
	//�r���[�s����v�Z����
	virtual void CalculationView() {};
	//���C�������擾
	DirectX::SimpleMath::Vector3 GetRayDirection()const;
};