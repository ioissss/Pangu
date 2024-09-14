#pragma once

#include"PANGU/Core/Core.h"

namespace PANGU {

	// �ӿ��࣬��ȡĳЩ��/��������״̬,��װ��GLFW�ṩ��һЩ�ӿڣ��Ӷ�����
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
		static Input* instance;	//ȫ�ֽ���Ψһ��Inputʵ����ֱ������Ϊ��̬
	};
}