// ================================================================ 
// ファイル名 : Transform.cpp
// 作成者 : 景山碧天
// 説明 :  位置、回転、大きさを扱う
// ================================================================
#include"pch.h"
#include"Transform.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
Transform::Transform(Object* object):Component(object)
	,
	m_position{DirectX::SimpleMath::Vector3(0,0,0)},
	m_scale{DirectX::SimpleMath::Vector3(1,1,1)},
	m_rotate{DirectX::SimpleMath::Quaternion::Identity},
	m_isCompute{false},
	m_parent{nullptr},
	m_children{}
{
	
}



/// <summary>
/// ワールド行列取得
/// </summary>
/// <returns>ワールド行列</returns>
DirectX::SimpleMath::Matrix Transform::GetWorldMatrix()
{
	using namespace DirectX::SimpleMath;

	//計算フラグがtrueなら計算
	if (m_isCompute)
	{
		//scale,rotate,position順で行列を計算する
		m_matrix = Matrix::CreateScale(m_scale);
		m_matrix *= Matrix::CreateFromQuaternion(m_rotate);
		m_matrix *= Matrix::CreateTranslation(m_position);
		m_isCompute = false;
	}
	Matrix worldMatrix = m_matrix;

	//親がいる場合親の行列をかける
	if (m_parent != nullptr)
	{
		worldMatrix *= m_parent->GetWorldMatrix();
	}

	return worldMatrix;
}

/// <summary>
/// ワールドポジションを返す
/// </summary>
/// <returns>ワールドポジション</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldPosition()
{
	DirectX::SimpleMath::Vector3 worldpos = m_position;
	//親がいる場合親のポジションを足す
	if (m_parent != nullptr)
	{
		worldpos += m_parent->GetWorldPosition();
	}
	return worldpos;
}

/// <summary>
/// ワールドスケールを返す
/// </summary>
/// <returns>ワールドスケール</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldScale()
{
	DirectX::SimpleMath::Vector3 worldscale = m_scale;
	//親がいる場合親のスケールを足す
	if (m_parent != nullptr)
	{
		worldscale += m_parent->GetWorldScale();
	}
	return worldscale;
}

/// <summary>
/// ワールド回転を返す
/// </summary>
/// <returns>ワールド回転</returns>
DirectX::SimpleMath::Quaternion Transform::GetWorldRotate()
{
	DirectX::SimpleMath::Quaternion worldrotate = m_rotate;
	//親がいる場合親の回転をかける
	if (m_parent != nullptr)
	{
		worldrotate *= m_parent->GetWorldRotate();
	}
	return worldrotate;
}

/// <summary>
/// ポジションセット
/// </summary>
/// <param name="position">セットポジション</param>
void Transform::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
	m_isCompute = true;
}

/// <summary>
/// ポジション移動(加算)
/// </summary>
/// <param name="position">加算量</param>
void Transform::Translate(const DirectX::SimpleMath::Vector3& position)
{
	m_position += position;
	m_isCompute = true;
}

/// <summary>
/// スケールセット
/// </summary>
/// <param name="scale">セットスケール</param>
void Transform::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
	m_isCompute = true;
}


/// <summary>
/// スケール変化(加算)
/// </summary>
/// <param name="scale">加算量</param>
void Transform::TransScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale += scale;
	m_isCompute = true;
}

/// <summary>
/// スケール変化(乗算)
/// </summary>
/// <param name="scale">乗算量</param>
void Transform::TransScale(const float& scale)
{
	m_scale *= scale;
	m_isCompute = true;
}

/// <summary>
/// ロテートセット
/// </summary>
/// <param name="rotate">セットロテート</param>
void Transform::SetRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = rotate;
	m_isCompute = true;
}


/// <summary>
/// 回転(クォータニオン)
/// </summary>
/// <param name="rotate">回転量</param>
void Transform::TransRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = m_rotate * rotate;
	m_isCompute = true;
}

/// <summary>
/// 回転(軸、角度)
/// </summary>
/// <param name="axis">回転軸</param>
/// <param name="angle">回転量(弧度法)</param>
void Transform::TransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle)
{
	DirectX::SimpleMath::Quaternion quaternion = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, DirectX::XMConvertToRadians(angle));
	TransRotate(quaternion);
}

