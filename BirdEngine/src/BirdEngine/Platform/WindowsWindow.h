#pragma once

#include "BirdEngine/Window.h"
#include "GLFW/glfw3.h"

#include "BirdEngine/Log.h"


namespace BE {
	///
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		//TODO:
		virtual ~WindowsWindow();
		
		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallBack = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallBack;
		};

		WindowData m_Data;
	};
}