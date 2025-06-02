// ================================================================ 
// ファイル名 : DebugCamera.cpp
// 作成者 : 景山碧天
// 説明 :  デバッグ用カメラ
// ================================================================
#include"pch.h"
#include"DebugCamera.h"
#include"Base/Screen.h"
#include"Base/CommonResources.h"
#include"Base/Mylib/InputManager.h"

const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
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

	// マウスのホイール値をリセット
	DirectX::Mouse::Get().ResetScrollWheelValue();

	m_input = GetCommonResources()->GetInputManager();
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">経過時間</param>
void DebugCamera::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);

	using namespace DirectX;

	const auto& state = m_input->GetMouseState();
	const auto& tracker = m_input->GetMouseTracker();

	// 相対モードなら何もしない
	if (state.positionMode == Mouse::MODE_RELATIVE)
	{
		return;
	}

	// マウスの左ボタンが押された
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		// マウスの座標を取得
		m_x = state.x;
		m_y = state.y;
	}
	// マウスの左ボタンが解放された
	else if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		// 現在の回転を保存
		m_xAngle = m_xTmp;
		m_yAngle = m_yTmp;
	}

	// マウスのボタンが押されていたらカメラを移動させる
	if (state.leftButton)
	{
		Motion(state.x, state.y);
	}

	// マウスのホイール値を取得
	m_scrollWheelValue = state.scrollWheelValue;
	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		Mouse::Get().ResetScrollWheelValue();
		//!! DirectX::Mouseはシングルトンなので…
	}

	// ビュー行列を算出する
	CalculateViewMatrix();


}

/// <summary>
/// 変異の計算
/// </summary>
/// <param name="x">マウスx</param>
/// <param name="y">マウスy</param>
void DebugCamera::Motion(int x, int y)
{
	using namespace DirectX;

	// マウスポインタの位置のドラッグ開始位置からの変位 (相対値)
	float dx = (x - m_x) * m_sx;
	float dy = (y - m_y) * m_sy;

	if (dx != 0.0f || dy != 0.0f)
	{
		// Ｙ軸の回転
		float yAngle = dx * XM_PI;
		// Ｘ軸の回転
		float xAngle = dy * XM_PI;

		m_xTmp = m_xAngle + xAngle;
		m_yTmp = m_yAngle + yAngle;
	}
}

/// <summary>
/// ビュー行列計算
/// </summary>
void DebugCamera::CalculateViewMatrix()
{
	using namespace DirectX::SimpleMath;

	// ビュー行列を算出する
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
/// 相対スケール計算
/// </summary>
/// <param name="windowWidth"></param>
/// <param name="windowHeight"></param>
void DebugCamera::CalculateRelativeScale(int windowWidth, int windowHeight)
{
	// 画面サイズに対する相対的なスケールに調整
	m_sx = 1.0f / static_cast<float>(windowWidth);
	m_sy = 1.0f / static_cast<float>(windowHeight);
}
