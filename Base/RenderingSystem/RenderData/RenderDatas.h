#pragma once

class IMaterial;


class RenderDatas
{
public:
	/// <summary>
	/// 一度で描画するデータのまとまり
	/// </summary>
	struct Data
	{
		//マテリアル
		IMaterial* m_material;
		//モデル
		DirectX::Model* m_model;
		//描画行列
		std::vector<const DirectX::SimpleMath::Matrix*> m_matrixs;
		//描画したか
		bool m_isRenderring;
	};
private:
	std::vector<Data> m_renderDatas;
public:
	RenderDatas();

	void AddInstance(IMaterial* material, DirectX::Model* model,const DirectX::SimpleMath::Matrix* matrix);

	std::vector<Data>& GetRenderData() { return m_renderDatas; }
};