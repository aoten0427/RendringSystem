// ================================================================ 
// �t�@�C���� : DebugCamera.h
// �쐬�� : �i�R�ɓV
// ���� :  �f�o�b�O�p�J����
// ================================================================

#pragma once
#include"Base/Camera/Camera.h"

class InputManager;

class DebugCamera:public Camera
{
public:
	//�v���W�F�N�V����matrix�擾
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const override { return m_projection; };
	//�r���[matrix�擾
	const DirectX::SimpleMath::Matrix& GetViewMatrix()  const override { return m_view; }
	//���_�擾
	const DirectX::SimpleMath::Vector3& GetEyePosition()  const override { return m_eye; }
	//�^�[�Q�b�g�擾
	const DirectX::SimpleMath::Vector3& GetTargetPosition()  const override { return m_target; }
	//�������擾
	const DirectX::SimpleMath::Vector3& GetUpPosition()  const override { return m_up; }
private:
	// �f�t�H���g�ŃJ�����������_����ǂ̂��炢����Ă��邩
	static const float DEFAULT_CAMERA_DISTANCE;
	// ����]�i�x����]�j
	float m_yAngle, m_yTmp;
	// �c��]�i�w����]�j
	float m_xAngle, m_xTmp;
	// �}�E�X�Ńh���b�O���ꂽ���W
	int m_x, m_y;
	// ���΃X�P�[��
	float m_sx, m_sy;
	// �X�N���[���z�C�[���l
	int m_scrollWheelValue;

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
	//���͋@�\
	InputManager* m_input;
public:
	DebugCamera(Scene* scene);
	~DebugCamera()override = default;;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
private:
	// �ψʂ��v������
	void Motion(int x, int y);
	// �r���[�s����v�Z����
	void CalculateViewMatrix();
	// ���΃X�P�[�����v�Z����
	void CalculateRelativeScale(int windowWidth, int windowHeight);
};