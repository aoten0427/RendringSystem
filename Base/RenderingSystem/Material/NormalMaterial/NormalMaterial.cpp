#include"pch.h"
#include"NormalMaterial.h"
#include"Base/Resources/ShaderManager.h"

NormalMaterial::NormalMaterial(ID3D11Device* device)
{
	Material::Initialize(device);
	InstancingMaterial::Initialize(device);
}

void NormalMaterial::InitializeShaders(ID3D11Device* device)
{
	m_vertexShader = ShaderManager::CreateVSShader(device, "NormalMaterialVS.cso");
	m_pixelShader = ShaderManager::CreatePSShader(device, "NormalMaterialPS.cso");
}

void NormalMaterial::InitializeInputLayout(ID3D11Device* device)
{
	m_inputLayout = ShaderManager::CreateInputLayout(device, MODEL_INPUT_LAYOUT, "NormalMaterialVS.cso");
}

void NormalMaterial::InitializeInstanceShaders(ID3D11Device* device)
{
	m_instanceVertexShader = ShaderManager::CreateVSShader(device, "InstancingBasicVS.cso");
}

void NormalMaterial::InitializeInstanceInputLayout(ID3D11Device* device)
{
	m_instanceInputLayout = ShaderManager::CreateInputLayout(device, INSTANCE_INPUT_LAYOUT, "InstancingBasicVS.cso");
}
