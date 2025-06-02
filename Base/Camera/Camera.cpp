// ================================================================ 
// ファイル名 : Camera.cpp
// 作成者 : 景山碧天
// 説明 :  カメラ基底クラス
// ================================================================

#include"pch.h"
#include"Camera.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Screen.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
Camera::Camera(Scene* scene):Object(scene)
{
	m_eye = GetTransform()->GetWorldPosition();
	m_target = DirectX::SimpleMath::Vector3(0, 0, 1) + m_eye;
	m_up = DirectX::SimpleMath::Vector3::Up;

	//ビュー行列計算
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);

	//プロジェクション行列計算
	RECT rect{ 0,0,Screen::WIDTH,Screen::HEIGHT };
	using namespace DirectX;
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.02f, 200.0f
	);
}

/// <summary>
/// レイ方向取得
/// </summary>
/// <returns>カメラ中心方向</returns>
DirectX::SimpleMath::Vector3 Camera::GetRayDirection() const
{
	using namespace DirectX::SimpleMath;

	Vector3 clipCoords(
		(2.0f * Screen::CENTER_X) / Screen::WIDTH - 1.0f,
		1.0f - (2.0f * (Screen::CENTER_Y)) / Screen::HEIGHT,
		1.0f  // 深度を1.0に設定
	);

	// 射影行列の逆行列を計算し、クリップ空間の座標をカメラ空間に変換
	Matrix invProjectionMatrix = GetProjectionMatrix().Invert();
	Vector3 cameraSpaceCoords = Vector3::Transform(clipCoords, invProjectionMatrix);
	cameraSpaceCoords.z = -1.0f;

	// ビュー行列の逆行列を計算し、カメラ空間の座標をワールド空間に変換
	Matrix invViewMatrix = GetViewMatrix().Invert();
	Vector3 rayDirection = Vector3::TransformNormal(cameraSpaceCoords, invViewMatrix);

	//正規化
	rayDirection.Normalize();

	return rayDirection;
}
