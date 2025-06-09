#pragma once
#include"Base/Mylib/Singleton.h"
#include"IMaterial.h"

/// <summary>
/// マテリアルを生成する
/// </summary>
class MaterialFactory :public Singleton<MaterialFactory>
{
	friend class Singleton<MaterialFactory>;
public:
	using MaterialCreator = std::function<std::unique_ptr<IMaterial>(ID3D11Device*)>;
private:
	//名前と対応したマテリアルを保存
	std::unordered_map<std::string, MaterialCreator> m_creators;
private:
	MaterialFactory();
	//初期マテリアルの登録
	void RegisterDefaultMaterials();
public:
	//マテリアルを登録
	void RegisterMaterial(const std::string& name, MaterialCreator creator);
	//マテリアルを生成
	std::unique_ptr<IMaterial> CreateMaterial(const std::string& name, ID3D11Device* device);
};