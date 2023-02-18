#pragma once

#ifdef BE_PLATFORM_WINDOWS

extern BE::Application* BE::CreateApplication();

int main(int argc, char** argv) {
	BE::Log::Init();

	BE_CORE_WARN("Initialized Log!");

	auto app = BE::CreateApplication();
	app->Run();
	delete app;
}
#else
#error BirdEngine now only support windows!
#endif