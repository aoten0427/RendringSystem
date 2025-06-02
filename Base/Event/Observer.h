// ================================================================ 
// �t�@�C���� : Observer.h
// �쐬�� : �i�R�ɓV
// ���� :  �ʒm���󂯂ē�����s��
// ================================================================

#pragma once
#include"Base/Event/IObserver.h"
#include"Base/Event/EventManager.h"
#include"Base/Component/Component.h"

template<typename ... Args>
class Observer :public Component,public IObserver
{
private:
	//���s�֐�
	std::function<void(Args...)> m_function;
	//�o�^�T�u�W�F�N�g��
	std::unordered_set<std::string> m_registrationSubject;
public:
	//�R���X�g���N�^
	Observer(Object* object) :Component(object)
		,
		m_function{nullptr}
	{

	}
	//�f�X�g���N�^
	~Observer()
	{
		m_function = nullptr;
		//�o�^�T�u�W�F�N�g�ɍ폜�˗�
		for (auto& subjectName : m_registrationSubject)
		{
			EventManager::GetInstance()->RemoveObserver(subjectName, this);
		}
	}

	//���s
	void Execution(Args...args)
	{
		if (!m_function)return;
		m_function(std::forward<Args>(args)...);
	}

	//�֐��Z�b�g
	void SetFunction(std::function<void(Args...)> function)
	{
		m_function = function;
	}

	//�T�u�W�F�N�g�o�^
	void RegistrationSubject(std::string subjectName)
	{
		//�}�l�[�W���[�ɓo�^�˗�
		EventManager::GetInstance()->AddObserver(subjectName, this);
		//���������疼�O�o�^
		m_registrationSubject.insert(subjectName);
		
	}

	//�T�u�W�F�N�g�폜
	void RemoveSubject(std::string subjectName)
	{
		//�}�l�[�W���[�ɍ폜�˗�
		if (EventManager::GetInstance()->RemoveObserver(subjectName, this))
		{
			//���������疼�O�폜
			m_registrationSubject.erase(subjectName);
		}
	}
};