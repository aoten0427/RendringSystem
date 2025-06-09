#pragma once
#include"Base/Object/Object.h"

class TestObject :public Object
{
public:
	TestObject(Scene* scene);
	~TestObject() = default;
};
