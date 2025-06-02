// ================================================================ 
// �t�@�C���� : EventManager.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �C�x���g�̓o�^�Ǘ����s��(�V���O���g��)
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
/// �T�u�W�F�N�g�ǉ�
/// </summary>
/// <param name="subject">�ǉ��T�u�W�F�N�g</param>
void EventManager::AddSubject(ISubject* subject)
{
	auto itr = m_subjects.find(subject->GetName());
	if (itr != m_subjects.end())return;

	m_subjects.insert({ subject->GetName(),subject });

	CheckAddScheduleSubject(subject->GetName());
}

/// <summary>
/// �T�u�W�F�N�폜
/// </summary>
/// <param name="subject">�폜�T�u�W�F�N�g</param>
void EventManager::RemoveSubject(ISubject* subject)
{
	auto itr = m_subjects.find(subject->GetName());
	if (itr == m_subjects.end())return;

	m_subjects.erase(itr);
}

/// <summary>
/// �T�u�W�F�N�g�ւ̓o�^��\�񂷂�
/// </summary>
/// <param name="subjectName">�\��T�u�W�F�N�g��</param>
/// <param name="observer">�I�u�U�[�o�[</param>
void EventManager::AddScheduleSubject(std::string subjectName, IObserver* observer)
{
	//�\����쐬
	m_scheduleSubject[subjectName].insert(observer);
}

/// <summary>
/// �\��̍폜
/// </summary>
/// <param name="subjectName">�폜�T�u�W�F�N�g��</param>
/// <param name="observer">�폜�I�u�U�[�o�[</param>
void EventManager::RemoveScheduleSubject(std::string subjectName, IObserver* observer)
{
	auto itr = m_scheduleSubject.find(subjectName);
	if (itr == m_scheduleSubject.end())return;
	//�\�񂩂�폜
	m_scheduleSubject[subjectName].erase(observer);
}

/// <summary>
/// �\��̗v�f���T�u�W�F�N�g�ɒǉ�
/// </summary>
/// <param name="subjectName">�T�u�W�F�N�g��</param>
void EventManager::CheckAddScheduleSubject(std::string subjectName)
{
	//�\��ɓ����Ă��邩����
	auto itr = m_scheduleSubject.find(subjectName);
	if (itr == m_scheduleSubject.end())return;

	//�\��I�u�U�[�o�[��o�^����
	for (auto& observer : m_scheduleSubject[subjectName])
	{
		observer->RegistrationSubject(subjectName);
	}

	//�\����폜
	m_scheduleSubject.erase(itr);
}







