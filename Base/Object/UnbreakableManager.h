// ================================================================ 
// ファイル名 : UnbreakableManager.h
// 作成者 : 景山碧天
// 説明 :  シーンをまたいでも破壊されないオブジェクトを管理
// ================================================================

#pragma once
#include"Base/MyLib/Singleton.h"
#include"Base/Object/Object.h"

class UnbreakableManager : public Singleton<UnbreakableManager>
{
	friend class Singleton<UnbreakableManager>;
private:
	UnbreakableManager();
private:
	//管理オブジェクトと名前
	std::unordered_map<std::string,std::unique_ptr<Object>> m_objects;
public:
	~UnbreakableManager() = default;

	//アップデート
	void Update(float deltatime);
	//削除
	void Delete();
	//オブジェクト追加
	template<typename Obj, typename... Args>
	Obj* AddObject(std::string name, Args&&... args);
	//シーン切り替えイベント
	void LoadScene(Scene* scene);
};

template<typename Obj, typename ...Args>
inline Obj* UnbreakableManager::AddObject(std::string name, Args&&... args)
{
	//同オブジェクトの複数生成を阻止
	if (m_objects.find(name) != m_objects.end())return nullptr;

	//オブジェクト生成
	auto object = std::make_unique<Obj>(std::forward<Args>(args)...);
	//戻り値生成
	Obj* back = object.get();
	//保存
	m_objects.insert({ name,std::move(object) });

	return back;
}
