// ================================================================ 
// ファイル名 : Object.cpp
// 作成者 : 景山碧天
// 説明 :  オブジェクト基底クラス
// ================================================================
#include"pch.h"
#include"Object.h"
#include"Base/Scene/Scene.h"
#include"Base/Component/Transform/Transform.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
Object::Object(Scene* scene)
	:
	m_scene{scene},
	m_components{},
	m_transform{nullptr},
	m_isActive{true},
	m_isDestroy{false},
	m_isComponentDestroy{false}
{
	assert(scene);
	m_commonResources = scene->GetCommonResources();
	m_transform = AddComponent<Transform>(this);
}

/// <summary>
/// デストラクタ
/// </summary>
Object::~Object()
{
	m_components.clear();
}



/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Object::Update(float deltatime)
{
	//コンポーネントアップデート
	ComponentUpdate(deltatime);
	//個別アップデート
	ObjectUpdate(deltatime);
	//コンポーネント削除
	RemoveComponent();
}

/// <summary>
/// コンポーネントアップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Object::ComponentUpdate(float deltatime)
{
	for (auto& component : m_components)
	{
		if (!component->GetActive())continue;
		component->Update(deltatime);
	}
}

/// <summary>
/// 自身を破壊
/// </summary>
void Object::Destroy()
{
	//シーンにオブジェクト破壊指示
	GetScene()->ObjectDestroyOn();
	//破壊フラグをオンに
	m_isDestroy = true;
	//アクティブをオフ
	SetActive(false);
}

/// <summary>
/// 破壊コンポーネントの検索と削除
/// </summary>
void Object::RemoveComponent()
{
	//破壊要請がオフならパス
	if (m_isComponentDestroy)return;
	//削除要素を削除
	m_components.erase(std::remove_if(m_components.begin(), m_components.end(), [&]
	(std::unique_ptr<Component>& comp) {
			return comp->GetIsDestroy();
		}), m_components.end());
	//破壊要請をオフに
	m_isComponentDestroy = true;
}

/// <summary>
/// 押し出し処理
/// </summary>
/// <param name="pushback">押し出し量</param>
void Object::PushBack(DirectX::SimpleMath::Vector3 pushback)
{
	m_transform->Translate(pushback);
}

/// <summary>
/// アクティブを変更
/// </summary>
/// <param name="active">アクティブ</param>
void Object::SetActive(bool active)
{
	m_isActive = active;
	//子へ伝播
	for (auto& children : m_transform->GetAllChild())
	{
		children->GetObject()->SetActive(active);
	}
	//コンポーネント
	for (auto& component : m_components)
	{
		component.get()->SetActive(active);
	}
}


