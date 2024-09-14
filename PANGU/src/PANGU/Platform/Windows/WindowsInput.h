#pragma once
#include"PANGU/Input.h"
#include"PANGU/Application.h"
#include"WindowsWindow.h"
namespace PANGU {


	class PANGU_API WindowsInput:public Input
	{
	protected:
		// 通过 Input 继承
		bool IsKeyPressedImpl(int keycode) override;

		bool IsMouseButtonPressedImpl(int button) override;

		float GetMouseXImpl() override;

		float GetMouseYImpl() override;


		// 通过 Input 继承
		std::pair<float, float> GetMousePositionImpl() override;

	};
}

