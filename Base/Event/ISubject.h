// ================================================================ 
// ファイル名 : ISubject.h
// 作成者 : 景山碧天
// 説明 :  Subjectインターフェース
// ================================================================

#pragma once
#include<string>


class IObserver;

class ISubject
{
public:
	virtual ~ISubject() = default;
	//名前取得
	virtual std::string GetName()const = 0;
	//オブザーバー追加
	virtual bool AddObserver(IObserver* observer) = 0;
	//オブザーバー削除
	virtual bool RemoveObserver(IObserver* observer) = 0;
};