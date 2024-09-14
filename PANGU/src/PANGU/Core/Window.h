#pragma once
#include"Core.h"
#include"PANGU/Events/Event.h"

namespace PANGU {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;

		WindowProps(const std::string& title = "PANGU Engine", uint32_t Width = 1600, uint32_t Height = 900):Title(title),Width(Width),Height(Height) {}
	};


	class PANGU_API Window
	{	
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() = default;
		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth()const = 0;
		virtual uint32_t GetHeight()const = 0;
		
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

	private:
		Window* instace;
	};
}

