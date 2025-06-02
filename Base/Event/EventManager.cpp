// ================================================================ 
// ファイル名 : EventManager.cpp
// 作成者 : 景山碧天
// 説明 :  イベントの登録管理を行う(シングルトン)
// ================================================================
#include"pch.h"
#include "EventManager.h"
#include"Base/Event/IObserver.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

/// <summary>
/// サブジェクト追加
/// </summary>
/// <param name="subject">追加サブジェクト</param>
void EventManager::AddSubject(ISubject* subject)
{
	auto itr = m_subjects.find(subject->GetName());
	if (itr != m_subjects.end())return;

	m_subjects.insert({ subject->GetName(),subject });

	CheckAddScheduleSubject(subject->GetName());
}

/// <summary>
/// サブジェク削除
/// </summary>
/// <param name="subject">削除サブジェクト</param>
void EventManager::RemoveSubject(ISubject* subject)
{
	auto itr = m_subjects.find(subject->GetName());
	if (itr == m_subjects.end())return;

	m_subjects.erase(itr);
}

/// <summary>
/// サブジェクトへの登録を予約する
/// </summary>
/// <param name="subjectName">予約サブジェクト名</param>
/// <param name="observer">オブザーバー</param>
void EventManager::AddScheduleSubject(std::string subjectName, IObserver* observer)
{
	//予約を作成
	m_scheduleSubject[subjectName].insert(observer);
}

/// <summary>
/// 予約の削除
/// </summary>
/// <param name="subjectName">削除サブジェクト名</param>
/// <param name="observer">削除オブザーバー</param>
void EventManager::RemoveScheduleSubject(std::string subjectName, IObserver* observer)
{
	auto itr = m_scheduleSubject.find(subjectName);
	if (itr == m_scheduleSubject.end())return;
	//予約から削除
	m_scheduleSubject[subjectName].erase(observer);
}

/// <summary>
/// 予約の要素をサブジェクトに追加
/// </summary>
/// <param name="subjectName">サブジェクト名</param>
void EventManager::CheckAddScheduleSubject(std::string subjectName)
{
	//予約に入っているか検索
	auto itr = m_scheduleSubject.find(subjectName);
	if (itr == m_scheduleSubject.end())return;

	//予約オブザーバーを登録する
	for (auto& observer : m_scheduleSubject[subjectName])
	{
		observer->RegistrationSubject(subjectName);
	}

	//予約を削除
	m_scheduleSubject.erase(itr);
}







