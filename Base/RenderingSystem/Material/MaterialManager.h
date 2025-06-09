#pragma once
class IMaterial;

/// <summary>
/// クラスに存在するマテリアルを管理
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