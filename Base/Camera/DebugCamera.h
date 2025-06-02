// ================================================================ 
// ファイル名 : DebugCamera.h
// 作成者 : 景山碧天
// 説明 :  デバッグ用カメラ
// ================================================================

#pragma once
#include"Base/Camera/Camera.h"

class InputManager;

class DebugCamera:public Camera
{
public:
	//プロジェクションmatrix取得
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const override { return m_projection; };
	//ビューmatrix取得
	const DirectX::SimpleMath::Matrix& GetViewMatrix()  const override { return m_view; }
	//視点取得
	const DirectX::SimpleMath::Vector3& GetEyePosition()  const override { return m_eye; }
	//ターゲット取得
	const DirectX::SimpleMath::Vector3& GetTargetPosition()  const override { return m_target; }
	//頭方向取得
	const DirectX::SimpleMath::Vector3& GetUpPosition()  const override { return m_up; }
private:
	// デフォルトでカメラが注視点からどのくらい離れているか
	static const float DEFAULT_CAMERA_DISTANCE;
	// 横回転（Ｙ軸回転）
	float m_yAngle, m_yTmp;
	// 縦回転（Ｘ軸回転）
	float m_xAngle, m_xTmp;
	// マウスでドラッグされた座標
	int m_x, m_y;
	// 相対スケール
	float m_sx, m_sy;
	// スクロールホイール値
	int m_scrollWheelValue;

	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;
	//プロジェクション行列
	DirectX::SimpleMath::Matrix m_projection;
	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// カメラの頭の方向
	DirectX::SimpleMath::Vector3 m_up;
	//入力機構
	InputManager* m_input;
public:
	DebugCamera(Scene* scene);
	~DebugCamera()override = default;;
	//アップデート
	void ObjectUpdate(float deltatime)override;
private:
	// 変位を計測する
	void Motion(int x, int y);
	// ビュー行列を計算する
	void CalculateViewMatrix();
	// 相対スケールを計算する
	void CalculateRelativeScale(int windowWidth, int windowHeight);
};