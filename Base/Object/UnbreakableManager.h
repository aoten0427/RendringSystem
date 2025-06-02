// ================================================================ 
// �t�@�C���� : UnbreakableManager.h
// �쐬�� : �i�R�ɓV
// ���� :  �V�[�����܂����ł��j�󂳂�Ȃ��I�u�W�F�N�g���Ǘ�
// ================================================================

#pragma once
#include"Base/MyLib/Singleton.h"
#include"Base/Object/Object.h"

class UnbreakableManager : public Singleton<UnbreakableManager>
{
	friend class Singleton<UnbreakableManager>;
private:
	UnbreakableManager();
private:
	//�Ǘ��I�u�W�F�N�g�Ɩ��O
	std::unordered_map<std::string,std::unique_ptr<Object>> m_objects;
public:
	~UnbreakableManager() = default;

	//�A�b�v�f�[�g
	void Update(float deltatime);
	//�폜
	void Delete();
	//�I�u�W�F�N�g�ǉ�
	template<typename Obj, typename... Args>
	Obj* AddObject(std::string name, Args&&... args);
	//�V�[���؂�ւ��C�x���g
	void LoadScene(Scene* scene);
};

template<typename Obj, typename ...Args>
inline Obj* UnbreakableManager::AddObject(std::string name, Args&&... args)
{
	//���I�u�W�F�N�g�̕���������j�~
	if (m_objects.find(name) != m_objects.end())return nullptr;

	//�I�u�W�F�N�g����
	auto object = std::make_unique<Obj>(std::forward<Args>(args)...);
	//�߂�l����
	Obj* back = object.get();
	//�ۑ�
	m_objects.insert({ name,std::move(object) });

	return back;
}
