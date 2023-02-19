#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace BE {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		BE_CORE_TRACE(e);

		while (1) {
		
		}
	}
}