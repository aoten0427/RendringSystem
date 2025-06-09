#pragma once
class IMaterial;

/// <summary>
/// �N���X�ɑ��݂���}�e���A�����Ǘ�
/// </summary>
class MaterialManager
{
private:
	std::vector<std::unique_ptr<IMaterial>> m_materials;
public:
	MaterialManager();
	~MaterialManager() = default;

	IMaterial* AddMaterial(std::unique_ptr<IMaterial> material);
};