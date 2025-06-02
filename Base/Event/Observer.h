// ================================================================ 
// ファイル名 : Observer.h
// 作成者 : 景山碧天
// 説明 :  通知を受けて動作を行う
// ================================================================

#pragma once
#include"Base/Event/IObserver.h"
#include"Base/Event/EventManager.h"
#include"Base/Component/Component.h"

template<typename ... Args>
class Observer :public Component,public IObserver
{
private:
	//実行関数
	std::function<void(Args...)> m_function;
	//登録サブジェクト名
	std::unordered_set<std::string> m_registrationSubject;
public:
	//コンストラクタ
	Observer(Object* object) :Component(object)
		,
		m_function{nullptr}
	{

	}
	//デストラクタ
	~Observer()
	{
		m_function = nullptr;
		//登録サブジェクトに削除依頼
		for (auto& subjectName : m_registrationSubject)
		{
			EventManager::GetInstance()->RemoveObserver(subjectName, this);
		}
	}

	//実行
	void Execution(Args...args)
	{
		if (!m_function)return;
		m_function(std::forward<Args>(args)...);
	}

	//関数セット
	void SetFunction(std::function<void(Args...)> function)
	{
		m_function = function;
	}

	//サブジェクト登録
	void RegistrationSubject(std::string subjectName)
	{
		//マネージャーに登録依頼
		EventManager::GetInstance()->AddObserver(subjectName, this);
		//成功したら名前登録
		m_registrationSubject.insert(subjectName);
		
	}

	//サブジェクト削除
	void RemoveSubject(std::string subjectName)
	{
		//マネージャーに削除依頼
		if (EventManager::GetInstance()->RemoveObserver(subjectName, this))
		{
			//成功したら名前削除
			m_registrationSubject.erase(subjectName);
		}
	}
};