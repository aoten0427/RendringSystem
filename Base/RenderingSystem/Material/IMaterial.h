#pragma once

class IMaterial
{
public:
	virtual ~IMaterial() = default;
	virtual void Bind(ID3D11DeviceContext* context) = 0;
	virtual void Clean(ID3D11DeviceContext* context) = 0;
};