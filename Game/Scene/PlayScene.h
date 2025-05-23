/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "IScene.h"
#include "Game/Mylib/Model3D.h"
// 前方宣言
class CommonResources;
class DebugCamera;


class PlayScene final :
    public IScene
{
private:
	// 共通リソース
	CommonResources* m_commonResources;
	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;
	//モデル
	Model3D m_model;
public:
	PlayScene();
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};
