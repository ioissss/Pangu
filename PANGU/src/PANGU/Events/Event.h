#pragma once
#include"pgpch.h"
#include"PANGU/Core/Core.h"

namespace PANGU {

	// 当前事件是阻塞的，当一个事件发生时会阻塞整个进程，直到事件被处理完成
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return type; }\
		virtual EventType GetEventType()const override{return type; }\
		virtual const char* GetName()const override{return #type; }

#define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags()const override{return category;}

	class Event {
	public:
		virtual ~Event() = default;
		bool Handled = false;
		virtual EventType GetEventType() const = 0;	//获取事件类型
		virtual int GetCategoryFlags() const = 0;	//获取事件类别标识 - EventCategory
		virtual const char* GetName()const = 0;
		virtual std::string ToString()const { return GetName(); }	//输出日志时使用


		bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatch {
	public:
		EventDispatch(Event& event):m_event(event){}
		template<typename T, typename F>
		bool Dispatch(const F& func) {
			if (m_event.GetEventType() == T::GetStaticType()) {
				m_event.Handled |= func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};
}