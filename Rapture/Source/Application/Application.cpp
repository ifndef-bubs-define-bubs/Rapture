#include "Application.h"

namespace Rapture
{
	
	void Application::run()
	{
		//processInput();
		//update();
		//render();

		Rapture::Mat<3, 3> mat = mat.random();
		std::cout << mat << "\n";

	}

	bool Application::running() const
	{
		return m_running;
	}

	void Application::render()
	{
		// stuff
		onRender();

	}

	void Application::update()
	{
		// stuff
		onUpdate();

	}

	void Application::shutDown()
	{

	}

	void Application::processInput()
	{

	}

}

