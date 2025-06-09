#include"pch.h"
#include "MaterialFactory.h"
#include "NormalMaterial/NormalMaterial.h"
#include "Base/Mylib/Log.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
MaterialFactory::MaterialFactory() {
	RegisterDefaultMaterials();
}

/// <summary>
/// �����}�e���A���̓o�^
/// </summary>
void MaterialFactory::RegisterDefaultMaterials()
{
	RegisterMaterial("Normal", [](ID3D11Device* device) ->std::unique_ptr<IMaterial> {
		return std::make_unique<NormalMaterial>(device);
		});
}

/// <summary>
/// �}�e���A����o�^
/// </summary>
/// <param name="name"></param>
/// <param name="creator"></param>
void MaterialFactory::RegisterMaterial(const std::string& name, MaterialCreator creator)
{
	//���ɓo�^����Ă���Ȃ�Ԃ�
	if (m_creators.find(name) != m_creators.end()) {
		Log::Warning("���̃}�e���A���͊��ɓo�^����Ă��܂�");
		return;
	}
	//�o�^
	m_creators[name] = creator;
}

std::unique_ptr<IMaterial> MaterialFactory::CreateMaterial(const std::string& name, ID3D11Device* device)
{
	auto itr = m_creators.find(name);
	//�o�^����Ă��Ȃ��Ȃ�nullptr��Ԃ�
	if (itr == m_creators.end())
	{
		Log::Warning("���̖��O�͓o�^����Ă��܂���");
		return nullptr;
	}

	return itr->second(device);
}
