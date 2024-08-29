#include"PANGU.h"

class Sandbox :public PANGU::Application {
public:
	Sandbox(){}
	~Sandbox(){}
};

PANGU::Application* PANGU::CreateApplication() {
	return new Sandbox();
}