#include "BirdEngine.h"

class SandboxApp : public BE::Application {
public:
	SandboxApp(){};
	~SandboxApp(){};
};


BE::Application* BE::CreateApplication() {
	return new SandboxApp();
}

