// ================================================================ 
// �t�@�C���� : SceneState.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �V�[���̏�Ԃ̊Ǘ�
// ================================================================
#include"pch.h"
#include"SceneState.h"
#include"Base/Event/Subject.h"

#include"Base/CommonResources.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
SceneState::SceneState(Scene* scene) :Object(scene)
,
m_currentState{ Scene::State::FEAD },
m_nextState{ Scene::State::FEAD }
{
	//��ԑJ�ڎ��ɌĂяo��
	m_changeStateSubject = AddComponent<Subject<Scene::State, Scene::State>>(this, "SceneStateChange");
	//����̏�ԂɂȂ������ɌĂяo��
	m_reserveSubject = AddComponent<Subject<>>(this, "Reserve");
	m_playSubject = AddComponent<Subject<>>(this, "Play");
	m_stopSubject = AddComponent<Subject<>>(this, "Stop");
	m_endSubject = AddComponent<Subject<>>(this, "End");
}

/// <summary>
/// �X�e�[�g�̕ύX�w��
/// </summary>
/// <param name="state">�ύX�X�e�[�g</param>
void SceneState::ChangeState(Scene::State state)
{
	m_nextState = state;
}

/// <summary>
/// �X�e�[�g�̕ύX
/// </summary>
void SceneState::ChangeState()
{
	//auto debug = GetCommonResources()->GetDebugString();
	////�e�X�g�p
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



	//���݂Ɠ����Ȃ�p�X
	if (m_currentState == m_nextState)return;

	//�ύX����
	Scene::State oldState = m_currentState;
	m_currentState = m_nextState;
	//��ԑJ�ڎ��ʒm
	m_changeStateSubject->Notify(m_currentState, oldState);
	//�e��Ԓʒm
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
