// ================================================================ 
// ファイル名 : UnbreakableManager.cpp
// 作成者 : 景山碧天
// 説明 :  シーンをまたいでも破壊されないオブジェクトを管理
// ================================================================
#include"pch.h"
#include"UnbreakableManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
UnbreakableManager::UnbreakableManager()
	:
	m_objects{}
{
}



/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void UnbreakableManager::Update(float deltatime)
{
	for (auto& object : m_objects)
	{
		object.second->Update(deltatime);
	}
}

/// <summary>
/// 削除処理
/// </summary>
void UnbreakableManager::Delete()
{
	for (auto& object : m_objects)
	{
		object.second->Finalize();
	}
	m_objects.clear();
}

/// <summary>
/// シーン切り替えイベント
/// </summary>
/// <param name="scene">切替後シーン</param>
void UnbreakableManager::LoadScene(Scene* scene)
{
	for (auto& object : m_objects)
	{
		//オブジェクトにシーンを登録
		object.second->SetScene(scene);
		//シーン切り替えイベント
		object.second->LoadScene(scene);
	}
}
