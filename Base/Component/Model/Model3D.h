#pragma once
#include"Base/Component/Component.h"

class RenderingSystem;
class IMaterial;

/// <summary>
/// 3Dモデル描画
/// </summary>
class Model3D :public Component
{
public:
	//ゲッター
	DirectX::Model* GetModel() { return m_model; }
	IMaterial* GetMaterial() { return m_material; }
	DirectX::SimpleMath::Matrix& GetMatrix();
	const DirectX::SimpleMath::Matrix* GetpMatrix();

	//セッター
	void SetMaterial(IMaterial* material) { m_material = material; }
	void Setmaterial(std::unique_ptr<IMaterial> material);
private:
	//レンダリングシステム
	RenderingSystem* m_renderingSystem;
	//描画モデル
	DirectX::Model* m_model;
	//マテリアル
	IMaterial* m_material;
	//オブジェクトも含めた行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	//自身の行列
	DirectX::SimpleMath::Matrix m_loaclMatrix;
public:
	Model3D(Object* object);
	~Model3D() = default;

	void LoadModel(const std::string& name);


};
