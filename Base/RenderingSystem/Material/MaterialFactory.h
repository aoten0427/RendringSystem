#pragma once
#include"Base/Mylib/Singleton.h"
#include"IMaterial.h"

/// <summary>
/// �}�e���A���𐶐�����
/// </summary>
class MaterialFactory :public Singleton<MaterialFactory>
{
	friend class Singleton<MaterialFactory>;
public:
	using MaterialCreator = std::function<std::unique_ptr<IMaterial>(ID3D11Device*)>;
private:
	//���O�ƑΉ������}�e���A����ۑ�
	std::unordered_map<std::string, MaterialCreator> m_creators;
private:
	MaterialFactory();
	//�����}�e���A���̓o�^
	void RegisterDefaultMaterials();
public:
	//�}�e���A����o�^
	void RegisterMaterial(const std::string& name, MaterialCreator creator);
	//�}�e���A���𐶐�
	std::unique_ptr<IMaterial> CreateMaterial(const std::string& name, ID3D11Device* device);
};