#pragma once
#include"Base/RenderingSystem/Material/InstancingMaterial.h"

class NormalMaterial :public InstancingMaterial
{
public:
	NormalMaterial(ID3D11Device* device);
	~NormalMaterial() = default;

	void InitializeShaders(ID3D11Device* device) override;
	void InitializeInputLayout(ID3D11Device* device) override;

	void InitializeInstanceShaders(ID3D11Device* device) override;
	void InitializeInstanceInputLayout(ID3D11Device* device)override;
};