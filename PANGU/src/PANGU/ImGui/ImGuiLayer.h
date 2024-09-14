#pragma once
#include"pgpch.h"
#include"PANGU/Layer.h"
#include"PANGU/Core/Core.h"

namespace PANGU {
	class PANGU_API ImGuiLayer :public Layer {
	public:
		ImGuiLayer(const std::string& name = "ImGuiLayer");
		~ImGuiLayer();

		// ÖØÐ´½Ó¿Ú
		void OnAttach()override;
		void OnDetatch()override;
		void OnImGuiRenderer()override;
		void Begin();
		void End();
	private:
		float m_Time = 0;
	};
}