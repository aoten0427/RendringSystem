#include"pch.h"
#include"MaterialManager.h"
#include"IMaterial.h"

MaterialManager::MaterialManager()
{

}

IMaterial* MaterialManager::AddMaterial(std::unique_ptr<IMaterial> material)
{
	IMaterial* back = material.get();
	m_materials.push_back(std::move(material));
	return back;
}
