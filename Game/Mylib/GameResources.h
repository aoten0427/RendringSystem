// ================================================================ 
// �t�@�C���� : GameResources.h
// �쐬�� : �i�R�ɓV
// ���� :  �摜�A���f�����Ǘ�
// ================================================================
#pragma once
#include"Singleton.h"

class GameResources:public Singleton<GameResources> 
{
	friend class Singleton<GameResources>;
private:
	GameResources();
private:
	//�f�o�C�X
	ID3D11Device* m_device;
	//���f�����
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> m_models;
	//�摜���
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;
public:
	~GameResources();
	//�f�o�C�X�Z�b�g
	void SetDevice(ID3D11Device* device) { m_device = device; }
	//�f�[�^�ǂݍ���
	void LoadData(int Pathnum = 1);
	//���f�����o��
	DirectX::Model* GetModel(std::string name);
	//�摜���o��
	ID3D11ShaderResourceView* GetTexture(std::string name);
private:
	//���f���ǂݍ���
	void LoadModels(std::string name, std::string fileName);
	//�摜�ǂݍ���
	void LoadTexture(std::string name, std::string fileName);
};