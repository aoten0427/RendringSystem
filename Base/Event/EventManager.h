// ================================================================ 
// ファイル名 : EventManager.h
// 作成者 : 景山碧天
// 説明 :  イベントの登録管理を行う(シングルトン)
// ================================================================

#pragma once
#include"Base/MyLib/Singleton.h"
#include"Base/Event/ISubject.h"

class ISubject;
class IObserver;

class EventManager:public Singleton<EventManager>
{
	friend class Singleton<EventManager>;
private:
	EventManager();
private:
	//登録サブジェクトと名前
	std::unordered_map<std::string, ISubject*> m_subjects;
	//登録予定サブジェクト名
	std::unordered_map<std::string,std::unordered_set<IObserver*>> m_scheduleSubject;
public:
	~EventManager();

	//サブジェクト追加
	void AddSubject(ISubject* subject);
	//サブジェクト削除
	void RemoveSubject(ISubject* subject);

	/// <summary>
	/// オブザーバー追加
	/// </summary>
	/// <param name="subjectName">追加サブジェクト名</param>
	/// <param name="observer">追加オブザーバー</param>
	/// <returns>追加成功か</returns>
	bool AddObserver(std::string subjectName, IObserver* observer)
	{
		//サブジェクト検索
		auto itr = m_subjects.find(subjectName);
		//ない場合失敗
		if (itr == m_subjects.end())
		{
			//予定候補に入れておく
			AddScheduleSubject(subjectName, observer);
			return false;
		}
		//追加処理
		return (*itr).second->AddObserver(observer);
	}

	/// <summary>
	/// オブザーバー削除
	/// </summary>
	/// <param name="subjectName">削除オブジェクト名</param>
	/// <param name="observer">削除オブザーバー</param>
	/// <returns>削除成功か</returns>
	bool RemoveObserver(std::string subjectName, IObserver* observer)
	{
		//サブジェクト検索
		auto itr = m_subjects.find(subjectName);
		//ない場合失敗
		if (itr == m_subjects.end())
		{
			//予約候補から削除
			RemoveScheduleSubject(subjectName, observer);
			return false;
		}
		//削除処理
		return (*itr).second->RemoveObserver(observer);
	}

	//予約を作成
	void AddScheduleSubject(std::string subjectName, IObserver* observer);
	//予約から削除
	void RemoveScheduleSubject(std::string subjectName, IObserver* observer);
	//予約の要素をサブジェクトに追加
	void CheckAddScheduleSubject(std::string subjectName);

	
};