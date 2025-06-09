#pragma once

class IMaterial;


class RenderDatas
{
public:
	/// <summary>
	/// ��x�ŕ`�悷��f�[�^�̂܂Ƃ܂�
	/// </summary>
	struct Data
	{
		//�}�e���A��
		IMaterial* m_material;
		//���f��
		DirectX::Model* m_model;
		//�`��s��
		std::vector<const DirectX::SimpleMath::Matrix*> m_matrixs;
		//�`�悵����
		bool m_isRenderring;
	};
private:
	std::vector<Data> m_renderDatas;
public:
	RenderDatas();

	void AddInstance(IMaterial* material, DirectX::Model* model,const DirectX::SimpleMath::Matrix* matrix);

	std::vector<Data>& GetRenderData() { return m_renderDatas; }
};