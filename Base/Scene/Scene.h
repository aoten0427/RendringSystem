// ================================================================ 
// �t�@�C���� : Scene.h
// �쐬�� : �i�R�ɓV
// ���� :  �V�[�����N���X
// ================================================================

#pragma once

// �O���錾
class CommonResources;
class Object;
class Camera;
class Canvas;


class SceneState;

class Scene
{
public:
	//�V�[��ID
	enum class SceneID
	{
		NONE,
		TITLE,
		SELECT,
		PLAY,
		RESULT,
		EDITOR,
		DEBUG
	};
	//�V�[���X�e�[�g
	enum class State
	{
		RESERVE, //�J�n
		PLAY,    //���s
		STOP,    //�X�g�b�v
		FEAD,    //�t�F�[�h
		END,     //�I��
	};
public:
	//���O�擾
	std::string GetName()const { return m_name; }
	//�R�������\�[�X�擾
	CommonResources* GetCommonResources()const { return m_commonResources; }
	//�J�����擾
	virtual Camera* GetCamera()const = 0;
	//�I�u�W�F�N�g�폜�t���O�I��
	void ObjectDestroyOn() { m_isObjectDestroy = true; }
private:
	//���O
	std::string m_name;
	//�l�N�X�g�V�[��
	SceneID m_nextSceneID;
	//�R�������\�[�X
	CommonResources* m_commonResources;
	//�Ǘ��I�u�W�F�N�g
	std::vector<std::unique_ptr<Object>> m_objects;
	//�ۗ��I�u�W�F�N�g
	std::vector<std::unique_ptr<Object>> m_pendingObjects;
	//�A�b�v�f�[�g�m�F
	bool m_updating;
	//�I�u�W�F�N�g�폜�t���O
	bool m_isObjectDestroy;

	//���
	SceneState* m_state;
public:
	//�R���X�g���N�^
	Scene(CommonResources* resources,std::string name);
	//�f�X�g���N�^
	virtual ~Scene();
	//������
	virtual void Initialize();
	//�A�b�v�f�[�g
	void Update(float deltatime);
	//�V�[���A�b�v�f�[�g
	virtual void SceneUpdate(float deltatime) { UNREFERENCED_PARAMETER(deltatime); };
	//�`��
	void Render();
	//�I������
	void Finalize();

	//�V�[��ID�擾
	virtual SceneID GetSceneID() = 0;
	//�V�[���؂�ւ�
	virtual void ChangeScene(SceneID nextscene) { m_nextSceneID = nextscene; };
	//�V�[��ID�擾
	virtual SceneID GetNextSceneID() { return m_nextSceneID; };

	//�I�u�W�F�N�g�ǉ�
	template<typename Obj,typename... Args>
	Obj* AddObject(Args&&... args);
	//�I�u�W�F�N�g�폜
	void RemoveObject();

	//��Ԑ؂�ւ�
	void ChangeState(Scene::State state);
	Scene::State GetState()const;
};

//�I�u�W�F�N�g�ǉ�
template<typename Obj, typename ...Args>
inline Obj* Scene::AddObject(Args && ...args)
{
	//�I�u�W�F�N�g����
	auto object = std::make_unique<Obj>(std::forward<Args>(args)...);
	//�߂�l����
	Obj* back = object.get();
	if (m_updating)
	{
		//�A�b�v�f�[�g���Ȃ�ۗ��I�u�W�F�N�g�ֈړ�
		m_pendingObjects.push_back(std::move(object));
	}
	else
	{
		//�A�b�v�f�[�g���łȂ��Ȃ�X�V�I�u�W�F�N�g�ֈړ�
		m_objects.push_back(std::move(object));
	}
	return back;
}
