// ================================================================ 
// ファイル名 : Subject.h
// 作成者 : 景山碧天
// 説明 :  イベント通知を行う
// ================================================================

#pragma once
#include"Base/Event/ISubject.h"
#include"Base/Event/EventManager.h"
#include"Base/Event/Observer.h"
#include"Base/Component/Component.h"


template<typename ... Args>
class Subject :public Component, public ISubject
{
public:
	//名前取得
	std::string GetName()const override { return m_name; }
private:
	//名前
	std::string m_name;
	//呼び出すオブザーバー
	std::unordered_set<Observer<Args...>*> m_observers;
public:
	//コンストラクタ
	Subject(Object* object, std::string name) :Component(object)
		,
		m_name{ name },
		m_observers{}
	{
		//マネージャに登録
		EventManager::GetInstance()->AddSubject(this);
	}
	~Subject()
	{
		//マネージャから削除
		EventManager::GetInstance()->RemoveSubject(this);
	}

	/// <summary>
	/// オブザーバー追加
	/// </summary>
	/// <param name="observer"></param>
	bool AddObserver(IObserver* observer)override
	{
		//変換
		auto castedObserver = static_cast<Observer<Args...>*>(observer);
		if (castedObserver)
		{
			//追加処理
			return AddObservers(castedObserver);
		}
		return false;
	}

	/// <summary>
	/// オブザーバー削除
	/// </summary>
	/// <param name="observer"></param>
	bool RemoveObserver(IObserver* observer)override
	{
		//変換
		auto castedObserver = static_cast<Observer<Args...>*>(observer);
		if (castedObserver)
		{
			//削除処理
			return RemoveObservers(castedObserver);
		}
		return false;
	}

	//実行
	void Notify(Args...args)
	{
		for (auto& observers : m_observers)
		{
			observers->Execution(std::forward<Args>(args)...);
		}
	}

	//追加
	bool AddObservers(Observer<Args...>* observer)
	{
		//検索
		auto itr = m_observers.find(observer);
		//ある場合失敗
		if (itr != m_observers.end())return false;
		//追加
		m_observers.insert(observer);
		return true;
	}

	//削除
	bool RemoveObservers(Observer<Args...>* observer)
	{
		//検索
		auto itr = m_observers.find(observer);
		//ない場合失敗
		if (itr == m_observers.end())return false;
		//削除
		m_observers.erase(itr);
		return true;
	}
};