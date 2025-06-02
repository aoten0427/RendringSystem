// ================================================================ 
// ファイル名 : Scene.cpp
// 作成者 : 景山碧天
// 説明 :  シーン基底クラス
// ================================================================

#include "pch.h"
#include "Scene.h"
#include "Base/CommonResources.h"
#include "DeviceResources.h"
#include "Base/Object/Object.h"
#include "Base/Object/UnbreakableManager.h"
#include "Base/Scene/SceneState.h"
#include "Base/Camera/Camera.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
Scene::Scene(CommonResources* resources,std::string name)
	:
	m_name{name},
	m_nextSceneID{SceneID::NONE},
	m_commonResources{nullptr},
	m_objects{},
	m_pendingObjects{},
	m_updating{ false },
	m_isObjectDestroy{false},
	m_state{nullptr}
{
	assert(resources);
	m_commonResources = resources;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//各マネージャー生成
	//ステート作成
	m_state = AddObject<SceneState>(this);
}

/// <summary>
/// デストラクタ
/// </summary>
Scene::~Scene()
{
	for (auto& object : m_objects)
	{
		object->Finalize();
	}
	m_objects.clear();
	m_pendingObjects.clear();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">コモンリソース</param>
void Scene::Initialize()
{
	
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void Scene::Update(float deltaTime)
{
	//UIを更新
	
	//更新フラグをtrueに
	m_updating = true;
	//オブジェクトをアップデート
	for (auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
	//非破壊オブジェクトアップデート
	UnbreakableManager::GetInstance()->Update(deltaTime);
	//シーン別アップデート
	SceneUpdate(deltaTime);
	//更新フラグをfalseに
	m_updating = false;

	//リジッドボディ、衝突判定をアップデート
	if (GetState() == State::PLAY)
	{
		
	}
	

	//カメラ更新
	GetCamera()->CalculationView();

	//保留オブジェクトを更新オブジェクトへ移動
	std::move(m_pendingObjects.begin(), m_pendingObjects.end(), std::back_inserter(m_objects));
	m_pendingObjects.clear();

	//オブジェクト削除
	RemoveObject();

	//状態の更新
	m_state->ChangeState();
}

/// <summary>
/// 描画
/// </summary>
void Scene::Render()
{

}

/// <summary>
/// 終了処理
/// </summary>
void Scene::Finalize()
{

}

/// <summary>
/// オブジェクト削除
/// </summary>
void Scene::RemoveObject()
{
	//削除要請がなければ返す
	if (!m_isObjectDestroy)return;
	//削除要素を削除
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [&]
	(std::unique_ptr<Object>& obj) {
			return obj->GetIsDestroy();
		}),m_objects.end());
	//削除要請をオフに
	m_isObjectDestroy = false;
}

/// <summary>
/// 状態切り替え
/// </summary>
/// <param name="state">変更ステート名</param>
void Scene::ChangeState(Scene::State state)
{
	m_state->ChangeState(state);
}

/// <summary>
/// 状態を返す
/// </summary>
/// <returns>現在の状態</returns>
Scene::State Scene::GetState() const
{
	return m_state->GetState();
}



