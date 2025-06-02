// ================================================================ 
// ファイル名 : SceneManager.h
// 作成者 : 景山碧天
// 説明 :  シーン管理マネージャー
// ================================================================

#pragma once
#include"Base/Scene/Scene.h"

class CommonResources;
class UnbreakableManager;

class SceneManager
{
private:
	//現在のシーン
	std::unique_ptr<Scene> m_currentScene;
	//非破壊オブジェクト
	UnbreakableManager* m_unbreakableManager;
	//コモンリソース
	CommonResources* m_commonResources;
public:
	//コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();
	//初期化
	void Initialize(CommonResources* resources);
	//アップデート
	void Update(float deltatime);
	//描画
	void Render();
	//終了処理
	void Finalize();

private:
	//シーン変更
	void ChangeScene(Scene::SceneID sceneID);
	//シーン作成
	void CreateScene(Scene::SceneID sceneID);
	//シーン削除
	void DeleteScene();
};