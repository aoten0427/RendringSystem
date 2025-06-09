#pragma once
#include"Base/Component/Component.h"

class RenderingSystem;
class IMaterial;

/// <summary>
/// 3D���f���`��
/// </summary>
class Model3D :public Component
{
public:
	//�Q�b�^�[
	DirectX::Model* GetModel() { return m_model; }
	IMaterial* GetMaterial() { return m_material; }
	DirectX::SimpleMath::Matrix& GetMatrix();
	const DirectX::SimpleMath::Matrix* GetpMatrix();

	//�Z�b�^�[
	void SetMaterial(IMaterial* material) { m_material = material; }
	void Setmaterial(std::unique_ptr<IMaterial> material);
private:
	//�����_�����O�V�X�e��
	RenderingSystem* m_renderingSystem;
	//�`�惂�f��
	DirectX::Model* m_model;
	//�}�e���A��
	IMaterial* m_material;
	//�I�u�W�F�N�g���܂߂��s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	//���g�̍s��
	DirectX::SimpleMath::Matrix m_loaclMatrix;
public:
	Model3D(Object* object);
	~Model3D() = default;

	void LoadModel(const std::string& name);


};
