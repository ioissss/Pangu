#pragma once
#include"pgpch.h"
#include"PANGU/Core/Core.h"
#include"PANGU/Events/Event.h"
#include"PANGU/Core/TimeStep.h"

namespace PANGU {
	class PANGU_API Layer
	{
	public:
		Layer(const std::string& Name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetatch() {}
		virtual void OnUpdate(TimeStep timeStep){}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRenderer(){}

		inline const std::string& GetName() { return debugName; }

	private:
		std::string debugName;
	};
}

