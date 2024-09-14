#include "pgpch.h"
#include "LayerStack.h"

namespace PANGU {
	LayerStack::LayerStack(){
		layerInsert = 0;	//插入指针指向初始位置
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		layers.emplace(layers.begin()+layerInsert, layer);	//在指定位置直接插入元素
		layerInsert++;
	}

	void LayerStack::PushOverlay(Layer* layer) {
		layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layers.erase(it);
			layerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer) {
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end())
			layers.erase(it);
	}
}