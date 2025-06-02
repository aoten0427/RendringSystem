// ================================================================ 
// ファイル名 : Component.cpp
// 作成者 : 景山碧天
// 説明 :  コンポーネント基底クラス
// ================================================================
#include"pch.h"
#include"Component.h"
#include"Base/Object/Object.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
Component::Component(Object* object,int updateorder)
	:
	m_object{object},
	m_isActive{true},
	m_updateOrder{updateorder},
	m_isDestroy{false}
{
	assert(object);
	m_commonResources = object->GetCommonResources();
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Component::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

/// <summary>
/// 自身を破壊
/// </summary>
void Component::Destroy()
{
	GetObject()->ComponentDestroyOn();
	m_isDestroy = true;
	SetActive(false);
}


