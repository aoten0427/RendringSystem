// ================================================================ 
// ファイル名 : SceneState.h
// 作成者 : 景山碧天
// 説明 :  シーンの状態の管理
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Base/Scene/Scene.h"

template<typename...Args>
class Subject;

class SceneState :public Object
{
public:
	Scene::State GetState()const { return m_currentState; }
private:
	//現在の状態
	Scene::State m_currentState;
	//次の状態
	Scene::State m_nextState;

	//状態遷移時に呼び出すサブジェクト
	Subject<Scene::State, Scene::State>* m_changeStateSubject;
	Subject<>* m_reserveSubject;
	Subject<>* m_playSubject;
	Subject<>* m_stopSubject;
	Subject<>* m_endSubject;
public:
	//コンストラクタ
	SceneState(Scene* scene);
	//デストラクタ
	~SceneState()override = default;

	void ChangeState(Scene::State state);
	void ChangeState();

private:
};