#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();
/*
* 主函数
*/
int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_INFO("Init 文件: {0} :: {1}行", __FILE__, __LINE__);
	//HZ_INFO("Hello");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS
