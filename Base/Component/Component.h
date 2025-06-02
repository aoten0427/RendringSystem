// ================================================================ 
// ファイル名 : Component.h
// 作成者 : 景山碧天
// 説明 :  コンポーネント基底クラス
// ================================================================

#pragma once

class Scene;
class Object;
class CommonResources;

class Component
{
public:
	//オブジェクト取得
	Object* GetObject() const{ return m_object; }
	//コモンリソース取得
	CommonResources* GetCommonResources()const { return m_commonResources; }
	//アクティブフラグセット
	void SetActive(bool isactive) { m_isActive = isactive; }
	//アクティブ取得
	bool GetActive() const{ return m_isActive; }
	//アップデートオーダー取得
	int GetUpdateOrder() const{ return m_updateOrder; }
	//破壊フラグ取得
	bool GetIsDestroy()const { return m_isDestroy; }
private:
	//所属オブジェクト
	Object* m_object;
	//コモンリソース
	CommonResources * m_commonResources;
	//アクティブフラグ
	bool m_isActive;
	//アップデートオーダー
	int m_updateOrder;
	//破壊フラグ
	bool m_isDestroy;
public:
	//コンストラクタ
	Component(Object* object, int updateOrder = 0);
	//デストラクタ
	virtual ~Component() = default;
	//アップデート
	virtual void Update(float deltatime);
	//削除
	void Destroy();
	//シーン切り替えイベント
	virtual void LoadScene(Scene* scene) { UNREFERENCED_PARAMETER(scene); };
};