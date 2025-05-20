/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "IScene.h"
#include "Game/Mylib/Model3D.h"
// �O���錾
class CommonResources;
class DebugCamera;


class PlayScene final :
    public IScene
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
	//���f��
	Model3D m_model;
public:
	PlayScene();
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};
