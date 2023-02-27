#include "bepch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"


namespace BE {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		//TODO:
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& e) {
		BE_CORE_INFO("{0}", e);
	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}