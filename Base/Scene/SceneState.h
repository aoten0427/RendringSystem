// ================================================================ 
// �t�@�C���� : SceneState.h
// �쐬�� : �i�R�ɓV
// ���� :  �V�[���̏�Ԃ̊Ǘ�
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
	//���݂̏��
	Scene::State m_currentState;
	//���̏��
	Scene::State m_nextState;

	//��ԑJ�ڎ��ɌĂяo���T�u�W�F�N�g
	Subject<Scene::State, Scene::State>* m_changeStateSubject;
	Subject<>* m_reserveSubject;
	Subject<>* m_playSubject;
	Subject<>* m_stopSubject;
	Subject<>* m_endSubject;
public:
	//�R���X�g���N�^
	SceneState(Scene* scene);
	//�f�X�g���N�^
	~SceneState()override = default;

	void ChangeState(Scene::State state);
	void ChangeState();

private:
};