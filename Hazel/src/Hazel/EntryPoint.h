#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();
/*
* ������
*/
int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_INFO("Init �ļ�: {0} :: {1}��", __FILE__, __LINE__);
	//HZ_INFO("Hello");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS
