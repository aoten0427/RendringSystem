// ================================================================ 
// �t�@�C���� : EventManager.h
// �쐬�� : �i�R�ɓV
// ���� :  �C�x���g�̓o�^�Ǘ����s��(�V���O���g��)
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
	//�o�^�T�u�W�F�N�g�Ɩ��O
	std::unordered_map<std::string, ISubject*> m_subjects;
	//�o�^�\��T�u�W�F�N�g��
	std::unordered_map<std::string,std::unordered_set<IObserver*>> m_scheduleSubject;
public:
	~EventManager();

	//�T�u�W�F�N�g�ǉ�
	void AddSubject(ISubject* subject);
	//�T�u�W�F�N�g�폜
	void RemoveSubject(ISubject* subject);

	/// <summary>
	/// �I�u�U�[�o�[�ǉ�
	/// </summary>
	/// <param name="subjectName">�ǉ��T�u�W�F�N�g��</param>
	/// <param name="observer">�ǉ��I�u�U�[�o�[</param>
	/// <returns>�ǉ�������</returns>
	bool AddObserver(std::string subjectName, IObserver* observer)
	{
		//�T�u�W�F�N�g����
		auto itr = m_subjects.find(subjectName);
		//�Ȃ��ꍇ���s
		if (itr == m_subjects.end())
		{
			//�\����ɓ���Ă���
			AddScheduleSubject(subjectName, observer);
			return false;
		}
		//�ǉ�����
		return (*itr).second->AddObserver(observer);
	}

	/// <summary>
	/// �I�u�U�[�o�[�폜
	/// </summary>
	/// <param name="subjectName">�폜�I�u�W�F�N�g��</param>
	/// <param name="observer">�폜�I�u�U�[�o�[</param>
	/// <returns>�폜������</returns>
	bool RemoveObserver(std::string subjectName, IObserver* observer)
	{
		//�T�u�W�F�N�g����
		auto itr = m_subjects.find(subjectName);
		//�Ȃ��ꍇ���s
		if (itr == m_subjects.end())
		{
			//�\���₩��폜
			RemoveScheduleSubject(subjectName, observer);
			return false;
		}
		//�폜����
		return (*itr).second->RemoveObserver(observer);
	}

	//�\����쐬
	void AddScheduleSubject(std::string subjectName, IObserver* observer);
	//�\�񂩂�폜
	void RemoveScheduleSubject(std::string subjectName, IObserver* observer);
	//�\��̗v�f���T�u�W�F�N�g�ɒǉ�
	void CheckAddScheduleSubject(std::string subjectName);

	
};