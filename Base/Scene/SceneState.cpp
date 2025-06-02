// ================================================================ 
// ファイル名 : SceneState.cpp
// 作成者 : 景山碧天
// 説明 :  シーンの状態の管理
// ================================================================
#include"pch.h"
#include"SceneState.h"
#include"Base/Event/Subject.h"

#include"Base/CommonResources.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
SceneState::SceneState(Scene* scene) :Object(scene)
,
m_currentState{ Scene::State::FEAD },
m_nextState{ Scene::State::FEAD }
{
	//状態遷移時に呼び出し
	m_changeStateSubject = AddComponent<Subject<Scene::State, Scene::State>>(this, "SceneStateChange");
	//特定の状態になった時に呼び出し
	m_reserveSubject = AddComponent<Subject<>>(this, "Reserve");
	m_playSubject = AddComponent<Subject<>>(this, "Play");
	m_stopSubject = AddComponent<Subject<>>(this, "Stop");
	m_endSubject = AddComponent<Subject<>>(this, "End");
}

/// <summary>
/// ステートの変更指示
/// </summary>
/// <param name="state">変更ステート</param>
void SceneState::ChangeState(Scene::State state)
{
	m_nextState = state;
}

/// <summary>
/// ステートの変更
/// </summary>
void SceneState::ChangeState()
{
	//auto debug = GetCommonResources()->GetDebugString();
	////テスト用
	//switch (m_currentState)
	//{
	//case Scene::State::RESERVE:
	//	debug->AddString("Reserve");
	//	break;
	//case Scene::State::PLAY:
	//	debug->AddString("Play");
	//	break;
	//case Scene::State::STOP:
	//	debug->AddString("Stop");
	//	break;
	//case Scene::State::FEAD:
	//	debug->AddString("Fead");
	//	break;
	//case Scene::State::END:
	//	debug->AddString("End");
	//	break;
	//default:
	//	break;
	//}



	//現在と同じならパス
	if (m_currentState == m_nextState)return;

	//変更処理
	Scene::State oldState = m_currentState;
	m_currentState = m_nextState;
	//状態遷移時通知
	m_changeStateSubject->Notify(m_currentState, oldState);
	//各状態通知
	switch (m_currentState)
	{
	case Scene::State::RESERVE:
		m_reserveSubject->Notify();
		break;
	case Scene::State::PLAY:
		m_playSubject->Notify();
		break;
	case Scene::State::STOP:
		m_stopSubject->Notify();
		break;
	case Scene::State::FEAD:
		break;
	case Scene::State::END:
		m_endSubject->Notify();
		break;
	default:
		break;
	}
}
