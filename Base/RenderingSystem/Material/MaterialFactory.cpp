#include"pch.h"
#include "MaterialFactory.h"
#include "NormalMaterial/NormalMaterial.h"
#include "Base/Mylib/Log.h"

/// <summary>
/// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
/// </summary>
MaterialFactory::MaterialFactory() {
	RegisterDefaultMaterials();
}

/// <summary>
/// ‰Šúƒ}ƒeƒŠƒAƒ‹‚Ì“o˜^
/// </summary>
void MaterialFactory::RegisterDefaultMaterials()
{
	RegisterMaterial("Normal", [](ID3D11Device* device) ->std::unique_ptr<IMaterial> {
		return std::make_unique<NormalMaterial>(device);
		});
}

/// <summary>
/// ƒ}ƒeƒŠƒAƒ‹‚ğ“o˜^
/// </summary>
/// <param name="name"></param>
/// <param name="creator"></param>
void MaterialFactory::RegisterMaterial(const std::string& name, MaterialCreator creator)
{
	//Šù‚É“o˜^‚³‚ê‚Ä‚¢‚é‚È‚ç•Ô‚·
	if (m_creators.find(name) != m_creators.end()) {
		Log::Warning("‚±‚Ìƒ}ƒeƒŠƒAƒ‹‚ÍŠù‚É“o˜^‚³‚ê‚Ä‚¢‚Ü‚·");
		return;
	}
	//“o˜^
	m_creators[name] = creator;
}

std::unique_ptr<IMaterial> MaterialFactory::CreateMaterial(const std::string& name, ID3D11Device* device)
{
	auto itr = m_creators.find(name);
	//“o˜^‚³‚ê‚Ä‚¢‚È‚¢‚È‚çnullptr‚ğ•Ô‚·
	if (itr == m_creators.end())
	{
		Log::Warning("‚±‚Ì–¼‘O‚Í“o˜^‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ");
		return nullptr;
	}

	return itr->second(device);
}
