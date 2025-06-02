// ================================================================ 
// �t�@�C���� : Subject.h
// �쐬�� : �i�R�ɓV
// ���� :  �C�x���g�ʒm���s��
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
	//���O�擾
	std::string GetName()const override { return m_name; }
private:
	//���O
	std::string m_name;
	//�Ăяo���I�u�U�[�o�[
	std::unordered_set<Observer<Args...>*> m_observers;
public:
	//�R���X�g���N�^
	Subject(Object* object, std::string name) :Component(object)
		,
		m_name{ name },
		m_observers{}
	{
		//�}�l�[�W���ɓo�^
		EventManager::GetInstance()->AddSubject(this);
	}
	~Subject()
	{
		//�}�l�[�W������폜
		EventManager::GetInstance()->RemoveSubject(this);
	}

	/// <summary>
	/// �I�u�U�[�o�[�ǉ�
	/// </summary>
	/// <param name="observer"></param>
	bool AddObserver(IObserver* observer)override
	{
		//�ϊ�
		auto castedObserver = static_cast<Observer<Args...>*>(observer);
		if (castedObserver)
		{
			//�ǉ�����
			return AddObservers(castedObserver);
		}
		return false;
	}

	/// <summary>
	/// �I�u�U�[�o�[�폜
	/// </summary>
	/// <param name="observer"></param>
	bool RemoveObserver(IObserver* observer)override
	{
		//�ϊ�
		auto castedObserver = static_cast<Observer<Args...>*>(observer);
		if (castedObserver)
		{
			//�폜����
			return RemoveObservers(castedObserver);
		}
		return false;
	}

	//���s
	void Notify(Args...args)
	{
		for (auto& observers : m_observers)
		{
			observers->Execution(std::forward<Args>(args)...);
		}
	}

	//�ǉ�
	bool AddObservers(Observer<Args...>* observer)
	{
		//����
		auto itr = m_observers.find(observer);
		//����ꍇ���s
		if (itr != m_observers.end())return false;
		//�ǉ�
		m_observers.insert(observer);
		return true;
	}

	//�폜
	bool RemoveObservers(Observer<Args...>* observer)
	{
		//����
		auto itr = m_observers.find(observer);
		//�Ȃ��ꍇ���s
		if (itr == m_observers.end())return false;
		//�폜
		m_observers.erase(itr);
		return true;
	}
};