/// <summary>
/// ローカル回転(軸、角度)
/// </summary>
/// <param name="axis">回転軸</param>
/// <param name="angle">回転量(弧度法)</param>
void Transform::LocalTransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle)
{
	DirectX::SimpleMath::Vector3 localaxis = GetWorldAxisFromLocal(axis);
	TransRotate(localaxis, angle);
}

/// <summary>
/// 自身の姿勢に対する軸の方向を返す
/// </summary>
/// <param name="axis">指定軸</param>
/// <returns>指定軸のワールド方向</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldAxisFromLocal(const DirectX::SimpleMath::Vector3& axis)
{
	DirectX::SimpleMath::Vector3 worldaxis = DirectX::SimpleMath::Vector3::Transform(axis, m_rotate);
	worldaxis.Normalize();
	return worldaxis;
}

/// <summary>
/// 親の回転を考慮したポジションを返す
/// </summary>
/// <returns>回転込みポジション</returns>
DirectX::SimpleMath::Vector3 Transform::GetRotatePosition()
{
	using namespace DirectX::SimpleMath;

	if (m_parent == nullptr)return m_position;
	Vector3 distance = m_position * m_parent->m_scale;
	distance = DirectX::SimpleMath::Vector3::Transform(distance, m_parent->GetWorldRotate());
	return m_parent->GetRotatePosition() + distance;
}

/// <summary>
/// 親をセット
/// </summary>
/// <param name="parent">親</param>
void Transform::SetParent(Transform* parent)
{
	if (parent == nullptr)
	{
		if (m_parent != nullptr)//引数がnullで親が存在している場合
		{
			//親の情報から逆算した情報にする
			CalculationReMoveParent();
			//親から解除
			m_parent->ReMoveChild(this);
			m_parent = nullptr;
		}
	}
	else
	{
		if (m_parent != parent)//引数が存在して、現在の親と違う場合
		{
			if (m_parent != nullptr)
			{
				//元の親の情報から逆算した情報にする
				CalculationReMoveParent();
			}
			m_parent = parent;
			m_parent->SetChild(this);
			CalculationSetParent();
		}
	}
}

/// <summary>
/// 子供取得
/// </summary>
/// <param name="num">インデックス番号</param>
/// <returns>子</returns>
Transform* Transform::GetChild(int num)
{
	if (num >= m_children.size())
	{
		return nullptr;
	}

	return m_children[num];
}

/// <summary>
/// 子供削除
/// </summary>
/// <param name="child">削除子</param>
void Transform::ReMoveChild(Transform* child)
{
	auto searchChile = std::find(m_children.begin(), m_children.end(), child);

	if (searchChile != m_children.end())
	{
		m_children.erase(searchChile);
	}
	
}

/// <summary>
/// 親を設定した際の情報変更
/// </summary>
void Transform::CalculationSetParent()
{
	using namespace DirectX::SimpleMath;

	//ポジション移動
	m_position -= m_parent->m_position;
	//スケール変換
	m_scale = DirectX::SimpleMath::Vector3
	{
		m_scale.x / m_parent->m_scale.x,
		m_scale.y / m_parent->m_scale.y,
		m_scale.z / m_parent->m_scale.z,
	};
	//回転変換
	Quaternion invers = m_parent->m_rotate;
	invers.Inverse(invers);
	m_rotate *= invers;


	//回転移動
	Vector3 dire = m_position;
	dire = Vector3(
		dire.x / m_parent->m_scale.x,
		dire.y / m_parent->m_scale.y,
		dire.z / m_parent->m_scale.z
	);

	Matrix mat = Matrix::CreateFromQuaternion(invers);
	m_position = Vector3::Transform(dire, mat);

	m_isCompute = true;
}

/// <summary>
/// 親を解除した際の情報変更
/// </summary>
void Transform::CalculationReMoveParent()
{
	using namespace DirectX::SimpleMath;

	Quaternion invers = m_parent->GetWorldRotate();
	Vector3 dire = m_position;
	dire = Vector3(
		dire.x * m_parent->m_scale.x,
		dire.y * m_parent->m_scale.y,
		dire.z * m_parent->m_scale.z
	);

	Matrix mat = Matrix::CreateFromQuaternion(invers);
	m_position = Vector3::Transform(dire, mat);

	m_position += m_parent->m_position;
	m_scale = DirectX::SimpleMath::Vector3
	{
		m_scale.x * m_parent->m_scale.x,
		m_scale.y * m_parent->m_scale.y,
		m_scale.z * m_parent->m_scale.z,
	};

	m_rotate *= m_parent->m_rotate;

	m_isCompute = true;
}
