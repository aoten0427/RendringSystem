// ================================================================ 
// �t�@�C���� : ISubject.h
// �쐬�� : �i�R�ɓV
// ���� :  Subject�C���^�[�t�F�[�X
// ================================================================

#pragma once
#include<string>


class IObserver;

class ISubject
{
public:
	virtual ~ISubject() = default;
	//���O�擾
	virtual std::string GetName()const = 0;
	//�I�u�U�[�o�[�ǉ�
	virtual bool AddObserver(IObserver* observer) = 0;
	//�I�u�U�[�o�[�폜
	virtual bool RemoveObserver(IObserver* observer) = 0;
};