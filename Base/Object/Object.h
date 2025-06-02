// ================================================================ 
// ファイル名 : Object.h
// 作成者 : 景山碧天
// 説明 :  オブジェクト基底クラス
// ================================================================

#pragma once
#include"Base/Component/Component.h"


class Scene;
class CommonResources;
class Transform;
class Collider;

//オブジェクトタグ
enum class ObjectTag
{
	Player,
	Stage,
	ClearStage,
	Target,
	Search,
	TargetBox,
	Enemy,
	Goal,
	Coin,
	Help,
	Spike,
	Laser,
	Barrier,
	Other
};

class Object
{
public:
	//タグ取得
	virtual ObjectTag GetTag() { return ObjectTag::Other; };
	//シーンセット
	void SetScene(Scene* scene){ m_scene = scene; }
	//シーン取得
	Scene* GetScene() const { return m_scene; }
	//コモンリソース取得
	CommonResources* GetCommonResources()const{return m_commonResources;}
	//トランスフォーム取得
	Transform* GetTransform() const { return m_transform; }
	//アクティブセット
	void SetActive(bool active);
	//アクティブ取得
	bool GetActive() const { return m_isActive; }
	//破壊フラグ取得
	bool GetIsDestroy()const { return m_isDestroy; }
	//コンポーネント破壊フラグセット
	void ComponentDestroyOn() { m_isComponentDestroy = true; }
private:
	//所属シーン
	Scene* m_scene;
	//コモンリソース
	CommonResources* m_commonResources;
	//コンポーネント
	std::vector<std::unique_ptr<Component>> m_components;
	//トランスフォーム
	Transform* m_transform;
	//アクティブフラグ
	bool m_isActive;
	//破壊フラグ
	bool m_isDestroy;
	//コンポーネント破壊フラグ
	bool m_isComponentDestroy;
public:
	//コンストラクタ
	Object(Scene* scene);
	//デストラクタ
	virtual ~Object();
	//初期化
	virtual void Initialize() {};
	//アップデート
	void Update(float deltatime);
	//コンポーネントアップデート
	void ComponentUpdate(float deltatime);
	//自身のアップデートoverride用
	virtual void ObjectUpdate(float deltatime) { UNREFERENCED_PARAMETER(deltatime); };
	//終了処理
	virtual void Finalize() {};
	//削除
	void Destroy();
	//コンポーネント追加
	template<typename Comp, typename... Args>
	Comp* AddComponent(Args&&... args);
	//コンポーネント取得
	template<typename T>
	T* GetComponent();
	

	//判定系
	//Triggerの実行有無
	virtual bool IsTriggerAct(Collider* collider) { UNREFERENCED_PARAMETER(collider); return true; }
	//Collisionの実行有無
	virtual bool IsCollisionAct(Collider* collider) { UNREFERENCED_PARAMETER(collider); return true; }
	//押し戻し(押し出し量)
	virtual void PushBack(DirectX::SimpleMath::Vector3 pushback);
	//Trigger処理
	virtual void OnTrigger(Collider* collider) { UNREFERENCED_PARAMETER(collider); };
	//Collision処理
	virtual void OnCollision(Collider* collider) { UNREFERENCED_PARAMETER(collider); };
	//めり込み計算実行の有無
	virtual bool IsDetectionAct(Collider* collider) { UNREFERENCED_PARAMETER(collider); return true; }

	//シーン切り替えイベント
	virtual void LoadScene(Scene* scene) { UNREFERENCED_PARAMETER(scene); };
private:
	//コンポーネント削除
	void RemoveComponent();
};


//コンポーネント追加
template<typename Comp, typename ...Args>
inline Comp* Object::AddComponent(Args && ...args)
{
	// コンポーネント生成
	auto component = std::make_unique<Comp>(std::forward<Args>(args)...);
	auto order = component->GetUpdateOrder();

	// 挿入位置をオーダーから検索
	auto itr = std::find_if(m_components.begin(), m_components.end(),
		[order](const std::unique_ptr<Component>& comp) {
			return comp->GetUpdateOrder() > order;
		});

	// 戻り値生成
	Comp* back = component.get();
	// 挿入
	m_components.insert(itr, std::move(component));

	return back;
}


//コンポーネント取得
template<typename Comp>
inline Comp* Object::GetComponent()
{
	//指定クラスを検索し最初に見つけたものを返す
	for (auto& component : m_components) {
		if (typeid(*component) == typeid(Comp)) {
			Comp* comp = dynamic_cast<Comp*>(component.get());
			return comp;
		}
	}
	return nullptr;
}
