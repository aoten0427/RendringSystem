// ================================================================ 
// �t�@�C���� : Object.h
// �쐬�� : �i�R�ɓV
// ���� :  �I�u�W�F�N�g���N���X
// ================================================================

#pragma once
#include"Base/Component/Component.h"


class Scene;
class CommonResources;
class Transform;
class Collider;

//�I�u�W�F�N�g�^�O
enum class ObjectTag
{
	Player,
	Stage,
	ClearStage,
	Target,
	Search,
	TargetBox,
	Enemy,
	Goal,
	Coin,
	Help,
	Spike,
	Laser,
	Barrier,
	Other
};

class Object
{
public:
	//�^�O�擾
	virtual ObjectTag GetTag() { return ObjectTag::Other; };
	//�V�[���Z�b�g
	void SetScene(Scene* scene){ m_scene = scene; }
	//�V�[���擾
	Scene* GetScene() const { return m_scene; }
	//�R�������\�[�X�擾
	CommonResources* GetCommonResources()const{return m_commonResources;}
	//�g�����X�t�H�[���擾
	Transform* GetTransform() const { return m_transform; }
	//�A�N�e�B�u�Z�b�g
	void SetActive(bool active);
	//�A�N�e�B�u�擾
	bool GetActive() const { return m_isActive; }
	//�j��t���O�擾
	bool GetIsDestroy()const { return m_isDestroy; }
	//�R���|�[�l���g�j��t���O�Z�b�g
	void ComponentDestroyOn() { m_isComponentDestroy = true; }
private:
	//�����V�[��
	Scene* m_scene;
	//�R�������\�[�X
	CommonResources* m_commonResources;
	//�R���|�[�l���g
	std::vector<std::unique_ptr<Component>> m_components;
	//�g�����X�t�H�[��
	Transform* m_transform;
	//�A�N�e�B�u�t���O
	bool m_isActive;
	//�j��t���O
	bool m_isDestroy;
	//�R���|�[�l���g�j��t���O
	bool m_isComponentDestroy;
public:
	//�R���X�g���N�^
	Object(Scene* scene);
	//�f�X�g���N�^
	virtual ~Object();
	//������
	virtual void Initialize() {};
	//�A�b�v�f�[�g
	void Update(float deltatime);
	//�R���|�[�l���g�A�b�v�f�[�g
	void ComponentUpdate(float deltatime);
	//���g�̃A�b�v�f�[�goverride�p
	virtual void ObjectUpdate(float deltatime) { UNREFERENCED_PARAMETER(deltatime); };
	//�I������
	virtual void Finalize() {};
	//�폜
	void Destroy();
	//�R���|�[�l���g�ǉ�
	template<typename Comp, typename... Args>
	Comp* AddComponent(Args&&... args);
	//�R���|�[�l���g�擾
	template<typename T>
	T* GetComponent();
	

	//����n
	//Trigger�̎��s�L��
	virtual bool IsTriggerAct(Collider* collider) { UNREFERENCED_PARAMETER(collider); return true; }
	//Collision�̎��s�L��
	virtual bool IsCollisionAct(Collider* collider) { UNREFERENCED_PARAMETER(collider); return true; }
	//�����߂�(�����o����)
	virtual void PushBack(DirectX::SimpleMath::Vector3 pushback);
	//Trigger����
	virtual void OnTrigger(Collider* collider) { UNREFERENCED_PARAMETER(collider); };
	//Collision����
	virtual void OnCollision(Collider* collider) { UNREFERENCED_PARAMETER(collider); };
	//�߂荞�݌v�Z���s�̗L��
	virtual bool IsDetectionAct(Collider* collider) { UNREFERENCED_PARAMETER(collider); return true; }

	//�V�[���؂�ւ��C�x���g
	virtual void LoadScene(Scene* scene) { UNREFERENCED_PARAMETER(scene); };
private:
	//�R���|�[�l���g�폜
	void RemoveComponent();
};


//�R���|�[�l���g�ǉ�
template<typename Comp, typename ...Args>
inline Comp* Object::AddComponent(Args && ...args)
{
	// �R���|�[�l���g����
	auto component = std::make_unique<Comp>(std::forward<Args>(args)...);
	auto order = component->GetUpdateOrder();

	// �}���ʒu���I�[�_�[���猟��
	auto itr = std::find_if(m_components.begin(), m_components.end(),
		[order](const std::unique_ptr<Component>& comp) {
			return comp->GetUpdateOrder() > order;
		});

	// �߂�l����
	Comp* back = component.get();
	// �}��
	m_components.insert(itr, std::move(component));

	return back;
}


//�R���|�[�l���g�擾
template<typename Comp>
inline Comp* Object::GetComponent()
{
	//�w��N���X���������ŏ��Ɍ��������̂�Ԃ�
	for (auto& component : m_components) {
		if (typeid(*component) == typeid(Comp)) {
			Comp* comp = dynamic_cast<Comp*>(component.get());
			return comp;
		}
	}
	return nullptr;
}
