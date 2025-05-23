/*
	@file	CommonResources.h
	@brief	シーンへ渡す、ゲーム内で使用する共通リソース
*/
#pragma once

// 前方宣言
namespace DX
{
	class StepTimer;
	class DeviceResources;
}

class DebugString;
class InputManager;



// 共通リソース
class CommonResources
{
private:
	// 受け渡しするリソース一覧
	DX::StepTimer* m_stepTimer;

	DX::DeviceResources* m_deviceResources;

	DirectX::CommonStates* m_commonStates;

	DebugString* m_debugString;

	InputManager* m_inputManager;


public:
	CommonResources();
	~CommonResources() = default;

	void Initialize(
		DX::StepTimer* timer,
		DX::DeviceResources* dr,
		DirectX::CommonStates* commonStates,
		DebugString* debugString,
		InputManager* inputManager
	);

	// getter
	DX::StepTimer* GetStepTimer() const
	{
		return m_stepTimer;
	}

	DX::DeviceResources* GetDeviceResources() const
	{
		return m_deviceResources;
	}

	DirectX::CommonStates* GetCommonStates() const
	{
		return m_commonStates;
	}

	DebugString* GetDebugString() const
	{
		return m_debugString;
	}

	InputManager* GetInputManager() const
	{
		return m_inputManager;
	}
};
