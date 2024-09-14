#pragma once
#include"PANGU/Layer.h"
namespace PANGU {
	class PANGU_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		using it = std::vector<Layer*>::iterator;
		it begin() { return layers.begin(); }
		it end() { return layers.end(); }

	private:
		std::vector<Layer*> layers;
		unsigned int layerInsert;	//�������������ڱ��������Vector�е�Ԫ��
	};
}

