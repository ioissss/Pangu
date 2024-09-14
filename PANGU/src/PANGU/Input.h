#pragma once

#include"PANGU/Core/Core.h"

namespace PANGU {

	// 接口类，获取某些键/鼠标的输入状态,封装了GLFW提供的一些接口，从而解耦
	class PANGU_API Input {
	public:
		inline static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return instance->GetMousePositionImpl(); }
		inline static bool GetMouseX() { return instance->GetMouseXImpl(); }
		inline static bool GetMouseY() { return instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float,float> GetMousePositionImpl() = 0;
	private:
		static Input* instance;	//全局仅有唯一的Input实例，直接设置为静态
	};
}