// ================================================================ 
// ファイル名 : IObserver
// 作成者 : 景山碧天
// 説明 :  Observerインターフェース
// ================================================================

#pragma once

class IObserver
{
public:
	virtual ~IObserver() = default;

	virtual void RegistrationSubject(std::string subjectName) = 0;
};