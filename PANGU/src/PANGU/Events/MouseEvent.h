#pragma once

#include"Event.h"
#include"PANGU/Core/MouseCode.h"

namespace PANGU {
	class MouseMovedEvent :public Event {
	public:
		MouseMovedEvent(float mouseX, float mouseY):mouseX(mouseX),mouseY(mouseY){}
		float GetX()const { return mouseX; }
		float GetY()const { return mouseY; }
		std::string ToString()const override {
			std::stringstream ss;
			ss << "MouseMoveEvent: " << mouseX << " , " << mouseY;
			return ss.str();
		}
		EVENT_CLASS_TYPE(EventType::MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mouseX, mouseY;
	};

	class MouseScrolledEvent :public Event {
	public:
		MouseScrolledEvent(const float xOffset,const float yOffset):xOffset(xOffset),yOffset(yOffset){}
		float GetXOffset()const { return xOffset; }
		float GetYOffset()const { return yOffset; }
		std::string ToString()const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << xOffset << ", " << yOffset;
			return ss.str();
		}
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(EventType::MouseScrolled)
	private:
		float xOffset, yOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(const MouseCode button)
			: m_Button(button) {}

		MouseCode m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
	};

}