#include "bepch.h"
#include "WindowsWindow.h"

#include "BirdEngine/Events/ApplicationEvent.h"
#include "BirdEngine/Events/MouseEvent.h"
#include "BirdEngine/Events/KeyEvent.h"

namespace BE {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		BE_CORE_ERROR("GLFW_ERROR ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;

		BE_CORE_INFO("Creating window {0] ({1}, {2})", props.Title, props.Height, props.Width);

		//If you haven't initialized the window yet
		if (!s_GLFWInitialized) {
			//TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			BE_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(TRUE);

		//Set GLFW Callback
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallBack(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallBack(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
					case GLFW_PRESS: {
						KeyPressedEvent event(key, 0);
						data.EventCallBack(event);
						break;
					}
					case GLFW_REPEAT: {
						KeyPressedEvent event(key, 1);
						data.EventCallBack(event);
						break;
					}
					case GLFW_RELEASE: {
						KeyReleasedEvent event(key);
						data.EventCallBack(event);
						break;
					}
				};

			});


		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action) {
					case GLFW_PRESS: {
						MouseButtonPressedEvent event(button);
						data.EventCallBack(event);

						break;
					}

					case GLFW_RELEASE:{
						MouseButtonReleasedEvent event(button);
						data.EventCallBack(event);

						break;
					}				
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallBack(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallBack(event);
			});

	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	} 

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}


	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}



}