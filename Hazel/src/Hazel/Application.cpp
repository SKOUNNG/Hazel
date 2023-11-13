#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

namespace Hazel
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}
	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		HZ_TRACE(e);
		if (e.IsInCategory(EventCategoryApplication))
		{
			HZ_TRACE(e);

		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HZ_TRACE(e);

		}
		while (true)
		{

		}
	}
}