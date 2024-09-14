#pragma once

#include"Event.h"
#include"PANGU/Core/KeyCode.h"

namespace PANGU {
	class KeyEvent :public Event {
	public:
		KeyCode GetKeyCode()const { return keyCode; }

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)

	protected:
		KeyEvent(const KeyCode keycode):keyCode(keycode){}
		KeyCode keyCode;
	};

	class KeyPressedEvent :public KeyEvent {
	public:
		KeyPressedEvent(const KeyCode keycode, bool isRepeat = false):KeyEvent(keycode),isRepeat(isRepeat){}
		bool IsRepeat()const { return isRepeat; }

		std::string ToString()const override{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode << "(repeat = " << isRepeat << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyPressed)
	private:
		bool isRepeat;	//判断是否一直摁着
	};

	class KeyReleasedEvent :public KeyEvent {
	public:
		KeyReleasedEvent(const KeyCode keycode):KeyEvent(keycode){}

		std::string ToString()const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(EventType::KeyReleased)
	};

	class KeyTypeEvent :public KeyEvent {
	public:
		KeyTypeEvent(const KeyCode keycode):KeyEvent(keycode){}

		std::string ToString()const override{
			std::stringstream ss;
			ss << "KeyTypeEvent: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyTyped)
	};
}