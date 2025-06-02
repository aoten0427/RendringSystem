// ================================================================ 
// �t�@�C���� : Camera.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �J�������N���X
// ================================================================

#include"pch.h"
#include"Camera.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Screen.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
Camera::Camera(Scene* scene):Object(scene)
{
	m_eye = GetTransform()->GetWorldPosition();
	m_target = DirectX::SimpleMath::Vector3(0, 0, 1) + m_eye;
	m_up = DirectX::SimpleMath::Vector3::Up;

	//�r���[�s��v�Z
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);

	//�v���W�F�N�V�����s��v�Z
	RECT rect{ 0,0,Screen::WIDTH,Screen::HEIGHT };
	using namespace DirectX;
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.02f, 200.0f
	);
}

/// <summary>
/// ���C�����擾
/// </summary>
/// <returns>�J�������S����</returns>
DirectX::SimpleMath::Vector3 Camera::GetRayDirection() const
{
	using namespace DirectX::SimpleMath;

	Vector3 clipCoords(
		(2.0f * Screen::CENTER_X) / Screen::WIDTH - 1.0f,
		1.0f - (2.0f * (Screen::CENTER_Y)) / Screen::HEIGHT,
		1.0f  // �[�x��1.0�ɐݒ�
	);

	// �ˉe�s��̋t�s����v�Z���A�N���b�v��Ԃ̍��W���J������Ԃɕϊ�
	Matrix invProjectionMatrix = GetProjectionMatrix().Invert();
	Vector3 cameraSpaceCoords = Vector3::Transform(clipCoords, invProjectionMatrix);
	cameraSpaceCoords.z = -1.0f;

	// �r���[�s��̋t�s����v�Z���A�J������Ԃ̍��W�����[���h��Ԃɕϊ�
	Matrix invViewMatrix = GetViewMatrix().Invert();
	Vector3 rayDirection = Vector3::TransformNormal(cameraSpaceCoords, invViewMatrix);

	//���K��
	rayDirection.Normalize();

	return rayDirection;
}
