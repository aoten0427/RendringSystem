// ================================================================ 
// �t�@�C���� : IObserver
// �쐬�� : �i�R�ɓV
// ���� :  Observer�C���^�[�t�F�[�X
// ================================================================

#pragma once

class IObserver
{
public:
	virtual ~IObserver() = default;

	virtual void RegistrationSubject(std::string subjectName) = 0;
};