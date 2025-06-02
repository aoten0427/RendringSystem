// ================================================================ 
// ファイル名 : Transform.h
// 作成者 : 景山碧天
// 説明 :  位置、回転、大きさを扱う
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class Transform:public Component
{
private:
	//ポジション
	DirectX::SimpleMath::Vector3 m_position;
	//スケール
	DirectX::SimpleMath::Vector3 m_scale;
	//回転
	DirectX::SimpleMath::Quaternion m_rotate;
	//matrix
	DirectX::SimpleMath::Matrix m_matrix;
	//matrix計算判断
	bool m_isCompute;
	//親
	Transform* m_parent;
	//子供
	std::vector<Transform*> m_children;
public:
	//コンストラクト
	Transform(Object* object);
	//デストラクタ
	~Transform() = default;

	//自身の行列を返す
	DirectX::SimpleMath::Matrix GetWorldMatrix();
	//ワールドPositionを返す
	DirectX::SimpleMath::Vector3 GetWorldPosition();
	//ワールドScaleを返す
	DirectX::SimpleMath::Vector3 GetWorldScale();
	//ワールドRotateを返す
	DirectX::SimpleMath::Quaternion GetWorldRotate();

	//ポジションセット
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	//ポジションゲット
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	//ポジションを移動させる(加算)
	void Translate(const DirectX::SimpleMath::Vector3& position);
	//スケールセット
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
	//スケールゲット
	DirectX::SimpleMath::Vector3 GetScale()const { return m_scale; }
	//大きさを変更する(加算)
	void TransScale(const DirectX::SimpleMath::Vector3& scale);
	//大きさを変更する(乗算)
	void TransScale(const float& scale);
	//回転セット
	void SetRotate(const DirectX::SimpleMath::Quaternion& roteto);
	//回転ゲット
	DirectX::SimpleMath::Quaternion GetRotate()const { return m_rotate; }
	//回転を変更する
	//クォータニオン回転
	void TransRotate(const DirectX::SimpleMath::Quaternion& roteto);
	//軸と角度で回転
	void TransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle);
	//ローカルの軸と角度で回転
	void LocalTransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle);
	//自身の姿勢に対する軸の方向を返す
	DirectX::SimpleMath::Vector3 GetWorldAxisFromLocal(const DirectX::SimpleMath::Vector3& axis);
	//回転考慮のポジション
	DirectX::SimpleMath::Vector3 GetRotatePosition();
	//親をセット
	void SetParent(Transform* parent);
	//子供取得
	Transform* GetChild(int num);
	//全ての子供を返す
	std::vector<Transform*>& GetAllChild()  { return m_children; };
private:
	//子供セット
	void SetChild(Transform* child) { m_children.push_back(child); }
	//子供消去
	void ReMoveChild(Transform* child);

	//親設定時の情報変更
	void CalculationSetParent();
	//親解除時の情報変更
	void CalculationReMoveParent();
};