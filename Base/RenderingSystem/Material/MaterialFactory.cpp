#include"pch.h"
#include "MaterialFactory.h"
#include "NormalMaterial/NormalMaterial.h"
#include "Base/Mylib/Log.h"

/// <summary>
/// コンストラクタ
/// </summary>
MaterialFactory::MaterialFactory() {
	RegisterDefaultMaterials();
}

/// <summary>
/// 初期マテリアルの登録
/// </summary>
void MaterialFactory::RegisterDefaultMaterials()
{
	RegisterMaterial("Normal", [](ID3D11Device* device) ->std::unique_ptr<IMaterial> {
		return std::make_unique<NormalMaterial>(device);
		});
}

/// <summary>
/// マテリアルを登録
/// </summary>
/// <param name="name"></param>
/// <param name="creator"></param>
void MaterialFactory::RegisterMaterial(const std::string& name, MaterialCreator creator)
{
	//既に登録されているなら返す
	if (m_creators.find(name) != m_creators.end()) {
		Log::Warning("このマテリアルは既に登録されています");
		return;
	}
	//登録
	m_creators[name] = creator;
}

std::unique_ptr<IMaterial> MaterialFactory::CreateMaterial(const std::string& name, ID3D11Device* device)
{
	auto itr = m_creators.find(name);
	//登録されていないならnullptrを返す
	if (itr == m_creators.end())
	{
		Log::Warning("この名前は登録されていません");
		return nullptr;
	}

	return itr->second(device);
}
