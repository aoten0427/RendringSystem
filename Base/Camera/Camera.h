// ================================================================ 
// ファイル名 : Camera.h
// 作成者 : 景山碧天
// 説明 :  カメラ基底クラス
// ================================================================

#pragma once
#include"Base/Object/Object.h"


class Camera :public Object
{
public:
	//プロジェクションmatrix取得
	virtual const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }
	//ビューmatrix取得
	virtual const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_view; }
	//視点取得
	virtual const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }
	//ターゲット取得
	virtual const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }
	//頭方向取得
	virtual const DirectX::SimpleMath::Vector3& GetUpPosition() const { return m_up; }
private:
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
public:
	//コンストラクタ
	Camera(Scene* scene);
	//デストラクタ
	~Camera()override = default;
	//ビュー行列を計算する
	virtual void CalculationView() {};
	//レイ方向を取得
	DirectX::SimpleMath::Vector3 GetRayDirection()const;
};