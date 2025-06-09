#include"pch.h"
#include"RenderDatas.h"

RenderDatas::RenderDatas()
{
}

void RenderDatas::AddInstance(IMaterial* material, DirectX::Model* model,const DirectX::SimpleMath::Matrix* matrix)
{
	auto itr = std::find_if(m_renderDatas.begin(), m_renderDatas.end(), [&](Data data) {
		return (data.m_material == material) && (data.m_model == model);
		});

	if (itr != m_renderDatas.end())
	{
		(*itr).m_matrixs.push_back(matrix);
	}
	else
	{
		Data newdata;
		newdata.m_material = material;
		newdata.m_model = model;
		newdata.m_matrixs.push_back(matrix);
		m_renderDatas.push_back(newdata);
	}
}
