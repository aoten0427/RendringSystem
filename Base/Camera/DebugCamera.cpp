// ================================================================ 
// �t�@�C���� : DebugCamera.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �f�o�b�O�p�J����
// ================================================================
#include"pch.h"
#include"DebugCamera.h"
#include"Base/Screen.h"
#include"Base/CommonResources.h"
#include"Base/Mylib/InputManager.h"

const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
DebugCamera::DebugCamera(Scene* scene):Camera(scene)
	,
	m_yAngle{ 0.0f },
	m_yTmp{ 0.0f },
	m_xAngle{ 0.0f },
	m_xTmp{ 0.0f },
	m_x{ 0 },
	m_y{ 0 },
	m_sx{ 0.0f },
	m_sy{ 0.0f },
	m_view{},
	m_projection{},
	m_scrollWheelValue{ 0 },
	m_eye{},
	m_target{}
{
	CalculateRelativeScale(Screen::WIDTH, Screen::HEIGHT);
	CalculateViewMatrix();

	RECT rect{ 0,0,Screen::WIDTH,Screen::HEIGHT };
	using namespace DirectX;
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.02f, 100.0f
	);

	// �}�E�X�̃z�C�[���l�����Z�b�g
	DirectX::Mouse::Get().ResetScrollWheelValue();

	m_input = GetCommonResources()->GetInputManager();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�o�ߎ���</param>
void DebugCamera::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);

	using namespace DirectX;

	const auto& state = m_input->GetMouseState();
	const auto& tracker = m_input->GetMouseTracker();

	// ���΃��[�h�Ȃ牽�����Ȃ�
	if (state.positionMode == Mouse::MODE_RELATIVE)
	{
		return;
	}

	// �}�E�X�̍��{�^���������ꂽ
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		// �}�E�X�̍��W���擾
		m_x = state.x;
		m_y = state.y;
	}
	// �}�E�X�̍��{�^����������ꂽ
	else if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		// ���݂̉�]��ۑ�
		m_xAngle = m_xTmp;
		m_yAngle = m_yTmp;
	}

	// �}�E�X�̃{�^����������Ă�����J�������ړ�������
	if (state.leftButton)
	{
		Motion(state.x, state.y);
	}

	// �}�E�X�̃z�C�[���l���擾
	m_scrollWheelValue = state.scrollWheelValue;
	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		Mouse::Get().ResetScrollWheelValue();
		//!! DirectX::Mouse�̓V���O���g���Ȃ̂Łc
	}

	// �r���[�s����Z�o����
	CalculateViewMatrix();


}

/// <summary>
/// �ψق̌v�Z
/// </summary>
/// <param name="x">�}�E�Xx</param>
/// <param name="y">�}�E�Xy</param>
void DebugCamera::Motion(int x, int y)
{
	using namespace DirectX;

	// �}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����̕ψ� (���Βl)
	float dx = (x - m_x) * m_sx;
	float dy = (y - m_y) * m_sy;

	if (dx != 0.0f || dy != 0.0f)
	{
		// �x���̉�]
		float yAngle = dx * XM_PI;
		// �w���̉�]
		float xAngle = dy * XM_PI;

		m_xTmp = m_xAngle + xAngle;
		m_yTmp = m_yAngle + yAngle;
	}
}

/// <summary>
/// �r���[�s��v�Z
/// </summary>
void DebugCamera::CalculateViewMatrix()
{
	using namespace DirectX::SimpleMath;

	// �r���[�s����Z�o����
	Matrix rotY = Matrix::CreateRotationY(m_yTmp);
	Matrix rotX = Matrix::CreateRotationX(m_xTmp);

	Matrix rotYX = rotY * rotX;

	Vector3 eye(0.0f, 1.0f, 1.0f);
	Vector3 target(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	eye = Vector3::Transform(eye, rotYX.Invert());
	eye *= (DEFAULT_CAMERA_DISTANCE - m_scrollWheelValue / 100);
	up = Vector3::Transform(up, rotYX.Invert());

	m_eye = eye;
	m_target = target;
	m_up = up;

	m_view = Matrix::CreateLookAt(eye, target, up);
}

/// <summary>
/// ���΃X�P�[���v�Z
/// </summary>
/// <param name="windowWidth"></param>
/// <param name="windowHeight"></param>
void DebugCamera::CalculateRelativeScale(int windowWidth, int windowHeight)
{
	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	m_sx = 1.0f / static_cast<float>(windowWidth);
	m_sy = 1.0f / static_cast<float>(windowHeight);
}
