// ================================================================ 
// �t�@�C���� : GameResources.h
// �쐬�� : �i�R�ɓV
// ���� :  �摜�A���f�����Ǘ�
// ================================================================
#include"pch.h"
#include"GameResources.h"
#include"nlohmann/json.hpp"
#include <fstream>
#include <sstream>

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameResources::GameResources()
	:
	m_device{nullptr},
	m_models{},
	m_textures{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameResources::~GameResources()
{
	m_models.clear();
	m_textures.clear();
}

/// <summary>
/// �f�[�^�̓ǂݍ���
/// </summary>
/// <param name="Pathnum">�p�X�̔ԍ�</param>
void GameResources::LoadData(int Pathnum)
{
	//JSON�t�@�C���I��
	std::string file = "Resources/JSON/GameResources/Path" + std::to_string(Pathnum) + ".json";

	//�ǂݍ���
	std::ifstream ifs(file.c_str());
	if (ifs.good())
	{
		nlohmann::json m_json;
		ifs >> m_json;

		//���f���f�[�^�̓ǂݍ���
		for (auto itr = m_json["Model"].begin(); itr != m_json["Model"].end(); itr++)
		{
			std::string name = itr.key();
			std::string fileName = itr.value();
			LoadModels(name, fileName);
		}

		//�摜�f�[�^�̓ǂݍ���
		for (auto itr = m_json["Texture"].begin(); itr != m_json["Texture"].end(); itr++)
		{
			std::string name = itr.key();
			std::string fileName = itr.value();
			LoadTexture(name, fileName);
		}

		//�t�@�C�������
		ifs.close();
	}
}

/// <summary>
/// ���f���擾
/// </summary>
/// <param name="name">���O</param>
/// <returns>���f��</returns>
DirectX::Model* GameResources::GetModel(std::string name)
{
	auto itr = m_models.find(name);
	if (itr != m_models.end())
	{
		return m_models[name].get();
	}
	return nullptr;
}

/// <summary>
/// �摜�擾
/// </summary>
/// <param name="name">���O</param>
/// <returns>�摜</returns>
ID3D11ShaderResourceView* GameResources::GetTexture(std::string name)
{
	auto itr = m_textures.find(name);
	if (itr != m_textures.end())
	{
		return m_textures[name].Get();
	}
	return nullptr;
}

/// <summary>
/// ���f���̍쐬
/// </summary>
/// <param name="name">�o�^��</param>
/// <param name="fileName">���f���̃t�@�C����</param>
void GameResources::LoadModels(std::string name, std::string fileName)
{
	std::string folderPath = "Resources/Models/";

	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(m_device);
	std::wstring myWideString = std::wstring(folderPath.begin(), folderPath.end());
	const wchar_t* folder = myWideString.c_str();
	fx->SetDirectory(folder);

	//	���f���̍쐬
	folderPath += fileName;
	myWideString = std::wstring(folderPath.begin(), folderPath.end());
	folder = myWideString.c_str();
	std::unique_ptr<DirectX::Model> model = DirectX::Model::CreateFromCMO(m_device, folder, *fx);

	//�}��
	m_models.insert({ name, std::move(model) });
}

/// <summary>
/// �摜�̍쐬
/// </summary>
/// <param name="name">�o�^��</param>
/// <param name="fileName">�摜�̃t�@�C����</param>
void GameResources::LoadTexture(std::string name, std::string fileName)
{
	std::string folderPath = "Resources/Textures/" + fileName;

	std::wstring myWideString = std::wstring(folderPath.begin(), folderPath.end());
	const wchar_t* file = myWideString.c_str();

	// �摜�̍쐬
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> image;
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			m_device,
			file,
			nullptr,
			image.ReleaseAndGetAddressOf(),
			0
		)
	);

	//�}��
	m_textures.insert({ name,image });
}






